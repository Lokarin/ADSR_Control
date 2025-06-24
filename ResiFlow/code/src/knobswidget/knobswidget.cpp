#include "knobswidget.h"

KnobsWidget::KnobsWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

void KnobsWidget::init() {
    this->setMinimumHeight(200);
    mainLayout = new QHBoxLayout(this);
    knobNames = {"Attack", "Hold", "Sustain", "Decay/Release"};

    for (const QString &nome : knobNames) {
        QVBoxLayout * knobAndTextLayout = new QVBoxLayout;
        CustomKnob * knob = new CustomKnob;

        knob->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        knob->setValue(0);
        knob->setMaximum(255);

        QLabel * knobLabel = new QLabel(nome + ": " + QString::number(knob->value()));
        knobLabel->setAlignment(Qt::AlignCenter);

        knobs[nome] = knob;

        connect(knob, &QDial::valueChanged, this, [=](int value){
            knobLabel->setText(QString("%1: %2").arg(nome).arg(value));
            emit knobsChanged();
        });

        knobAndTextLayout->addWidget(knob);
        knobAndTextLayout->addWidget(knobLabel);

        mainLayout->addLayout(knobAndTextLayout);
    }
    knobs["Sustain"]->setValue(255);
}

QVector<int> KnobsWidget::getKnobValues() const {
    QVector<int> valores;
    for (const QString &nome : knobNames) {
        valores.append(knobs.value(nome)->value());
    }
    return valores;
}

void KnobsWidget::setKnobValues(const QVector<int> &valores) {
    for (int i = 0; i < knobNames.size() && i < valores.size(); ++i) {
        knobs[knobNames[i]]->setValue(valores[i]);
    }
}

KnobsWidget::~KnobsWidget() = default;
