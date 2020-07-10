#pragma once

#include <QWidget>
#include "ui_Tester.h"
#include "Service.h"
#include "Observer.h"
#include <algorithm>
#include <qmessagebox.h>

class Tester : public QWidget, public Observer
{
	Q_OBJECT

public:
	Tester(Service& srv, User& user, QWidget* parent = Q_NULLPTR);
	~Tester();

private:
	Service& srv;
	User user;
	Ui::TesterClass ui;

	void loadData();
	void update() override;
	void addIssue();
	void removeIssue() {
		this->srv.removeIssue(ui.descriptionEdit->text().toStdString());
	}
};
