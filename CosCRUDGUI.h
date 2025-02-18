#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "cos_magazin.h"
#include "observer.h"
using namespace std;
class CosGUILista:public QWidget, public Observer
{
private:

	CosMagazin& cos;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnrandom;

	void loadlist(const vector<Magazin>& m)
	{
		lst->clear();
		for(auto& p:m)
		{
			auto item = new QListWidgetItem(QString::fromStdString(p.get_name() + " " + p.get_type() + " " + p.get_producer()
				+ " " + to_string(p.get_price())));
			lst->addItem(item);
		}
		//cos.notify();
	}

	void initGUI()
	{
		cos.notify();
		QVBoxLayout* ly = new QVBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Clear cos");
		ly->addWidget(btn);
		btnrandom = new QPushButton("Add random to cos");  // Adaugat buton pentru adaugare random
		ly->addWidget(btnrandom);  
		setLayout(ly);

	}

	void connectSignals()
	{
		cos.addObserver(this);
		connect(btn, &QPushButton::clicked, [&]()	
		{
				cos.sterge_cos();
				loadlist(cos.get_all_cos());
		});
		connect(btnrandom, &QPushButton::clicked, [&]()
		{
				cos.umple(3);
				loadlist(cos.get_all_cos());
		});
		cos.notify();
	}

public:

	CosGUILista(CosMagazin& cos): cos{cos}
	{
		initGUI();
		connectSignals();
		loadlist(cos.get_all_cos());
	}

	void update() override
	{
		loadlist(cos.get_all_cos());	
	}

	~CosGUILista()
	{
		cos.removeObserver(this);
	}
};
