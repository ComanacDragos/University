/********************************************************************************
** Form generated from reading UI file 'lecture12_demo_strategy.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE12_DEMO_STRATEGY_H
#define UI_LECTURE12_DEMO_STRATEGY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture12_demo_StrategyClass
{
public:
    QAction *actionSave_As_CSV;
    QAction *actionSave_As_HTML;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture12_demo_StrategyClass)
    {
        if (Lecture12_demo_StrategyClass->objectName().isEmpty())
            Lecture12_demo_StrategyClass->setObjectName(QString::fromUtf8("Lecture12_demo_StrategyClass"));
        Lecture12_demo_StrategyClass->resize(801, 549);
        actionSave_As_CSV = new QAction(Lecture12_demo_StrategyClass);
        actionSave_As_CSV->setObjectName(QString::fromUtf8("actionSave_As_CSV"));
        QFont font;
        font.setPointSize(18);
        actionSave_As_CSV->setFont(font);
        actionSave_As_HTML = new QAction(Lecture12_demo_StrategyClass);
        actionSave_As_HTML->setObjectName(QString::fromUtf8("actionSave_As_HTML"));
        actionSave_As_HTML->setFont(font);
        centralWidget = new QWidget(Lecture12_demo_StrategyClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setFont(font);

        horizontalLayout->addWidget(textEdit);

        Lecture12_demo_StrategyClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lecture12_demo_StrategyClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 801, 21));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QString::fromUtf8("menuFiles"));
        Lecture12_demo_StrategyClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture12_demo_StrategyClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture12_demo_StrategyClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lecture12_demo_StrategyClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture12_demo_StrategyClass->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuFiles->addSeparator();
        menuFiles->addAction(actionSave_As_CSV);
        menuFiles->addAction(actionSave_As_HTML);
        menuFiles->addSeparator();

        retranslateUi(Lecture12_demo_StrategyClass);

        QMetaObject::connectSlotsByName(Lecture12_demo_StrategyClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture12_demo_StrategyClass)
    {
        Lecture12_demo_StrategyClass->setWindowTitle(QCoreApplication::translate("Lecture12_demo_StrategyClass", "Lecture12_demo_Strategy", nullptr));
        actionSave_As_CSV->setText(QCoreApplication::translate("Lecture12_demo_StrategyClass", "Save As CSV", nullptr));
        actionSave_As_HTML->setText(QCoreApplication::translate("Lecture12_demo_StrategyClass", "Save As HTML", nullptr));
        menuFiles->setTitle(QCoreApplication::translate("Lecture12_demo_StrategyClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture12_demo_StrategyClass: public Ui_Lecture12_demo_StrategyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE12_DEMO_STRATEGY_H
