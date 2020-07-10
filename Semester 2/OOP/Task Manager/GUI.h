#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& srv, QWidget *parent = Q_NULLPTR);

private:
    Service& srv;
    Ui::GUIClass ui;

    void listTasks();

    void duration();
};
