#include <algorithm>
#include "repo_magazin.h"
#include "Errors.h"
using namespace std;
void RepoLab::random() const
{
	double random = ((double)rand() / (RAND_MAX));
	if (random > probabilitate)
	{
		random *= 100;
		cout << "Probabilitatea: " << random << endl;
		throw RepoException("Nu se poate executa aceasta functie");
	}


}

bool RepoLab::exist(const Magazin& m)
{
	random();
	for (auto& mg : magazine)
	{
		if (mg.second.get_name() == m.get_name() && mg.second.get_type() == m.get_type())
			return true;

	}
	return false;
}

void RepoLab::set_probabilitate(double p)
{
	probabilitate = p;
}

void RepoLab::adauga(const Magazin& m)
{
	random();
	if (exist(m))
	{
		throw RepoException("Magazinul exista deja");

	}
	int i = int(magazine.size());
	magazine.insert(std::make_pair(i, m));
}

void RepoLab::sterge(const Magazin& m)
{
	random();
	int i = 0;
	while (i < magazine.size() && magazine.at(i).get_name() != m.get_name() && magazine.at(i).get_type() != m.get_type())
	{
		i++;
	}
	if (i >= magazine.size())
		throw RepoException("Magazinul nu exista");
	for (int j = i; j < magazine.size() - 1; j++)
	{
		magazine.at(j) = magazine.at(j + 1);
	}
	magazine.erase((int)magazine.size() - 1);
}

const Magazin& RepoLab::cauta(string name, string type)
{
	random();
	auto it = find_if(magazine.begin(), magazine.end(), [=](const std::pair<int, Magazin> m)
		{
			return m.second.get_name() == name && m.second.get_type() == type;
		});
	if (it == magazine.end())
		throw RepoException("Magazinul nu exista");
	return (*it).second;
}

vector<Magazin> MAGAZINE;

vector<Magazin>& RepoLab::get_all()
{
	random();
	MAGAZINE.clear();

	for (auto& m : magazine)
	{
		MAGAZINE.push_back(m.second);

	}
	return MAGAZINE;
}




