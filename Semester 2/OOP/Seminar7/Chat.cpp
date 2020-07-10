#include "Chat.h"

Chat::Chat(ChatSession& session, User& user, QWidget *parent)
    :session{ session }, user{ user },QWidget(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.sendButton, &QPushButton::clicked, this, [this]() {this->sendMessage(); });
    this->setWindowTitle(QString::fromStdString(this->user.getName()));
}

void Chat::update()
{
    if (ui.messages->count() > 0)
        ui.messages->clear();
    for (auto& msg : this->session.getMessages())
    {
        QString itemInList = QString::fromStdString(msg.getUser().getName() + ": "+ msg.getMessage().getMessage());
        QListWidgetItem* item = new QListWidgetItem{ itemInList };
        ui.messages->addItem(item);
    }
}

void Chat::sendMessage()
{
    std::string message = ui.messageEdit->text().toStdString();
    if (message.size() != 0)
    {
        Message msg{ message };
        this->session.addMessage(this->user, msg);
    }
}
