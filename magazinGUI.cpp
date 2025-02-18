#include "magazinGUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"

void MagazinGUI::initializeGUIComponents()
{
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left part of the window, pentru care setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editnume = new QLineEdit;
	editproducer = new QLineEdit;
	edittip = new QLineEdit;
	editprice = new QLineEdit;

	// denumire
	lyForm->addRow(lblnume, editnume);

	// destinatie
	lyForm->addRow(lblproducer, editproducer);

	// tip
	lyForm->addRow(lbltip, edittip);

	// pret
	lyForm->addRow(lblprice, editprice);
	btnAddMagazin = new QPushButton("Adauga magazin");
	lyForm->addWidget(btnAddMagazin);

	btnModifyMagazin = new QPushButton("Modifica magazin");
	lyForm->addWidget(btnModifyMagazin);

	btnDeleteMagazin = new QPushButton("Delete magazin");
	lyForm->addWidget(btnDeleteMagazin);

	btnExit = new QPushButton("Exit");
	lyForm->addWidget(btnExit);

	//adaugam toate componentele legate de adaugare oferta in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);

	//cream un GroupBox pentru radiobuttons care corespund criteriilor de sortare pe care le avem (dupa denumire, destinatie, tip+pret) + butonul de sortare
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtNume);
	lyRadioBox->addWidget(radioSrtPret);
	lyRadioBox->addWidget(radioSrtNumeTip);

	btnSortMagazin = new QPushButton("Sorteaza magazine");
	lyRadioBox->addWidget(btnSortMagazin);

	//adaugam acest grup in partea stanga, dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrari

	

	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);

	editFilterPret = new QLineEdit;
	lyFormFilter->addRow(lblFilterCriteria, editFilterPret);
	btnFilterMagazin1 = new QPushButton("Filtreaza magazine dupa pret");
	lyFormFilter->addWidget(btnFilterMagazin1);

	editFilterProducer = new QLineEdit;
	lyFormFilter->addRow(lblFilterCriteria2, editFilterProducer);
	btnFilterMagazin2 = new QPushButton("Filtreaza magazine dupa producator");
	lyFormFilter->addWidget(btnFilterMagazin2);

	lyLeft->addWidget(formFilter);

	//Buton folosit pentru a reincarca datele; afisam toate oferte in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);

	btnUndo = new QPushButton("Undo");
	lyLeft->addWidget(btnUndo);

	btnCos = new QPushButton("Wishlist");
	adaugaCos = new QPushButton("Adauga magazin in wishlist");
	numeCos = new QLineEdit;
	producerCos = new QLineEdit;
	adaugaRandomCos = new QPushButton("Adauga magazine random in wishlist");
	numarRandom = new QLineEdit;
	golesteCos = new QPushButton("Goleste wishlist");
	editExport = new QLineEdit;
	this->listaCos = new QListWidget;
	exportCos = new QPushButton("Exporta wishlist");

	btnCosCRUDGUI = new QPushButton("CosCRUDGui");
	lyLeft->addWidget(btnCosCRUDGUI);

	btnCosReadOnlyGUI = new QPushButton("CosReadOnlyGUI");
	lyLeft->addWidget(btnCosReadOnlyGUI);

	//componenta right - contine doar tabelul cu oferte
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableMagazin = new QTableWidget{ noLines, noColumns };

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Nume" << "Producer" << "Tip" << "Pret";
	this->tableMagazin->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableMagazin->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	btnProfi = new QPushButton("Profi");
	btnSelgros = new QPushButton("Selgros");
	btnMega = new QPushButton("Mega");
	btnMinimarket = new QPushButton("Minimarket");
	btnAltele = new QPushButton("Altele");
	lyRight->addWidget(btnProfi);
	lyRight->addWidget(btnSelgros);
	lyRight->addWidget(btnMega);
	lyRight->addWidget(btnMinimarket);
	lyRight->addWidget(btnAltele);

	for (const auto& type : srv.get_all()) {
		QPushButton* btn = new QPushButton(QString::fromStdString(type.get_type()));
		lyRight->addWidget(btn);

		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == type.get_type())
				cnt++;
		if (cnt == 0)
			btn->setVisible(false);
		else
			btn->setVisible(true);

		

		connect(btn, &QPushButton::clicked, [this, type]() {
			int cnt = 0;
			for (int i = 0; i < srv.get_all().size(); i++)
				if (srv.get_all().at(i).get_type() == type.get_type())
					cnt++;
			QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine " + type.get_type() + ": %1").arg(cnt));
			});
	}


	lyRight->addWidget(tableMagazin);


	lyRight->addWidget(btnCos);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

	listaProduse = new QListWidget;
	lyRight->addWidget(listaProduse);
}

void MagazinGUI::connectSignalsSlots()
{
	connect(listaProduse, &QListWidget::itemSelectionChanged, [&]()
	{
			auto sel = listaProduse->selectedItems();
			if(sel.isEmpty())
			{
				editnume->setText("");
				editprice->setText("");
				editproducer->setText("");
				edittip->setText("");
			}
			else
			{
				auto selNume = sel.at(0)->text().split(" ").at(0);
				auto selTip = sel.at(0)->text().split(" ").at(2);
				auto selProducer = sel.at(0)->text().split(" ").at(1);
				auto selPrice = sel.at(0)->text().split(" ").at(3);
				editnume->setText(selNume);
				edittip->setText(selTip);
				editproducer->setText(selProducer);
				editprice->setText(selPrice);
			}
	});

	connect(btnExit, &QPushButton::clicked, [&]()
	{
			QMessageBox::information(nullptr, "Info", "Exiting...");
			close();
	});
	QObject::connect(btnAddMagazin, &QPushButton::clicked, this, &MagazinGUI::guiAddMagazin);
	QObject::connect(btnModifyMagazin, &QPushButton::clicked, this, &MagazinGUI::guiModifyMagazin);
	QObject::connect(btnDeleteMagazin, &QPushButton::clicked, this, &MagazinGUI::guiDeleteMagazin);

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			this->srv.undo();
			this->reloadMagazinList(this->srv.get_all());
			QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes."));
		}
		catch (Exception& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", "");
		}
		});

	QObject::connect(btnSortMagazin, &QPushButton::clicked, [&]() {
		if (this->radioSrtNume->isChecked())
			this->reloadMagazinList(srv.sort_by_name());
		else if (this->radioSrtPret->isChecked())
			this->reloadMagazinList(srv.sort_by_price());
		else if (this->radioSrtNumeTip->isChecked())
			this->reloadMagazinList(srv.sort_by_name_type());
		});
		
	QObject::connect(btnFilterMagazin1, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterPret->text().toStdString();
		this->reloadMagazinList(srv.filtrarePret(stoi(filterC)));
		editFilterPret->clear();
		});



	QObject::connect(btnFilterMagazin2, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterProducer->text().toStdString();
		this->reloadMagazinList(srv.filtrareProducator(filterC));
		editFilterProducer->clear();
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadMagazinList(srv.get_all());
		});

	QObject::connect(btnProfi, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == "Profi")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine Profi: %1").arg(cnt));
		});

	QObject::connect(btnSelgros, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == "Selgros")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine Selgros: %1").arg(cnt));
		});

	QObject::connect(btnMega, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == "Mega")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine Mega: %1").arg(cnt));
		});

	QObject::connect(btnMinimarket, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == "Minimarket")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine Minimarket: %1").arg(cnt));
		});

	QObject::connect(btnAltele, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < srv.get_all().size(); i++)
			if (srv.get_all().at(i).get_type() == "Altele")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr magazine Altele: %1").arg(cnt));
		});



	QObject::connect(btnCos, &QPushButton::clicked, [&]() {
		QWidget* fereastraCos = new QWidget;
		QFormLayout* lyCos = new QFormLayout;
		fereastraCos->setLayout(lyCos);
		numeCos = new QLineEdit;
		lyCos->addRow("Nume magazin: ", numeCos);
		producerCos = new QLineEdit;
		lyCos->addRow("Producator magazin: ", producerCos);
		lyCos->addWidget(adaugaCos);
		lyCos->addRow(lblRandom, numarRandom);
		lyCos->addWidget(adaugaRandomCos);
		lyCos->addWidget(golesteCos);
		editExport = new QLineEdit;
		lyCos->addRow(lblExport, editExport);
		lyCos->addWidget(exportCos);
		lyCos->addWidget(listaCos);
		fereastraCos->show();
		});

	QObject::connect(adaugaCos, &QPushButton::clicked, [&]() {
		try {
			string nume = numeCos->text().toStdString();
			string producer = producerCos->text().toStdString();
			numeCos->clear();
			producerCos->clear();
			this->srv.cos_adauga(nume, producer);
			this->reloadMagazinCosList(this->srv.get_all_cos());
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", "Magazinul nu exista!");
		}
		});

	QObject::connect(adaugaRandomCos, &QPushButton::clicked, [&]() {
		try {
			int nr = numarRandom->text().toInt();
			numarRandom->clear();
			this->srv.cos_adauga_random(nr);
			this->reloadMagazinCosList(this->srv.get_all_cos());
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", "Nu exista magazine");
		}
		});

	QObject::connect(golesteCos, &QPushButton::clicked, [&]() {
		try {
			this->srv.cos_sterge();
			this->reloadMagazinCosList(this->srv.get_all_cos());
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", "Cosul este gol deja");
		}
		});

	QObject::connect(exportCos, &QPushButton::clicked, [&]() {
		try {
			string fisier = editExport->text().toStdString();
			editExport->clear();
			this->srv.cos_export(fisier);
			listaCos->clear();
			this->srv.cos_sterge();
			this->reloadMagazinCosList(this->srv.get_all_cos());
		}
		catch (RepoException) {
			QMessageBox::warning(this, "Warning", "");
		}
		});

	connect(btnCosCRUDGUI, &QPushButton::clicked, [&]()
	{
			auto fereastraNoua = new CosGUILista{ srv.getCos()};
			fereastraNoua->show();
	});

	connect(btnCosReadOnlyGUI, &QPushButton::clicked, [&]()
	{
			auto fereastraFiguri = new HistogramGUI(srv.getCos());
			fereastraFiguri->show();

	});


}

void MagazinGUI::reloadMagazinList(vector<Magazin> magazine)
{

	listaProduse->clear();
	for (const auto& product : magazine) {
		auto item = new QListWidgetItem(QString::fromStdString(
			product.get_name() + " " + product.get_producer() + " " + product.get_type() + " " + std::to_string(product.get_price())
		));
		listaProduse->addItem(item);
	}


	tableMagazin->clearContents();
	tableMagazin->setRowCount(magazine.size());
	int linenumber = 0;
	for(const auto& magazin:magazine)
	{
		tableMagazin->setItem(linenumber, 0, new QTableWidgetItem(QString::fromStdString(magazin.get_name())));
		tableMagazin->setItem(linenumber, 1, new QTableWidgetItem(QString::fromStdString(magazin.get_producer())));
		tableMagazin->setItem(linenumber, 2, new QTableWidgetItem(QString::fromStdString(magazin.get_type())));
		tableMagazin->setItem(linenumber, 3, new QTableWidgetItem(QString::fromStdString(to_string(magazin.get_price()))));
		linenumber++;
	}


	int cnt = 0;
	for (int i = 0; i < srv.get_all().size(); i++)
		if (srv.get_all().at(i).get_type() == "Profi")
			cnt++;
	if (cnt == 0)
		btnProfi->setVisible(false);
	else
		btnProfi->setVisible(true);

	cnt = 0;
	for (int i = 0; i < srv.get_all().size(); i++)
		if (srv.get_all().at(i).get_type() == "Selgros")
			cnt++;
	if (cnt == 0)
		btnSelgros->setVisible(false);
	else
		btnSelgros->setVisible(true);

	cnt = 0;
	for (int i = 0; i < srv.get_all().size(); i++)
		if (srv.get_all().at(i).get_type() == "Mega")
			cnt++;
	if (cnt == 0)
		btnMega->setVisible(false);
	else
		btnMega->setVisible(true);

	cnt = 0;
	for (int i = 0; i < srv.get_all().size(); i++)
		if (srv.get_all().at(i).get_type() == "Minimarket")
			cnt++;
	if (cnt == 0)
		btnMinimarket->setVisible(false);
	else
		btnMinimarket->setVisible(true);

	cnt = 0;
	for (int i = 0; i < srv.get_all().size(); i++)
		if (srv.get_all().at(i).get_type() == "Altele")
			cnt++;
	if (cnt == 0)
		btnAltele->setVisible(false);
	else
		btnAltele->setVisible(true);

}

void MagazinGUI::reloadMagazinCosList(vector<Magazin> magazine) {


	this->listaCos->clear();
	for (const auto& elem : magazine) {
		auto item = new QListWidgetItem(QString::fromStdString(
			elem.get_name() + " " + elem.get_producer() + " " + elem.get_type() + " " + std::to_string(elem.get_price())
		));
		this->listaCos->addItem(item);
	}
}

void MagazinGUI::guiAddMagazin()
{
	try {
		string nume = editnume->text().toStdString();
		string producer = editproducer->text().toStdString();
		string tip = edittip->text().toStdString();
		int pret = editprice->text().toInt();

		editnume->clear();
		editproducer->clear();
		edittip->clear();
		editprice->clear();

		this->srv.add(nume, tip, pret, producer);
		this->reloadMagazinList(this->srv.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Magazin adaugata cu succes."));


		auto lyRight = new QVBoxLayout;
		vector<Magazin>magazine = srv.get_all();
		for(const auto& pr:magazine)
		{
			auto btn = new QPushButton(QString::fromStdString(pr.get_type()));
			lyRight->addWidget(btn);

			connect(btn, &QPushButton::clicked, [&]()
			{
					int cnt = 0;
					for (int i = 0; i < magazine.size(); i++) {
						if (magazine.at(i).get_type() == pr.get_type())
							cnt++;
					}
					if (cnt > 0)
						QMessageBox::information(nullptr, "Info", QString::fromStdString("Nr magazine cu tipul " + pr.get_type() + ": %1").arg(cnt));
					else
						btn->setVisible(false);
			});

		}

		
		

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", "");
	}
	catch (Exception& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}
}

void MagazinGUI::guiModifyMagazin()
{
	try {
		string nume = editnume->text().toStdString();
		string producer = editproducer->text().toStdString();
		string tip = edittip->text().toStdString();
		int pret = editprice->text().toInt();

		editnume->clear();
		editproducer->clear();
		edittip->clear();
		editprice->clear();

		this->srv.modifica(nume, tip, pret, producer);
		this->reloadMagazinList(this->srv.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Magazin modificat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", "");
	}
	catch (Exception& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}
}

void MagazinGUI::guiDeleteMagazin()
{
	try {
		string nume = editnume->text().toStdString();
		string producer = editproducer->text().toStdString();
		string tip = edittip->text().toStdString();
		int pret = editprice->text().toInt();

		editnume->clear();
		editproducer->clear();
		edittip->clear();
		editprice->clear();

		this->srv.sterge(nume, tip);
		this->reloadMagazinList(this->srv.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Magazin sters cu succes."));



	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", "");
	}
	catch (Exception& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}
}