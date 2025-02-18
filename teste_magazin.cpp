#include "teste_magazin.h"
#include <assert.h>
#include <cassert>
#include <sstream>
#include <vector>
using std::ostream;
using std::stringstream;


void test_adauga_repo()
{
	RepoMagazin repo;
	Magazin m("a", "a", 122, "a");
	repo.adauga(m);
	const auto magazine = repo.get_all();
	assert(magazine.size() == 1);

	try {
		repo.adauga(m);
		assert(false);
	}
	catch (const RepoException& ex)
	{
		stringstream os;
		os << ex;
		assert(os.str().find("Exista") >= 0);

	}

}
void test_adauga_service()
{
	RepoMagazin rep;
	Validator valid;
	CosMagazin cos{rep};
	assert(rep.get_all().size() == 0);
	ServiceMagazin serv{ rep ,valid,cos };
	serv.add("s", "s", 12, "s");
	auto magazine = serv.get_all();
	assert(magazine.size() == 1);

	try {
		serv.add("12343", "", -2, "12"); assert(false);
	}
	catch (Exception& exception) {
		assert(exception.get_message().find("corect") != std::string::npos);
		assert(true);
	}

}

void test_cauta()
{
	RepoMagazin repo;
	Magazin m{ "a","a",1,"b" };
	repo.adauga(m);
	assert(repo.get_all().size() == 1);
	m = repo.cauta("a", "a");
	assert(m.get_price() == 1);
	assert(m.get_name() == "a");
	assert(m.get_producer() == "b");
	assert(m.get_type() == "a");

	try
	{
		repo.cauta("s", "s");
		assert(false);
	}
	catch (RepoException& ex)
	{
		stringstream os;
		os << ex;
		assert(os.str().find("exista") >= 0);
		assert(true);
	}
}

void test_sterge()
{
	Magazin m{ "a","b",1,"c" };
	RepoMagazin repo;
	repo.adauga(m);
	assert(repo.get_all().size() == 1);
	Magazin m2{ "s","b",100,"c" };
	Magazin m3{ "f","c",1,"c" };
	repo.adauga(m2);
	repo.adauga(m3);
	repo.sterge(m2);
	repo.sterge(m3);
	repo.sterge(m);

	assert(repo.get_all().size() == 0);


}

void test_getAll()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	repo.adauga(Magazin("a", "a", 1, "a"));
	assert(repo.get_all().size() == 1);
	repo.adauga(Magazin("b", "c", 1, "a"));
	assert(repo.get_all().size() == 2);
	auto magazine = serv.get_all();
	assert(magazine.size() == 2);

}

void test_modifica()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	serv.add("a", "a", 100, "s");
	serv.modifica("a", "a", 10, "b");
	const auto m = repo.cauta("a", "a");
	assert(m.get_price() == 10);
	assert(m.get_name() == "a");
	assert(m.get_producer() == "b");
	assert(m.get_type() == "a");

}

void test_sterge_serv()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	repo.adauga(Magazin("a", "a", 1, "a"));
	assert(repo.get_all().size() == 1);
	try {
		serv.sterge("La munte", "Sinaia");
	}
	catch (RepoException& ex) {
		stringstream os;
		os << ex;
		assert(os.str().find("exista") > 0);
		assert(true);
	}

	serv.sterge("a", "a");
	assert(serv.get_all().size() == 0);

}

void test_filtrare_nume()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	repo.adauga(Magazin("a", "a", 1, "a"));
	assert(repo.get_all().size() == 1);
	repo.adauga(Magazin("b", "c", 1, "a"));
	repo.adauga(Magazin("a", "x", 1, "v"));
	auto mag = serv.filtrareNume("a");
	assert(mag.size() == 2);
	assert(mag.at(0).get_type() == "a");
	assert(mag.at(0).get_price() == 1);
	assert(mag.at(0).get_producer() == "a");
	assert(mag.at(1).get_type() == "x");
	assert(mag.at(1).get_price() == 1);
	assert(mag.at(1).get_producer() == "v");
	auto mag2 = serv.filtrareNume("asas");
	assert(mag2.size() == 0);
}

void test_filtrare_pret()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	repo.adauga(Magazin("a", "a", 201, "a"));
	assert(repo.get_all().size() == 1);
	repo.adauga(Magazin("b", "c", 100, "a"));
	repo.adauga(Magazin("a", "x", 199, "v"));
	auto mag = serv.filtrarePret(200);
	assert(mag.size() == 2);
	assert(mag.at(0).get_type() == "c");
	assert(mag.at(0).get_price() == 100);
	assert(mag.at(0).get_producer() == "a");
	assert(mag.at(1).get_type() == "x");
	assert(mag.at(1).get_price() == 199);
	assert(mag.at(1).get_producer() == "v");
	auto mag2 = serv.filtrarePret(10);
	assert(mag2.size() == 0);
}

void test_filtrare_producator()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo ,valid,cos };
	repo.adauga(Magazin("a", "a", 1, "a"));
	assert(repo.get_all().size() == 1);
	repo.adauga(Magazin("b", "c", 1, "a"));
	repo.adauga(Magazin("a", "x", 1, "v"));
	auto mag = serv.filtrareProducator("a");
	assert(mag.size() == 2);
	assert(mag.at(0).get_type() == "a");
	assert(mag.at(0).get_price() == 1);
	assert(mag.at(0).get_name() == "a");
	assert(mag.at(1).get_type() == "c");
	assert(mag.at(1).get_price() == 1);
	assert(mag.at(1).get_name() == "b");
	auto mag2 = serv.filtrareProducator("asas");
	assert(mag2.size() == 0);
}


void test_sortare_magazine()
{
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin serv{ repo,valid ,cos };
	serv.add("a", "b", 100, "c");
	serv.add("sa", "c", 10, "d");
	serv.add("a", "x", 2000, "h");
	serv.add("a", "d", 20, "c");

	auto list = serv.sort_by_name();
	auto list2 = serv.sort_by_price();
	auto list3 = serv.sort_by_name_type();

	assert(list.size() == 4);
	assert(list.at(0).get_name() == "a");
	assert(list.at(3).get_name() == "sa");

	assert(list2.size() == 4);
	assert(list2.at(0).get_price() == 10);
	assert(list2.at(3).get_price() == 2000);

	assert(list3.size() == 4);
	assert(list3.at(0).get_name() == "a");
	assert(list.at(3).get_name() == "sa");
}

void test_raport() {
	RepoMagazin rep;
	Validator valid;
	CosMagazin cos{rep};
	ServiceMagazin service{ rep, valid, cos };
	service.add("a", "b", 100, "x");
	service.add("sa", "a", 200, "y");
	service.add("t", "y", 300, "z");
	service.add("o", "xc", 400, "v");
	service.add("lolo", "a", 500, "m");

	auto map = service.frecvente_type();
	assert(map.size() == 4);
}

void test_undo() {
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin service{ repo, valid, cos };
	try {
		service.undo();
	}
	catch (Exception ex) {
		assert(true);
	}
	service.add("unu", "a", 1233, "asa");
	service.add("doi", "b", 890, "mnbh");
	service.modifica("unu", "a", 456, "vgbhj");
	service.sterge("doi", "b");
	service.undo();
	assert(service.get_all().size() == 2);
	auto oferta = repo.cauta("unu", "a");
	service.undo();
	service.undo();
	try {
		repo.cauta("doi", "b");
	}
	catch (RepoException ex) {
		assert(true);
	}
	service.undo();
	assert(service.get_all().empty());
}

void test_fisier() {
	FileRepoMagazin repo{
			"C:/Users/marin/OneDrive/Desktop/OOP/lab6_7/lab6_7/magazin.txt" };
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin service{ repo, valid, cos };
	int x = int(service.get_all().size());
	assert(service.get_all().size() == x);
	service.add("c", "c", 456, "nbhju");
	int nr = int(service.get_all().size());
	assert(service.get_all().size() == nr);
	service.sterge("c", "c");
}

void test_cos() {
	RepoMagazin repo;
	Validator valid;
	CosMagazin cos{repo};
	ServiceMagazin service{ repo, valid, cos };
	service.add("a", "b", 100, "asa");
	service.add("sa", "a", 50, "asas");
	service.add("t", "y", 789, "nb");
	service.add("o", "xc", 762, "vgy");
	service.cos_adauga("a", "b");
	assert(service.get_all_cos().size() == 1);
	try {
		service.cos_adauga("aaaa", "aaaa");
	}
	catch (RepoException&) {
		assert(true);
	}
	assert(service.get_all_cos().size() == 1);
	service.cos_sterge();
	service.cos_adauga_random(3);
	assert(service.get_all_cos().size() == 3);

	// test export

	string fisier_csv = "C:/Users/marin/OneDrive/Desktop/OOP/lab6_7/lab6_7/test.csv/";
	string fisier_html = "C:/Users/marin/OneDrive/Desktop/OOP/lab6_7/lab6_7/test.html/";
	string fisier_alt = "C:/Users/marin/OneDrive/Desktop/OOP/lab6_7/lab6_7/test_cos.txt/";
	service.cos_export(fisier_csv);
	service.cos_export(fisier_html);
	try {
		service.cos_export(fisier_alt);
	}
	catch (Exception exception) {
		//assert(exception.get_message() == "Fisierul nu este valid!");
		assert(true);
	}
}

void test_repo_lab()
{
	RepoLab repolab;
	repolab.set_probabilitate(1);
	assert(repolab.get_all().size() == 0);
	Magazin m{ "a","a",100,"a" };
	repolab.adauga(m);
	assert(repolab.get_all().size() == 1);

	Magazin m2{ "nume_magazin", "tip_magazin", 100, "adresa_magazin" };
	repolab.adauga(m2);


	Magazin found_magazin = repolab.cauta("nume_magazin", "tip_magazin");

	assert(found_magazin.get_name() == m2.get_name());
	assert(found_magazin.get_type() == m2.get_type());

	auto magazine = repolab.get_all();
	assert(magazine.size() == 2);
	assert(magazine.at(0).get_name() == "a");
	assert(magazine.at(1).get_name() == "nume_magazin");
	assert(repolab.exist(m) == true);
	assert(repolab.exist(m2) == true);
	repolab.sterge(m);

	/*try
	{
		repolab.adauga(m2);//exista deja
	}
	catch(Exception& )
	{
		assert(true);
	}
	*/



	Magazin m3{ "s","c",123,"x" };
	repolab.set_probabilitate(0);
	try {
		repolab.adauga(m3);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try
	{
		repolab.exist(m);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}




}

void test_all()
{
	test_adauga_repo();
	test_adauga_service();
	test_cauta();
	test_filtrare_nume();
	test_filtrare_pret();
	test_filtrare_producator();
	test_getAll();
	test_modifica();
	test_sterge();
	test_sterge_serv();
	test_sortare_magazine();
	test_fisier();
	test_cos();
	test_raport();
	test_undo();
	test_repo_lab();
}
