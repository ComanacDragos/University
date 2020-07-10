/********************************************************************************
** Form generated from reading UI file 'TrenchCoatAdministrator.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRENCHCOATADMINISTRATOR_H
#define UI_TRENCHCOATADMINISTRATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrenchCoatAdministratorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrenchCoatAdministratorClass)
    {
        if (TrenchCoatAdministratorClass->objectName().isEmpty())
            TrenchCoatAdministratorClass->setObjectName(QString::fromUtf8("TrenchCoatAdministratorClass"));
        TrenchCoatAdministratorClass->resize(600, 400);
        menuBar = new QMenuBar(TrenchCoatAdministratorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TrenchCoatAdministratorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TrenchCoatAdministratorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TrenchCoatAdministratorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TrenchCoatAdministratorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TrenchCoatAdministratorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TrenchCoatAdministratorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TrenchCoatAdministratorClass->setStatusBar(statusBar);

        retranslateUi(TrenchCoatAdministratorClass);

        QMetaObject::connectSlotsByName(TrenchCoatAdministratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrenchCoatAdministratorClass)
    {
        TrenchCoatAdministratorClass->setWindowTitle(QCoreApplication::translate("TrenchCoatAdministratorClass", "TrenchCoatAdministrator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrenchCoatAdministratorClass: public Ui_TrenchCoatAdministratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRENCHCOATADMINISTRATOR_H
