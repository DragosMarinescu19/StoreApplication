#pragma once
#ifndef DOMAIN_H
#define DOMAIN_H
#include<string>
#include<iostream>
using namespace std;
class Magazin {
private:
	string name;
	string type;
	double price;
	string producer;

public:

	[[nodiscard]] double get_price() const;
	[[nodiscard]] string get_type() const;
	[[nodiscard]] string get_name() const;
	[[nodiscard]] string get_producer() const;

	Magazin() = default;

	Magazin(const string& name, const string& type, double price, const string& producer) :name{ name }, type{ type }, price{ price }, producer{ producer }
	{
	}
	Magazin(const Magazin& ot) : name{ ot.name }, type{ ot.type }, price{ ot.price }, producer{ ot.producer }
	{

	}



};
bool cmp_name(const Magazin& m1, const Magazin& m2);
bool cmp_price(const Magazin& m1, const Magazin& m2);
bool cmp_name_type(const Magazin& m1, const Magazin& m2);
#endif