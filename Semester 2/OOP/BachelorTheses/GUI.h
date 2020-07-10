#pragma once

#include <QtWidgets/QWidget>
#include "Service.h"
#include "ui_GUI.h"
#include "EditWindow.h"

class GUI : public QWidget, public Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, const std::string& name, QWidget *parent = Q_NULLPTR);

private:
    Service& srv;
    std::string name;
    Ui::GUIClass ui;

    void loadStudents();
    void loadSearchedStudents();
    void update()override { this->loadStudents(); loadSearchedStudents(); }
    void selectStudent();
};
