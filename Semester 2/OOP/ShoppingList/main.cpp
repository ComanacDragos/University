#include "GUI.h"
#include <QtWidgets/QApplication>
#include "tests.h"
int main(int argc, char *argv[])
{
    testDelete();
    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}
