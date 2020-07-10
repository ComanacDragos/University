/********************************************************************************
** Form generated from reading UI file 'lecture9_demo_hello_world.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE9_DEMO_HELLO_WORLD_H
#define UI_LECTURE9_DEMO_HELLO_WORLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture9_demo_Hello_worldClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture9_demo_Hello_worldClass)
    {
        if (Lecture9_demo_Hello_worldClass->objectName().isEmpty())
            Lecture9_demo_Hello_worldClass->setObjectName(QString::fromUtf8("Lecture9_demo_Hello_worldClass"));
        Lecture9_demo_Hello_worldClass->resize(600, 400);
        menuBar = new QMenuBar(Lecture9_demo_Hello_worldClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lecture9_demo_Hello_worldClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture9_demo_Hello_worldClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture9_demo_Hello_worldClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lecture9_demo_Hello_worldClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lecture9_demo_Hello_worldClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lecture9_demo_Hello_worldClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture9_demo_Hello_worldClass->setStatusBar(statusBar);

        retranslateUi(Lecture9_demo_Hello_worldClass);

        QMetaObject::connectSlotsByName(Lecture9_demo_Hello_worldClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture9_demo_Hello_worldClass)
    {
        Lecture9_demo_Hello_worldClass->setWindowTitle(QCoreApplication::translate("Lecture9_demo_Hello_worldClass", "Lecture9_demo_Hello_world", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture9_demo_Hello_worldClass: public Ui_Lecture9_demo_Hello_worldClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE9_DEMO_HELLO_WORLD_H
