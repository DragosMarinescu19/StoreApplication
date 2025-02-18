#pragma once
#ifndef SERVICE_MAGAZIN_H
#define SERVICE_MAGAZIN_H
#include "Validator.h"
#include "domain.h"
#include "repo_magazin.h"
#include "Errors.h"
#include "cos_magazin.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
using namespace std;

//typedef int(*Sort)(const Magazin&, const Magazin&);

class ServiceMagazin {

	RepoAbstract& rep;
	Validator& valid;
	CosMagazin& cos_curent;

	vector<unique_ptr<ActiuneUndo>> undoActions;
	//VectorDinamic<Magazin> filtrare(const function<bool(const Magazin&)>& fct) const;
public:
	ServiceMagazin(RepoAbstract& rep, Validator& valid, CosMagazin& cos) :rep{ rep }, valid{ valid }, cos_curent{ cos } {

	}
	//constructor de copiere; punem delete fiindca nu vrem sa se faca nicio copie la Service

	ServiceMagazin(const ServiceMagazin& ot) = delete;
	ServiceMagazin() = delete;


	/*
	* Adauga un magazin
	* @param name: numele magazinului
	* @param type: tipul destinatiei
	* @param price: pretul magazinului
	* @param producer: producatorulk magazinului
	* @throws:
	*	Exception daca mai exista magazin cun numele dat
	*	Exception daca magazinul nu este valid
	*/
	void add(const string& name, const string& type, double price, const string& producer);

	void modifica(const string& name, const string& type, double price, const string& producer);
	void sterge(const string& name, const string& type);


	vector<Magazin>& get_all() noexcept {//& dupa magazin
		return rep.get_all();

	}

	vector<Magazin> filtrarePret(double price);
	vector<Magazin> filtrareNume(const string& name);
	vector<Magazin> filtrareProducator(const string& producer);
	vector<Magazin> sort_by_name();
	vector<Magazin> sort_by_price();
	vector<Magazin> sort_by_name_type();

	//Calculeaza frecventa magazinelor in functie de tip si construieste un dictionar
	unordered_map<string, int> frecvente_type();

	void cos_adauga(const string& name, const string& type);
	int cos_adauga_random(int nr);
	const vector<Magazin>& get_all_cos();
	void cos_sterge();
	void cos_export(const string& filename);

	void undo();

	CosMagazin& getCos() {
		return cos_curent;
	}
};



class ServiceException : public Exception {
public:
	explicit ServiceException(const string& err) : Exception(err) {}
};
#endif
