#pragma once

#include <QtWidgets/QWidget>
#include "ui_Chat.h"
#include "Observer.h"
#include "ChatSession.h"

class Chat : public QWidget, public Observer
{
    Q_OBJECT

public:
    Chat(ChatSession& session, User& user, QWidget *parent = Q_NULLPTR);

private:
    Ui::ChatClass ui;
    User& user;
    ChatSession& session;
    void update() override;
    void sendMessage();
};
