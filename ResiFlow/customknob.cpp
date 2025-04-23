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

void CustomKnob::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    int side = qMin(width(), height());
    QPoint center(width() / 2, height() / 2);
    
    // Desenhar Case Estática
    QPixmap scaledCase = caseImage.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap((width() - scaledCase.width()) / 2, 
                      (height() - scaledCase.height()) / 2, 
                      scaledCase);
    
    // Desenhar Knob Shaft
    int knobSize = int(side * 0.65);
    
    // Mover para o centro
    painter.translate(center);
    
    // Calcular ângulo
    qreal angle = -135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());
    
    // Rotacionar sistema de coordenada
    painter.rotate(angle);
    
    // Desenhar Imagem Knob Rotacionada com tamanho menor
    QPixmap scaled = knobImage.scaled(knobSize, knobSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(-scaled.width() / 2, -scaled.height() / 2, scaled);
}
