#include "serialwidget.h"

SerialWidget::SerialWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

void SerialWidget::init() {
    // main layout do widget
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    // nome em cima do widget
    titleLabel = new QLabel("Conexão Serial");
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    // layout horizontal para os botoes e combo
    layoutInterface = new QHBoxLayout;

    // combo para picker das portas
    serialPicker = new QComboBox;
    serialPicker->addItems({"tty0", "tty1", "tt2"});
    layoutInterface->addWidget(serialPicker);

    // botao de refres
    refreshButton = new QPushButton("Atualizar");
    layoutInterface->addWidget(refreshButton);

    // botao de connect/disconnect
    connectButton = new QPushButton("Conectar");
    layoutInterface->addWidget(connectButton);

    mainLayout->addLayout(layoutInterface);

    // iniciando objeto serial
    serial = new QSerialPort(this);

    refreshPorts();

    // Connects
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
    // se a porta está aberta, mudamos o texto
    // do botao, mudamos o texto da status
    // para refletir isso
    if (serial->isOpen()) {
        serial->close();
        connectButton->setText("Conectar");
        emit statusMessage("Porta desconectada!");
        return;
    }

    // se por alguma razao o picker estiver vazio
    // provavelmente a porta é inválida
    QString portName = serialPicker->currentText();
    if (portName.isEmpty() || portName == "Nenhuma porta disponível") {
        emit statusMessage("Porta inválida.");
        return;
    }

    // configuracoes da comunicacao serial
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud19200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // se a porta estiver em uso, mudamos os nomes do 
    // botao e do status para mostrar isso
    if (serial->open(QIODevice::ReadWrite)) {
        connectButton->setText("Desconectar");
        emit statusMessage("Conectado na porta " + portName);
    } else {
        emit statusMessage("Erro ao conectar: " + serial->errorString());
    }
}

void SerialWidget::sendAHDSRData(int rxHandler, int triggerCmd, int atk, int hold, int sus, int rel, int bpm, int freq, int wfMode) {
    if (!serial->isOpen()) {
        emit statusMessage("Erro: Porta serial não está conectada");
        return;
    }

    qDebug() << "RX: " << rxHandler;
    qDebug() << "TRIGON: " << triggerCmd;
    qDebug() << "Atk: " << atk;
    qDebug() << "Hold: " << hold;
    qDebug() << "Sust: " << sus;
    qDebug() << "Rele: " << rel;
    qDebug() << "BPM: " << bpm;
    qDebug() << "Freq: " << freq;
    qDebug() << "Form: " << wfMode;

    QByteArray data;
    qint64 bytesEscritos;
    if (rxHandler == 0) {
        data.append(static_cast<char>(rxHandler));
        data.append(static_cast<char>(triggerCmd));
        bytesEscritos = serial->write(data);
    } else {
        // bpm -> Hz
        float triggerOsqFreq = bpm / 60.0f;

        constexpr double F_CPU = 16000000.0;        
        constexpr int ocr1aPreScaler = 256;

        // calculando o valor dee ocr1 
        int ocr1aValue = static_cast<int>(round((F_CPU / (2.0 * ocr1aPreScaler * triggerOsqFreq)) - 1));

        // adicionando os valores em forma de bits
        data.append(static_cast<char>(rxHandler));
        data.append(static_cast<char>(atk));
        data.append(static_cast<char>(hold));
        data.append(static_cast<char>(sus));
        data.append(static_cast<char>(rel));

        data.append(static_cast<char>(wfMode));
        data.append(static_cast<char>((freq >> 8) & 0xFF));
        data.append(static_cast<char>(freq & 0xFF));

        data.append(static_cast<char>((ocr1aValue >> 8) & 0xFF));
        data.append(static_cast<char>(ocr1aValue & 0xFF));

        // enviando os valores
        bytesEscritos = serial->write(data);
    }

    // debug avisando se deu certo ou errado
    if (bytesEscritos == -1) {
        emit statusMessage("Erro ao enviar os dados: " + serial->errorString());
    } else {
        emit statusMessage("Dados enviados com sucesso!");

       //if (rxHandler == 0) {
       //     qDebug().noquote().nospace()
       //         << "Enviado: "
       //         << "RXHANDLER=0x" << QString::number((quint8)data[0], 16).rightJustified(2, '0') << ", "
       //         << "TRIGON=0x" << QString::number((quint8)data[1], 16).rightJustified(2, '0')
       //         << " (" << data.size() << " byte)";
       //} else {
       //    qDebug().noquote().nospace()
       //        << "Enviado: "
       //        << "RXHANDLER=0x" << QString::number((quint8)data[0], 16).rightJustified(2, '0') << ", "
       //        << "ATK=0x" << QString::number((quint8)data[1], 16).rightJustified(2, '0') << ", "
       //        << "HOLD=0x" << QString::number((quint8)data[2], 16).rightJustified(2, '0') << ", "
       //        << "SUS=0x" << QString::number((quint8)data[3], 16).rightJustified(2, '0') << ", "
       //        << "DEC/REL=0x" << QString::number((quint8)data[4], 16).rightJustified(2, '0') << ", "
       //        << "TRIG=0x" << QString::number((quint8)data[5], 16).rightJustified(2, '0') << ", "
       //        << "TRIG_LSB=0x" << QString::number((quint8)data[6], 16).rightJustified(2, '0') << ", "
       //        << "VCA=0x" << QString::number((quint8)data[6], 16).rightJustified(2, '0') << " ("
       //            << data.size() << " bytes)";
       //}
    }
}

SerialWidget::~SerialWidget() = default;
