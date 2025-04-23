#include "resiflow.h"
#include "ui_resiflow.h"
#include "customknob.h"

ResiFlow::ResiFlow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResiFlow)
{
    ui->setupUi(this);

    attackKnob = new CustomKnob(this);
    attackKnob->setMinimum(0);
    attackKnob->setMaximum(100);

    attackKnob->setParent(ui->knobPlaceholder);
    attackKnob->setGeometry(0, 0, ui->knobPlaceholder->width(), ui->knobPlaceholder->height());
    qDebug() << "Knob size:" << attackKnob->size();

    connect(attackKnob, &QDial::valueChanged, this, [=](int value){
        ui->attackLabel->setText(QString("Valor: %1").arg(value));
    });

}

ResiFlow::~ResiFlow()
{
    delete ui;
}
