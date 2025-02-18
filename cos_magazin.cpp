#include "cos_magazin.h"
#include <algorithm>
#include <random>
#include "observer.h"

using namespace std;

void CosMagazin::adauga_magazin_cos(const Magazin& m)
{
	this->cosMagazin.push_back(m);
	notify();
}

void CosMagazin::adauga_magazin_random_cos(vector<Magazin> magazine, int nr)
{
	shuffle(magazine.begin(), magazine.end(), default_random_engine(random_device{}()));//amesteca vectorul v
	int aux = int(cosMagazin.size());
	while (cosMagazin.size() < aux + nr && !magazine.empty())//cosMagazin.size()<nr && 
	{
		cosMagazin.push_back(magazine.back());
		magazine.pop_back();
	}
	notify();
}
const vector<Magazin>& CosMagazin::get_all_cos()
{
	return this->cosMagazin;
}

void CosMagazin::sterge_cos()
{
	this->cosMagazin.clear();
	notify();
}



