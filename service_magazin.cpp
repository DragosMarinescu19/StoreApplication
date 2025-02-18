#include "service_magazin.h"
#include<string>
#include <vector>
#include <algorithm>
#include <fstream>



//functie de adaugare
void ServiceMagazin::add(const string& name, const string& type, double price, const string& producer)
{
	valid.validatemagazin(name, type, price, producer);
	Magazin m{ name,type,price,producer };
	rep.adauga(m);
	undoActions.push_back(make_unique<UndoAdauga>(rep, m));
}

//Functie de modificare
//verifica daca exista obiectul cautata, daca nu arunca exceptie
void ServiceMagazin::modifica(const string& name, const string& type, double price, const string& producer)
{
	valid.validatemagazin(name, type, price, producer);
	Magazin m = rep.cauta(name, type);
	rep.sterge(m);
	Magazin nou{ name,type,price,producer };
	rep.adauga(nou);
	undoActions.push_back(make_unique<UndoModifica>(rep, m, nou));
}

//Functie de stergere
//verifica daca exista obiectul cautata, daca nu arunca exceptie
void ServiceMagazin::sterge(const string& name, const string& type)
{
	valid.validatemagazin(name, type, 1, "exemplu");
	Magazin m = rep.cauta(name, type);
	rep.sterge(m);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, m));

}

//functie de filtrare dupa nume
vector<Magazin> ServiceMagazin::filtrareNume(const string& name)
{
	const vector<Magazin>& magazine = get_all();
	vector<Magazin> magazine_filtrate;
	std::copy_if(magazine.begin(), magazine.end(), back_inserter(magazine_filtrate), [name](const Magazin& m) {
		return m.get_name() == name;
		});
	return (magazine_filtrate);
}
//funcie de filtrare dupa pret
vector<Magazin> ServiceMagazin::filtrarePret(double price)
{
	vector<Magazin> m = get_all();
	vector<Magazin> magazine_filtrate;
	copy_if(m.begin(), m.end(), back_inserter(magazine_filtrate), [&](const Magazin& m1)
	{
			return m1.get_price() == price;
	});
	return magazine_filtrate;

}

//functie de filtarre producer
vector<Magazin> ServiceMagazin::filtrareProducator(const string& producer)
{


	const vector<Magazin> magazine = get_all();
	vector<Magazin> magazine_filtrate;
	std::copy_if(magazine.begin(), magazine.end(), back_inserter(magazine_filtrate), [producer](const Magazin& m) {
		return m.get_producer() == producer;
		});
	return(magazine_filtrate);
}

vector<Magazin> ServiceMagazin::sort_by_name()
{
	vector<Magazin> sortedCopy{ rep.get_all() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmp_name);
	return sortedCopy;
}

vector<Magazin> ServiceMagazin::sort_by_price()
{

	vector<Magazin> sorted_copy = get_all();// sau cu functie lambda
	sort(sorted_copy.begin(), sorted_copy.end(), [&](const Magazin& m1, const Magazin& m2)
	{
			return m1.get_price() < m2.get_price();
	});
	return sorted_copy;
}

vector<Magazin> ServiceMagazin::sort_by_name_type()
{
	vector<Magazin> sortedCopy{ rep.get_all() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmp_name_type);
	return sortedCopy;
}

unordered_map<string, int> ServiceMagazin::frecvente_type() {
	unordered_map<string, int> map;
	vector<Magazin> m = this->get_all();
	for (const auto& i : m) {
		if (map.find(i.get_type()) != map.end())
			map[i.get_type()]++;
		else
			map[i.get_type()] = 1;
	}
	return map;
}

void ServiceMagazin::cos_adauga(const string& name, const string& type) {
	const auto& magazin = rep.cauta(name, type);
	cos_curent.adauga_magazin_cos(magazin);
}

int ServiceMagazin::cos_adauga_random(int nr) {
	cos_curent.adauga_magazin_random_cos(this->get_all(), nr);
	return static_cast<int>(cos_curent.get_all_cos().size());

}

const vector<Magazin>& ServiceMagazin::get_all_cos()
{
	return cos_curent.get_all_cos();
}

void ServiceMagazin::cos_sterge()
{
	cos_curent.sterge_cos();
}

void ServiceMagazin::cos_export(const string& filename)
{


	if (filename.find(".csv") == std::string::npos && filename.find(".html") == std::string::npos)
	{
		throw Exception("Fisierul nu este valid");
	}
	else
	{
		ofstream fout(filename);
		if (filename.find(".html") != std::string::npos)
		{
			fout << "<html>";
			fout << "<style> table, th, td {border:1px solid black} body{background-color: #E6E6FA;} </style>";
			fout << "<body>";
			fout << "<h1> COS CUMPARATURI </h1>";
			fout << "<table><tr><th>Nume</th> <th>Tip</th> <th>Pret</th> <th>tip </th><th>Producator</th></tr>";
			for (auto& m : get_all_cos())
			{
				fout << "<tr><td>" << m.get_name() << "<td>" << m.get_type() << "</td><td>" << m.get_price()
					<< "</td><td>" << m.get_producer() << "</td></tr>";
			}
			fout << "</table></body>";
			fout << "<html>";
		}
		else
		{
			for (auto& m : get_all_cos())
			{
				fout << m.get_name() << ";" << m.get_type() << ";" << m.get_price() << ";" << m.get_producer() << endl;
			}
		}
		fout.close();
	}
}

void ServiceMagazin::undo()
{
	if (undoActions.empty())
		throw Exception("Nu mai exista operatii pentru a se face undo");
	undoActions.back()->doUndo();
	undoActions.pop_back();

}