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

#include "chartwidget/chartwidget.h"
#include "customknob/customknob.h"
#include "serialwidget/serialwidget.h"
#include "presetwidget/presetwidget.h"

class ResiFlow : public QMainWindow
{
    Q_OBJECT

public:
    ResiFlow(QWidget *parent = nullptr);
    ~ResiFlow();
private:
    QMap<QString, CustomKnob*> knobs;
    ChartWidget * chart;
    QStatusBar * status;
    QSlider * freqSlider;
    QLabel * freqLabel;
    QStringList freqLabels;
    SerialWidget * conexaoGroup;
    QVector<int> getAHDSRValues();
    void updateChart();
    void sendSerialData();
    void getKnobValues();
signals:
    void parametersChanged(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);
private slots:
    void onParametersRequest();
    void onLoadParameters(int attack, int hold, int sustain, int decayRelease, int bpmVal, int freq);
};
#endif // RESIFLOW_H
