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
    serial->setBaudRate(QSerialPort::Baud9600);
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

void SerialWidget::sendAHDSRData(int atk, int hold, int sus, int rel, int bpm, int freq) {
    if (!serial->isOpen()) {
        emit statusMessage("Erro: Porta serial não está conectada");
        return;
    }

    qDebug() << "Atk: " << atk << "\n";
    qDebug() << "Hold: " << hold << "\n";
    qDebug() << "Sust: " << sus << "\n";
    qDebug() << "Rele: " << rel << "\n";
    qDebug() << "BPM: " << bpm << "\n";
    qDebug() << "Freq: " << freq << "\n";

    float triggerOsqFreq;
    switch (bpm) {
        case 60:
            triggerOsqFreq = 1;
            break;
        case 100:
            triggerOsqFreq = 1.6;
            break;
        case 120:
            triggerOsqFreq = 2;
            break;
        case 150:
            triggerOsqFreq = 2.5;
            break;
        case 180:
            triggerOsqFreq = 3;
            break;
        default:
            triggerOsqFreq = 1;
            break;
    }

    constexpr double F_CPU = 16000000.0;        
    constexpr int ocr1aPreScaler = 1024;
    constexpr int ocr2aPreScaler = 256;

    int ocr1aValue = static_cast<int>(round((F_CPU / (2.0 * ocr1aPreScaler * triggerOsqFreq)) - 1));
    int ocr2aValue = static_cast<int>(round((F_CPU / (2.0 * ocr2aPreScaler * freq)) - 1));

    QByteArray data;
    data.append(static_cast<char>(atk));
    data.append(static_cast<char>(hold));
    data.append(static_cast<char>(sus));
    data.append(static_cast<char>(rel));

    data.append(static_cast<char>((ocr1aValue >> 8) & 0xFF));
    data.append(static_cast<char>(ocr1aValue & 0xFF));

    data.append(static_cast<char>(ocr2aValue));

    qint64 bytesEscritos = serial->write(data);
    if (bytesEscritos == -1) {
        emit statusMessage("Erro ao enviar os dados: " + serial->errorString());
    } else {
        emit statusMessage("Dados enviados com sucesso!");

        qDebug().noquote().nospace()
        << "Enviado: "
        << "ATK=0x" << QString::number((quint8)data[0], 16).rightJustified(2, '0') << ", "
        << "HOLD=0x" << QString::number((quint8)data[1], 16).rightJustified(2, '0') << ", "
        << "SUS=0x" << QString::number((quint8)data[2], 16).rightJustified(2, '0') << ", "
        << "DEC/REL=0x" << QString::number((quint8)data[3], 16).rightJustified(2, '0') << ", "
        << "TRIG=0x" << QString::number((quint8)data[4], 16).rightJustified(2, '0') << ", "
        << "VCA=0x" << QString::number((quint8)data[6], 16).rightJustified(2, '0') << " ("
        << data.size() << " bytes)";
    }
}

SerialWidget::~SerialWidget() = default;
