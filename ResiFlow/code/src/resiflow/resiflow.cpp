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

    // Criar um botao na esquerda
    QPushButton * botao = new QPushButton("Enviar Curva Atual");

    // Grupo de conexão
    SerialWidget * conexaoGroup = new SerialWidget;

    // teste //
    PresetWidget * teste = new PresetWidget;
    ///////////

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
    //layoutMainEsquerda->addLayout(chartLayout);
    layoutMainEsquerda->addWidget(chartGroup);
    layoutMainEsquerda->addWidget(trayGroup);

    layoutMainDireita->addWidget(conexaoGroup);
    layoutMainDireita->addWidget(teste);
    
    // Connects
    connect(botao, &QPushButton::clicked, this, [=]() {
          chart->updatePontosReais(); 
    });

    connect(freqSlider, &QSlider::valueChanged, this, [=]() {
           int freqIndex = freqSlider->value();
           freqLabel->setText(QString("BPM: %1").arg(freqLabels[freqIndex]));
           getKnobValues();
    });
}

void ResiFlow::getKnobValues(){
            int A = (knobs["Attack"]->value()*100)+1;
            int DR = (knobs["Decay/Release"]->value()*100)+1;
            int S = (knobs["Sustain"]->value()*100)+1;
            int H = (knobs["Hold"]->value()*100)+1;

            int freqIndex = freqSlider->value();
            int freqVal = freqLabels[freqIndex].toInt();

            chart->updateChartSim(A, H, DR, S, freqVal, 5);
}

ResiFlow::~ResiFlow() = default;
