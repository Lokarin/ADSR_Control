#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSettings>
#include <QString>

QT_USE_NAMESPACE

    class PresetWidget: public QGroupBox {
        Q_OBJECT
    public:
        PresetWidget(QWidget *parent = nullptr);
        ~PresetWidget();
    private:
        QVBoxLayout * mainLayout;
        QHBoxLayout * layoutInterface;
        QLabel      * titleLabel;
        QPushButton * savePresetButton;
        QPushButton * deletePresetButton;
        QPushButton * loadPresetButton;
        QComboBox   * presetSelector;
        unsigned int  presetCounter = 0;
        int           presetParametersList[6];
    private:
        void init();
        void updatePresetList();
        void loadPreset();
        void savePreset();
        void deletePreset();
    signals:
        void parametersRequest();
        void loadParametersToInterface(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);
    public slots:
        void receiveParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);
    };

#endif // PRESETWIDGET_H
