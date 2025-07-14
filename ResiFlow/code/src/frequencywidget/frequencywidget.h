#ifndef FREQUENCYWIDGET_H
#define FREQUENCYWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

#include "customfreqslider/customfreqslider.h"

QT_USE_NAMESPACE

class FrequencyWidget : public QGroupBox {
    Q_OBJECT

public:
    FrequencyWidget(QWidget *parent = nullptr);
    ~FrequencyWidget();

    double getFrequency() const;
    int getWaveformIndex() const;

private:
    QVBoxLayout * mainLayout;
    QHBoxLayout * layoutInterface;
    QLabel * titleLabel;

    CustomFreqSlider * slider;
    QComboBox * waveSelector;

    void init();

signals:
   
};

#endif // FREQUENCYWIDGET_H
