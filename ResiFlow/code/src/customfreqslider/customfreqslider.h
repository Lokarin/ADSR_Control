#ifndef CUSTOMFREQSLIDER_H
#define CUSTOMFREQSLIDER_H

#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>

class CustomFreqSlider : public QGroupBox {
    Q_OBJECT

public:
    CustomFreqSlider(QWidget *parent = nullptr);
    ~CustomFreqSlider();

    double currentFrequency() const;

private:
    QSlider * slider;
    QLabel * label;

    double sliderToFreq(int val) const;
    int freqToSlider(double freq) const;

    static constexpr int SLIDER_MIN = 0;
    static constexpr int SLIDER_MAX = 1000;

signals:
    void frequencyChanged(double freq);

private slots:
    void handleSliderChanged(int value);
};

#endif // CUSTOMFREQSLIDER_H
