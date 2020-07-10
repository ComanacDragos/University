#include "BarChart.h"

void BarChart::paintEvent(QPaintEvent* event)
{
    std::unordered_map<std::string, int> map;

    for (auto& coat : this->coats)
    {
        if (map.find(coat.getName()) == map.end())
            map.insert(std::make_pair(coat.getName(), 1));
        else
            map[coat.getName()] += 1;

        qDebug() << QString::fromStdString(coat.getName());
    }

    QPainter painter(this);

    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);

    QLine* x = new QLine{ 50, 300, 10000, 300 };

    painter.drawLine(*x);

    QLine* y = new QLine{ 50, 0, 50, 300 };
    painter.drawLine(*y);

    for(int i=0;i<map.size();i++)
    {
        painter.drawRect(110+i*60, 300-10*i-10, 50, 10*i + 10);
        QPoint p{ 130+ i*60, 320 };

        painter.drawText(p, "coat" + QString::fromStdString(std::to_string(map["S"])));

    }

    // Rect
    //painter.drawRect(10, 10, 60, 80);
    // 110-160 170-220 230
}
