#pragma once

#include <QtWidgets/QWidget>
#include "ui_UserGUI.h"
#include "Service.h"
#include <utility>
#include "SearchWindow.h"
#include <qmessagebox.h>

class UserGUI : public QWidget, public Observer
{
    Q_OBJECT

public:
    UserGUI(Service& srv, const std::string user,QWidget *parent = Q_NULLPTR);

private:
    Ui::UserGUIClass ui;
    Service& srv;
    std::string user;
    int idSelectedQ=-1;

    void update()override
    {
        this->loadAnswers();
        this->loadQuestions();
    }

    void loadQuestions();
    void addQuestion();
    void addAnswer();

    void setVotes();

    void setSpinBox();

    void loadAnswers();
};
