#pragma once
#include <string>
#include <vector>
#include <iostream>

/*
class Action
{
public:
	virtual void execute()=0;
	virtual ~Action(){}
};

class CreateAction : public Action
{
public:
	virtual void execute() override
	{
		std::cout << "Create File\n";
	}
	virtual ~CreateAction(){}
};

class ExitAction : public Action
{
public:
	virtual void execute() override
	{
		std::cout << "Exit File\n";
	}
	virtual ~ExitAction() {}
};

class MenuItem
{
private:
	std::string text;
	std::unique_ptr<Action> action;
public:
	MenuItem(const std::string& text, std::unique_ptr<Action> action=nullptr):text{text}, action{std::move(action)}{}

	virtual void print()
	{
		std::cout << text << '\n';
	}
	
	virtual void clicked()
	{
		if (this->action != nullptr)
			this->action->execute();
	}
	virtual ~MenuItem(){}
};

class Menu : public MenuItem
{
private:
	std::vector<std::unique_ptr<MenuItem>> items;

public:
	Menu(const std::string& text) :MenuItem{ text } {}

	void add(std::unique_ptr<MenuItem>& item)
	{
		this->items.push_back(std::move(item));
	}

	virtual void print()override
	{
		MenuItem::print();
		for (auto& item : this->items)
			item->print();
		std::cout << '\n';
	}
	virtual ~Menu(){}
};

class MenuBar
{
private:
	std::vector<std::unique_ptr<Menu>> menus;

public:
	MenuBar(){}
	
	void add(std::unique_ptr<Menu>& menu)
	{
		this->menus.push_back(std::move(menu));
	}

	void print()
	{
		for (auto& menu : this->menus)
			menu->print();
	}
};

void MenuBarUnique()
{
	MenuBar menuBar;

	std::unique_ptr<Menu> File = std::make_unique<Menu>("File");

	std::unique_ptr<Action> create1 = std::make_unique<CreateAction>();
	std::unique_ptr<Action> create2 = std::make_unique<CreateAction>();

	std::unique_ptr<MenuItem> C = std::make_unique<MenuItem>("C++", create1);
	std::unique_ptr<MenuItem> Text = std::make_unique<MenuItem>("Text", create2);

	std::unique_ptr<Menu> New = std::make_unique<Menu>("New");
	New->add(Text);
	New->add(C);

	std::unique_ptr<Action> exitAction = std::make_unique<ExitAction>();
	std::unique_ptr<MenuItem> Exit = std::make_unique<MenuItem>("Exit", exitAction);

	//File->add(New);


	std::unique_ptr<Menu> About = std::make_unique<Menu>("About");
}*/