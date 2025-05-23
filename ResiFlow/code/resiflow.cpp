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
    //botao->setGeometry(50,50,200,40);
    layoutMainEsquerda->addWidget(botao);

    // Criar um botao na direita
    QPushButton * botao1 = new QPushButton("Botao na Direita");
    layoutMainDireita->addWidget(botao1);

    // Criar um botao na direita 2
    QPushButton * botao2 = new QPushButton("Botao na Direita Dois");
    layoutMainDireita->addWidget(botao2);

    // Cria widget do grafico
    ChartWidget * chart = new ChartWidget;
    layoutMainEsquerda->addWidget(chart);

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

        connect(knob, &QDial::valueChanged, this, [=](int value){
            label->setText(QString("%1: %2").arg(name).arg(value));
        });
        
        textKnobLayout->addWidget(knob);
        textKnobLayout->addWidget(label);

        knobTray->addWidget(knobTextContainer);
    }
    layoutMainEsquerda->addWidget(trayContainer);
}

ResiFlow::~ResiFlow() = default;
