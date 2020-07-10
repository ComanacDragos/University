/********************************************************************************
** Form generated from reading UI file 'Tester.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTER_H
#define UI_TESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tester
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *issueList;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *descriptionEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *deleteButton;

    void setupUi(QWidget *Tester)
    {
        if (Tester->objectName().isEmpty())
            Tester->setObjectName(QString::fromUtf8("Tester"));
        Tester->resize(400, 300);
        verticalLayout = new QVBoxLayout(Tester);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        issueList = new QListWidget(Tester);
        issueList->setObjectName(QString::fromUtf8("issueList"));

        verticalLayout->addWidget(issueList);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(Tester);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        descriptionEdit = new QLineEdit(Tester);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, descriptionEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(Tester);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout->addWidget(addButton);

        deleteButton = new QPushButton(Tester);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayout->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Tester);

        QMetaObject::connectSlotsByName(Tester);
    } // setupUi

    void retranslateUi(QWidget *Tester)
    {
        Tester->setWindowTitle(QCoreApplication::translate("Tester", "Tester", nullptr));
        label->setText(QCoreApplication::translate("Tester", "Description", nullptr));
        addButton->setText(QCoreApplication::translate("Tester", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("Tester", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tester: public Ui_Tester {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTER_H
