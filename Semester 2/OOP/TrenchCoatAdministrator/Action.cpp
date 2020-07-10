#include "Action.h"

void ActionAdd::executeUndo()
{
	this->repository->deleteCoat(this->coat.getName());
}

void ActionAdd::executeRedo()
{
	this->repository->storeCoat(this->coat);
}

void ActionDelete::executeUndo()
{
	this->repository->storeCoat(this->coat);
}

void ActionDelete::executeRedo()
{
	this->repository->deleteCoat(this->coat.getName());
}

void ActionUpdate::executeUndo()
{
	this->repository->updateCoat(this->oldCoat);
}

void ActionUpdate::executeRedo()
{
	this->repository->updateCoat(this->newCoat);
}

void CompositeAction::attachAction(std::unique_ptr<Action> action)
{
	this->actions.push_back(std::move(action));
}

void CompositeAction::executeUndo()
{
	for (int i = 0; i < this->actions.size(); i++)
		this->actions[i]->executeUndo();
}

void CompositeAction::executeRedo()
{
	for (int i = 0; i < this->actions.size(); i++)
		this->actions[i]->executeRedo();
}
