#ifndef CUSTOMKNOB_H
#define CUSTOMKNOB_H

#include <QDial>
#include <QPainter>
#include <QPixmap>

class CustomKnob : public QDial {
    Q_OBJECT

public:
    explicit CustomKnob(QWidget *parent = nullptr);

private:
    QPixmap knobImage;
    QPixmap caseImage;
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOMKNOB_H
