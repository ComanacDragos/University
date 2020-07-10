#include "Painter.h"
Painter::Painter(Service& srv, const std::string name, QWidget *parent)
	:srv{srv},  name{ name }, QWidget(parent)
{
	//ui.setupUi(this);
}

Painter::~Painter()
{
}

void Painter::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QPen pen;
	pen.setWidth(2);
	painter.setPen(pen);

	for (Star& star : this->srv.getStars())
	{
		if (star.getName() == this->name)
		{
			QPen pen{ Qt::red, 2 };
			//pen.setWidth(2);
			
			painter.setPen(pen);
		}
		else
		{
			QPen pen{ Qt::black, 2 };

			painter.setPen(pen);
		}
		painter.drawEllipse(star.getRA(), star.getDec(), star.getDiameter(), star.getDiameter());
	}
}
