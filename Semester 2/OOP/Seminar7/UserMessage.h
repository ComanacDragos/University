#pragma once
#include "User.h"

class UserMessage
{
private:
	Message msg;
	User user;
public:
	UserMessage(Message msg, User user) :msg{ msg }, user{ user }{}

	Message getMessage() { return this->msg; };
	User getUser() { return this->user; };
};

