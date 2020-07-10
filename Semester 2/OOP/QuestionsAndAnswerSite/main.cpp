#include "UserGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "Users.txt", "Questions.txt","Answers.txt" };
    Service srv{ repo };

    for (auto& name : srv.getUsers())
    {
        UserGUI* user = new UserGUI{ srv,name };
        user->show();
    }

    SearchWindow* window = new SearchWindow{ srv };
    window->show();

    return a.exec();
}
