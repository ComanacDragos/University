#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include <qmessagebox.h>

class GUI : public QWidget, public Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, const std::string name, QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    Service& srv;
    std::string name;

    void update()override
    {
        this->loadAnswers();
        this->loadQuestions();
    }

    void loadQuestions();

    void addQuestion();

    void loadAnswers();

    void addAnswer();
};
