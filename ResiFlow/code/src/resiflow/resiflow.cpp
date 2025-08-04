#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWidgets();
    setupLayout();
    setupStatusBar();
    setupConnects();
    setupNoteMap();
}

void ResiFlow::setupWidgets() {
    // Foco
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    // Grupo de conexão
    conexaoGroup = new SerialWidget(this);

    // PresetWidget
    presetWidget = new PresetWidget(this);

    // Cria widget do grafico
    chart = new ChartWidget;
    chartGroup = new QGroupBox("", this);
    chartGroup->setMinimumHeight(450);
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

    bpmLayout = new QHBoxLayout();
    QLabel* bpmTextLabel = new QLabel("BPM:", this);
    bpmLineEdit = new QLineEdit(freqLabels[2], this);
    bpmLineEdit->setValidator(new QIntValidator(30, 300, bpmLineEdit));  // faixa opcional
    QFontMetrics fm(bpmLineEdit->font());
    int width = fm.horizontalAdvance("888") + 20;
    bpmLineEdit->setFixedWidth(width);
    bpmLayout->addWidget(bpmTextLabel);
    bpmLayout->addWidget(bpmLineEdit);
    bpmLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    //freqLabel = new QLabel("BPM: 120", this);
    //QFontMetrics fm(freqLabel->font());
    //freqLabel->setMinimumWidth(fm.horizontalAdvance("BPM: 180"));

    // Controles do Trigger
    controlsWidget = new ControlsWidget;
    
    // Controles de Audio
    freqWidget = new FrequencyWidget;
}

void ResiFlow::setupLayout() {
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);
    central->setMinimumHeight(800);

    // Layout Principal Horizontal
    QHBoxLayout * layoutMain = new QHBoxLayout(central);

    ///////////// Wid da esquerda
    QWidget * esquerda = new QWidget(central);
    esquerda->setMinimumWidth(800);
    QVBoxLayout * layoutEsquerda = new QVBoxLayout(esquerda);
    layoutEsquerda->setAlignment(Qt::AlignTop);

    // Freq picker (label + slider)
    QVBoxLayout * freqPicker = new QVBoxLayout();
    freqPicker->addLayout(bpmLayout, 0);
    freqPicker->addWidget(freqSlider, 0, Qt::AlignHCenter);
    // Adiciona freqPicker ao layout do gráfico
    static_cast<QHBoxLayout*>(chartGroup->layout())->addLayout(freqPicker);

    // Layout knobs + freq
    QHBoxLayout * layoutKnobsFreq = new QHBoxLayout();
    layoutKnobsFreq->addWidget(knobsWidget);

    // Adiciona widgets à esquerda
    layoutEsquerda->addWidget(controlsWidget);
    layoutEsquerda->addWidget(chartGroup);
    //layoutEsquerda->addWidget(knobsWidget);
    layoutEsquerda->addLayout(layoutKnobsFreq);
    esquerda->setLayout(layoutEsquerda);

    ///////////// Wid da direita
    QWidget * direita = new QWidget(central);
    direita->setMinimumWidth(600);
    QVBoxLayout * layoutDireita = new QVBoxLayout(direita);
    layoutDireita->setAlignment(Qt::AlignTop);

    // Adiciona widgets à direita
    layoutDireita->addWidget(conexaoGroup);
    layoutDireita->addWidget(presetWidget);
    layoutDireita->addWidget(freqWidget);
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
    connect(controlsWidget, &ControlsWidget::sendButtonClicked, this, [=]() {
        chart->updatePontosReais(); 
        sendSerialData(1, 0);
    });

    // Slider de BPM atualizar label e chart simulado
    connect(freqSlider, &QSlider::valueChanged, this, [=](int value){
           int freqIndex = freqSlider->value();
           //freqLabel->setText(QString("BPM: %1").arg(freqLabels[freqIndex]));
           bpmLineEdit->setText(freqLabels[value]);
           updateChart();
    });

    connect(bpmLineEdit, &QLineEdit::textChanged, this, [=](const QString& text){
        updateChart();
    });

    // Connect para statusbar mostrar mensagens
    connect(conexaoGroup, &SerialWidget::statusMessage, this, [this](const QString &msg){
        status->showMessage(msg);
    });

    // Sempre que os knobs se alteram, atualiza chart simulado
    connect(knobsWidget, &KnobsWidget::knobsChanged, this, &ResiFlow::updateChart);

    // Ao clicar o botao de trigger, colocar trigger em alto
    // e ao soltar, colocar em baixo
    // Ao pressionar o botão de trigger (manual)
    connect(controlsWidget, &ControlsWidget::trigButtonPressed, this, [=]() {
        if (!controlsWidget->isAutoModeEnabled()) { 
            sendSerialData(0, 3);
        }
    });
    
    // Ao soltar o botão de trigger (manual)
    connect(controlsWidget, &ControlsWidget::trigButtonReleased, this, [=]() {
        if (!controlsWidget->isAutoModeEnabled()) {
            sendSerialData(0, 1);
        }
    });
    
    // Ao alternar o modo automático
    connect(controlsWidget, &ControlsWidget::autoModeToggled, this, [=](bool checked) {
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
    
    int bpmVal = bpmLineEdit->text().isEmpty() ? 120 : bpmLineEdit->text().toInt();
    
    int freq = static_cast<int>(freqWidget->getFrequency());
    int wfForm = freqWidget->getWaveformIndex();

    return {
        knobValues[0],  
        knobValues[1],  
        knobValues[2],  
        knobValues[3],  
        bpmVal,
        freq,
        wfForm
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
            data.freq,
            data.wfForm
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
            data.freq,
            data.wfForm
    );
}

void ResiFlow::onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq, int wfForm) {
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

    freqWidget->setFrequency(freq);
    freqWidget->setWaveformIndex(wfForm);

    // Atualiza gráfico simulado com o preset selecionado
    updateChart();
}

void ResiFlow::setupNoteMap() {
    noteMap.clear();

    noteMap[Qt::Key_1] = {261, 2};     // C
    noteMap[Qt::Key_2] = {277, 2};     // C#
    noteMap[Qt::Key_3] = {293, 2};     // D
    noteMap[Qt::Key_4] = {311, 2};     // D#
    noteMap[Qt::Key_5] = {329, 2};     // E
    noteMap[Qt::Key_6] = {349, 2};     // F
    noteMap[Qt::Key_7] = {369, 2};     // F#
    noteMap[Qt::Key_8] = {391, 2};     // G
    noteMap[Qt::Key_9] = {415, 2};     // G#
    noteMap[Qt::Key_0] = {440, 2};     // A
    noteMap[Qt::Key_Minus] = {466, 2}; // A#
    noteMap[Qt::Key_Equal] = {493, 2}; // B
}

void ResiFlow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    int key = event->key();

    switch (key) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            sendSerialData(1, 0);
            chart->updatePontosReais();
        return;

        case Qt::Key_Q:
            if (!controlsWidget->isAutoModeEnabled()) { 
                sendSerialData(0, 3);
            }
        return;

        case Qt::Key_F1:
            formaDeOnda = (formaDeOnda + 1) % 3;
            qDebug() << "Forma de onda atual:" << formaDeOnda;
        return;

        case Qt::Key_Z:
            if (!controlsWidget->isAutoModeEnabled()) { 
                sendSerialData(0, 3);
            }
        return;
        
        case Qt::Key_X:
            if (!controlsWidget->isAutoModeEnabled()) { 
                sendSerialData(0, 1);  // Baixa o trigger
            }
        return;

        case Qt::Key_C:
            conexaoGroup->sendAHDSRData(1, 0, 0, 0, 0, 90, 120, 20000, 3);
            sendSerialData(0, 3);
    }

    if (noteMap.contains(key) && !pressedKeys.contains(key)) {
        pressedKeys.insert(key);

        const auto& [freq, defaultWaveform] = noteMap[key];

        AHDSRValues data = getAHDSRValues();
        data.freq = freq;
        data.wfForm = formaDeOnda;

        conexaoGroup->sendAHDSRData(1, 0,
            data.attack, data.hold, data.sustain,
            data.decayRelease, data.bpm, data.freq, data.wfForm);

        sendSerialData(0, 3);
        chart->updatePontosReais();
    }
}

void ResiFlow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    int key = event->key();

    switch (key) {
        case Qt::Key_C:
        case Qt::Key_Q:
            if (!controlsWidget->isAutoModeEnabled()) { 
                sendSerialData(0, 1);  // Baixa o trigger
            }
        return;
    }

    if (noteMap.contains(key) && pressedKeys.contains(key)) {
        pressedKeys.remove(key);
        sendSerialData(0, 1);  // Também baixa o trigger
    }
}

ResiFlow::~ResiFlow() = default;
