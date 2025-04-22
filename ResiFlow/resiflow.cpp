#include "resiflow.h"
#include "./ui_resiflow.h"

ResiFlow::ResiFlow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ResiFlow)
{
    ui->setupUi(this);
}

ResiFlow::~ResiFlow()
{
    delete ui;
}
