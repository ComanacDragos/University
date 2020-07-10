#pragma once

#include <QWidget>
#include "ui_Tester.h"
#include "Service.h"
#include "Observer.h"

class Tester : public QWidget
{
	Q_OBJECT

public:
	Tester(Service& srv, User& user, QWidget *parent = Q_NULLPTR);
	~Tester();

private:
	Service& srv;
	User user;
	Ui::Tester ui;
};
