#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "Histogram.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{"Teachers.txt", "Students.txt"};
    Service srv{ repo };

    for (auto t : srv.getTeachers())
    {
        GUI* gui = new GUI{ srv,t };
        gui->show();
    }

    Histogram* histogram = new Histogram{ srv };
    histogram->show();

    return a.exec();
}
