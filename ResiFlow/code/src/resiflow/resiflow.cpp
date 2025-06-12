#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);
    central->setMinimumHeight(700);

    status = new QStatusBar(this);
    this->setStatusBar(status);
    status->showMessage("Aguardando conexão...");

    // Layout Principal Horizontal
    QHBoxLayout * layoutMain = new QHBoxLayout(central);

    // Wid da esquerda
    QWidget * esquerda = new QWidget(central);
    esquerda->setMinimumWidth(800);
    layoutMain->addWidget(esquerda);

    // Wid da direita
    QWidget * direita = new QWidget(central);
    direita->setMinimumWidth(600);
    layoutMain->addWidget(direita);

    // Layout Vertical no Wid da esquerda
    QVBoxLayout * layoutMainEsquerda = new QVBoxLayout();
    layoutMainEsquerda->setAlignment(Qt::AlignTop);
    esquerda->setLayout(layoutMainEsquerda);

    // Layout Vertical no Wid da direita
    QVBoxLayout * layoutMainDireita = new QVBoxLayout();
    layoutMainDireita->setAlignment(Qt::AlignTop);
    direita->setLayout(layoutMainDireita);

    // Criar um botao de envio de dados
    QPushButton * botaoSend = new QPushButton("Enviar Curva Atual");

    // Grupo de conexão
    conexaoGroup = new SerialWidget;

    // PresetWidget
    PresetWidget * presetWidget = new PresetWidget;

    // Cria widget do grafico
    QGroupBox * chartGroup = new QGroupBox();
    QHBoxLayout * chartLayout = new QHBoxLayout();
    chartGroup->setLayout(chartLayout);
    chart = new ChartWidget;
    chartLayout->addWidget(chart);

    // Criar tray de quatro knobs
    QGroupBox * trayGroup = new QGroupBox(esquerda);
    trayGroup->setMaximumHeight(300);
    QHBoxLayout * knobTray = new QHBoxLayout(trayGroup);

    QStringList knobNames = {"Attack", "Hold", "Decay/Release", "Sustain"};
    for (const QString &name : knobNames) {
        // Layout vertical para cada set de knobs+txt
        QWidget * knobTextContainer = new QWidget();
        QVBoxLayout * textKnobLayout = new QVBoxLayout(knobTextContainer);

        // Cria um knob
        CustomKnob * knob = new CustomKnob();
        //knob->setFixedSize(200,200);
        //knobTray->addWidget(knob);
        knob->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        knob->setValue(0);

        // Cria o texto do knob
        QString textLabel = name+": "+QString::number(knob->value());
        QLabel * label = new QLabel(textLabel);
        label->setAlignment(Qt::AlignCenter);
        knobs[name] = knob;

        connect(knob, &QDial::valueChanged, this, [=](int value){
            label->setText(QString("%1: %2").arg(name).arg(value));
            updateChart();
        });
        
        textKnobLayout->addWidget(knob);
        textKnobLayout->addWidget(label);

        knobTray->addWidget(knobTextContainer);
    }

    // Slider para frequencia
    QVBoxLayout * freqPicker = new QVBoxLayout();
    freqLabels = {"60", "100", "120", "150", "180"};
    freqSlider = new QSlider(Qt::Vertical);
    freqSlider->setMinimum(0);
    freqSlider->setMaximum(freqLabels.size() - 1);
    freqSlider->setTickInterval(1);
    freqSlider->setTickPosition(QSlider::TicksBothSides);
    freqSlider->setSliderPosition(4);
    freqLabel = new QLabel(QString("BPM: 180"));
    QFontMetrics fm(freqLabel->font());
    int freqLabelW = fm.horizontalAdvance("BPM: 180");  // largura do maior valor
    freqLabel->setMinimumWidth(freqLabelW);

    freqPicker->addWidget(freqLabel, 0, Qt::AlignHCenter);
    freqPicker->addWidget(freqSlider, 0, Qt::AlignHCenter);

    QHBoxLayout * triggerModeLayout = new QHBoxLayout;
    triggerModeSwitch = new QCheckBox;
    triggerModeSwitch->setCheckState(Qt::Checked);
    triggerModeSwitch->setText("Automático");
    triggerModeLayout->addWidget(triggerModeSwitch);

    triggerButton = new QPushButton("Trigger");
    triggerModeLayout->addWidget(triggerButton);

    // Adicionando as coisas aos layouts
    layoutMainEsquerda->addWidget(botaoSend);
    chartLayout->addLayout(freqPicker);
    //layoutMainEsquerda->addLayout(chartLayout);
    layoutMainEsquerda->addWidget(chartGroup);
    layoutMainEsquerda->addWidget(trayGroup);

    layoutMainDireita->addWidget(conexaoGroup);
    layoutMainDireita->addWidget(presetWidget);
    layoutMainDireita->addLayout(triggerModeLayout);
    
    // Connects
    connect(botaoSend, &QPushButton::clicked, this, [=]() {
          chart->updatePontosReais(); 
          sendSerialData();
    });

    connect(freqSlider, &QSlider::valueChanged, this, [=]() {
           int freqIndex = freqSlider->value();
           freqLabel->setText(QString("BPM: %1").arg(freqLabels[freqIndex]));
           updateChart();
    });

    connect(conexaoGroup, &SerialWidget::statusMessage, this, [this](const QString &msg){
        status->showMessage(msg);
    });

    // Teste de shortcut
    QShortcut * shortcut = new QShortcut(QKeySequence("Ctrl+Return"), this);
    connect(shortcut, &QShortcut::activated, this, [=]() {
          chart->updatePontosReais(); 
          sendSerialData();
    });

    connect(triggerButton, &QPushButton::pressed, this, [=]() {
          sendSerialData();
    });
    
    connect(triggerButton, &QPushButton::released, this, [=]() {
          sendSerialData();
    });

    connect(triggerModeSwitch, &QCheckBox::toggled, this, [=]() {
          setAuto();
    });

    // Conects entre resiflow e presetWidget
    connect(this, &ResiFlow::parametersChanged, presetWidget, &PresetWidget::receiveParameters);
    connect(presetWidget, &PresetWidget::parametersRequest, this, &ResiFlow::onParametersRequest);
    connect(presetWidget, &PresetWidget::loadParametersToInterface, this, &ResiFlow::onLoadParameters);

}

QVector<int> ResiFlow::getAHDSRValues(){
            int A = knobs["Attack"]->value();
            int H = knobs["Hold"]->value();
            int S = knobs["Sustain"]->value();
            int DR = knobs["Decay/Release"]->value();

            int bpmIndex = freqSlider->value();
            int bpmVal = freqLabels[bpmIndex].toInt();

            int freq = 500;

            return {A, H, S, DR, bpmVal, freq};
}

void ResiFlow::updateChart(){
    QVector<int> data = getAHDSRValues();

    chart->updateChartSim(
            (data[0]*100)+1,
            (data[1]*100)+1, 
            (data[2]*100)+1, 
            (data[3]*100)+1, 
            data[4], 
            5);
}

void ResiFlow::sendSerialData(){
    QVector<int> data = getAHDSRValues();
    int triggerCmd = 00;

    if (triggerButton->isDown()) {
        triggerCmd = 10;
    } else {
        triggerCmd = 11;
    }

    conexaoGroup->sendAHDSRData(
            triggerCmd,
            data[0], 
            data[1],
            data[2],
            data[3],
            data[4],
            data[5]);
}

void ResiFlow::setAuto() {
    QVector<int> data = getAHDSRValues();
    int triggerCmd = 00;

    if (triggerModeSwitch->isChecked()) {
        triggerCmd = 00;
    } else {
        triggerCmd = 01;
    }

    conexaoGroup->sendAHDSRData(
            triggerCmd,
            data[0], 
            data[1],
            data[2],
            data[3],
            data[4],
            data[5]);

}

// Envia parâmetros para presetWidget
void ResiFlow::onParametersRequest() {
    QVector<int> tempData = getAHDSRValues();
    emit parametersChanged(tempData[0], tempData[1], tempData[2], tempData[3], tempData[4], tempData[5]);
}

void ResiFlow::onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq) {
    // Atualiza valores dos knobs com o valor do preset selecionado

    knobs["Attack"]->setValue(attack);
    knobs["Hold"]->setValue(hold);
    knobs["Sustain"]->setValue(sustain);
    knobs["Decay/Release"]->setValue(decayRelease);

    // Atualiza slider BPM com o valor do preset selecionado
    int freqIndex = 0;
    for (int i = 0; i < freqLabels.size(); ++i) {
        if (freqLabels[i].toInt() == bpmVal) {
            freqIndex = i;
            break;
        }
    }
    freqSlider->setValue(freqIndex);
    freqLabel->setText(QString("BPM: %1").arg(bpmVal));

    // Atualiza gráfico com o preset selecionado
    updateChart();
}

ResiFlow::~ResiFlow() = default;
