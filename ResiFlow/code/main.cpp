#include "resiflow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ResiFlow w;
    w.show();
    return a.exec();
}
