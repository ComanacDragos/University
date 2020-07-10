#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Tests.h"

int main(int argc, char *argv[])
{
    Tests t{};
    QApplication a(argc, argv);
    Repository repo{"Astronomers.txt", "Stars.txt" };
    Service srv{ repo };
    TableModel* model = new TableModel{ srv };

    for (Astronomer& a : srv.getAstronomers())
    {
        GUI* gui = new GUI{ srv,a, model };
        gui->show();
    }

    return a.exec();
}
