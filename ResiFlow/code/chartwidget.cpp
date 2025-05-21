#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    // Cria a serie estilo Spline
    QSplineSeries * splineSeries = new QSplineSeries();
    splineSeries->append(1, 0);
    splineSeries->append(2, 3);
    splineSeries->append(3, 4);
    splineSeries->append(5, 4);
    splineSeries->append(6, 3);
    splineSeries->append(7, 2);
    splineSeries->append(9, 2);
    splineSeries->append(10, 1);
    splineSeries->append(11, 0);

    // Cria a serie estilo Line
    //QLineSeries * lineSeries = new QLineSeries();
    //lineSeries->append(0, 3);
    //lineSeries->append(1, 5);
    //lineSeries->append(2, 6);
    //lineSeries->append(3, 7);
    //lineSeries->append(4, 8);
    //lineSeries->append(5, 9);

    // Cria o grafico
    QChart * chart = new QChart();
    chart->addSeries(splineSeries);
    //chart->addSeries(lineSeries);
    chart->createDefaultAxes();
    chart->legend()->hide();
    //chart->setTitle("Exemplo com QSplineSeries e QLineSeries");

    // Seta o grafico a ser mostrado pelo chartwidget, no caso chart, criado em cima ali
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

ChartWidget::~ChartWidget() = default;
