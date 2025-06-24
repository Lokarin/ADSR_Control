#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QFile>
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

    bool saveChartAsImage(const QString &filePath);
    bool saveChartAsBinary(const QString &filePath);
    bool saveChartAsCArray(const QString &filePath);

private:
    double _maxTime, _holdTime, _amplitudeMax, _sustainVolt, _maxAttackVolt;
    int _attackRes, _holdRes, _decayReleaseRes, _sustainRes, _resolucao, _minDecayVolt;

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

    QImage renderToMonochromeImage();
    QVector<QPointF> getPontos() const;
    void debugPontos();
    void drawLine(int x0, int y0, int x1, int y1, std::function<void(int, int)> setPixel);
    
};

#endif // CHARTWIDGET_H
