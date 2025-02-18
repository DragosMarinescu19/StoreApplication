#pragma once
#include <string>

using namespace std;

class Exception {

	string msg;

public:

	explicit Exception(string m) : msg{ m } {}

	string get_message() {
		return msg;
	}
};