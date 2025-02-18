#include "domain.h"
//getteri pentru tip,nume,producer,price
string Magazin::get_type() const
{
	return type;
}

string Magazin::get_name() const
{
	return name;
}

string Magazin::get_producer() const
{
	return producer;
}

double Magazin::get_price() const
{
	return price;
}

bool cmp_name(const Magazin& m1, const Magazin& m2)
{
	return m1.get_name() < m2.get_name();
}

bool cmp_price(const Magazin& m1, const Magazin& m2)
{
	return m1.get_price() < m2.get_price();
}

bool cmp_name_type(const Magazin& m1, const Magazin& m2)
{
	if (m1.get_name() == m2.get_name())
		return m1.get_type() < m2.get_type();
	return m1.get_name() < m2.get_name();
}