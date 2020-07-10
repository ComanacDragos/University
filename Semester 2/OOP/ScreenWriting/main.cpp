#include "GUI.h"
#include "Senior.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    testAcceptIdea();
    testAddIdeea();
    QApplication a(argc, argv);
    Repository repo{ "Writer.txt", "Ideeas.txt" };
    Service srv{ repo };

    TableModel* model = new TableModel{ srv };
    for (Writer& wr : srv.getWriters())
    {
        if (wr.getExpertise() == "Senior")
        {
            Senior* senior = new Senior{ srv,wr, model };
            senior->show();
        }
        else
        {
            GUI* gui = new GUI{ srv,wr, model };
            gui->show();
        }
    }
    return a.exec();
}
