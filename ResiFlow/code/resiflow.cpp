#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);
    central->setMinimumHeight(700);

    // Layout Principal Horizontal
    QHBoxLayout * layoutMain = new QHBoxLayout(central);

    // Wid da esquerda
    QWidget * esquerda = new QWidget(central);
    esquerda->setMinimumWidth(500);
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
    QPushButton * botao = new QPushButton("Botao na Esquerda");

    // Criar um botao na direita
    QPushButton * botao1 = new QPushButton("Botao na Direita");

    // Criar um botao na direita 2
    QPushButton * botao2 = new QPushButton("Botao na Direita Dois");

    // Cria widget do grafico
    chart = new ChartWidget;

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

        // Cria o texto do knob
        QString textLabel = name+": "+QString::number(0);
        QLabel * label = new QLabel(textLabel);
        label->setAlignment(Qt::AlignCenter);
        knobs[name] = knob;

        connect(knob, &QDial::valueChanged, this, [=](int value){
            label->setText(QString("%1: %2").arg(name).arg(value));
        });
        
        textKnobLayout->addWidget(knob);
        textKnobLayout->addWidget(label);

        knobTray->addWidget(knobTextContainer);
    }

    // Slider para frequencia
    QHBoxLayout * freqPicker = new QHBoxLayout();
    this->freqLabels = {"60", "100", "120", "150", "180"};
    this->freqSlider = new QSlider(Qt::Horizontal);
    this->freqSlider->setMinimum(0);
    this->freqSlider->setMaximum(freqLabels.size() - 1);
    this->freqSlider->setTickInterval(1);
    this->freqSlider->setTickPosition(QSlider::TicksBelow);
    freqLabel = new QLabel(QString("BPM: 60"));

    freqPicker->addWidget(freqLabel);
    freqPicker->addWidget(freqSlider);

    // Adicionando as coisas aos layouts
    layoutMainEsquerda->addWidget(botao);
    layoutMainEsquerda->addWidget(chart);
    layoutMainEsquerda->addWidget(trayContainer);

    layoutMainDireita->addWidget(botao1);
    layoutMainDireita->addWidget(botao2);
    layoutMainDireita->addLayout(freqPicker);

    connect(botao, &QPushButton::clicked, this, [=]() {
           int A = (knobs["Attack"]->value()*100)+1;
           int DR = (knobs["Decay/Release"]->value()*100)+1;
           int S = (knobs["Sustain"]->value()*100)+1;
           int H = (knobs["Hold"]->value()*100)+1;

           int freqIndex = this->freqSlider->value();
           int freqVal = this->freqLabels[freqIndex].toInt();

           this->chart->updateChart(A, H, DR, S, freqVal, 5); 
    });

    connect(freqSlider, &QSlider::valueChanged, this, [=]() {
           int freqIndex = this->freqSlider->value();
           this->freqLabel->setText(QString("BPM: %1").arg(this->freqLabels[freqIndex]));
    });
}

ResiFlow::~ResiFlow() = default;
