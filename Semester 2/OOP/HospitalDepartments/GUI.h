#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include"Service.h"
#include <qformlayout.h>
#include <qlineedit.h>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    QPushButton* addSurgeryBttn;
    QPushButton* addNeonatalBttn;
    Service srv;

    QLineEdit* nameEdit;
    QLineEdit* doctorsEdit;
    QLineEdit* mothersEdit;
    QLineEdit* newbornsEdit;
    QLineEdit* avgEdit;
    

    QLineEdit* surgeryNameEdit;
    QLineEdit* surgeryDoctorsEdit;
    QLineEdit* patientsEdit;

    void list();
    void listEfficient();
    void addSurgery();
    void saveSurgery();
    void addNeonatal();
    void saveNeonatal();
};
