#include<iostream>
#include "ui.h"
#include "domain.h"
#include <vector>
#include "Errors.h"
using namespace std;

void UI::uiClearconsole()
{
	cout << "\n\n\n\n\n\n\n";
}

void UI::uiMENU()
{

	printf("-- MENIU --\n");
	printf("1. Adaugare magazin \n");
	printf("2. Afisare magazine\n");
	printf("3. Modifica magazin\n");
	printf("4. Sterge magazin\n");
	printf("5. Afisare magazine dupa nume\n");
	printf("6. Filtrare magazine dupa suma\n");
	printf("7. Afisare magazine dupa producator\n");
	printf("8. Sortare magazine dupa anumite criterii\n");
	printf("9. Raport privind tipul magazinelor\n");
	printf("10. MENIU COS\n");
	printf("11. UNDO\n");
	printf("0. Iesire din program.\n");
	printf("--\t--\t--\n");

}

void UI::addUI()
{
	string type;
	string name;
	string producer;
	double price;
	cout << "Dati numele:\t";
	cin >> name;
	cout << "Dati tipul:\t";
	cin >> type;
	cout << "Dati pretul:\t";
	cin >> price;
	if (cin.fail()) {
		cout << "Eroare: Pretul trebuie sa fie un numar.\n";
		cin.clear(); // Resetãm starea obiectului cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorãm restul de caractere din bufferul de intrare
		return;
	}
	cout << "Dati un producator:\t";
	cin >> producer;
	try {
		serv.add(name, type, price, producer);
		cout << "Magazin adaugat\n";

	}
	catch (Exception exception) {
		cout << exception.get_message();

	}
}

void UI::afisareUI(const vector<Magazin>& magazine)
{
	cout << "MAGAZINE\n";
	if (magazine.size() == 0)
		cout << "Lista este goala...\n";
	else {
		for (const auto& m : magazine)
		{
			cout << "Nume: " << m.get_name() << " - Tip: " << m.get_type() << " - Pret: " << m.get_price() << " - Producator: " << m.get_producer() << endl;
		}
	}
}

void UI::modificaUI()
{
	cout << "Modificare Magazin" << endl;
	string name, type, producer;
	double price;
	cout << "Numele magazinului de schimbat: ";
	cin >> name;
	cout << "Tipul magazinului de schimbat: ";
	cin >> type;
	cout << "Dati suma :";
	cin >> price;
	if (cin.fail()) {
		cout << "Eroare: Pretul trebuie sa fie un numar.\n";
		cin.clear(); // Resetãm starea obiectului cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorãm restul de caractere din bufferul de intrare
		return;
	}
	cout << "Dati producatorul: ";
	cin >> producer;

	try {
		serv.modifica(name, type, price, producer);
	}
	catch (Exception exception)
	{
		cout << exception.get_message();
	}
}

void UI::stergeUI()
{
	cout << "Stergere Magazin\n";
	string name, type;
	cout << "Dati numele magazinului pe care sa il stergeti: ";
	cin >> name;
	cout << "Dati tipul magazinului pe care sa il stergeti: ";
	cin >> type;

	try {
		serv.sterge(name, type);
		cout << "Oferta s-a sters cu succes!" << endl;
	}
	catch (Exception exception)
	{
		cout << exception.get_message();
	}
}

void UI::filtrareUINume()
{
	cout << "Filtrare dupa nume\n";
	string nume;
	cout << "Dati numele magazinului: ";
	cin >> nume;
	afisareUI(serv.filtrareNume(nume));

}

void UI::filtrareUIPret()
{
	cout << "Filtrare dupa pret\n";
	double price;
	cout << "Dati pretul maxim dupa care sa vedeti magazinele: ";
	cin >> price;
	afisareUI(serv.filtrarePret(price));

}

void UI::filtrareUIProducator()
{
	cout << "Filtrare dupa producator\n";
	string producer;
	cout << "Dati producatorul magazinului: ";
	cin >> producer;
	afisareUI(serv.filtrareProducator(producer));

}


void UI::sortare()
{
	cout << "SORTARE" << endl;
	cout << "1. NUME\t 2. PRET\t 3.NUME/TIP" << endl;
	string optiune;
	cout << "Dati optiunea\t";
	cin >> optiune;
	if (optiune == "1")
	{
		auto lista_sortata = serv.sort_by_name();
		afisareUI(lista_sortata);
	}
	else if (optiune == "2")
	{
		auto lista_sortata = serv.sort_by_price();
		afisareUI(lista_sortata);
	}
	else if (optiune == "3")
	{
		auto lista_sortata = serv.sort_by_name_type();
		afisareUI(lista_sortata);
	}
}

void UI::raportUI() {
	cout << "Raport privind cumparaturile" << endl;
	auto map = serv.frecvente_type();
	for (const auto& pereche : map) {
		cout << pereche.first << ": " << pereche.second << " magazine" << endl;
	}
}

void UI::cos_adauga_UI()
{
	string name, type;
	cout << "Numele obiecului de adaugat in cosul de cumparauri\t";
	cin >> name;
	cout << "Tipul obiectului de adaugat in cosul de cumparaturi\t";
	cin >> type;
	try
	{
		serv.cos_adauga(name, type);
		cout << "S a adaugat cu succes!\n";

	}
	catch (Exception ex)
	{
		cout << ex.get_message() << endl;
	}

}

void UI::cos_adauga_random_UI()
{
	int nr;
	char str[101];
	cout << "Cate obiecte random vreti in cos?\t";
	cin >> str;
	nr = atoi(str);
	if (!(nr < 0 || strlen(str)>10))
	{
		try
		{
			int nr_magazine = serv.cos_adauga_random(nr);
			cout << "S-au adaugat " << nr_magazine << " oferte random in cos " << endl;

		}
		catch (Exception ex)
		{
			cout << ex.get_message() << endl;
		}
	}
	else
		cout << "Numarul este invalid!\n";
}

void UI::cos_sterge_UI()
{
	serv.cos_sterge();
	cout << "S-au sters toate obiectele din cosul de cumparaturi!";
}

void UI::cos_export_UI()
{
	string filename;
	cout << "Dati numele fisierului in care vreti sa salvati cosul de cumparaturi (.csv sau .html): " << endl;
	cin >> filename;
	string referinta = "C:/Users/marin/OneDrive/Desktop/OOP/lab6_7/lab6_7/cos_cumparaturi/";
	serv.cos_export(referinta.append(filename));

}


void UI::MeniuCos() {
	while (true) {
		cout << "COS CUMPARATURI" << endl;
		cout << "Exista " << serv.get_all_cos().size() << " obiecte in cos.\n";
		cout << "---\t---\tMENIU COS CUMPARATURI\t---\t---" << endl;
		cout
			<< "1. Adaugare obiect in cos\n2. Adaugare obiecte random in cos\n3. Goleste cosul\n4. Afisare cos\n5. Export\n6. Iesire\n---\t---\t---\n";
		int optiune;
		cout << "Optiunea: ";
		cin >> optiune;
		try {
			switch (optiune) {
			case 1:
				cos_adauga_UI();
				uiClearconsole();
				break;
			case 2:
				cos_adauga_random_UI();
				uiClearconsole();
				break;
			case 3:
				cos_sterge_UI();
				uiClearconsole();
				break;
			case 4:
				afisareUI(serv.get_all_cos());
				uiClearconsole();
				break;
			case 5:
				cos_export_UI();
				uiClearconsole();
				break;
			case 6:
				cout << "Iesire din cos";
				return;
			default:
				cout << "Comanda invalida!";
			}
		}
		catch (const RepoException& ex) {
			cout << ex << endl;
		}
	}
}


void UI::run()
{
	while (true)
	{
		const auto& lista = serv.get_all();
		uiMENU();
		int cmd;
		cout << "Optiunea:\t";
		cin >> cmd;
		try {
			switch (cmd)
			{
			case 0:
				cout << "Iesire din aplicatie...\n";
				return;
			case 1:
				addUI();
				uiClearconsole();
				break;
			case 2:

				afisareUI(lista);
				uiClearconsole();
				break;
			case 3:
				modificaUI();
				uiClearconsole();
				break;
			case 4:
				stergeUI();
				uiClearconsole();
				break;
			case 5:
				filtrareUINume();
				uiClearconsole();
				break;
			case 6:
				filtrareUIPret();
				uiClearconsole();
				break;
			case 7:
				filtrareUIProducator();
				uiClearconsole();
				break;
			case 8:
				sortare();
				uiClearconsole();
				break;
			case 9:
				raportUI();
				break;
			case 10:
				MeniuCos();
				break;
			case 11:
				try
				{
					serv.undo();
					cout << "S a efectuat operatia undo!" << endl;
				}
				catch (Exception ex)
				{
					cout << ex.get_message() << endl;
				}
				break;

			default:
				cout << "Comanda invalida!\n";

			}
		}
		catch (const RepoException& ex) {
			cout << ex << endl;
		}


	}

}

