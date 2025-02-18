#pragma once
#ifndef UI_H
#define UI_H
#include <iostream>
#include "domain.h"
#include "service_magazin.h"
#include <vector>
using namespace std;

class UI {
	ServiceMagazin& serv;
	void uiMENU();
	void uiClearconsole();
	static void afisareUI(const vector<Magazin>& magazine);
	void modificaUI();
	void stergeUI();
	void filtrareUIPret();
	void filtrareUINume();
	void filtrareUIProducator();
	void addUI();
	void sortare();
	void raportUI();
	void cos_adauga_UI();
	void cos_adauga_random_UI();
	void cos_sterge_UI();
	void cos_export_UI();
	void MeniuCos();
public:
	UI(const UI& ui) = delete;
	explicit UI(ServiceMagazin& serv) :serv{ serv }
	{

	}
	void run();

};
#endif



