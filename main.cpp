#include "BreakTimer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BreakTimer w;
    w.show();
    return a.exec();
}

