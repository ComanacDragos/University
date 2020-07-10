#include "Histogram.h"

Histogram::Histogram(Service& srv, QWidget *parent)
	:srv{ srv }, QWidget(parent)
{
	//ui.setupUi(this);
	this->srv.addObserver(this);
}

Histogram::~Histogram()
{
}

void Histogram::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QPen pen;
	pen.setWidth(2);
	painter.setPen(pen);

	std::vector<std::string> teachers = srv.getTeachers();
	teachers.push_back("");

	int i = 1;
	for (auto& t : teachers)
	{
		QString teacher = "No teacher";
		if (t != "")
			teacher = QString::fromStdString(t);

		int students= this->srv.getStudentsOfTeacher(t).size();
		painter.drawText(QPoint{ i*100,100 }, teacher +':'+ QString::number(students));
		painter.drawRect(QRect{ i * 100+15, 120, 25,students * 10 });
		
		i += 1;
	}

}

