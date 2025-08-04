#ifndef RESIFLOW_H
#define RESIFLOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QLineEdit>

#include "chartwidget/chartwidget.h"
#include "serialwidget/serialwidget.h"
#include "presetwidget/presetwidget.h"
#include "knobswidget/knobswidget.h"
#include "controlsWidget/controlsWidget.h"
#include "frequencywidget/frequencywidget.h"

struct AHDSRValues {
    int attack;
    int hold;
    int sustain;
    int decayRelease;
    int bpm;
    int freq;
    int wfForm;
};

class ResiFlow : public QMainWindow
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

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
    QHBoxLayout * bpmLayout;
    QLineEdit * bpmLineEdit;
    QSlider * freqSlider;
    QLabel * freqLabel;
    QStringList freqLabels;

    // painel de controles
    ControlsWidget * controlsWidget;

    // widget de config de onda 
    FrequencyWidget * freqWidget;


    void setupWidgets();
    void setupLayout();
    void setupStatusBar();
    void setupConnects();
    void setupNoteMap();

    AHDSRValues getAHDSRValues();
    void updateChart();
    void sendSerialData(int rxHandler, int triggerCmd);

    int formaDeOnda = 2;
    QMap<int, QPair<int, int>> noteMap;
    QSet<int> pressedKeys; // Ter certeza de unica tecla pressionada

signals:
    void parametersChanged(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq, int wfForm);

private slots:
    void onParametersRequest();
    void onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq, int wfForm);
};
#endif // RESIFLOW_H
