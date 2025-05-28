#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_USE_NAMESPACE

class ChartWidget : public QChartView {
    Q_OBJECT

public:
    ChartWidget(QWidget *parent = nullptr);
    ~ChartWidget();
    void updateChart(int A, int H, int DR, int S, float freq, double maxVol);

private:
    double holdTime, maxTime, maxVol;
    int attack, hold, decayRelease, sustain;

    QLineSeries * pontos;
    QChart * chart;
    QValueAxis * yAxis;
    QValueAxis * xAxis;

    void attackCalculation();
    void holdCalculation();
};

#endif // CHARTWIDGET_H
