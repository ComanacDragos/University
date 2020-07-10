#include "Tester.h"

Tester::Tester(Service& srv, User& user, QWidget *parent)
	:srv{ srv }, user{ user }, QWidget(parent)
{
	ui.setupUi(this);
}

Tester::~Tester()
{
}
