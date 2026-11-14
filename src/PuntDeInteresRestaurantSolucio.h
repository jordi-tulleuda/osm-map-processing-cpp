#pragma once
#include "PuntDeInteresBase.h"

using namespace std;

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() : m_cuisine(""), m_wheelchair("") {};
	PuntDeInteresRestaurantSolucio(const string& cuisine, const string& wheelchair, Coordinate coord, const string& name) : PuntDeInteresBase(coord, name) { m_cuisine = cuisine, m_wheelchair = wheelchair; }
	~PuntDeInteresRestaurantSolucio() {};

	string getName();
	unsigned int getColor();
private:
	string m_cuisine;
	string m_wheelchair;
};