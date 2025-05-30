#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent),
    _amplitudeMax(5), _maxTime(0.33), _resolucao(25),
    _attackRes(10000), _holdRes(10000), _decayReleaseRes(10000), _sustainRes(10000)
{
    initializeChart();
    initializeAxes();
    initializeSeries();
    setupChartStyling();

    // uptate no grafico, no caso só com a onda de preview
    updateChartSim(_attackRes, _holdRes, _decayReleaseRes, _sustainRes, 180, _amplitudeMax);
}

void ChartWidget::initializeChart() {
    // Cria o grafico
    chart = new QChart();
    chart->legend()->hide();
    chart->setBackgroundBrush(QBrush(Qt::black));        
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::black)); 
    chart->setPlotAreaBackgroundVisible(true);
}

void ChartWidget::initializeAxes() {
    // Eixo Y
    yAxis = new QValueAxis;
    yAxis->setRange(0, 1.1 * _amplitudeMax);
    yAxis->setLinePen(QPen(Qt::white));
    yAxis->setLabelsColor(Qt::white);
    yAxis->setGridLinePen(QPen(Qt::gray));
    
    // Eixo X
    xAxis = new QValueAxis;
    xAxis->setRange(0, 0.33); // Valor inicial
    xAxis->setLinePen(QPen(Qt::white));
    xAxis->setLabelsColor(Qt::white);
    xAxis->setGridLinePen(QPen(Qt::gray));
    
    chart->addAxis(yAxis, Qt::AlignLeft);
    chart->addAxis(xAxis, Qt::AlignBottom);
}

void ChartWidget::initializeSeries() {
    // inicia duas series, uma para os pontos 
    // enviados, e a outra para os pontos de preview
    pontosEnviados = new QLineSeries();
    pontosPreview = new QLineSeries();
    
    // adicionamos essas series ao grafico
    chart->addSeries(pontosPreview);
    chart->addSeries(pontosEnviados);
    
    // comportamos essas serias aos eixos
    pontosEnviados->attachAxis(yAxis);
    pontosEnviados->attachAxis(xAxis);
    pontosPreview->attachAxis(yAxis);
    pontosPreview->attachAxis(xAxis);
}

void ChartWidget::setupChartStyling() {
    // aparenci da linha da serie de preview
    QPen pen1(QColor(100, 100, 0));
    pen1.setWidth(4);
    pontosPreview->setPen(pen1);
    
    // colocamos o grafico na tela
    setRenderHint(QPainter::Antialiasing);
    setChart(chart);
}

void ChartWidget::updateChartSim(int A, int H, int DR, int S, float freq, double _amplitudeMax) {
    //qDebug() << "######################################" << "\n";
    //qDebug() << "Frequencia: " << freq << "\n";

    _attackRes = A;
    _holdRes = H;
    _decayReleaseRes = DR;
    _sustainRes = S;

    //qDebug() << "Resistencia Attack: " << _attackRes << "\n";
    //qDebug() << "Resistencia Hold: " << _holdRes << "\n";
    //qDebug() << "Resistencia Sustain: " << _sustainRes << "\n";

    // calculando a Frequencia em hertz, 
    // e entao encontrando o periodo
    _maxTime = 1/(freq/60);

    // atualizando os eixos para novos valores
    xAxis->setRange(0, _maxTime);
    yAxis->setRange(0, 1.1*_amplitudeMax);

    // limpamos os pontos de preview antigos
    pontosPreview->clear();

    // determinamos como a linha da onda de preview se parece
    QPen pen1(QColor(100, 100, 0));
    pen1.setWidth(4);
    pontosPreview->setPen(pen1);

    // calculando os pontos da onda preview
    holdCalculation();
    sustainCalculation();
    attackCalculation();
    decayCalculation();
    releaseCalculation();

    //qDebug() << "######################################" << "\n";
}

void ChartWidget::updatePontosReais(){
    // limpamos os pontos da onda enviada
    pontosEnviados->clear();

    // determinamos como a linha da onda de preview se parece
    QPen pen(QColor(0, 255, 0));
    pen.setWidth(6); 
    pontosEnviados->setPen(pen);

    // determinamos que os pontos enviados sao 
    // iguais aos pontos de preview atuais
    pontosEnviados->append(pontosPreview->points());
}

void ChartWidget::holdCalculation(){
    int R = _holdRes;

    // formula para encontrar tempo (foi mto dificil calcular isso)
    _holdTime = -log(0.6 * (R * 1000.0 / (R + 1000.0)) * (R + 1000.0) / (R * 5000.0)) * (R * 1000.0 / (R + 1000.0)) * 75e-6;
    //qDebug() << "HoldTime: " << _holdTime << "s" << "\n";
}

void ChartWidget::attackCalculation() {
    double v = 0.0;

    for (int i = 0; i < _resolucao; ++i) {
        // Calcula a fração do tempo atual
        double t = _holdTime * (static_cast<double>(i) / (_resolucao - 1));

        // Fórmula do capacitor carregando
        v = _amplitudeMax * (1.0 - exp(-t / (_attackRes * 1e-6)));

        // Adiciona o ponto na série
        pontosPreview->append(t, v);
    }

    _maxAttackVolt = v;
}

void ChartWidget::sustainCalculation() {
    // o potenciometro é de 10k, logo o outro lado do 
    // potenciometro é 10k menos a resistencia de sustain
    int sustainRComp = 10000-_sustainRes;
    //qDebug() << "Sustain Complement: " << sustainRComp << "\n";

    // Rv = R1 / R1 + R2
    double div = static_cast<double>(_sustainRes)/(sustainRComp + _sustainRes);
    //qDebug() << "Divsor de tensao (Resistencia): " << div << "\n";

    // Vsus = Vtotal * Rv
    _sustainVolt = _amplitudeMax * div;
    //qDebug() << "Sustain Value: " << _sustainVolt << "V" << "\n";
}

void ChartWidget::decayCalculation() {
    int i;

    //qDebug() << "Decay Resistencia: " << _decayReleaseRes << "\n";
    //qDebug() << "_maxTime/2: " << _maxTime/2 << "\n";
    //qDebug() << "_holdTime: " << _holdTime << "\n";

    for (i = 0; i < _resolucao; i++) {
        // O tempo é de decay começa no final do hold.
        // Logo somamos o tempo final do hold mais uma 
        // fracao do tempo até a metade do tempo total.
        double t = _holdTime + (((_maxTime/2)-_holdTime) * (static_cast<double>(i) / (_resolucao - 1)));

        // Fórmula da descarga em um capacitor, com uma tensão final.
        // Aqui vale destacar que como t não começa em zero, 
        // devemos subtrair o tempo de hold de t na fórmula, pois 
        // do contrário ele vai estar calculando essa curva a 
        // partir do zero do grafico.
        double v = _sustainVolt + (_maxAttackVolt - _sustainVolt) * exp(-(t - _holdTime) / (_decayReleaseRes * 1e-6) );

        // Adiciona os pontos à série de preview
        pontosPreview->append(t,v);
    }
}

void ChartWidget::releaseCalculation() {
    int i;

    for (i = 0; i < _resolucao; i++) {
        // o release começa no tempo final do sustain. 
        // Que também é a metade do tempo total.
        // Logo o tempo começa da metade do tempo total, 
        // mais uma fracao do tempo até o final
        double t = (_maxTime/2) + ( (_maxTime/2) *  (static_cast<double>(i) / (_resolucao - 1)) );

        // Fórmula da descarga em capacitor.
        // Que nem no decay, devemos subtrair de t um valor 
        // que quando i = 0, a fórmula entenda que estamos 
        // calculando a tensão para o momento 0.
        double v = _sustainVolt * exp( -(t - (_maxTime/2)) / (_decayReleaseRes * 1e-6) );

        // Adiciona os pontos à série de preview
        pontosPreview->append(t,v);
    }
}

ChartWidget::~ChartWidget() = default;
