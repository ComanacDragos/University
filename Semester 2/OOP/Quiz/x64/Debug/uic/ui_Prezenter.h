/********************************************************************************
** Form generated from reading UI file 'Prezenter.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREZENTER_H
#define UI_PREZENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrezenterClass
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *idEdit;
    QLabel *label_2;
    QLineEdit *textEdit;
    QLabel *label_3;
    QLineEdit *answerEdit;
    QLabel *label_4;
    QLineEdit *scoreEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *PrezenterClass)
    {
        if (PrezenterClass->objectName().isEmpty())
            PrezenterClass->setObjectName(QString::fromUtf8("PrezenterClass"));
        PrezenterClass->resize(600, 400);
        verticalLayout = new QVBoxLayout(PrezenterClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(PrezenterClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(PrezenterClass);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        idEdit = new QLineEdit(PrezenterClass);
        idEdit->setObjectName(QString::fromUtf8("idEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, idEdit);

        label_2 = new QLabel(PrezenterClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        textEdit = new QLineEdit(PrezenterClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, textEdit);

        label_3 = new QLabel(PrezenterClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        answerEdit = new QLineEdit(PrezenterClass);
        answerEdit->setObjectName(QString::fromUtf8("answerEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, answerEdit);

        label_4 = new QLabel(PrezenterClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        scoreEdit = new QLineEdit(PrezenterClass);
        scoreEdit->setObjectName(QString::fromUtf8("scoreEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, scoreEdit);


        verticalLayout->addLayout(formLayout);

        pushButton = new QPushButton(PrezenterClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(PrezenterClass);

        QMetaObject::connectSlotsByName(PrezenterClass);
    } // setupUi

    void retranslateUi(QWidget *PrezenterClass)
    {
        PrezenterClass->setWindowTitle(QCoreApplication::translate("PrezenterClass", "Prezenter", nullptr));
        label->setText(QCoreApplication::translate("PrezenterClass", "ID", nullptr));
        label_2->setText(QCoreApplication::translate("PrezenterClass", "Text", nullptr));
        label_3->setText(QCoreApplication::translate("PrezenterClass", "Answer", nullptr));
        label_4->setText(QCoreApplication::translate("PrezenterClass", "Score", nullptr));
        pushButton->setText(QCoreApplication::translate("PrezenterClass", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrezenterClass: public Ui_PrezenterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREZENTER_H
