#pragma once

#include <string>

using namespace std;


class Mission
{
private:
	string name_;
	bool isExpress_;

public:

	Mission(string name, bool exp);
	~Mission();

	inline string getName() { return name_; }
	inline bool isExpress() { return isExpress_; }
};

