#include "src/resiflow/resiflow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/imgs/imgs/resiflow.ico"));

    ResiFlow w;
    w.show();
    return a.exec();
}
