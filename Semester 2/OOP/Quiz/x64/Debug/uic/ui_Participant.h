/********************************************************************************
** Form generated from reading UI file 'Participant.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICIPANT_H
#define UI_PARTICIPANT_H

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

class Ui_Participant
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *answerEdit;
    QPushButton *answerButton;
    QLabel *scoreLabel;

    void setupUi(QWidget *Participant)
    {
        if (Participant->objectName().isEmpty())
            Participant->setObjectName(QString::fromUtf8("Participant"));
        Participant->resize(400, 386);
        verticalLayout = new QVBoxLayout(Participant);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(Participant);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(Participant);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        answerEdit = new QLineEdit(Participant);
        answerEdit->setObjectName(QString::fromUtf8("answerEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, answerEdit);


        verticalLayout->addLayout(formLayout);

        answerButton = new QPushButton(Participant);
        answerButton->setObjectName(QString::fromUtf8("answerButton"));

        verticalLayout->addWidget(answerButton);

        scoreLabel = new QLabel(Participant);
        scoreLabel->setObjectName(QString::fromUtf8("scoreLabel"));

        verticalLayout->addWidget(scoreLabel);


        retranslateUi(Participant);

        QMetaObject::connectSlotsByName(Participant);
    } // setupUi

    void retranslateUi(QWidget *Participant)
    {
        Participant->setWindowTitle(QCoreApplication::translate("Participant", "Participant", nullptr));
        label->setText(QCoreApplication::translate("Participant", "Answer", nullptr));
        answerButton->setText(QCoreApplication::translate("Participant", "Answer", nullptr));
        scoreLabel->setText(QCoreApplication::translate("Participant", "Score: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Participant: public Ui_Participant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICIPANT_H
