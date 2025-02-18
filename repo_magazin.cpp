#include "repo_magazin.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>	
#include <algorithm>
#include <fstream>
using std::ostream;
using std::stringstream;
using std::string;
using std::exception;

bool RepoMagazin::exist(const Magazin& m)
{
	try
	{

		cauta(m.get_name(), m.get_type());
		return true;
	}
	catch (RepoException&)
	{
		return false;
	}
}

//verifica daca magazinul nu exista deja in lista, altfel arunca exceptie
void RepoMagazin::adauga(const Magazin& magazin)
{
	if (exist(magazin))
		throw RepoException("Magazinul exista deja\n");
	else
		magazine.push_back(magazin);


}
//cauta dupa nume si tip in lista de magazine si verifica daca exista asau nu
const Magazin& RepoMagazin::cauta(string name, string type)
{
	auto it = find_if(magazine.begin(), magazine.end(), [&](const Magazin& m)
	{
			return m.get_name() == name && m.get_type() == type;
	});
	if (it != magazine.end())
		return*it;
	throw RepoException{ "Nu exista niciun magazin cu cerintele date" };

}

//functie de stergere
//verifica daca exista deja, daca nu arunca exceptie
void RepoMagazin::sterge(const Magazin& m)
{
	if(!exist(m))
		throw RepoException{ "Nu exista niciun magazin cu cerintele date" };

	int i = 0;
	while(i<magazine.size())
	{
		if (magazine.at(i).get_name() == m.get_name() && magazine.at(i).get_type() == m.get_type()) {

			magazine.erase(magazine.begin() + i);
			break;
		}
		i++;

		
	}
	
}

void FileRepoMagazin::load_from_file()
{
	std::ifstream in(filename);
	if (!in.is_open())
		throw RepoException("Eroare la deschiderea fisierului");
	string name, type, producer;
	double price;
	while (in >> name >> type >> price >> producer)
	{
		Magazin m{ name, type, price, producer };
		RepoMagazin::adauga(m);
	}

	in.close();
}

void FileRepoMagazin::write_to_file()
{
	std::ofstream out(filename);

	if (!out.is_open())
		throw RepoException("Eroare la deschiderea fisierului");
	for (auto& m : RepoMagazin::get_all())
	{
		out << m.get_name() << endl << m.get_type() << endl << m.get_price() << endl << m.get_producer() << endl;
	}
	out.close();

}



//suprascriu operatorul<< pentru a arunca exceptia 
ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}




