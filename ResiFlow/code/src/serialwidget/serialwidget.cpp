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

    serial = new QSerialPort(this);

    refreshPorts();

    connect(refreshButton, &QPushButton::clicked, this, [=]() {
            refreshPorts();
    });

    connect(connectButton, &QPushButton::clicked, this, [=]() {
            connectSerial();
    });
}

void SerialWidget::refreshPorts() {
    // Limpando o picker
    serialPicker->clear();

    // Lista de objetos do tipo QSerialPortInfo
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    // Para cada QSerialPortInfo em ports
    for (const QSerialPortInfo &port : ports) {
        // Adicionamos um item com o mesmo nome de port
        // ao picker
        serialPicker->addItem(port.portName());
    }

    if (ports.isEmpty()) {
        serialPicker->addItem("Nenhuma porta disponível");
    }
}

void SerialWidget::connectSerial() {
    if (serial->isOpen()) {
        serial->close();
        connectButton->setText("Conectar");
        emit statusMessage("Porta desconectada!");
        return;
    }

    QString portName = serialPicker->currentText();
    if (portName.isEmpty() || portName == "Nenhuma porta disponível") {
        emit statusMessage("Porta inválida.");
        return;
    }

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        connectButton->setText("Desconectar");
        emit statusMessage("Conectado na porta " + portName);
    } else {
        emit statusMessage("Erro ao conectar: " + serial->errorString());
    }
}

SerialWidget::~SerialWidget() = default;
