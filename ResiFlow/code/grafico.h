#ifndef GRAFICO_H
#define GRAFICO_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

QT_USE_NAMESPACE

class ChartWindow : public QMainWindow {
    Q_OBJECT

public:
    ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();
};

#endif // GRAFICO_H
