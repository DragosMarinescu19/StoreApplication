#pragma once
#ifndef REPO_MAGAZIN_H
#define REPO_MAGAZIN_H

#include "domain.h"
#include <utility>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <unordered_map>
#include <random>

using namespace std;

class RepoAbstract
{
public:
	RepoAbstract() = default;

	RepoAbstract(const RepoAbstract& ot) = delete;

	//adaug magazinul
	virtual void adauga(const Magazin& m) = 0;

	//sterge oferta
	virtual void sterge(const Magazin& m) = 0;

	//caut oferta
	virtual const Magazin& cauta(string name, string type) = 0;

	virtual vector<Magazin>& get_all() = 0;


};


class RepoMagazin :public RepoAbstract {
private:
	vector<Magazin> magazine;
	bool exist(const Magazin& m);
public:
	RepoMagazin(const RepoMagazin& ot) = delete;
	RepoMagazin() = default;// constructor 

	vector<Magazin>& get_all() override {
		return magazine;
	}

	const Magazin& cauta(string name, string type) override;
	void sterge(const Magazin& m) override;
	void adauga(const Magazin& magazin) override; //nu se modifica lista

};

class FileRepoMagazin :public RepoMagazin
{
private:

	string filename;

	void load_from_file();
	void write_to_file();

public:

	explicit FileRepoMagazin(string filename) : RepoMagazin(), filename{ filename }
	{
		load_from_file();
	}

	void adauga(const Magazin& m) override
	{
		RepoMagazin::adauga(m);	
		write_to_file();
	}

	void sterge(const Magazin& m) override
	{
		RepoMagazin::sterge(m);
		write_to_file();
	}
};

class RepoLab : public RepoAbstract
{
private:

	std::unordered_map<int, Magazin> magazine;
	double probabilitate;

	//functia ce returneaza probabilitatea
	void random() const;



public:


	RepoLab() {
		std::mt19937 gen(123);
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		probabilitate = dis(gen);
	};

	bool exist(const Magazin& m);

	void set_probabilitate(double p);

	RepoLab(const RepoMagazin& alt) = delete;

	void adauga(const Magazin& m) override;

	void sterge(const Magazin& m) override;

	const Magazin& cauta(string name, string type) override;

	vector<Magazin>& get_all() override;
};

class RepoException {
	string msg;
public:
	explicit RepoException(string m) : msg{ std::move(std::move(m)) } {} // m este un obiect temporar, astfel nu se cpiaza ineficient
	/*string get_message() {
		return msg;
	}*/
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};
ostream& operator<<(ostream& out, const RepoException& ex);
#endif