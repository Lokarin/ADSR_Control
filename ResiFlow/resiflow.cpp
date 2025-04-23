#include "resiflow.h"
#include "ui_resiflow.h"
#include "customknob.h"

ResiFlow::ResiFlow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResiFlow)
{
    ui->setupUi(this);

    // Instancia o knob customizado
    knob = new CustomKnob(this);
    knob->setMinimum(0);
    knob->setMaximum(100);

    knob->setParent(ui->knobPlaceholder);
    knob->setGeometry(0, 0, ui->knobPlaceholder->width(), ui->knobPlaceholder->height());
    qDebug() << "Knob size:" << knob->size();


}

ResiFlow::~ResiFlow()
{
    delete ui;
}
