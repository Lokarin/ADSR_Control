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

private:
    double holdTime, maxTime, maxVol;
    void attackCalculation(double maxTime, int resistencia, double maxVol, QLineSeries *data);
    void holdCalculation(int R);
};

#endif // CHARTWIDGET_H
