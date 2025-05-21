#include "resiflow.h"

QT_USE_NAMESPACE

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
{
    // Wid central
    QWidget * central = new QWidget(this);
    setCentralWidget(central);

    // Layout vertical
    QVBoxLayout * layoutMain = new QVBoxLayout(central);

    // Criar um botao
    QPushButton * botao = new QPushButton("Clique aqui", central);
    botao->setGeometry(50,50,200,40);
    layoutMain->addWidget(botao);

    // Cria widget do grafico
    ChartWidget * chart = new ChartWidget;
    layoutMain->addWidget(chart);

    // Criar tray de quatro knobs
    QHBoxLayout * knobTray = new QHBoxLayout();
    for (int i = 0; i < 4; ++i) {
        CustomKnob * knob = new CustomKnob();
        //knob->setFixedSize(200,200);
        //knobTray->addWidget(knob);
        knob->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        knobTray->addWidget(knob, 0);
    }
    layoutMain->addLayout(knobTray);
}

ResiFlow::~ResiFlow() = default;
