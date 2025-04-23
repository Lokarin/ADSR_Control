#include "customknob.h"

CustomKnob::CustomKnob(QWidget *parent)
    : QDial(parent), knobImage("://imgs/knob.png")  // Coloque o caminho para a imagem
{
    setMinimum(0);
    setMaximum(100);
    setWrapping(false);
    setNotchesVisible(false);
    qDebug() << "Imagem carregada:" << !knobImage.isNull(); // <- Aqui!
}

void CustomKnob::paintEvent(QPaintEvent *) {
    //() << "paintEvent chamado!";

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int side = qMin(width(), height());
    QPoint center(width() / 2, height() / 2);

    // Translada e rotaciona de acordo com o valor do knob
    painter.translate(center);

    // ângulo de rotação do ponteiro (270º de sweep total, começa em -135º)
    qreal angle = 135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());
    painter.rotate(angle);

    painter.drawPixmap(-side / 2, -side / 2, side, side, knobImage);

}

