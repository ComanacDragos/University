#pragma once
#include "Service.h"
#include <QWidget>
#include "ui_EditWindow.h"

class EditWindow : public QWidget
{
	Q_OBJECT

public:
	EditWindow(Service& srv, const std::string& teacher, QWidget *parent = Q_NULLPTR);
	~EditWindow();

private:
	Service& srv;
	std::string teacher;
	Ui::EditWindow ui;

	void loadData();

	void save();
};
