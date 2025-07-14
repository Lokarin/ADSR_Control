#include "customfreqslider.h"

CustomFreqSlider::CustomFreqSlider(QWidget *parent)
    : QGroupBox(parent),
      slider(new QSlider(Qt::Horizontal)),
      label(new QLabel)
{
    slider->setRange(SLIDER_MIN, SLIDER_MAX);
    slider->setValue(freqToSlider(262)); 

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(slider);
    setLayout(layout);

    handleSliderChanged(slider->value());

    connect(slider, &QSlider::valueChanged, this, &CustomFreqSlider::handleSliderChanged);
}

void CustomFreqSlider::handleSliderChanged(int value) {
    double freq = sliderToFreq(value);

    QString text;
    if (freq >= 1000.0)
        text = QString::number(freq / 1000.0, 'f', 2) + " kHz";
    else
        text = QString::number(freq, 'f', 0) + " Hz";

    label->setText("Frequência: " + text);
    emit frequencyChanged(freq);
}

double CustomFreqSlider::sliderToFreq(int val) const {
    double minLog = std::log10(20.0);
    double maxLog = std::log10(20000.0);
    double scale = static_cast<double>(val - SLIDER_MIN) / (SLIDER_MAX - SLIDER_MIN);
    return std::pow(10.0, minLog + scale * (maxLog - minLog));
}

int CustomFreqSlider::freqToSlider(double freq) const {
    double minLog = std::log10(20.0);
    double maxLog = std::log10(20000.0);
    double logVal = std::log10(freq);
    double scale = (logVal - minLog) / (maxLog - minLog);
    return static_cast<int>(scale * (SLIDER_MAX - SLIDER_MIN) + SLIDER_MIN);
}

double CustomFreqSlider::currentFrequency() const {
    return sliderToFreq(slider->value());
}

CustomFreqSlider::~CustomFreqSlider() = default;
