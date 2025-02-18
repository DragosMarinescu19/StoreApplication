#pragma once
#include "domain.h"
#include "repo_magazin.h"

class ActiuneUndo
{
public:

	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};

};

class UndoAdauga: public ActiuneUndo
{
private:

	Magazin magazin_adaugat;
	RepoAbstract& rep;

public:

	UndoAdauga(RepoAbstract& rep, Magazin& magazin_adaugat): rep{rep}, magazin_adaugat{magazin_adaugat} {}

	void doUndo() override
	{
		rep.sterge(magazin_adaugat);
	}
};

class UndoModifica : public ActiuneUndo
{
private:

	Magazin magazin_vechi;
	Magazin magazin_nou;
	RepoAbstract& rep;

public:

	UndoModifica(RepoAbstract& rep, Magazin& magazin_vechi, Magazin& magazin_nou) : rep{ rep }, magazin_vechi{ magazin_vechi},
		magazin_nou{magazin_nou} {}

	void doUndo() override
	{
		rep.sterge(magazin_nou);
		rep.adauga(magazin_vechi);
	}
};

class UndoSterge : public ActiuneUndo
{
private:

	Magazin magazin_sters;
	RepoAbstract& rep;

public:

	UndoSterge(RepoAbstract& rep, Magazin& magazin_sters ): rep{ rep }, magazin_sters{ magazin_sters } {}

	void doUndo() override
	{
		rep.adauga(magazin_sters);
	}
};