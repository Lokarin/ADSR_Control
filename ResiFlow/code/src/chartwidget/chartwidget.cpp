#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent),
    _amplitudeMax(5), _maxTime(0.33), _resolucao(25),
    _attackRes(1), _holdRes(1), _decayReleaseRes(1), _sustainRes(1)
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

void ChartWidget::updateChartSim(int atk, int hold, int sus, int rel, float freq, double _amplitudeMax) {
    //qDebug() << "######################################" << "\n";
    //qDebug() << "Frequencia: " << freq << "\n";

    _attackRes = atk;
    _holdRes = hold;
    _decayReleaseRes = rel;
    _sustainRes = sus;

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
    pontosPreview->clear(); // remove se já estiver limpa antes

    // Estimativa de tempo necessário até atingir sustain (caso necessário)
    double tempoFinalAttack = _holdTime;
    double t, step;

    // Primeira tentativa com tempo padrão
    for (int i = 0; i < _resolucao; ++i) {
        t = _holdTime * (static_cast<double>(i) / (_resolucao - 1));
        v = _amplitudeMax * (1.0 - exp(-t / (_attackRes * 1e-6)));

        pontosPreview->append(t, v);
    }

    _maxAttackVolt = v;

    // Se sustain > valor final do attack, significa que o attack deve continuar
    if (_sustainVolt > _maxAttackVolt) {
        double vAttack = _maxAttackVolt;
        t = _holdTime;
        step = (_maxTime / 200.0); // passo pequeno para interpolação suave

        while (vAttack < _sustainVolt && t < _maxTime / 2) {
            t += step;
            vAttack = _amplitudeMax * (1.0 - exp(-t / (_attackRes * 1e-6)));
            pontosPreview->append(t, vAttack);
        }

        _maxAttackVolt = vAttack;
        _holdTime = t; // nova duração real da fase de attack
        _minDecayVolt = vAttack;
    }
}

void ChartWidget::sustainCalculation() {
    // o potenciometro é de 100k, logo o outro lado do 
    // potenciometro é 100k menos a resistencia de sustain
    int sustainRComp = 100000-_sustainRes;
    //qDebug() << "Sustain Complement: " << sustainRComp << "\n";

    // Rv = R1 / R1 + R2
    double div = static_cast<double>(sustainRComp)/(sustainRComp + _sustainRes);
    //qDebug() << "Divsor de tensao (Resistencia): " << div << "\n";

    // Vsus = Vtotal * Rv
    _sustainVolt = _amplitudeMax * div;
    //qDebug() << "Sustain Value: " << _sustainVolt << "V" << "\n";
}

void ChartWidget::decayCalculation() {
    int i;
    double v;

    //qDebug() << "Decay Resistencia: " << _decayReleaseRes << "\n";
    //qDebug() << "_maxTime/2: " << _maxTime/2 << "\n";
    //qDebug() << "_holdTime: " << _holdTime << "\n";
    //qDebug() << "_sustainVolt: " << _sustainVolt << "\n";
    //qDebug() << "_maxAttackVolt: " << _maxAttackVolt << "\n";

    for (i = 0; i < _resolucao; i++) {
        double t = _holdTime + (((_maxTime / 2) - _holdTime) * (static_cast<double>(i) / (_resolucao - 1)));

        if (_sustainVolt >= _maxAttackVolt) {
            return;
        } else {
            // Decaimento exponencial padrão
            v = _sustainVolt + (_maxAttackVolt - _sustainVolt) * exp(-(t - _holdTime) / (_decayReleaseRes * 1e-6));
        }

        pontosPreview->append(t, v);
    }

    _minDecayVolt = v;
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
        double v = _minDecayVolt * exp( -(t - (_maxTime/2)) / (_decayReleaseRes * 1e-6) );

        // Adiciona os pontos à série de preview
        pontosPreview->append(t,v);
    }
}

QVector<QPointF> ChartWidget::getPontos() const {
    return pontosEnviados->points();
}

bool ChartWidget::saveChartAsImage(const QString &filePath) {
    QImage image(128, 64, QImage::Format_RGB32);
    image.fill(Qt::black); // fundo branco

    QPainter p(&image);
    p.setPen(QPen(Qt::white, 1));
    p.setRenderHint(QPainter::LosslessImageRendering);

    QVector<QPointF> pontos = getPontos();
    if (pontos.isEmpty()) {
        qDebug() << "Nenhum ponto encontrado em pontosEnviados";
        return false;
    }

    qDebug() << "Número de pontos:" << pontos.size();
    qDebug() << "Primeiro ponto:" << pontos.first();
    qDebug() << "Último ponto:" << pontos.last();
    qDebug() << "_maxTime:" << _maxTime;
    qDebug() << "_amplitudeMax:" << _amplitudeMax;

    // Mapeamento manual: transforma (tempo, voltagem) em (x, y da imagem)
    QPoint lastMapped;
    bool firstPoint = true;
    
    // Debug mais detalhado dos primeiros 10 pontos
    qDebug() << "=== ANÁLISE DOS PRIMEIROS 10 PONTOS ===";
    for (int i = 0; i < qMin(10, pontos.size()); ++i) {
        qDebug() << QString("Ponto %1: x=%2, y=%3").arg(i).arg(pontos[i].x(), 0, 'e', 6).arg(pontos[i].y());
    }
    
    // Encontrar os valores mínimos e máximos reais dos pontos
    double minX = pontos.first().x();
    double maxX = pontos.first().x();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();
    
    for (const auto& ponto : pontos) {
        minX = qMin(minX, ponto.x());
        maxX = qMax(maxX, ponto.x());
        minY = qMin(minY, ponto.y());
        maxY = qMax(maxY, ponto.y());
    }
    
    qDebug() << "Range X real:" << minX << "a" << maxX;
    qDebug() << "Range Y real:" << minY << "a" << maxY;
    
    // Se o range X for muito pequeno, usar índice dos pontos
    bool useIndex = (maxX - minX) < 1e-3;  // Se menor que 1ms
    if (useIndex) {
        qDebug() << "Range X muito pequeno, usando índice dos pontos";
    }
    
    for (int i = 0; i < pontos.size(); ++i) {
        double xData = pontos[i].x();
        double yData = pontos[i].y();

        int xImg, yImg;
        
        if (useIndex) {
            // Usar o índice do ponto para distribuir uniformemente
            xImg = static_cast<int>((static_cast<double>(i) / (pontos.size() - 1)) * (image.width() - 1));
        } else {
            // Mapear usando o range real dos dados
            xImg = static_cast<int>(((xData - minX) / (maxX - minX)) * (image.width() - 1));
        }
        
        yImg = static_cast<int>(((maxY - yData) / (maxY - minY)) * (image.height() - 1));

        // Clamping adicional para coordenadas da imagem
        xImg = qMax(0, qMin(xImg, image.width() - 1));
        yImg = qMax(0, qMin(yImg, image.height() - 1));

        QPoint pontoImg(xImg, yImg);

        if (firstPoint) {
            // Para o primeiro ponto, desenha um pixel
            p.drawPoint(pontoImg);
            firstPoint = false;
        } else {
            p.drawLine(lastMapped, pontoImg);  // desenha linha entre os pontos
        }

        lastMapped = pontoImg;
        
        // Debug dos primeiros pontos
        if (i < 5) {
            qDebug() << QString("Ponto %1: (%2, %3) -> (%4, %5)")
                        .arg(i).arg(xData).arg(yData).arg(xImg).arg(yImg);
        }
    }

    // Converter para monocromático antes de salvar
    QImage monoImage = image.convertToFormat(QImage::Format_Mono);
    
    // Salva a imagem e verifica se foi bem-sucedido
    bool success = monoImage.save(filePath, "BMP");
    if (success) {
        qDebug() << "Imagem salva com sucesso:" << filePath;
    } else {
        qDebug() << "Erro ao salvar imagem:" << filePath;
    }

    return success;
}

bool ChartWidget::saveChartAsBinary(const QString &filePath) {
    const int WIDTH = 128;
    const int HEIGHT = 64;
    
    // Criar array de bits (1 bit por pixel)
    // 128x64 = 8192 bits = 1024 bytes
    QByteArray imageData(WIDTH * HEIGHT / 8, 0x00); // Inicializa com 0 (preto)
    
    QVector<QPointF> pontos = getPontos();
    if (pontos.isEmpty()) {
        qDebug() << "Nenhum ponto encontrado em pontosEnviados";
        return false;
    }

    // Encontrar os valores mínimos e máximos reais dos pontos
    double minX = pontos.first().x();
    double maxX = pontos.first().x();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();
    
    for (const auto& ponto : pontos) {
        minX = qMin(minX, ponto.x());
        maxX = qMax(maxX, ponto.x());
        minY = qMin(minY, ponto.y());
        maxY = qMax(maxY, ponto.y());
    }
    
    qDebug() << "Salvando formato binário - Range X:" << minX << "a" << maxX;
    qDebug() << "Range Y:" << minY << "a" << maxY;
    
    // Se o range X for muito pequeno, usar índice dos pontos
    bool useIndex = (maxX - minX) < 1e-3;
    if (useIndex) {
        qDebug() << "Usando índice dos pontos para distribuição X";
    }
    
    // Função para definir um pixel (x, y) como branco (1)
    auto setPixel = [&](int x, int y) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            int byteIndex = (y * WIDTH + x) / 8;
            int bitIndex = 7 - ((y * WIDTH + x) % 8); // MSB primeiro
            imageData[byteIndex] |= (1 << bitIndex);
        }
    };
    
    // Mapear pontos e desenhar linha
    QPoint lastPoint;
    bool firstPoint = true;
    
    for (int i = 0; i < pontos.size(); ++i) {
        double xData = pontos[i].x();
        double yData = pontos[i].y();

        int xImg, yImg;
        
        if (useIndex) {
            xImg = static_cast<int>((static_cast<double>(i) / (pontos.size() - 1)) * (WIDTH - 1));
        } else {
            xImg = static_cast<int>(((xData - minX) / (maxX - minX)) * (WIDTH - 1));
        }
        
        yImg = static_cast<int>(((maxY - yData) / (maxY - minY)) * (HEIGHT - 1));
        
        // Clamping
        xImg = qMax(0, qMin(xImg, WIDTH - 1));
        yImg = qMax(0, qMin(yImg, HEIGHT - 1));
        
        QPoint currentPoint(xImg, yImg);
        
        if (firstPoint) {
            setPixel(xImg, yImg);
            firstPoint = false;
        } else {
            // Desenhar linha usando algoritmo de Bresenham simplificado
            drawLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), setPixel);
        }
        
        lastPoint = currentPoint;
    }
    
    // Salvar arquivo binário
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Erro ao abrir arquivo para escrita:" << filePath;
        return false;
    }
    
    qint64 bytesWritten = file.write(imageData);
    file.close();
    
    if (bytesWritten == imageData.size()) {
        qDebug() << "Arquivo binário salvo com sucesso:" << filePath;
        qDebug() << "Tamanho:" << bytesWritten << "bytes";
        return true;
    } else {
        qDebug() << "Erro na escrita do arquivo";
        return false;
    }
}

// Método auxiliar para desenhar linha (algoritmo de Bresenham simplificado)
void ChartWidget::drawLine(int x0, int y0, int x1, int y1, std::function<void(int, int)> setPixel) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    int x = x0, y = y0;
    
    while (true) {
        setPixel(x, y);
        
        if (x == x1 && y == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

bool ChartWidget::saveChartAsCArray(const QString &filePath) {
    const int WIDTH = 128;
    const int HEIGHT = 64;
    
    // Criar array de bits (1 bit por pixel)
    QByteArray imageData(WIDTH * HEIGHT / 8, 0x00); // Inicializa com 0 (preto)
    
    QVector<QPointF> pontos = getPontos();
    if (pontos.isEmpty()) {
        qDebug() << "Nenhum ponto encontrado em pontosEnviados";
        return false;
    }

    // Encontrar os valores mínimos e máximos reais dos pontos
    double minX = pontos.first().x();
    double maxX = pontos.first().x();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();
    
    for (const auto& ponto : pontos) {
        minX = qMin(minX, ponto.x());
        maxX = qMax(maxX, ponto.x());
        minY = qMin(minY, ponto.y());
        maxY = qMax(maxY, ponto.y());
    }
    
    qDebug() << "Salvando C Array - Range X:" << minX << "a" << maxX;
    qDebug() << "Range Y:" << minY << "a" << maxY;
    
    // Se o range X for muito pequeno, usar índice dos pontos
    bool useIndex = (maxX - minX) < 1e-3;
    if (useIndex) {
        qDebug() << "Usando índice dos pontos para distribuição X";
    }
    
    // Função para definir um pixel (x, y) como branco (1)
    auto setPixel = [&](int x, int y) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            int byteIndex = (y * WIDTH + x) / 8;
            int bitIndex = 7 - ((y * WIDTH + x) % 8); // MSB primeiro
            imageData[byteIndex] |= (1 << bitIndex);
        }
    };
    
    // Mapear pontos e desenhar linha
    QPoint lastPoint;
    bool firstPoint = true;
    
    for (int i = 0; i < pontos.size(); ++i) {
        double xData = pontos[i].x();
        double yData = pontos[i].y();

        int xImg, yImg;
        
        if (useIndex) {
            xImg = static_cast<int>((static_cast<double>(i) / (pontos.size() - 1)) * (WIDTH - 1));
        } else {
            xImg = static_cast<int>(((xData - minX) / (maxX - minX)) * (WIDTH - 1));
        }
        
        yImg = static_cast<int>(((maxY - yData) / (maxY - minY)) * (HEIGHT - 1));
        
        // Clamping
        xImg = qMax(0, qMin(xImg, WIDTH - 1));
        yImg = qMax(0, qMin(yImg, HEIGHT - 1));
        
        QPoint currentPoint(xImg, yImg);
        
        if (firstPoint) {
            setPixel(xImg, yImg);
            firstPoint = false;
        } else {
            // Desenhar linha usando algoritmo de Bresenham simplificado
            drawLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), setPixel);
        }
        
        lastPoint = currentPoint;
    }
    
    // Salvar como array C
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erro ao abrir arquivo para escrita:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out << "// Imagem 128x64 em formato binário\n";
    out << "// 1 bit por pixel, 1024 bytes total\n";
    out << "const unsigned char image_data[1024] PROGMEM = {\n";
    
    for (int i = 0; i < imageData.size(); ++i) {
        if (i % 16 == 0) out << "  ";
        out << QString("0x%1").arg(static_cast<unsigned char>(imageData[i]), 2, 16, QChar('0'));
        if (i < imageData.size() - 1) out << ",";
        if (i % 16 == 15) out << "\n";
    }
    
    out << "};\n";
    file.close();
    
    qDebug() << "Array C salvo:" << filePath;
    return true;
}

void ChartWidget::debugPontos() {
    qDebug() << "=== DEBUG PONTOS ===";
    qDebug() << "pontosEnviados->points().size():" << pontosEnviados->points().size();
    qDebug() << "pontosPreview->points().size():" << pontosPreview->points().size();
    qDebug() << "_maxTime:" << _maxTime;
    qDebug() << "_amplitudeMax:" << _amplitudeMax;
    
    if (!pontosEnviados->points().isEmpty()) {
        auto pontos = pontosEnviados->points();
        qDebug() << "Primeiro ponto enviado:" << pontos.first();
        qDebug() << "Último ponto enviado:" << pontos.last();
    }
}

ChartWidget::~ChartWidget() = default;
