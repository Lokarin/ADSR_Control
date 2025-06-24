#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
<<<<<<< Updated upstream
=======
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
    freqSlider->setSliderPosition(4);

    freqLabel = new QLabel("BPM: 180", this);
    QFontMetrics fm(freqLabel->font());
    freqLabel->setMinimumWidth(fm.horizontalAdvance("BPM: 180"));

    // Criar um botao de envio de dados
    botaoSend = new QPushButton("⚙", this);
    botaoSend->setFixedWidth(fm.horizontalAdvance("BPM: 180"));
    botaoSend->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    
    // Controles do Trigger
    triggerModeSwitch = new QCheckBox("Automático", this);
    triggerModeSwitch->setCheckState(Qt::Checked);

    triggerButton = new QPushButton("Trigger", this);

    // Botao de salvar em bmp 
    botaoSalvaBmp = new QPushButton("Salvar Gráfico", this);

}

void ResiFlow::setupLayout() {
>>>>>>> Stashed changes
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);
    central->setMinimumHeight(700);

    // Layout Principal Horizontal
    QHBoxLayout * layoutMain = new QHBoxLayout(central);

    // Wid da esquerda
    QWidget * esquerda = new QWidget(central);
    esquerda->setMinimumWidth(800);
    layoutMain->addWidget(esquerda);

    // Wid da direita
    QWidget * direita = new QWidget(central);
    direita->setMinimumWidth(600);
<<<<<<< Updated upstream
=======
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
    layoutDireita->addWidget(botaoSalvaBmp);
    direita->setLayout(layoutDireita);

    // Adiciona os dois lados ao layout principal
    layoutMain->addWidget(esquerda);
>>>>>>> Stashed changes
    layoutMain->addWidget(direita);

    // Layout Vertical no Wid da esquerda
    QVBoxLayout * layoutMainEsquerda = new QVBoxLayout();
    layoutMainEsquerda->setAlignment(Qt::AlignTop);
    esquerda->setLayout(layoutMainEsquerda);

    // Layout Vertical no Wid da direita
    QVBoxLayout * layoutMainDireita = new QVBoxLayout();
    layoutMainDireita->setAlignment(Qt::AlignTop);
    direita->setLayout(layoutMainDireita);

    // Criar um botao na esquerda
    QPushButton * botao = new QPushButton("Enviar Curva Atual");

    // Criar um botao na direita
    QPushButton * botao1 = new QPushButton("Botao na Direita");

    // Criar um botao na direita 2
    QPushButton * botao2 = new QPushButton("Botao na Direita Dois");

    // Cria widget do grafico
    chart = new ChartWidget;
    QHBoxLayout * chartLayout = new QHBoxLayout();
    chartLayout->addWidget(chart);

    // Criar tray de quatro knobs
    QWidget * trayContainer = new QWidget(esquerda);
    trayContainer->setMaximumHeight(300);
    QHBoxLayout * knobTray = new QHBoxLayout(trayContainer);

    QStringList knobNames = {"Attack", "Decay/Release", "Sustain", "Hold"};
    for (const QString &name : knobNames) {
        // Layout vertical para cada set de knobs+txt
        QWidget * knobTextContainer = new QWidget();
        QVBoxLayout * textKnobLayout = new QVBoxLayout(knobTextContainer);

        // Cria um knob
        CustomKnob * knob = new CustomKnob();
        //knob->setFixedSize(200,200);
        //knobTray->addWidget(knob);
        knob->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        knob->setValue(100);

        // Cria o texto do knob
        QString textLabel = name+": "+QString::number(100);
        QLabel * label = new QLabel(textLabel);
        label->setAlignment(Qt::AlignCenter);
        knobs[name] = knob;

        connect(knob, &QDial::valueChanged, this, [=](int value){
            label->setText(QString("%1: %2").arg(name).arg(value));
            getKnobValues();
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

    // Adicionando as coisas aos layouts
    layoutMainEsquerda->addWidget(botao);
    chartLayout->addLayout(freqPicker);
    layoutMainEsquerda->addLayout(chartLayout);
    layoutMainEsquerda->addWidget(trayContainer);

    //layoutMainDireita->addLayout(freqPicker);
    layoutMainDireita->addWidget(botao1);
    layoutMainDireita->addWidget(botao2);
    
    // Connects
    connect(botao, &QPushButton::clicked, this, [=]() {
          chart->updatePontosReais(); 
    });

    connect(freqSlider, &QSlider::valueChanged, this, [=]() {
           int freqIndex = freqSlider->value();
           freqLabel->setText(QString("BPM: %1").arg(freqLabels[freqIndex]));
           getKnobValues();
    });
<<<<<<< Updated upstream
=======

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

    connect(botaoSalvaBmp, &QPushButton::clicked, this, [=]() {
            qDebug() << "Escolha o formato";
            QString filePath = QFileDialog::getSaveFileName(this, "Salvar Gráfico", "", 
                "Binary Files (*.bin);;Bitmap Files (*.bmp);;C Array Files (*.h)");
            
            if (!filePath.isEmpty()) {
                bool success = false;
                
                if (filePath.endsWith(".bin")) {
                    success = chart->saveChartAsBinary(filePath);
                } else if (filePath.endsWith(".h")) {
                    qDebug() << "foi em array";
                    success = chart->saveChartAsCArray(filePath);
                } else {
                    success = chart->saveChartAsImage(filePath);
                }

                if (success) {
                    status->showMessage("Gráfico salvo com sucesso.");
                } else {
                    status->showMessage("Erro ao salvar gráfico.");
                }
            }
    });
>>>>>>> Stashed changes
}

void ResiFlow::getKnobValues(){
            int A = (knobs["Attack"]->value()*100)+1;
            int DR = (knobs["Decay/Release"]->value()*100)+1;
            int S = (knobs["Sustain"]->value()*100)+1;
            int H = (knobs["Hold"]->value()*100)+1;

            int freqIndex = freqSlider->value();
            int freqVal = freqLabels[freqIndex].toInt();

<<<<<<< Updated upstream
            chart->updateChartSim(A, H, DR, S, freqVal, 5);
=======
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
            (data.hold * 375) + 277,
            (data.sustain * 375) + 1,
            (data.decayRelease * 375) +1,
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
>>>>>>> Stashed changes
}

ResiFlow::~ResiFlow() = default;
