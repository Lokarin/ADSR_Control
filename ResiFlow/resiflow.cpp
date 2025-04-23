#include "resiflow.h"
#include "ui_resiflow.h"
#include "customknob.h"

ResiFlow::ResiFlow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResiFlow)
{
    ui->setupUi(this);

    // Nome das Labels
    QStringList knobNames = {"Attack", "Decay", "Sustain", "Release"};

    QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(ui->knobPlaceholder->layout());

    for (const QString &name : knobNames) {
        // Layout vertical para cada conjunto label+knob
        QVBoxLayout *knobLayout = new QVBoxLayout();

        QLabel *label = new QLabel(name, this);
        label->setAlignment(Qt::AlignCenter);

        CustomKnob *knob = new CustomKnob(this);
        knob->setMinimum(0);
        knob->setMaximum(100);
        knob->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        qDebug() << "Knob size:" << knob->size();

        connect(knob, &QDial::valueChanged, this, [=](int value){
            label->setText(QString("%1: %2").arg(name).arg(value));
        });

        // Adiciona primeiro o knob e depois a label
        knobLayout->addWidget(knob);
        knobLayout->addWidget(label);

        QWidget *container = new QWidget(this);
        container->setLayout(knobLayout);

        mainLayout->addWidget(container);
    }

}

ResiFlow::~ResiFlow()
{
    delete ui;
}
