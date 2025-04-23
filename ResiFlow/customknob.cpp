#include "customknob.h"

CustomKnob::CustomKnob(QWidget *parent)
    : QDial(parent), knobImage("://imgs/knob.png")  // Coloque o caminho para a imagem
{
    setMinimum(0);
    setMaximum(100);
    setWrapping(false);
    setNotchesVisible(false);
    qDebug() << "Imagem carregada:" << !knobImage.isNull();
}

void CustomKnob::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int side = qMin(width(), height());
    QPoint center(width() / 2, height() / 2);

    // Centro do widget
    painter.translate(center);

    // Calcular angulo
    qreal angle = -135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());

    // Rotacionar sistema de coordenada
    painter.rotate(angle);

    // Desenhar Imagem Knob Rotacionada
    QPixmap scaled = knobImage.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(-scaled.width() / 2, -scaled.height() / 2, scaled);

    //// Indicação vermelha
    //painter.setPen(Qt::red);
    //painter.drawLine(0, 0, 0, -side / 2);  // Line from center to top
}

