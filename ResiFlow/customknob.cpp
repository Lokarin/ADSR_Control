#include "customknob.h"

CustomKnob::CustomKnob(QWidget *parent)
    : QDial(parent),
        knobImage("://imgs/knobShaft.png"),
        caseImage("://imgs/knobCase.png")
{
    setMinimum(0);
    setMaximum(100);
    setWrapping(false);
    setNotchesVisible(false);
    qDebug() << "Imagem carregada:" << !caseImage.isNull();
}

///void CustomKnob::paintEvent(QPaintEvent *) {
///    QPainter painter(this);
///    painter.setRenderHint(QPainter::Antialiasing);
///    painter.setRenderHint(QPainter::SmoothPixmapTransform);
///
///    int side = qMin(width(), height());
///    QPoint center(width() / 2, height() / 2);
///
///    // Centro do widget
///    painter.translate(center);
///
///    // Calcular angulo
///    qreal angle = -135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());
///
///    // Rotacionar sistema de coordenada
///    painter.rotate(angle);
///
///    // Desenhar Imagem Knob Rotacionada
///    QPixmap scaled = knobImage.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation);
///    painter.drawPixmap(-scaled.width() / 2, -scaled.height() / 2, scaled);
///
///    //// Indicação vermelha
///    //painter.setPen(Qt::red);
///    //painter.drawLine(0, 0, 0, -side / 2);  // Line from center to top
///}

void CustomKnob::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    int side = qMin(width(), height());
    QPoint center(width() / 2, height() / 2);
    
    // 1. Desenhar a case estática (fundo) - usando o tamanho completo
    QPixmap scaledCase = caseImage.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap((width() - scaledCase.width()) / 2, 
                      (height() - scaledCase.height()) / 2, 
                      scaledCase);
    
    // 2. Desenhar o knob rotativo (por cima) - usando um tamanho menor
    // Definir o knob para ter por exemplo 80% do tamanho da case
    int knobSize = int(side * 0.65);  // Ajuste este valor conforme necessário
    
    painter.translate(center); // Mover para o centro
    
    // Calcular ângulo
    qreal angle = -135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());
    
    // Rotacionar sistema de coordenada
    painter.rotate(angle);
    
    // Desenhar Imagem Knob Rotacionada com tamanho menor
    QPixmap scaled = knobImage.scaled(knobSize, knobSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(-scaled.width() / 2, -scaled.height() / 2, scaled);
}
