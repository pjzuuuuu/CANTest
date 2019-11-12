#include "cantestmmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CANTestmMainWindow w;
    w.show();

    return a.exec();
}
