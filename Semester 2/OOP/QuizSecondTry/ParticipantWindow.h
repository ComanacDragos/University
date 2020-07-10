#pragma once

#include <QWidget>
#include "ui_ParticipantWindow.h"
#include "Observer.h"
#include "Service.h"
#include <qmessagebox.h>

class ParticipantWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ParticipantWindow(Service& service, const std::string& name, QWidget *parent = Q_NULLPTR);
	~ParticipantWindow();

	void update() override { this->loadData(); }
	void loadData();
	void answer();
private:
	Ui::ParticipantWindow ui;
	Service& srv;
	std::string name;
	std::vector<int> answeredQuestions;
};
