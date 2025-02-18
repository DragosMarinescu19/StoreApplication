#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include "cos_magazin.h"
#include "qdebug.h"


class HistogramGUI: public QWidget,public Observer
{
private:
	CosMagazin& cos;

public:
	HistogramGUI(CosMagazin& cos):cos{cos}
	{
		cos.addObserver(this);
		cos.notify();
	}

	void update() override
	{
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override
	{
		QPainter p{ this };
		srand(time(NULL));

		for(const auto& u:cos.get_all_cos())
		{
			int x = rand() % 300;
			int y = rand() % 300;
			qDebug() << x << " " << y << '\n';
			p.drawRect(x, y, 20, u.get_price() );//  /10
			p.drawImage(x, y, QImage("C://Users//marin//OneDrive//Desktop//OOP//lab10_11//sky.png"));
		}
		
	}

	


};