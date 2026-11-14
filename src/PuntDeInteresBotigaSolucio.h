#pragma once
#include "PuntDeInteresBase.h"

using namespace std;

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() : m_shop(""), m_openingHours(""), m_wheelchair("") {};
	PuntDeInteresBotigaSolucio(const string& shop, const string& wheelchair, const string& openingHours, Coordinate coord, const string& name) : PuntDeInteresBase(coord, name) { m_shop = shop, m_openingHours = openingHours, m_wheelchair = wheelchair; }
	~PuntDeInteresBotigaSolucio() {};

	string getName();
	unsigned int getColor();

private:
	string m_shop;
	string m_openingHours;
	string m_wheelchair;
};