/********************************************************************************
** Form generated from reading UI file 'lecture9_demo_widgets.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE9_DEMO_WIDGETS_H
#define UI_LECTURE9_DEMO_WIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture9_demo_widgetsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture9_demo_widgetsClass)
    {
        if (Lecture9_demo_widgetsClass->objectName().isEmpty())
            Lecture9_demo_widgetsClass->setObjectName(QString::fromUtf8("Lecture9_demo_widgetsClass"));
        Lecture9_demo_widgetsClass->resize(600, 400);
        menuBar = new QMenuBar(Lecture9_demo_widgetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lecture9_demo_widgetsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture9_demo_widgetsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture9_demo_widgetsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lecture9_demo_widgetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lecture9_demo_widgetsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lecture9_demo_widgetsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture9_demo_widgetsClass->setStatusBar(statusBar);

        retranslateUi(Lecture9_demo_widgetsClass);

        QMetaObject::connectSlotsByName(Lecture9_demo_widgetsClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture9_demo_widgetsClass)
    {
        Lecture9_demo_widgetsClass->setWindowTitle(QCoreApplication::translate("Lecture9_demo_widgetsClass", "Lecture9_demo_widgets", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture9_demo_widgetsClass: public Ui_Lecture9_demo_widgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE9_DEMO_WIDGETS_H
