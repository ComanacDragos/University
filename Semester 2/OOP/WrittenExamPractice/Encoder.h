#pragma once
#include <string>
#include <vector>
#include <memory>

class Encoder
{
public:
	virtual std::string encode(const std::string& msg) = 0;
	virtual ~Encoder(){}
};

class AlienEncode : public Encoder
{
private:
	std::string header;
public:
	AlienEncode(const std::string& header):header{header}{}

	virtual std::string encode(const std::string& msg)override
	{
		return msg + this->header;
	}
	virtual ~AlienEncode(){}
};

class MorseEncoder : public Encoder
{
public:
	virtual std::string encode(const std::string& msg) override
	{
		std::string s=msg;
		for (auto& c : s)
			c = '.';
		return s;
	}
	virtual ~MorseEncoder(){}
};

class Mixer: public Encoder
{
private:
	std::unique_ptr<Encoder> s1, s2;

public:
	Mixer(std::unique_ptr<Encoder>& s1, std::unique_ptr<Encoder>& s2):s1{std::move(s1)}, s2{std::move(s2)}{}

	virtual std::string encode(const std::string& msg)
	{
		std::string msg1 = s1->encode(msg);
		std::string msg2 = s2->encode(msg);
		std::string result;
		int i = 0;
		while (i < msg1.size() && i < msg2.size())
		{
			result += msg1[i];
			result += msg2[i];
			i++;
		}
		while (i < msg1.size())
		{
			result += msg1[i];
			i++;
		}
		while (i < msg2.size())
		{
			result += msg2[i];
			i++;
		}
		return result;
	}
};

class Communication
{
private:
	std::unique_ptr<Encoder> encoder;
	std::vector<std::string> messages;
public:
	Communication(std::unique_ptr<Encoder>& encoder) :encoder{ std::move(encoder) }{}

	void addMessage(const std::string& msg)
	{
		this->messages.push_back(msg);
	}

	void communicate()
	{
		for (auto& m : this->messages)
			std::cout << this->encoder->encode(m) << ' ';
		std::cout << '\n';
	}
};

void communication()
{
	std::unique_ptr<Encoder> morseEncoder = std::make_unique<MorseEncoder>();

	std::unique_ptr<Encoder> morseEncoderAux = std::make_unique<MorseEncoder>();
	std::unique_ptr<Encoder> alien = std::make_unique<AlienEncode>("PSD");

	std::unique_ptr<Encoder> mixed = std::make_unique<Mixer>(morseEncoderAux, alien);

	Communication c1{ morseEncoder };
	Communication c2{ mixed };

	c1.addMessage("Msg1");
	c1.addMessage("Msg2");
	c2.addMessage("Msg3");
	c2.addMessage("Msg4");

	c1.communicate();
	std::cout << "\n\n";
	c2.communicate();
}

