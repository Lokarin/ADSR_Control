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
        unsigned int  presetParametersList[5];

        void init();
    private slots:
        void updatePresetList();
        void loadPreset();
        void savePreset();
        void deletePreset();
    };

#endif // PRESETWIDGET_H
