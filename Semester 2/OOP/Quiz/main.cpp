#include "Prezenter.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Participant.h"
#include "Prezenter.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Service srv;
    for (Participant& p : srv.getParticipants())
    {
        ParticipantGUI* participantGUI = new ParticipantGUI{ srv, p } ;
        srv.addObserver(participantGUI);
        participantGUI->show();
    }
    Prezenter* presenter = new Prezenter{ srv };
    presenter->show();

    return a.exec();
}
