#ifndef RESIFLOW_H
#define RESIFLOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
<<<<<<< Updated upstream
=======
#include <QStatusBar>
#include <QGroupBox>
#include <QShortcut>
#include <QKeyCombination>
#include <QCheckBox>
#include <QFileDialog>
>>>>>>> Stashed changes

#include "chartwidget/chartwidget.h"
#include "customknob/customknob.h"

class ResiFlow : public QMainWindow
{
    Q_OBJECT

public:
    ResiFlow(QWidget *parent = nullptr);
    ~ResiFlow();
private:
    QMap<QString, CustomKnob*> knobs;
    ChartWidget * chart;

    QSlider * freqSlider;
    QLabel * freqLabel;
    QStringList freqLabels;

<<<<<<< Updated upstream
=======
    // controle de modos
    QCheckBox * triggerModeSwitch;
    QPushButton * triggerButton;

    // botao salva grafico
    QPushButton * botaoSalvaBmp;

    void setupWidgets();
    void setupLayout();
    void setupStatusBar();
    void setupConnects();

    AHDSRValues getAHDSRValues();
    void updateChart();
    void sendSerialData(int rxHandler, int triggerCmd);
>>>>>>> Stashed changes
    void getKnobValues();
};
#endif // RESIFLOW_H
