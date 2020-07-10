#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    testService();
    QApplication a(argc, argv);
    Service srv{ "file.txt" };
    GUI w{ srv };
    w.show();
    return a.exec();
}
