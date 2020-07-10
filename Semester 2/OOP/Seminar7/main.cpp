#include "Chat.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatSession session;
    User user1{ "1","user1" };
    User user2{ "2","user2" };
    User user3{ "3","user3" };
    Chat* chat1 = new Chat{ session, user1 };
    Chat* chat2 = new Chat{ session, user2 };
    Chat* chat3 = new Chat{ session, user3 };
    session.addObserver(chat1);
    session.addObserver(chat2);
    session.addObserver(chat3);

    chat1->show();
    chat2->show();
    chat3->show();
    return a.exec();
}
