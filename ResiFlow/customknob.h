#ifndef CUSTOMKNOB_H
#define CUSTOMKNOB_H

#include <QDial>
#include <QPainter>
#include <QPixmap>

class CustomKnob : public QDial {
    Q_OBJECT

public:
    explicit CustomKnob(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap knobImage;
    QPixmap caseImage;
};

#endif // CUSTOMKNOB_H

