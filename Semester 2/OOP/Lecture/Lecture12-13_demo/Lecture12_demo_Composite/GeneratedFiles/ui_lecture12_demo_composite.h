/********************************************************************************
** Form generated from reading UI file 'lecture12_demo_composite.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE12_DEMO_COMPOSITE_H
#define UI_LECTURE12_DEMO_COMPOSITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <mywidget.h>

QT_BEGIN_NAMESPACE

class Ui_Lecture12_demo_CompositeClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *graphicsListWidget;
    MyWidget *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture12_demo_CompositeClass)
    {
        if (Lecture12_demo_CompositeClass->objectName().isEmpty())
            Lecture12_demo_CompositeClass->setObjectName(QString::fromUtf8("Lecture12_demo_CompositeClass"));
        Lecture12_demo_CompositeClass->resize(940, 484);
        centralWidget = new QWidget(Lecture12_demo_CompositeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsListWidget = new QListWidget(centralWidget);
        graphicsListWidget->setObjectName(QString::fromUtf8("graphicsListWidget"));
        graphicsListWidget->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setPointSize(18);
        graphicsListWidget->setFont(font);

        horizontalLayout->addWidget(graphicsListWidget);

        widget = new MyWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        horizontalLayout_2->addLayout(horizontalLayout);

        Lecture12_demo_CompositeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lecture12_demo_CompositeClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 940, 21));
        Lecture12_demo_CompositeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture12_demo_CompositeClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture12_demo_CompositeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lecture12_demo_CompositeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture12_demo_CompositeClass->setStatusBar(statusBar);

        retranslateUi(Lecture12_demo_CompositeClass);

        QMetaObject::connectSlotsByName(Lecture12_demo_CompositeClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture12_demo_CompositeClass)
    {
        Lecture12_demo_CompositeClass->setWindowTitle(QCoreApplication::translate("Lecture12_demo_CompositeClass", "Lecture12_demo_Composite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture12_demo_CompositeClass: public Ui_Lecture12_demo_CompositeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE12_DEMO_COMPOSITE_H
