#pragma once
#include <string>
#include <memory>
#include <time.h>
#include <iostream>
#include <vector>

class Channel
{
public:
	virtual void send(const std::string& msg) = 0;
	virtual ~Channel() {}
};

class Telephone : public Channel
{
private:
	std::string nr;
public:
	Telephone(const std::string& nr):nr{nr}{}

	virtual void send(const std::string& msg) override
	{
		int r = rand() % 2;
		if (r == 0)
			throw std::exception{ "Line is busy" };
		std::cout << "dialing: " << this->nr;
	}
	virtual ~Telephone(){}
};

class Fax: public Telephone
{
public:
	Fax(const std::string& nr):Telephone{nr}{}
	~Fax(){}

	virtual void send(const std::string& msg)override
	{
		Telephone::send(msg);
		std::cout << " sending fax";
	}
};

class SMS : public Telephone
{
public:
	SMS(const std::string& nr) :Telephone{ nr } {}
	~SMS() {}

	virtual void send(const std::string& msg)override
	{
		Telephone::send(msg);
		std::cout << " sending SMS";
	}
};

class Failover : public Channel
{
private:

	std::unique_ptr<Channel> c1,c2;
public:
	Failover(std::unique_ptr<Channel>& c1, std::unique_ptr<Channel>& c2):c1{std::move(c1)},c2{std::move(c2)}{}

	virtual void send(const std::string& msg)
	{
		bool isSent = false;
		try
		{
			c1->send(msg);
			isSent = true;
		}
		catch (std::exception & exc)
		{
		}
		if (isSent == false)
		{
			try
			{
				c2->send(msg);
			}
			catch (std::exception & exc)
			{
			}
		}
	}
	virtual ~Failover(){}
};

class Contact
{
private:
	std::unique_ptr<Channel> c1, c2, c3;
public:
	Contact(std::unique_ptr<Channel>& c1, std::unique_ptr<Channel>& c2, std::unique_ptr<Channel>& c3) :c1{ std::move(c1) }, c2{ std::move(c2) }, c3{ std::move(c3) }{}

	void sendAlarm(const std::string& msg)
	{
		while (true)
		{
			try
			{
				c1->send(msg);
				std::cout << '\n';
				break;
			}
			catch (std::exception & exc)
			{
				std::cout << "First channel is busy\n";
			}
			try
			{
				c2->send(msg);
				std::cout << '\n';
				break;
			}
			catch (std::exception & exc)
			{
				std::cout << "Second channel is busy\n";
			}
			try
			{
				c3->send(msg);
				std::cout << '\n';
				break;
			}
			catch (std::exception & exc)
			{
				std::cout << "Third channel is busy\n";
			}
		}
	}

};

std::unique_ptr<Contact> channelWithUnique()
{
	std::unique_ptr<Channel> telephone1 = std::make_unique<Telephone>("nr1" );
	std::unique_ptr<Channel> fax1 = std::make_unique<Fax>("nr2");
	std::unique_ptr<Channel> sms1 = std::make_unique<SMS>("nr3");

	std::unique_ptr<Channel> telephone2 = std::make_unique<Telephone>("nr4");
	std::unique_ptr<Channel> fax2 = std::make_unique<Fax>("nr5");
	std::unique_ptr<Channel> sms2 = std::make_unique<SMS>("nr6");

	std::unique_ptr<Channel> failover1 = std::make_unique<Failover>(fax1, sms1);

	std::unique_ptr<Channel> failover2 = std::make_unique<Failover>(telephone2, fax2);

	std::unique_ptr<Channel> failover3 = std::make_unique<Failover>(failover2, sms2);

	std::unique_ptr<Contact> contact = std::make_unique<Contact>(telephone1, failover1, failover3);

	return contact;
}

/*
		srand(time(0));
		std::unique_ptr<Contact> c = std::move(channelWithUnique());
		c->sendAlarm("msg1");
		std::cout << "\n\n";
		c->sendAlarm("msg2");
		std::cout << "\n\n";
		c->sendAlarm("msg3");
		std::cout << "\n\n";
		*/