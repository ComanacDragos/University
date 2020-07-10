#pragma once

#include <QWidget>
#include "ui_Programmer.h"
#include "Service.h"
#include "Observer.h"

class Programmer : public QWidget, public Observer
{
	Q_OBJECT

public:
	Programmer(Service& srv, User& user, QWidget* parent = Q_NULLPTR);
	~Programmer();

private:
	Service& srv;
	User user;
	Ui::Programmer ui;

	void loadData();
	void update()override;
	void removeIssue();

	void resolveIssue();
};
