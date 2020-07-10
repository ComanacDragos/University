#pragma once
#include "AbstractRepository.h"
#include <memory>

class Action
{
protected:
	AbstractRepository* repository;

public:
	Action() :repository{ nullptr } {}
	Action(AbstractRepository* repo):repository{repo}{}
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

	virtual ~Action(){}
};

class CompositeAction : public Action
{
protected:
	std::vector<std::unique_ptr<Action>> actions;

public:
	CompositeAction(){}

	void attachAction(std::unique_ptr<Action> action);
	void executeUndo();
	void executeRedo();

	~CompositeAction(){}

};

class ActionAdd : public Action
{
private:
	TrenchCoat coat;

public:
	ActionAdd(AbstractRepository* repo, const TrenchCoat& coat) :Action{ repo }, coat{ coat }{}

	void executeUndo();
	void executeRedo();

	~ActionAdd() {}
};

class ActionDelete : public Action
{
private:
	TrenchCoat coat;

public:
	ActionDelete(AbstractRepository* repo, const TrenchCoat& coat) :Action{ repo }, coat{ coat }{}

	void executeUndo();
	void executeRedo();

	~ActionDelete() {}
};

class ActionUpdate : public Action
{
private:
	TrenchCoat oldCoat;
	TrenchCoat newCoat;

public:
	ActionUpdate(AbstractRepository* repo, const TrenchCoat& oldCoat, const TrenchCoat& newCoat) :Action{ repo }, oldCoat{ oldCoat }, newCoat{ newCoat }{}

	void executeUndo();
	void executeRedo();

	~ActionUpdate() {}
};
