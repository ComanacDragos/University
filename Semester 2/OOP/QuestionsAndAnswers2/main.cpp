#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Search.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "Users.txt", "Questions.txt", "Answers.txt" };
    Service srv{ repo };

    for (auto& user : srv.getUsers())
    {
        GUI* gui = new GUI{ srv,user };
        gui->show();
    }
    Search* search = new Search{ srv };
    search->show();
    
    return a.exec();
}
