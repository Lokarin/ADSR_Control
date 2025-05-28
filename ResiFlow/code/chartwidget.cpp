#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    this->maxVol = 4.18;
    this->maxTime = 0.33;

    // Cria a serie estilo Spline
    QLineSeries * splineSeries = new QLineSeries();

    this->holdCalculation(10000);
    this->attackCalculation(this->holdTime, 1, this->maxVol, splineSeries);

    // Cria o grafico
    QChart * chart = new QChart();
    chart->addSeries(splineSeries);
   
    QValueAxis * yAxis = new QValueAxis;
    yAxis->setRange(0, 1.1*this->maxVol);

    QValueAxis * xAxis = new QValueAxis;
    xAxis->setRange(0, this->maxTime);

    chart->addAxis(yAxis, Qt::AlignLeft);
    chart->addAxis(xAxis, Qt::AlignBottom);

    splineSeries->attachAxis(yAxis);
    splineSeries->attachAxis(xAxis);

    chart->legend()->hide();
    //chart->setTitle("Exemplo com QSplineSeries e QLineSeries");

    // Seta o grafico a ser mostrado pelo chartwidget, no caso chart, criado em cima ali
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void ChartWidget::attackCalculation(double holdTime, int resistencia, double maxVol, QLineSeries *data) {
    data->clear();

    int numPontos = 20;

    qDebug() << "Resistencia Attack: " << resistencia << "\n";
    for (int i = 0; i < numPontos; ++i) {
        // Calcula a fração do tempo atual
        double t = holdTime * (static_cast<double>(i) / (numPontos - 1));

        // Fórmula do capacitor carregando
        double v = maxVol * (1.0 - exp(-t / (resistencia * 1e-6)));

        // Adiciona o ponto na série
        data->append(t, v);
    }
}

void ChartWidget::holdCalculation(int R){
    this->holdTime = -log(0.6 * (R * 1000.0 / (R + 1000.0)) * (R + 1000.0) / (R * 5000.0)) * (R * 1000.0 / (R + 1000.0)) * 75e-6;
    qDebug() << "Resistencia Hold: " << R;
    qDebug() << "HoldTime: " << this->holdTime << "\n";
}

ChartWidget::~ChartWidget() = default;
