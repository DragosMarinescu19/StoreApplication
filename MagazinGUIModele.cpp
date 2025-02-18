#include "MagazinGUIModele.h"

void MagazinGUIModele::initGUI()
{
    //main layout
    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);

    //left part of the window, pentru care setam layout vertical
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    // Form layout
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);

    // Initialize form fields
    editnume = new QLineEdit;
    editproducer = new QLineEdit;
    editTip = new QLineEdit;
    editPret = new QLineEdit;

    lblnume = new QLabel("Nume:");
    lblproducer = new QLabel("Producator:");
    lblTip = new QLabel("Tip:");
    lblPret = new QLabel("Pret:");

    lyForm->addRow(lblnume, editnume);
    lyForm->addRow(lblproducer, editproducer);
    lyForm->addRow(lblTip, editTip);
    lyForm->addRow(lblPret, editPret);

    // Add buttons
    btnAddMagazin = new QPushButton("Adauga Magazin");
    lyForm->addWidget(btnAddMagazin);
    btnModifyMagazin = new QPushButton("Modifica magazin");
    lyForm->addWidget(btnModifyMagazin);
    btnDeleteMagazin = new QPushButton("Delete Magazin");
    lyForm->addWidget(btnDeleteMagazin);

    // Add form to the left layout
    lyLeft->addWidget(form);

    // GroupBox for sorting
    QVBoxLayout* lyRadioBox = new QVBoxLayout;
    groupBox = new QGroupBox("Sortare");
    groupBox->setLayout(lyRadioBox);
    radioSrtNume = new QRadioButton("Sortare dupa nume");
    radioSrtPret = new QRadioButton("Sortare dupa pret");
    radioSrtNumeTip = new QRadioButton("Sortare dupa nume si tip");
    lyRadioBox->addWidget(radioSrtNume);
    lyRadioBox->addWidget(radioSrtPret);
    lyRadioBox->addWidget(radioSrtNumeTip);
    btnSortMagazin = new QPushButton("Sorteaza magazine");
    lyRadioBox->addWidget(btnSortMagazin);
    lyLeft->addWidget(groupBox);

    // Filter form
    QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);

    editFilterPret = new QLineEdit;
    lblFilterCriteria = new QLabel("Filtrare pret:");
    lyFormFilter->addRow(lblFilterCriteria, editFilterPret);
    btnFilterMagazin1 = new QPushButton("Filtreaza oferte dupa pret");
    lyFormFilter->addWidget(btnFilterMagazin1);

    editFilterProducer = new QLineEdit;
    lblFilterCriteria2 = new QLabel("Filtrare producator:");
    lyFormFilter->addRow(lblFilterCriteria2, editFilterProducer);
    btnFilterMagazin2 = new QPushButton("Filtreaza oferte dupa producator");
    lyFormFilter->addWidget(btnFilterMagazin2);

    lyLeft->addWidget(formFilter);

    // Other buttons
    btnReloadData = new QPushButton("Reload data");
    lyLeft->addWidget(btnReloadData);
    btnUndo = new QPushButton("Undo");
    lyLeft->addWidget(btnUndo);
    btnCos = new QPushButton("Cos");
    lyLeft->addWidget(btnCos);

    addCos = new QPushButton("Adauga magazin in cos");
    numeCos = new QLineEdit;
    addRandomCos = new QPushButton("Adauga magazine random in cos");
    editRandom = new QLineEdit;
    golesteCos = new QPushButton("Goleste cos");
    editExport = new QLineEdit;
    listaCos = new QListWidget();
    exportCos = new QPushButton("Export cos");

    // Right layout - contains the table
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);
    lyRight->addWidget(tblV);
    btnCosCRUDGUI = new QPushButton("CosCRUDGui");
    lyRight->addWidget(btnCosCRUDGUI);
    btnCosReadOnlyGUI = new QPushButton("CosReadOnlyGUI");
    lyRight->addWidget(btnCosReadOnlyGUI);
    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void MagazinGUIModele::connectSignalsSlots()
{
    QObject::connect(btnAddMagazin, &QPushButton::clicked, this, &MagazinGUIModele::guiAddMagazin);
    QObject::connect(btnModifyMagazin, &QPushButton::clicked, this, &MagazinGUIModele::guiModifyMagazin);
    QObject::connect(btnDeleteMagazin, &QPushButton::clicked, this, &MagazinGUIModele::guiDeleteMagazin);

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
        });

    QObject::connect(btnFilterMagazin2, &QPushButton::clicked, [&]() {
        string filterC = this->editFilterProducer->text().toStdString();
        this->reloadMagazinList(srv.filtrareProducator(filterC));
        });

    QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
        this->reloadMagazinList(srv.get_all());
        });

    QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
            editnume->setText("");
            editproducer->setText("");
            editTip->setText("");
            editPret->setText("");
            return;
        }
        int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = tblV->model()->index(selRow, 0);
        auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
        editnume->setText(cel0Value);
        auto cel1Index = tblV->model()->index(selRow, 1);
        auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
        editproducer->setText(cel1Value);
        auto cel2Index = tblV->model()->index(selRow, 2);
        auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
        editTip->setText(cel2Value);
        auto cel3Index = tblV->model()->index(selRow, 3);
        auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
        editPret->setText(cel3Value);
        });

    QObject::connect(btnCos, &QPushButton::clicked, [&]() {
        QWidget* fereastraCos = new QWidget;
        QFormLayout* lyCos = new QFormLayout;
        fereastraCos->setLayout(lyCos);
        numeCos = new QLineEdit;
        lyCos->addRow("Nume magazin: ", numeCos);
        producerCos = new QLineEdit;
        lyCos->addRow("Producator magazin: ", producerCos);
        lyCos->addWidget(addCos);
        lblRandom = new QLabel("Nr. random:");
        lyCos->addRow(lblRandom, editRandom);
        lyCos->addWidget(addRandomCos);
        lyCos->addWidget(golesteCos);
        lblExport = new QLabel("Fisier export:");
        lyCos->addRow(lblExport, editExport);
        lyCos->addWidget(exportCos);
        lyCos->addWidget(listaCos);
        fereastraCos->show();
        });

    QObject::connect(addCos, &QPushButton::clicked, [&]() {
        try {
            string nume = numeCos->text().toStdString();
            string producer = producerCos->text().toStdString();
            numeCos->clear();
            producerCos->clear();
            this->srv.cos_adauga(nume, producer);
            this->reloadMagazinList(this->srv.get_all_cos());
        }
        catch (RepoException& repoException) {
            QMessageBox::warning(this, "Warning", "Magazinul nu exista!");
        }
        });

    QObject::connect(addRandomCos, &QPushButton::clicked, [&]() {
        try {
            int nr = editRandom->text().toInt();
            editRandom->clear();
            this->srv.cos_adauga_random(nr);
            this->reloadMagazinList(this->srv.get_all_cos());
        }
        catch (RepoException& repoException) {
            QMessageBox::warning(this, "Warning", "Nu exista magazine");
        }
        });

    QObject::connect(golesteCos, &QPushButton::clicked, [&]() {
        try {
            this->srv.cos_sterge();
            this->reloadMagazinList(this->srv.get_all_cos());
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
            this->reloadMagazinList(this->srv.get_all_cos());
        }
        catch (RepoException) {
            QMessageBox::warning(this, "Warning", "");
        }
        });

    QObject::connect(btnCosCRUDGUI, &QPushButton::clicked, [&]() {
        auto fereastraNoua = new CosGUILista{ srv.getCos() };
        fereastraNoua->show();
        });

    QObject::connect(btnCosReadOnlyGUI, &QPushButton::clicked, [&]() {
        auto fereastraFiguri = new HistogramGUI(srv.getCos());
        fereastraFiguri->show();
        });
}

void MagazinGUIModele::reloadMagazinList(std::vector<Magazin> magazine)
{
    modelTabel->setMagazine(magazine);
}

void MagazinGUIModele::guiAddMagazin()
{
    try {
        string nume = editnume->text().toStdString();
        string producer = editproducer->text().toStdString();
        string tip = editTip->text().toStdString();
        int pret = editPret->text().toInt();

        editnume->clear();
        editproducer->clear();
        editTip->clear();
        editPret->clear();

        this->srv.add(nume, tip, pret, producer);
        this->reloadMagazinList(this->srv.get_all());

        QMessageBox::information(this, "Info", QString::fromStdString("Magazin adaugat cu succes."));

        auto lyRight = new QVBoxLayout;
        vector<Magazin> magazine = srv.get_all();
        for (const auto& pr : magazine)
        {
            auto btn = new QPushButton(QString::fromStdString(pr.get_type()));
            lyRight->addWidget(btn);

            connect(btn, &QPushButton::clicked, [&]() {
                int cnt = 0;
                for (const auto& mag : magazine) {
                    if (mag.get_type() == pr.get_type())
                        cnt++;
                }
                if (cnt > 0)
                    QMessageBox::information(nullptr, "Info", QString::fromStdString("Nr magazine cu tipul " + pr.get_type() + ": " + std::to_string(cnt)));
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

void MagazinGUIModele::guiModifyMagazin()
{
    try {
        string nume = editnume->text().toStdString();
        string producer = editproducer->text().toStdString();
        string tip = editTip->text().toStdString();
        int pret = editPret->text().toInt();

        editnume->clear();
        editproducer->clear();
        editTip->clear();
        editPret->clear();

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

void MagazinGUIModele::guiDeleteMagazin()
{
    try {
        string nume = editnume->text().toStdString();
        string producer = editproducer->text().toStdString();
        string tip = editTip->text().toStdString();
        int pret = editPret->text().toInt();

        editnume->clear();
        editproducer->clear();
        editTip->clear();
        editPret->clear();

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
