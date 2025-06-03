#include "serialwidget.h"

SerialWidget::SerialWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

void SerialWidget::init() {
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    titleLabel = new QLabel("Conexão Serial");
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    layoutInterface = new QHBoxLayout;

    serialPicker = new QComboBox;
    serialPicker->addItems({"tty0", "tty1", "tt2"});
    layoutInterface->addWidget(serialPicker);

    refreshButton = new QPushButton("Atualizar");
    layoutInterface->addWidget(refreshButton);

    connectButton = new QPushButton("Conectar");
    layoutInterface->addWidget(connectButton);

    mainLayout->addLayout(layoutInterface);
}

SerialWidget::~SerialWidget() = default;
