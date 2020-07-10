#include "Programmer.h"

Programmer::Programmer(Service& srv, User& user, QWidget *parent)
	:srv{ srv }, user{ user }, QWidget(parent)
{
	ui.setupUi(this);
}

Programmer::~Programmer()
{
}
