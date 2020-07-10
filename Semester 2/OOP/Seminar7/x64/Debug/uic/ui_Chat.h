/********************************************************************************
** Form generated from reading UI file 'Chat.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatClass
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *messages;
    QHBoxLayout *horizontalLayout;
    QLineEdit *messageEdit;
    QPushButton *sendButton;

    void setupUi(QWidget *ChatClass)
    {
        if (ChatClass->objectName().isEmpty())
            ChatClass->setObjectName(QString::fromUtf8("ChatClass"));
        ChatClass->resize(600, 400);
        verticalLayout = new QVBoxLayout(ChatClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        messages = new QListWidget(ChatClass);
        messages->setObjectName(QString::fromUtf8("messages"));

        verticalLayout->addWidget(messages);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        messageEdit = new QLineEdit(ChatClass);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));

        horizontalLayout->addWidget(messageEdit);

        sendButton = new QPushButton(ChatClass);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ChatClass);

        QMetaObject::connectSlotsByName(ChatClass);
    } // setupUi

    void retranslateUi(QWidget *ChatClass)
    {
        ChatClass->setWindowTitle(QCoreApplication::translate("ChatClass", "Chat", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatClass", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatClass: public Ui_ChatClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
