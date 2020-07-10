#include <QtWidgets/QApplication>
#include "Tester.h"
#include "Programmer.h"

int main(int argc, char* argv[])
{
    TestRepo();
    TestResolve();
    QApplication a(argc, argv);
    Repository repo{ "Issues.txt","Users.txt" };
    Service srv{ repo };

    for (User& u : srv.getUsers())
    {
        if (u.getType() == "tester")
        {
            Tester* tester = new Tester{ srv, u };
            tester->show();
        }
        else
        {
            Programmer* programmer = new Programmer{ srv,u };
            programmer->show();
        }
    }
    return a.exec();
}
