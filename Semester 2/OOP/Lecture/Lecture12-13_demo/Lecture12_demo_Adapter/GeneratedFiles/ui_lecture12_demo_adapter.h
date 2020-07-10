/********************************************************************************
** Form generated from reading UI file 'lecture12_demo_adapter.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE12_DEMO_ADAPTER_H
#define UI_LECTURE12_DEMO_ADAPTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture12_demo_AdapterClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *housesListWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *payPalButton;
    QPushButton *skrillButton;
    QPushButton *goCardlessButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture12_demo_AdapterClass)
    {
        if (Lecture12_demo_AdapterClass->objectName().isEmpty())
            Lecture12_demo_AdapterClass->setObjectName(QString::fromUtf8("Lecture12_demo_AdapterClass"));
        Lecture12_demo_AdapterClass->resize(556, 364);
        centralWidget = new QWidget(Lecture12_demo_AdapterClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        housesListWidget = new QListWidget(centralWidget);
        housesListWidget->setObjectName(QString::fromUtf8("housesListWidget"));

        verticalLayout->addWidget(housesListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        payPalButton = new QPushButton(centralWidget);
        payPalButton->setObjectName(QString::fromUtf8("payPalButton"));
        QFont font;
        font.setPointSize(18);
        payPalButton->setFont(font);

        horizontalLayout->addWidget(payPalButton);

        skrillButton = new QPushButton(centralWidget);
        skrillButton->setObjectName(QString::fromUtf8("skrillButton"));
        skrillButton->setFont(font);

        horizontalLayout->addWidget(skrillButton);

        goCardlessButton = new QPushButton(centralWidget);
        goCardlessButton->setObjectName(QString::fromUtf8("goCardlessButton"));
        goCardlessButton->setFont(font);

        horizontalLayout->addWidget(goCardlessButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        Lecture12_demo_AdapterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lecture12_demo_AdapterClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 21));
        Lecture12_demo_AdapterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture12_demo_AdapterClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture12_demo_AdapterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lecture12_demo_AdapterClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture12_demo_AdapterClass->setStatusBar(statusBar);

        retranslateUi(Lecture12_demo_AdapterClass);

        QMetaObject::connectSlotsByName(Lecture12_demo_AdapterClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture12_demo_AdapterClass)
    {
        Lecture12_demo_AdapterClass->setWindowTitle(QCoreApplication::translate("Lecture12_demo_AdapterClass", "Lecture12_demo_Adapter", nullptr));
        payPalButton->setText(QCoreApplication::translate("Lecture12_demo_AdapterClass", "PayPal", nullptr));
        skrillButton->setText(QCoreApplication::translate("Lecture12_demo_AdapterClass", "Skrill", nullptr));
        goCardlessButton->setText(QCoreApplication::translate("Lecture12_demo_AdapterClass", "GoCardless", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture12_demo_AdapterClass: public Ui_Lecture12_demo_AdapterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE12_DEMO_ADAPTER_H
