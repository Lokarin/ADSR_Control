#include "frequencywidget.h"

FrequencyWidget::FrequencyWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

void FrequencyWidget::init() {
    // main layout do widget
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    // nome em cima do widget
    titleLabel = new QLabel("Configurações do Áudio");
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    // layout horizontal para o slider e combo
    layoutInterface = new QHBoxLayout;

    // slider de frequencia
    slider = new CustomFreqSlider(this);
    layoutInterface->addWidget(slider);

    // combobox para selecionar tipos de onda
    waveSelector = new QComboBox;
    waveSelector->addItems({"Quadrada", "Triangular", "Senoidal", "Ruído"});
    layoutInterface->addWidget(waveSelector);

    mainLayout->addLayout(layoutInterface);
}

double FrequencyWidget::getFrequency() const {
    return slider->currentFrequency(); 
}

int FrequencyWidget::getWaveformIndex() const {
    return waveSelector->currentIndex();
}

void FrequencyWidget::setFrequency(double freqHz) {
    slider->setFrequency(freqHz);
}

void FrequencyWidget::setWaveformIndex(int index) {
    waveSelector->setCurrentIndex(index);
}

FrequencyWidget::~FrequencyWidget() = default;
