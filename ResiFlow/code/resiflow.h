#ifndef RESIFLOW_H
#define RESIFLOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

#include "chartwidget.h"
#include "customknob.h"

class ResiFlow : public QMainWindow
{
    Q_OBJECT

public:
    ResiFlow(QWidget *parent = nullptr);
    ~ResiFlow();
private:
    QMap<QString, CustomKnob*> knobs;
    QSlider * freqSlider;
    ChartWidget * chart;
};
#endif // RESIFLOW_H
