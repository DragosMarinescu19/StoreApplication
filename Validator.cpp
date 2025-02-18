#include "Validator.h"
#include "Errors.h"

bool validstring(string str)
{
	if (str.size() == 0)
		return false;

	for (int i = 0; i < size(str); i++)
	{
		if (!(str.at(i) >= 'a' && str.at(i) <= 'z' || str.at(i) >= 'A' && str.at(i) <= 'Z' || str.at(i) == ' '))
			return false;

	}
	return true;
}

void Validator::validatemagazin(string name, string type, double price, string producer)
{
	string errors;
	if (!validstring(name))
		errors.append("Numele nu este corect\n");
	if (!validstring(type))
		errors.append("Tipul nu este corect\n");
	if (!validstring(producer))
		errors.append("Producator este gresit\n");
	if (price < 0)
		errors.append("Pretul nu poate fi nul\n");
	if (errors.size() != 0)
		throw Exception(errors);
}
