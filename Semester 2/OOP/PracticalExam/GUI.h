#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include <qmessagebox.h>
#include "TableModel.h"
#include "Painter.h"
#include <qsortfilterproxymodel.h>
#include "FilterModel.h"

class GUI : public QWidget, public Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, Astronomer a,TableModel* model, QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    Service& srv;
    Astronomer astronomer;
    TableModel* model;
    TableModel* allModel;
    FilterModel* filterModel;
    
    
    void loadStars();

    void update()override
    {
        this->loadStars();
        ui.starsView->viewport()->update();
    }
    void addStar();

    void viewStar();

    void checkBox();
};
