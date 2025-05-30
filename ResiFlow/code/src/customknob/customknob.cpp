#include "customknob.h"

CustomKnob::CustomKnob(QWidget *parent)
    : QDial(parent),
        knobImage(":/imgs/imgs/knobShaft2.png"),
        caseImage(":/imgs/imgs/knobCase.png")
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

    const int side = qMin(width(), height());
    const QPoint center(width() / 2, height() / 2);

    // Desenha a case
    const QPixmap scaledCase = caseImage.scaled(side, side, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    const QPoint topLeft((width() - scaledCase.width()) / 2, (height() - scaledCase.height()) / 2);
    painter.drawPixmap(topLeft, scaledCase);

    // Desenha a shaft
    painter.translate(center);

    const qreal angle = -135.0 + 270.0 * (value() - minimum()) / (maximum() - minimum());
    painter.rotate(angle);

    const int knobSize = int(side * 0.65);
    const QPixmap scaledKnob = knobImage.scaled(knobSize, knobSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(-scaledKnob.width() / 2, -scaledKnob.height() / 2, scaledKnob);
}
