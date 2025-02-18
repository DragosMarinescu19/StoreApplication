#pragma once
#include<string>
#include "Errors.h"
using namespace std;

class Validator {
public:
	void validatemagazin(string name, string type, double price, string producer);
};

class ValidatorException : public Exception {
public:
	explicit ValidatorException(const string& err) : Exception(err) {}
};
