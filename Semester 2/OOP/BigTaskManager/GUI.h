#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include "qmessagebox.h"

class GUI : public QWidget, Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, Programmer programmer, QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    Service& srv;
    Programmer programmer;

    void loadData();
    void update()override { this->loadData(); }

    void addTask();
    void removeTask();
    void startTask();
    void closeTask();
};
