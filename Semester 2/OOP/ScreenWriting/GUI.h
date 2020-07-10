#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include "TableModel.h"
#include "qmessagebox.h"
#include <qtextedit.h>

class GUI : public QWidget, public Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, Writer writer, TableModel* model, QWidget *parent = Q_NULLPTR);

protected:
    Ui::GUIClass ui;
    Service& srv;
    Writer writer;
    TableModel* model;

    void addIdea();
    void update()override
    {
        ui.ideeasView->viewport()->update();
    }

    void developIdeeas();

    void savePlot();
};
