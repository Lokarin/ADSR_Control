#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    this->maxVol = 4.18;
    this->maxTime = 0.33;

    // Cria a serie estilo Spline
    QLineSeries * splineSeries = new QLineSeries();

    this->holdCalculation(5000);
    this->attackCalculation(this->holdTime, 10000, this->maxVol, splineSeries);

    // Cria o grafico
    QChart * chart = new QChart();
    chart->addSeries(splineSeries);
   
    QValueAxis * yAxis = new QValueAxis;
    yAxis->setRange(0, 1.1*this->maxVol);
    yAxis->setLinePen(QPen(Qt::white));
    yAxis->setLabelsColor(Qt::white);
    yAxis->setGridLinePen(QPen(Qt::gray));

    QValueAxis * xAxis = new QValueAxis;
    xAxis->setRange(0, this->maxTime);
    // Configura o eixo X
    xAxis->setLinePen(QPen(Qt::white));
    xAxis->setLabelsColor(Qt::white);
    xAxis->setGridLinePen(QPen(Qt::gray));

    chart->addAxis(yAxis, Qt::AlignLeft);
    chart->addAxis(xAxis, Qt::AlignBottom);

    splineSeries->attachAxis(yAxis);
    splineSeries->attachAxis(xAxis);

    chart->legend()->hide();
    //chart->setTitle("Exemplo com QSplineSeries e QLineSeries");
    chart->setBackgroundBrush(QBrush(Qt::black));        
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::black)); 
    chart->setPlotAreaBackgroundVisible(true);


    // Configura o eixo Y

    // Seta o grafico a ser mostrado pelo chartwidget, no caso chart, criado em cima ali
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void ChartWidget::attackCalculation(double holdTime, int resistencia, double maxVol, QLineSeries *data) {
    data->clear();
    QPen pen(Qt::red);
    pen.setWidth(6); 
    data->setPen(pen);

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
