#include "controlsWidget.h"

ControlsWidget::ControlsWidget(QWidget *parent)
    : QGroupBox(parent)
{
    init();
}

void ControlsWidget::init() {
    // main layout do widget
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    // nome em cima do widget
    titleLabel = new QLabel("Controles");
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    // layout horizontal para os botoes e combo
    layoutInterface = new QHBoxLayout;

    // botao de send
    sendButton = new QPushButton("Enviar Configuração");
    layoutInterface->addWidget(sendButton);

    // botao de auto trigger
    autoButton = new QPushButton("Modo Manual");
    autoButton->setCheckable(true);
    layoutInterface->addWidget(autoButton);

    // botao de manual trigger
    trigButton = new QPushButton("Trigger");
    layoutInterface->addWidget(trigButton);

    mainLayout->addLayout(layoutInterface);


    // Connects
    connect(sendButton, &QPushButton::clicked, this, &ControlsWidget::sendButtonClicked);

    connect(trigButton, &QPushButton::pressed, this, &ControlsWidget::trigButtonPressed);

    connect(trigButton, &QPushButton::released, this, &ControlsWidget::trigButtonReleased);

    connect(autoButton, &QPushButton::toggled, this, [=](bool checked) {
        // Atualiza o texto
        if (checked) {
            autoButton->setText("Modo Automático");
        } else {
            autoButton->setText("Modo Manual");
        }
    
        // Emite o sinal para o Resiflow
        emit autoModeToggled(checked);
    });


}

bool ControlsWidget::isAutoModeEnabled() const {
    return autoButton->isChecked();
}

ControlsWidget::~ControlsWidget() = default;
