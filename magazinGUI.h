#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
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

using std::vector;
using std::string;
class MagazinGUI : public QWidget {
private:
	
	ServiceMagazin& srv;

	QLabel* lblnume = new QLabel{ "Nume magazin:" };
	QLabel* lbltip = new QLabel{ "Tip magazin:" };
	QLabel* lblproducer = new QLabel{ "Producator:" };
	QLabel* lblprice = new QLabel{ "Pret magazin:" };

	QLineEdit* editnume;
	QLineEdit* edittip;
	QLineEdit* editproducer;
	QLineEdit* editprice;

	QPushButton* btnAddMagazin;
	QPushButton* btnModifyMagazin;
	QPushButton* btnDeleteMagazin;
	QPushButton* btnExit;
	

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

	QPushButton* btnProfi;
	QPushButton* btnSelgros;
	QPushButton* btnMega;
	QPushButton* btnMinimarket;
	QPushButton* btnAltele;

	QPushButton* btnUndo;

	// pentru tabel
	QTableWidget* tableMagazin;
	// pentru lista
	QListWidget* listaMagazin;

	QListWidget* listaProduse;

	QPushButton* btnCos;
	//    QWidget* fereastraCos;
	QPushButton* adaugaCos;
	QLineEdit* numeCos;
	QLineEdit* producerCos;
	QPushButton* adaugaRandomCos;
	QLineEdit* numarRandom;
	QPushButton* golesteCos;
	QListWidget* listaCos;
	QLineEdit* editExport;
	QPushButton* exportCos;
	QLabel* lblRandom = new QLabel{ "Numar magazine random:" };
	QLabel* lblExport = new QLabel{ "Nume fisier:" };

	QPushButton* btnCosCRUDGUI;
	QPushButton* btnCosReadOnlyGUI;

	CosGUILista* fereastraCos;
	HistogramGUI* fereastraFiguri;

	QPushButton* btnAddCos;
	QPushButton* btnDeleteCos;
	QPushButton* btnRandomCos;

	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadMagazinList(vector<Magazin> magazine);
	void reloadMagazinCosList(vector<Magazin> magazine);
public:
	MagazinGUI(ServiceMagazin& ofSrv) : srv{ ofSrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadMagazinList(srv.get_all());
	}

	int getSelectedIndex() {
		auto currentIndex = this->listaMagazin->selectionModel()->currentIndex();
		return currentIndex.row();
	}

	void guiAddMagazin();
	void guiModifyMagazin();
	void guiDeleteMagazin();
};