#include "Presenter.h"
#include "ParticipantWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    testScore();
    testAdd();
    Repository repo{ "Questions.txt", "Participants.txt" };
    Service srv{ repo };

    for (Participant& p : srv.getParticipants())
    {
        ParticipantWindow* participant = new ParticipantWindow{ srv, p.getName() };
        srv.addObserver(participant);
        participant->show();
    }
    Presenter p{ srv };
    p.show();
    return a.exec();
}
