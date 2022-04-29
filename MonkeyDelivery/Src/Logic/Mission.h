#pragma once

#include <string>

using namespace std;


class Mission
{
private:
	string name_;
	bool isExpress_;

public:

	Mission(string name, bool exp) : name_(name), isExpress_(exp) {};
	~Mission() {};

	inline string getName() { return name_; }
	inline bool isExpress() { return isExpress_; }
};