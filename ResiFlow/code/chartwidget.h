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
    void updateChartSim(int A, int H, int DR, int S, float freq, double maxVol);
    void updatePontosReais();

private:
    double maxTime, holdTime, amplitudeMax, sustainVolt, maxAttackVolt;
    int attackRes, holdRes, decayReleaseRes, sustainRes;

    QLineSeries * pontosEnviados;
    QLineSeries * pontosPreview;
    QChart * chart;
    QValueAxis * yAxis;
    QValueAxis * xAxis;

    void attackCalculation();
    void holdCalculation();
    void sustainCalculation();
    void decayCalculation();
    void releaseCalculation();
};

#endif // CHARTWIDGET_H
