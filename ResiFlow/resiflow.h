#ifndef RESIFLOW_H
#define RESIFLOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ResiFlow; }
QT_END_NAMESPACE

class ResiFlow : public QMainWindow
{
    Q_OBJECT

public:
    ResiFlow(QWidget *parent = nullptr);
    ~ResiFlow();

private:
    Ui::ResiFlow *ui;
};
#endif // RESIFLOW_H

// TESTE
