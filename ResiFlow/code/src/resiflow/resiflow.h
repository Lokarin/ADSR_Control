#ifndef RESIFLOW_H
#define RESIFLOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QStatusBar>
#include <QGroupBox>
#include <QShortcut>
#include <QKeyCombination>
#include <QCheckBox>
#include <QFileDialog>

#include "chartwidget/chartwidget.h"
#include "customknob/customknob.h"
#include "serialwidget/serialwidget.h"
#include "presetwidget/presetwidget.h"
#include "knobswidget/knobswidget.h"

struct AHDSRValues {
    int attack;
    int hold;
    int sustain;
    int decayRelease;
    int bpm;
    int freq;
};

class ResiFlow : public QMainWindow
{
    Q_OBJECT

public:
    ResiFlow(QWidget *parent = nullptr);
    ~ResiFlow();

private:
    // Objeto Status Bar
    QStatusBar * status;

    // botao para send
    QPushButton * botaoSend;

    // serialwidget
    SerialWidget * conexaoGroup;

    // presetwidget
    PresetWidget * presetWidget;

    // grafico
    ChartWidget * chart;
    QGroupBox * chartGroup;

    // vetor com os knobs
    KnobsWidget * knobsWidget;

    // slider para frequencia
    QSlider * freqSlider;
    QLabel * freqLabel;
    QStringList freqLabels;

    // controle de modos
    QCheckBox * triggerModeSwitch;
    QPushButton * triggerButton;

    QMap<QString, CustomKnob*> knobs;

    // botao salva grafico
    QPushButton * botaoSalvaBmp;


    void setupWidgets();
    void setupLayout();
    void setupStatusBar();
    void setupConnects();

    AHDSRValues getAHDSRValues();
    void updateChart();
    void sendSerialData(int rxHandler, int triggerCmd);
    void getKnobValues();

signals:
    void parametersChanged(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);

private slots:
    void onParametersRequest();
    void onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);
};
#endif // RESIFLOW_H
