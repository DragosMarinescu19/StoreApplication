#include <iostream>
#include "teste_magazin.h"
#include "repo_magazin.h"
#include "magazinGUI.h"
#include "service_magazin.h"
#include "Validator.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include "MagazinGUIModele.h"
#include "TableModel.h"
#define _CRT_SECURE_NO_WARNINGS

void run(int argc, char* argv[])
{
	//test_all();
	QApplication a(argc, argv);
	string filename = "C://Users//marin//OneDrive//Desktop//OOP//lab6_7//lab6_7//magazin.txt";
	FileRepoMagazin rep{ filename };
	//RepoMagazin rep;
	//RepoLab rep;
	CosMagazin cos{rep};
	Validator valid;
	//rep.set_probabilitate(0.);
	ServiceMagazin serv{ rep ,valid,cos };
	MagazinGUIModele gui{ serv };
	gui.show();
	a.exec();

}


int main(int argc, char* argv[])
{
	run(argc,argv);
	_CrtDumpMemoryLeaks();//pt ca destructorul sa se apeleze inainte de asta

	return 0;

}

