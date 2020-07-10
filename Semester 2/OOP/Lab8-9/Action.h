#pragma once
#include "FileRepository.h"

class Action
{
protected:
	FileRepository& repository;

public:
	Action(FileRepository& repo):repository{repo}{}
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

	virtual ~Action(){}
};

class ActionAdd : public Action
{
private:
	TrenchCoat coat;

public:
	ActionAdd(FileRepository& repo, const TrenchCoat& coat) :Action{ repo }, coat{ coat }{}

	void executeUndo();
	void executeRedo();

	~ActionAdd() {}
};

class ActionDelete : public Action
{
private:
	TrenchCoat coat;

public:
	ActionDelete(FileRepository& repo, const TrenchCoat& coat) :Action{ repo }, coat{ coat }{}

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
	ActionUpdate(FileRepository& repo, const TrenchCoat& oldCoat, const TrenchCoat& newCoat) :Action{ repo }, oldCoat{ oldCoat }, newCoat{ newCoat }{}

	void executeUndo();
	void executeRedo();

	~ActionUpdate() {}
};
