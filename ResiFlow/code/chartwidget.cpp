#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    // Determinando valores de inicio
    this->amplitudeMax = 5;
    this->maxTime = 0.33;
    this->resolucao = 25;

    this->attackRes = 10000;
    this->holdRes = 10000;
    this->decayReleaseRes = 10000;
    this->sustainRes = 10000;

    // Cria a serie de pontos, esses de 
    // enviados para o AHDSR
    this->pontosEnviados = new QLineSeries();

    // Cria a serie de pontos, esses de 
    // pontos ainda somente simulados
    this->pontosPreview = new QLineSeries();

    // Cria o grafico
    this->chart = new QChart();
    this->chart->addSeries(pontosPreview);
    this->chart->addSeries(pontosEnviados);
    this->chart->legend()->hide();
    this->chart->setBackgroundBrush(QBrush(Qt::black));        
    this->chart->setPlotAreaBackgroundBrush(QBrush(Qt::black)); 
    this->chart->setPlotAreaBackgroundVisible(true);
    //this->chart->setTitle("Gráfico AHDSR");
   
    // Cria o eixo Y
    this->yAxis = new QValueAxis;
    this->yAxis->setRange(0, 1.1*this->amplitudeMax);
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
    this->pontosEnviados->attachAxis(yAxis);
    this->pontosEnviados->attachAxis(xAxis);
    this->pontosPreview->attachAxis(yAxis);
    this->pontosPreview->attachAxis(xAxis);

    
    // Seta o grafico a ser mostrado pelo 
    // chartwidget, no caso chart, criado em cima ali
    setRenderHint(QPainter::Antialiasing);
    setChart(chart);

    // uptate no grafico, no caso só com a onda de preview
    this->updateChartSim(this->attackRes, this->holdRes, this->decayReleaseRes, this->sustainRes, 180, this->amplitudeMax);
}

void ChartWidget::updateChartSim(int A, int H, int DR, int S, float freq, double amplitudeMax) {
    //qDebug() << "######################################" << "\n";
    //qDebug() << "Frequencia: " << freq << "\n";

    this->attackRes = A;
    this->holdRes = H;
    this->decayReleaseRes = DR;
    this->sustainRes = S;

    //qDebug() << "Resistencia Attack: " << this->attackRes << "\n";
    //qDebug() << "Resistencia Hold: " << this->holdRes << "\n";
    //qDebug() << "Resistencia Sustain: " << this->sustainRes << "\n";

    // calculando a Frequencia em hertz, 
    // e entao encontrando o periodo
    this->maxTime = 1/(freq/60);

    // atualizando os eixos para novos valores
    this->xAxis->setRange(0, this->maxTime);
    this->yAxis->setRange(0, 1.1*amplitudeMax);

    // limpamos os pontos de preview antigos
    this->pontosPreview->clear();

    // determinamos como a linha da onda de preview se parece
    QPen pen1(QColor(100, 100, 0));
    pen1.setWidth(4);
    this->pontosPreview->setPen(pen1);

    // calculando os pontos da onda preview
    this->holdCalculation();
    this->sustainCalculation();
    this->attackCalculation();
    this->decayCalculation();
    this->releaseCalculation();

    //qDebug() << "######################################" << "\n";
}

void ChartWidget::updatePontosReais(){
    // limpamos os pontos da onda enviada
    this->pontosEnviados->clear();

    // determinamos como a linha da onda de preview se parece
    QPen pen(QColor(0, 255, 0));
    pen.setWidth(6); 
    this->pontosEnviados->setPen(pen);

    // determinamos que os pontos enviados sao 
    // iguais aos pontos de preview atuais
    this->pontosEnviados->append(this->pontosPreview->points());
}

void ChartWidget::holdCalculation(){
    int R = this->holdRes;

    // formula para encontrar tempo (foi mto dificil calcular isso)
    this->holdTime = -log(0.6 * (R * 1000.0 / (R + 1000.0)) * (R + 1000.0) / (R * 5000.0)) * (R * 1000.0 / (R + 1000.0)) * 75e-6;
    //qDebug() << "HoldTime: " << this->holdTime << "s" << "\n";
}


void ChartWidget::attackCalculation() {
    double v = 0.0;

    for (int i = 0; i < this->resolucao; ++i) {
        // Calcula a fração do tempo atual
        double t = this->holdTime * (static_cast<double>(i) / (this->resolucao - 1));

        // Fórmula do capacitor carregando
        v = this->amplitudeMax * (1.0 - exp(-t / (this->attackRes * 1e-6)));

        // Adiciona o ponto na série
        this->pontosPreview->append(t, v);
    }

    this->maxAttackVolt = v;
}

void ChartWidget::sustainCalculation() {
    // o potenciometro é de 10k, logo o outro lado do 
    // potenciometro é 10k menos a resistencia de sustain
    int sustainRComp = 10000-this->sustainRes;
    //qDebug() << "Sustain Complement: " << sustainRComp << "\n";

    // Rv = R1 / R1 + R2
    double div = static_cast<double>(this->sustainRes)/(sustainRComp + this->sustainRes);
    //qDebug() << "Divsor de tensao (Resistencia): " << div << "\n";

    // Vsus = Vtotal * Rv
    this->sustainVolt = amplitudeMax * div;
    //qDebug() << "Sustain Value: " << this->sustainVolt << "V" << "\n";
}

void ChartWidget::decayCalculation() {
    int i;

    //qDebug() << "Decay Resistencia: " << this->decayReleaseRes << "\n";
    //qDebug() << "maxTime/2: " << this->maxTime/2 << "\n";
    //qDebug() << "holdTime: " << this->holdTime << "\n";

    for (i = 0; i < this->resolucao; i++) {
        // O tempo é de decay começa no final do hold.
        // Logo somamos o tempo final do hold mais uma 
        // fracao do tempo até a metade do tempo total.
        double t = this->holdTime + (((this->maxTime/2)-this->holdTime) * (static_cast<double>(i) / (this->resolucao - 1)));

        // Fórmula da descarga em um capacitor, com uma tensão final.
        // Aqui vale destacar que como t não começa em zero, 
        // devemos subtrair o tempo de hold de t na fórmula, pois 
        // do contrário ele vai estar calculando essa curva a 
        // partir do zero do grafico.
        double v = this->sustainVolt + (this->maxAttackVolt - this->sustainVolt) * exp(-(t - this->holdTime) / (this->decayReleaseRes * 1e-6) );

        // Adiciona os pontos à série de preview
        this->pontosPreview->append(t,v);
    }
}

void ChartWidget::releaseCalculation() {
    int i;

    for (i = 0; i < this->resolucao; i++) {
        // o release começa no tempo final do sustain. 
        // Que também é a metade do tempo total.
        // Logo o tempo começa da metade do tempo total, 
        // mais uma fracao do tempo até o final
        double t = (this->maxTime/2) + ( (maxTime/2) *  (static_cast<double>(i) / (this->resolucao - 1)) );

        // Fórmula da descarga em capacitor.
        // Que nem no decay, devemos subtrair de t um valor 
        // que quando i = 0, a fórmula entenda que estamos 
        // calculando a tensão para o momento 0.
        double v = this->sustainVolt * exp( -(t - (this->maxTime/2)) / (this->decayReleaseRes * 1e-6) );

        // Adiciona os pontos à série de preview
        this->pontosPreview->append(t,v);
    }
}

ChartWidget::~ChartWidget() = default;
