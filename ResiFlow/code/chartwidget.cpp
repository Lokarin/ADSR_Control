#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    this->maxVol = 4.18;
    this->maxTime = 0.33;

    this->attack = 10000;
    this->hold = 10000;
    this->decayRelease = 10000;
    this->sustain = 10000;

    // Cria a serie estilo Line
    this->pontos = new QLineSeries();

    this->updateChart(this->attack, this->hold, this->decayRelease, this->sustain, 180, this->maxVol);

    // Cria o grafico
    QChart * chart = new QChart();
    chart->addSeries(pontos);
   
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

    pontos->attachAxis(yAxis);
    pontos->attachAxis(xAxis);

    chart->legend()->hide();
    //chart->setTitle("Exemplo com QSplineSeries e QLineSeries");
    chart->setBackgroundBrush(QBrush(Qt::black));        
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::black)); 
    chart->setPlotAreaBackgroundVisible(true);
    
    // Seta o grafico a ser mostrado pelo chartwidget, no caso chart, criado em cima ali
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void ChartWidget::updateChart(int A, int H, int DR, int S, float freq, double maxVol) {
    this->attack = A;
    this->hold = H;
    this->decayRelease = DR;
    this->sustain = S;

    this->maxTime = 1/(freq/60);

    this->pontos->clear();

    QPen pen(Qt::red);
    pen.setWidth(6); 
    this->pontos->setPen(pen);

    this->holdCalculation();
    this->attackCalculation();
}

void ChartWidget::holdCalculation(){
    int R = this->hold;

    this->holdTime = -log(0.6 * (R * 1000.0 / (R + 1000.0)) * (R + 1000.0) / (R * 5000.0)) * (R * 1000.0 / (R + 1000.0)) * 75e-6;
    qDebug() << "Resistencia Hold: " << R;
    qDebug() << "HoldTime: " << this->holdTime << "\n";
}

void ChartWidget::attackCalculation() {
    int numPontos = 20;

    qDebug() << "Resistencia Attack: " << this->attack << "\n";
    for (int i = 0; i < numPontos; ++i) {
        // Calcula a fração do tempo atual
        double t = this->holdTime * (static_cast<double>(i) / (numPontos - 1));

        // Fórmula do capacitor carregando
        double v = this->maxVol * (1.0 - exp(-t / (this->attack * 1e-6)));

        // Adiciona o ponto na série
        this->pontos->append(t, v);
    }
}


ChartWidget::~ChartWidget() = default;
