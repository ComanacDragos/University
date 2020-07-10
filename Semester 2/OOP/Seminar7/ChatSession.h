#pragma once
#include "Observer.h"
#include "UserMessage.h"
class ChatSession: public Observable
{
	std::vector<UserMessage> messages;
public:
	void addMessage(User u, Message m)
	{
		UserMessage msg{ m,u };
		this->messages.push_back(msg);
		this->notify();
	}
	std::vector<UserMessage> getMessages() { return this->messages; };
};

