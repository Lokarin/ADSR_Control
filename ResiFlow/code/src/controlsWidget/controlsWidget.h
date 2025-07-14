#ifndef CONTROLSWIDGET_H
#define CONTROLSWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

QT_USE_NAMESPACE

class ControlsWidget : public QGroupBox {
    Q_OBJECT

public:
    ControlsWidget(QWidget *parent = nullptr);
    ~ControlsWidget();

    bool isAutoModeEnabled() const;

private:
    QVBoxLayout * mainLayout;
    QHBoxLayout * layoutInterface;
    QLabel * titleLabel;
    QPushButton * sendButton;
    QPushButton * autoButton;
    QPushButton * trigButton;

    void init();

signals:
    void sendButtonClicked();
    void trigButtonPressed();
    void trigButtonReleased();
    void autoModeToggled(bool checked);

};

#endif // CONTROLSWIDGET_H
