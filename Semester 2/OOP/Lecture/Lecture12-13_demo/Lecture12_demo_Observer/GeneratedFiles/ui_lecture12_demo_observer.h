/********************************************************************************
** Form generated from reading UI file 'lecture12_demo_observer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE12_DEMO_OBSERVER_H
#define UI_LECTURE12_DEMO_OBSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture12_demo_ObserverClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture12_demo_ObserverClass)
    {
        if (Lecture12_demo_ObserverClass->objectName().isEmpty())
            Lecture12_demo_ObserverClass->setObjectName(QString::fromUtf8("Lecture12_demo_ObserverClass"));
        Lecture12_demo_ObserverClass->resize(600, 400);
        menuBar = new QMenuBar(Lecture12_demo_ObserverClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lecture12_demo_ObserverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture12_demo_ObserverClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture12_demo_ObserverClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lecture12_demo_ObserverClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lecture12_demo_ObserverClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lecture12_demo_ObserverClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture12_demo_ObserverClass->setStatusBar(statusBar);

        retranslateUi(Lecture12_demo_ObserverClass);

        QMetaObject::connectSlotsByName(Lecture12_demo_ObserverClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture12_demo_ObserverClass)
    {
        Lecture12_demo_ObserverClass->setWindowTitle(QCoreApplication::translate("Lecture12_demo_ObserverClass", "Lecture12_demo_Observer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture12_demo_ObserverClass: public Ui_Lecture12_demo_ObserverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE12_DEMO_OBSERVER_H
