#pragma once

#include <QtWidgets/QWidget>
#include "ui_Presenter.h"
#include "Observer.h"
#include "Service.h"
#include <qmessagebox.h>

class Presenter : public QWidget
{
    Q_OBJECT

public:
    Presenter(Service& service,QWidget *parent = Q_NULLPTR);

    void loadData();
    void addQuestion();

private:
    Ui::PresenterClass ui;
    Service& srv;
};
