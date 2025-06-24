#ifndef KNOBSWIDGET_H
#define KNOBSWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "customknob/customknob.h"

QT_USE_NAMESPACE

class KnobsWidget : public QGroupBox {
    Q_OBJECT

public:
    KnobsWidget(QWidget *parent = nullptr);
    ~KnobsWidget();
    QVector<int> getKnobValues() const;
    void setKnobValues(const QVector<int> &valores);

private:
    QHBoxLayout * mainLayout;
    QStringList knobNames;
    QMap<QString, CustomKnob*> knobs;

    void init();

signals:
    void knobsChanged();
};

#endif // KNOBSWIDGET_H
