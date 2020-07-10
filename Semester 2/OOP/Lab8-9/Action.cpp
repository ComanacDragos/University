#include "Action.h"

void ActionAdd::executeUndo()
{
	this->repository.deleteCoat(this->coat.getName());
}

void ActionAdd::executeRedo()
{
	this->repository.storeCoat(this->coat);
}

void ActionDelete::executeUndo()
{
	this->repository.storeCoat(this->coat);
}

void ActionDelete::executeRedo()
{
	this->repository.deleteCoat(this->coat.getName());
}

void ActionUpdate::executeUndo()
{
	this->repository.updateCoat(this->oldCoat);
}

void ActionUpdate::executeRedo()
{
	this->repository.updateCoat(this->newCoat);
}
