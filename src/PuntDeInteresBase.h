#pragma once
#include "pch.h"

#include <string>
#include "Common.h"

using namespace std;

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, string name);
		virtual ~PuntDeInteresBase() {};

		virtual string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();
};