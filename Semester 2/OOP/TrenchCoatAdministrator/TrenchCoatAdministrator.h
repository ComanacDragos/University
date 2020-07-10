#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrenchCoatAdministrator.h"

class TrenchCoatAdministrator : public QMainWindow
{
	Q_OBJECT

public:
	TrenchCoatAdministrator(QWidget *parent = Q_NULLPTR);

private:
	Ui::TrenchCoatAdministratorClass ui;
};
