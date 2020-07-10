/********************************************************************************
** Form generated from reading UI file 'lecture11_demo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE11_DEMO_H
#define UI_LECTURE11_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture11_demoClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *GenesWidgetButton;
    QPushButton *GenesViewButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture11_demoClass)
    {
        if (Lecture11_demoClass->objectName().isEmpty())
            Lecture11_demoClass->setObjectName(QString::fromUtf8("Lecture11_demoClass"));
        Lecture11_demoClass->resize(325, 164);
        centralWidget = new QWidget(Lecture11_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 283, 90));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        GenesWidgetButton = new QPushButton(layoutWidget);
        GenesWidgetButton->setObjectName(QString::fromUtf8("GenesWidgetButton"));
        QFont font;
        font.setPointSize(20);
        GenesWidgetButton->setFont(font);

        verticalLayout->addWidget(GenesWidgetButton);

        GenesViewButton = new QPushButton(layoutWidget);
        GenesViewButton->setObjectName(QString::fromUtf8("GenesViewButton"));
        GenesViewButton->setFont(font);

        verticalLayout->addWidget(GenesViewButton);

        Lecture11_demoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lecture11_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 325, 21));
        Lecture11_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture11_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture11_demoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lecture11_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture11_demoClass->setStatusBar(statusBar);

        retranslateUi(Lecture11_demoClass);

        QMetaObject::connectSlotsByName(Lecture11_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture11_demoClass)
    {
        Lecture11_demoClass->setWindowTitle(QCoreApplication::translate("Lecture11_demoClass", "Lecture11_demo", nullptr));
        GenesWidgetButton->setText(QCoreApplication::translate("Lecture11_demoClass", "Genes widget", nullptr));
        GenesViewButton->setText(QCoreApplication::translate("Lecture11_demoClass", "Genes view with model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture11_demoClass: public Ui_Lecture11_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE11_DEMO_H
