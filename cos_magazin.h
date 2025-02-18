#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "repo_magazin.h"
#include "observer.h"

using namespace std;

class CosMagazin:public Observable
{
private:
	vector<Magazin> cosMagazin;
	RepoMagazin& rep;



public:
	CosMagazin(RepoMagazin& rep): rep{rep} {}

	/*
	 * Adauga cumparaturi in cos.
	 * @param m:magazinul ce trebuie adaugata in cos.
	 */
	void adauga_magazin_cos(const Magazin& m);

	/*
	 * Adauga un numar de cumparaturi in cos.
	 * @param magazine: cumparaturile random ce trebuie adaugate in cos.
	 * @param numar: numarul de cmparaturi ce trebuie adaugate.
	 */
	void adauga_magazin_random_cos(vector<Magazin> magazine, int nr);

	//un vector cu toate cumparaturile din cos
	const vector<Magazin>& get_all_cos();	

	//strege toate cumparaturile din cos
	void sterge_cos();

	void umple(int cate)
	{	
		int seed = chrono::system_clock::now().time_since_epoch().count();
		vector<Magazin> all = rep.get_all();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed)); //amesteca vectorul v
		while (cosMagazin.size() < cate && all.size() > 0) {
			cosMagazin.push_back(all.back());
			all.pop_back();
		}
		//notificam can dse schimba ceva in cos
		notify();
	}

	void exportaCos(string filename);

};