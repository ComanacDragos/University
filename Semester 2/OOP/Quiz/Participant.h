#pragma once

#include <QWidget>
#include "ui_Participant.h"
#include "Service.h"
#include "qmessagebox.h"

class ParticipantGUI : public QWidget, public Observer
{
	Q_OBJECT

public:
	ParticipantGUI(Service& srv, Participant p, QWidget *parent = Q_NULLPTR);
	~ParticipantGUI();

	void listQuestions();
	void update()override;
	void answer();

private:
	Ui::Participant ui;
	Service& srv;
	Participant participant;
	std::vector<int> answeredQuestions;
};
