#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Test.h"

int main(int argc, char *argv[])
{
    testNrCars();
    QApplication a(argc, argv);
    Service srv{ "file.txt" };
    GUI w{ srv };
    w.show();
    return a.exec();
}
