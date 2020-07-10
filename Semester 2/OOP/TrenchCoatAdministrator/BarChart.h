#pragma once
#include <QtGui>
#include <QWidget>
#include <unordered_map>
#include "TrenchCoat.h"
#include <vector>
//#include <QtCharts>

class BarChart: public QWidget
{
    Q_OBJECT
public:
    BarChart(std::vector<TrenchCoat> coats, QWidget* parent = 0) :QWidget{ parent }, coats{ coats }{}

protected:
    std::vector<TrenchCoat> coats;

    void paintEvent(QPaintEvent* event);
signals:

public slots:

};

