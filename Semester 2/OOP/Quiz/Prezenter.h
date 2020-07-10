#pragma once

#include <QtWidgets/QWidget>
#include "ui_Prezenter.h"
#include "Service.h"
#include <qmessagebox.h>

class Prezenter : public QWidget
{
    Q_OBJECT

public:
    Prezenter(Service& srv, QWidget *parent = Q_NULLPTR);
    void listQuestions();
    void addQuestion();

private:
    Ui::PrezenterClass ui;
    Service& srv;
};
