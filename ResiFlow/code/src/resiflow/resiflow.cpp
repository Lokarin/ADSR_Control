#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWidgets();
    setupLayout();
    setupStatusBar();
    setupConnects();
}

void ResiFlow::setupWidgets() {
    // Grupo de conexão
    conexaoGroup = new SerialWidget(this);

    // PresetWidget
    presetWidget = new PresetWidget(this);

    // Cria widget do grafico
    chart = new ChartWidget;
    chartGroup = new QGroupBox("", this);
    chartGroup->setMinimumHeight(400);
    QHBoxLayout * chartLayout = new QHBoxLayout(chartGroup);
    chartLayout->addWidget(chart);

    // Criar tray de quatro knobs
    knobsWidget = new KnobsWidget(this);

    // Slider para frequencia
    freqLabels = {"60", "100", "120", "150", "180"};
    freqSlider = new QSlider(Qt::Vertical, this);
    freqSlider->setMinimum(0);
    freqSlider->setMaximum(freqLabels.size() - 1);
    freqSlider->setTickInterval(1);
    freqSlider->setTickPosition(QSlider::TicksBothSides);
    freqSlider->setSliderPosition(2);

    freqLabel = new QLabel("BPM: 120", this);
    QFontMetrics fm(freqLabel->font());
    freqLabel->setMinimumWidth(fm.horizontalAdvance("BPM: 180"));

    // Criar um botao de envio de dados
    botaoSend = new QPushButton("⚙", this);
    botaoSend->setFixedWidth(fm.horizontalAdvance("BPM: 180"));
    botaoSend->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    botaoSend->setMaximumHeight(300);
    
    // Controles do Trigger
    triggerModeSwitch = new QCheckBox("Automático", this);
    triggerModeSwitch->setCheckState(Qt::Checked);

    triggerButton = new QPushButton("Trigger", this);
}

void ResiFlow::setupLayout() {
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);
    central->setMinimumHeight(700);

    // Layout Principal Horizontal
    QHBoxLayout * layoutMain = new QHBoxLayout(central);

    ///////////// Wid da esquerda
    QWidget * esquerda = new QWidget(central);
    esquerda->setMinimumWidth(800);
    QVBoxLayout * layoutEsquerda = new QVBoxLayout(esquerda);
    layoutEsquerda->setAlignment(Qt::AlignTop);

    // Freq picker (label + slider)
    QVBoxLayout * freqPicker = new QVBoxLayout();
    freqPicker->addWidget(freqLabel, 0, Qt::AlignHCenter);
    freqPicker->addWidget(freqSlider, 0, Qt::AlignHCenter);
    // Adiciona freqPicker ao layout do gráfico
    static_cast<QHBoxLayout*>(chartGroup->layout())->addLayout(freqPicker);

    // Layout knobs + freq
    QHBoxLayout * layoutKnobsFreq = new QHBoxLayout();
    layoutKnobsFreq->addWidget(knobsWidget);
    layoutKnobsFreq->addWidget(botaoSend);

    // Adiciona widgets à esquerda
    //layoutEsquerda->addWidget(botaoSend);
    layoutEsquerda->addWidget(chartGroup);
    //layoutEsquerda->addWidget(knobsWidget);
    layoutEsquerda->addLayout(layoutKnobsFreq);
    esquerda->setLayout(layoutEsquerda);

    ///////////// Wid da direita
    QWidget * direita = new QWidget(central);
    direita->setMinimumWidth(600);
    QVBoxLayout * layoutDireita = new QVBoxLayout(direita);
    layoutDireita->setAlignment(Qt::AlignTop);

    // Layout trigger (check e botão)
    QHBoxLayout *triggerModeLayout = new QHBoxLayout();
    triggerModeLayout->addWidget(triggerModeSwitch);
    triggerModeLayout->addWidget(triggerButton);

    // Adiciona widgets à direita
    layoutDireita->addWidget(conexaoGroup);
    layoutDireita->addWidget(presetWidget);
    layoutDireita->addLayout(triggerModeLayout);
    direita->setLayout(layoutDireita);

    // Adiciona os dois lados ao layout principal
    layoutMain->addWidget(esquerda);
    layoutMain->addWidget(direita);
}

void ResiFlow::setupStatusBar() {
    status = new QStatusBar(this);
    setStatusBar(status);
    status->showMessage("Aguardando conexão...");
}

void ResiFlow::setupConnects() {
    // Botao send atualiza os pontos reais e envia os valores
    // de potenciometros, BPM e Freq
    connect(botaoSend, &QPushButton::clicked, this, [=]() {
          chart->updatePontosReais(); 
          sendSerialData(1, 0);
    });

    // Slider de BPM atualizar label e chart simulado
    connect(freqSlider, &QSlider::valueChanged, this, [=]() {
           int freqIndex = freqSlider->value();
           freqLabel->setText(QString("BPM: %1").arg(freqLabels[freqIndex]));
           updateChart();
    });

    // Connect para statusbar mostrar mensagens
    connect(conexaoGroup, &SerialWidget::statusMessage, this, [this](const QString &msg){
        status->showMessage(msg);
    });

    // Sempre que os knobs se alteram, atualiza chart simulado
    connect(knobsWidget, &KnobsWidget::knobsChanged, this, &ResiFlow::updateChart);

    // Teste de shortcut
    QShortcut * shortcut = new QShortcut(QKeySequence("Ctrl+Return"), this);
    connect(shortcut, &QShortcut::activated, this, [=]() {
          chart->updatePontosReais(); 
          sendSerialData(1, 0);
    });

    // Ao clicar o botao de trigger, colocar trigger em alto
    // e ao soltar, colocar em baixo
    connect(triggerButton, &QPushButton::pressed, this, [=]() {
            if (!triggerModeSwitch->isChecked()) {
                sendSerialData(0, 3);
            }
    });
    connect(triggerButton, &QPushButton::released, this, [=]() {
            if (!triggerModeSwitch->isChecked()) {
            sendSerialData(0, 1);
            }
    });

    // Ao mudar o checkbox, enviar o status do modo do trigger
    connect(triggerModeSwitch, &QCheckBox::toggled, this, [=](bool checked) {
    if (checked) {
        sendSerialData(0, 0);
    } else {
        sendSerialData(0, 1);
    }
});

    // Conects entre resiflow e presetWidget
    connect(this, &ResiFlow::parametersChanged, presetWidget, &PresetWidget::receiveParameters);
    connect(presetWidget, &PresetWidget::parametersRequest, this, &ResiFlow::onParametersRequest);
    connect(presetWidget, &PresetWidget::loadParametersToInterface, this, &ResiFlow::onLoadParameters);
}


AHDSRValues ResiFlow::getAHDSRValues(){
    QVector<int> knobValues = knobsWidget->getKnobValues();
    
    int bpmIndex = freqSlider->value();
    int bpmVal = freqLabels[bpmIndex].toInt();
    
    int freq = 500;

    return {
        knobValues[0],  
        knobValues[1],  
        knobValues[2],  
        knobValues[3],  
        bpmVal,
        freq
    };
}

void ResiFlow::updateChart(){
    AHDSRValues data = getAHDSRValues();

    chart->updateChartSim(
            (data.attack * 375) + 375,
            (data.hold * 277) + 277,
            (data.sustain * 392) + 1,
            (data.decayRelease * 375) + 375,
            data.bpm,
            5
    );
}

void ResiFlow::sendSerialData(int rxHandler, int triggerCmd){
    AHDSRValues data = getAHDSRValues();

    conexaoGroup->sendAHDSRData(
            rxHandler,
            triggerCmd,
            data.attack,
            data.hold,
            data.sustain,
            data.decayRelease,
            data.bpm,
            data.freq
    );
}

// Envia parâmetros para presetWidget
void ResiFlow::onParametersRequest() {
    AHDSRValues data = getAHDSRValues();

    emit parametersChanged(
            data.attack,
            data.hold,
            data.sustain,
            data.decayRelease,
            data.bpm,
            data.freq
    );
}

void ResiFlow::onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq) {
    // Atualiza valores dos knobs com o valor do preset selecionado
    knobsWidget->setKnobValues({attack, hold, sustain, decayRelease});

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

    // Atualiza gráfico simulado com o preset selecionado
    updateChart();
}

ResiFlow::~ResiFlow() = default;
