/********************************************************************************
** Form generated from reading UI file 'Programmer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMMER_H
#define UI_PROGRAMMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Programmer
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *issueList;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *deleteButton;

    void setupUi(QWidget *Programmer)
    {
        if (Programmer->objectName().isEmpty())
            Programmer->setObjectName(QString::fromUtf8("Programmer"));
        Programmer->resize(400, 300);
        verticalLayout = new QVBoxLayout(Programmer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        issueList = new QListWidget(Programmer);
        issueList->setObjectName(QString::fromUtf8("issueList"));

        verticalLayout->addWidget(issueList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(Programmer);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout->addWidget(addButton);

        deleteButton = new QPushButton(Programmer);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayout->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Programmer);

        QMetaObject::connectSlotsByName(Programmer);
    } // setupUi

    void retranslateUi(QWidget *Programmer)
    {
        Programmer->setWindowTitle(QCoreApplication::translate("Programmer", "Programmer", nullptr));
        addButton->setText(QCoreApplication::translate("Programmer", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("Programmer", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Programmer: public Ui_Programmer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMMER_H
