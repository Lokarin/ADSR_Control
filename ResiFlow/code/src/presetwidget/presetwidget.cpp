#include "presetwidget.h"

// Construtor
PresetWidget::PresetWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

// Inicialização
void PresetWidget::init() {
    // Visual gráfico
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    layoutInterface = new QHBoxLayout;

    titleLabel = new QLabel("Preset Manager");
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    presetSelector = new QComboBox(this);
    layoutInterface->addWidget(presetSelector);

    loadPresetButton = new QPushButton("Carregar Preset");
    layoutInterface->addWidget(loadPresetButton);

    savePresetButton = new QPushButton("Salvar Preset");
    layoutInterface->addWidget(savePresetButton);

    deletePresetButton = new QPushButton("Deletar Preset");
    layoutInterface->addWidget(deletePresetButton);

    mainLayout->addLayout(layoutInterface);

    // Connects
    connect(savePresetButton, &QPushButton::clicked, this, &PresetWidget::savePreset);
    connect(deletePresetButton, &QPushButton::clicked, this, &PresetWidget::deletePreset);

    // Carrega a lista de presets na inicialização
    updatePresetList();
}

// Método para atualizar lista de presets
void PresetWidget::updatePresetList() {
    presetSelector->clear();

    QSettings settings("ResiFlow", "Presets");
    QStringList groups = settings.childGroups();

    for (const QString &group : groups) {
        if (group.startsWith("preset")) {
            presetSelector->addItem(group);
        }
    }
}

// Método para carregar o preset selecionado da lista
void PresetWidget::loadPreset() {
    QSettings settings("ResiFlow", "Presets");

}

// Método para salvar um preset
void PresetWidget::savePreset() {
    QSettings settings("ResiFlow", "Presets");
    presetCounter = settings.value("presetCounter", 0).toInt(); // Carrega zero se presetCounter não existir na máquina

    for (int i = 0; i < 4; ++i) {
        settings.setValue(QString("preset%1/pot%2").arg(presetCounter + 1).arg(i + 1), 2);
    }

    presetCounter++;
    settings.setValue("presetCounter", presetCounter);
    updatePresetList();
}

// Método para deletar um preset
void PresetWidget::deletePreset() {
    QSettings settings("ResiFlow", "Presets");
    presetCounter = settings.value("presetCounter", 0).toInt();

    if (presetCounter != 0) {
        settings.beginGroup(presetSelector->currentText());
        settings.remove("");
        settings.endGroup();
        settings.remove(presetSelector->currentText());

        presetCounter--;
        settings.setValue("presetCounter", presetCounter);
    }

    updatePresetList();
}

PresetWidget::~PresetWidget() = default;
