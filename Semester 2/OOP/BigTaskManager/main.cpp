#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
int main(int argc, char *argv[])
{
    Tests t{};
    QApplication a(argc, argv);
    Repository repo{ "Programmers.txt", "Tasks.txt" };
    Service srv{ repo };

    for (Programmer& p : srv.getProgrammers())
    {
        GUI* gui = new GUI{ srv,p };
        gui->show();
    }

    return a.exec();
}
