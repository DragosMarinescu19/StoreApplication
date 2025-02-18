#pragma once
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include <QStringList>
#include "service_magazin.h"
#include<qmessagebox.h>
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include "TableModel.h"
#include "domain.h"

class MagazinGUIModele : public QWidget {
private:
	ServiceMagazin& srv;
	TableModel* modelTabel;
	//MyListModel* modelLista;
//	QLabel* lblCate = new QLabel{ "Cate:" };
	QListView* lstV = new QListView;

	QTableView* tblV = new QTableView;

	QLabel* lblnume = new QLabel{ "Nume magazin:" };
	QLabel* lblproducer = new QLabel{ "Producer magazin:" };
	QLabel* lblTip = new QLabel{ "Tip magazin:" };
	QLabel* lblPret = new QLabel{ "Pret magazin:" };

	QLineEdit* editnume;
	QLineEdit* editTip;
	QLineEdit* editproducer;
	QLineEdit* editPret;

	QPushButton* btnAddMagazin;
	QPushButton* btnModifyMagazin;
	QPushButton* btnDeleteMagazin;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtNume = new QRadioButton(QString::fromStdString("Nume"));
	QRadioButton* radioSrtPret = new QRadioButton(QString::fromStdString("Pret"));
	QRadioButton* radioSrtNumeTip = new QRadioButton(QString::fromStdString("Nume+Tip"));
	QPushButton* btnSortMagazin;

	QLabel* lblFilterCriteria = new QLabel{ "Pretul dupa care se filtreaza:" };
	QLineEdit* editFilterPret;
	QPushButton* btnFilterMagazin1;

	QLabel* lblFilterCriteria2 = new QLabel{ "Producatorul dupa care se filtreaza:" };
	QLineEdit* editFilterProducer;
	QPushButton* btnFilterMagazin2;

	QPushButton* btnReloadData;

	QPushButton* btnUndo;

	QPushButton* btnCos;
	QPushButton* addCos;
	QLineEdit* numeCos;
	QLineEdit* producerCos;
	QPushButton* addRandomCos;
	QLineEdit* editRandom;
	QPushButton* golesteCos;
	QListWidget* listaCos;
	QLineEdit* editExport;
	QPushButton* exportCos;
	QLabel* lblRandom = new QLabel{ "Nr magazine random: " };
	QLabel* lblDenumireCos = new QLabel{ "Nume magazin: " };
	QLabel* lblExport = new QLabel{ "Nume fisier: " };

	QPushButton* btnCosCRUDGUI;
	QPushButton* btnCosReadOnlyGUI;

	QPushButton* btnAddCos;
	QPushButton* btnDeleteCos;
	QPushButton* btnRandomCos;

	void initGUI();
	void connectSignalsSlots();
	void reloadMagazinList(std::vector<Magazin> magazine);
	void guiAddMagazin();
	void guiModifyMagazin();
	void guiDeleteMagazin();

public:
	MagazinGUIModele(ServiceMagazin& srv) :srv{ srv} {
		initGUI();
		modelTabel = new TableModel{ srv.get_all()};
		//modelLista = new MyListModel{ctr.getAllOferteCos()};
		//lstV->setModel(model2);
		tblV->setModel(modelTabel);
		//lstV->setModel(modelLista);
		connectSignalsSlots();
	}

};
