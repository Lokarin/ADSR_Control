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

    overwritePresetButton = new QPushButton("Sobescrever Preset");
    layoutInterface->addWidget(overwritePresetButton);

    savePresetButton = new QPushButton("Salvar Preset");
    layoutInterface->addWidget(savePresetButton);

    deletePresetButton = new QPushButton("Deletar Preset");
    layoutInterface->addWidget(deletePresetButton);

    mainLayout->addLayout(layoutInterface);

    // Connects
    connect(savePresetButton, &QPushButton::clicked, this, &PresetWidget::savePreset);
    connect(deletePresetButton, &QPushButton::clicked, this, &PresetWidget::deletePreset);
    connect(overwritePresetButton, &QPushButton::clicked, this, &PresetWidget::overwritePreset);
    connect(presetSelector, &QComboBox::currentIndexChanged, this, &PresetWidget::loadPreset);

    // Carrega a lista de presets na inicialização
    QSettings settings("ResiFlow", "Presets");
    presetCounter = settings.value("presetCounter", 0).toInt(); // Carrega zero se presetCounter não existir na máquina
    if (presetCounter != 0) {
        updatePresetList(""); // Popula a lista
        presetSelector->setCurrentIndex(0); // Define o índice para iniciar do primeiro preset
    }
}

// Método para atualizar lista de presets
void PresetWidget::updatePresetList(QString presetName) {
    presetSelector->clear();

    QSettings settings("ResiFlow", "Presets");
    QStringList groups = settings.childGroups();

    for (const QString &group : groups) {
        if (group.startsWith("preset")) {
            presetSelector->addItem(group);
        }
    }

    int QComboBoxIndex = presetSelector->findText(presetName);
    qDebug() << QComboBoxIndex << "\n";
    if (QComboBoxIndex != -1) {
        presetSelector->setCurrentIndex(QComboBoxIndex);
    }
}

// Método para sobescrever um preset selecionado da lista
void PresetWidget::overwritePreset() {
    QString selectedPreset = presetSelector->currentText();

    if (selectedPreset.isEmpty()) {
        return; // Não há preset selecionado
    } else {
        emit parametersRequest();
        QSettings settings("ResiFlow", "Presets");

        for (int i = 0; i < 6; ++i) {
            settings.setValue(QString("%1/param%2").arg(selectedPreset).arg(i + 1), presetParametersList[i]);
        }
    }
}

// Método para carregar o preset selecionado da lista
void PresetWidget::loadPreset() {
    QString selectedPreset = presetSelector->currentText();

    if (selectedPreset.isEmpty()) {
        return; // Não há preset selecionado
    } else {
        QSettings settings("ResiFlow", "Presets");

        // Carregar os valores salvos
        int attack = settings.value(QString("%1/param1").arg(selectedPreset)).toInt();
        int hold = settings.value(QString("%1/param2").arg(selectedPreset)).toInt();
        int sustain = settings.value(QString("%1/param3").arg(selectedPreset)).toInt();
        int decayRelease = settings.value(QString("%1/param4").arg(selectedPreset)).toInt();
        int bpmVal = settings.value(QString("%1/param5").arg(selectedPreset)).toInt();
        int freq = 500;

        // Emitir sinal para atualizar a interface
        emit loadParametersToInterface(attack, hold, sustain, decayRelease, bpmVal, freq);
    }

}

// Método para salvar um preset
void PresetWidget::savePreset() {
    emit parametersRequest();

    QSettings settings("ResiFlow", "Presets");
    // Encontra o próximo nome não utilizado
    int newPresetNumber = 1;
    while (settings.contains(QString("preset%1/param1").arg(newPresetNumber))) {
        newPresetNumber++;
    }

    for (int i = 0; i < 6; ++i) {
        settings.setValue(QString("preset%1/param%2").arg(newPresetNumber).arg(i + 1), presetParametersList[i]);
    }

    presetCounter++;
    settings.setValue("presetCounter", presetCounter);
    updatePresetList(QString("preset%1").arg(newPresetNumber));
}

// Método para deletar um preset
void PresetWidget::deletePreset() {
    QString selectedPreset = presetSelector->currentText();

    if (selectedPreset.isEmpty()) {
        return; // Não há presets para serem removidos
    } else {
        QSettings settings("ResiFlow", "Presets");
        int index = presetSelector->currentIndex();

        settings.beginGroup(presetSelector->currentText());
        settings.remove("");
        settings.endGroup();
        settings.remove(presetSelector->currentText());

        if (index != 0) { // Verifica se é o único preset da QComboBox antes de atualizar
            updatePresetList(presetSelector->itemText(index - 1)); // Passa o nome do preset anterior
        } else {
            updatePresetList(presetSelector->itemText(index + 1)); // Passa o nome do próximo preset
        }
        presetCounter--;
        settings.setValue("presetCounter", presetCounter);
    }
}

// Recebe parâmetros de ResiFlow
void PresetWidget::receiveParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq) {
    presetParametersList[0] = attack;
    presetParametersList[1] = hold;
    presetParametersList[2] = sustain;
    presetParametersList[3] = decayRelease;
    presetParametersList[4] = bpmVal;
    presetParametersList[5] = freq;
}

PresetWidget::~PresetWidget() = default;
