#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    this->maxVol = 5;
    this->maxTime = 0.33;

    this->attack = 10000;
    this->hold = 10000;
    this->decayRelease = 10000;
    this->sustain = 10000;

    // Cria a serie de pontos, esses de enviados para o AHDSR
    this->pontos = new QLineSeries();

    // Cria a serie de pontos, esses de pontos ainda somente simulados
    this->pontosSimulados = new QLineSeries();

    // Cria o grafico
    this->chart = new QChart();
    this->chart->addSeries(pontosSimulados);
    this->chart->addSeries(pontos);
    this->chart->legend()->hide();
    this->chart->setBackgroundBrush(QBrush(Qt::black));        
    this->chart->setPlotAreaBackgroundBrush(QBrush(Qt::black)); 
    this->chart->setPlotAreaBackgroundVisible(true);
    //this->chart->setTitle("Gráfico AHDSR");
   
    // Cria o eixo Y
    this->yAxis = new QValueAxis;
    this->yAxis->setRange(0, 1.1*this->maxVol);
    this->yAxis->setLinePen(QPen(Qt::white));
    this->yAxis->setLabelsColor(Qt::white);
    this->yAxis->setGridLinePen(QPen(Qt::gray));

    // Cria o eixo X
    this->xAxis = new QValueAxis;
    this->xAxis->setRange(0, this->maxTime);
    this->xAxis->setLinePen(QPen(Qt::white));
    this->xAxis->setLabelsColor(Qt::white);
    this->xAxis->setGridLinePen(QPen(Qt::gray));

    // Adiciona os eixos ao grafico
    this->chart->addAxis(yAxis, Qt::AlignLeft);
    this->chart->addAxis(xAxis, Qt::AlignBottom);

    // Ajusta os pontos aos eixos
    this->pontos->attachAxis(yAxis);
    this->pontos->attachAxis(xAxis);
    this->pontosSimulados->attachAxis(yAxis);
    this->pontosSimulados->attachAxis(xAxis);

    
    // Seta o grafico a ser mostrado pelo chartwidget, no caso chart, criado em cima ali
    setRenderHint(QPainter::Antialiasing);
    setChart(chart);

    this->updateChartSim(this->attack, this->hold, this->decayRelease, this->sustain, 180, this->maxVol);
}

void ChartWidget::updateChartSim(int A, int H, int DR, int S, float freq, double maxVol) {
    qDebug() << "######################################" << "\n";
    qDebug() << "Frequencia: " << freq << "\n";

    this->attack = A;
    this->hold = H;
    this->decayRelease = DR;
    this->sustain = S;

    qDebug() << "Resistencia Attack: " << this->attack << "\n";
    qDebug() << "Resistencia Hold: " << "\n";

    this->maxTime = 1/(freq/60);

    this->xAxis->setRange(0, this->maxTime);
    this->yAxis->setRange(0, 1.1*maxVol);

    this->pontosSimulados->clear();
    QPen pen1(Qt::green);
    pen1.setWidth(10);
    this->pontosSimulados->setPen(pen1);

    this->holdCalculation();
    this->attackCalculation();

    qDebug() << "######################################" << freq << "\n";
}

void ChartWidget::updatePontosReais(){
    this->pontos->clear();

    QPen pen(Qt::red);
    pen.setWidth(6); 
    this->pontos->setPen(pen);

    this->pontos->append(this->pontosSimulados->points());
}

void ChartWidget::holdCalculation(){
    int R = this->hold;

    this->holdTime = -log(0.6 * (R * 1000.0 / (R + 1000.0)) * (R + 1000.0) / (R * 5000.0)) * (R * 1000.0 / (R + 1000.0)) * 75e-6;
    qDebug() << "HoldTime: " << this->holdTime << "s" << "\n";
}


void ChartWidget::attackCalculation() {
    int numPontos = 50;

    for (int i = 0; i < numPontos; ++i) {
        // Calcula a fração do tempo atual
        double t = this->holdTime * (static_cast<double>(i) / (numPontos - 1));

        // Fórmula do capacitor carregando
        double v = this->maxVol * (1.0 - exp(-t / (this->attack * 1e-6)));

        // Adiciona o ponto na série
        this->pontosSimulados->append(t, v);
    }
}


ChartWidget::~ChartWidget() = default;
