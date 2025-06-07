#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_USE_NAMESPACE

class SerialWidget : public QGroupBox {
    Q_OBJECT

public:
    SerialWidget(QWidget *parent = nullptr);
    ~SerialWidget();

private:
    QVBoxLayout * mainLayout;
    QHBoxLayout * layoutInterface;
    QComboBox * serialPicker;
    QLabel * titleLabel;
    QPushButton * connectButton;
    QPushButton * refreshButton;
    QSerialPort * serial;

    void init();
    void refreshPorts();
    void connectSerial();

signals:
    void statusMessage(const QString &message);
};

#endif // SERIALWIDGET_H
