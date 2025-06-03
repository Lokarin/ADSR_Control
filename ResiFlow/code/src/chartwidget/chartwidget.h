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
    double _maxTime, _holdTime, _amplitudeMax, _sustainVolt, _maxAttackVolt, _minDecayVolt;
    int _attackRes, _holdRes, _decayReleaseRes, _sustainRes, _resolucao;

    QLineSeries * pontosEnviados;
    QLineSeries * pontosPreview;
    QChart * chart;
    QValueAxis * yAxis;
    QValueAxis * xAxis;

    void initializeChart();
    void initializeAxes();
    void initializeSeries();
    void setupChartStyling();

    void attackCalculation();
    void holdCalculation();
    void sustainCalculation();
    void decayCalculation();
    void releaseCalculation();
};

#endif // CHARTWIDGET_H
