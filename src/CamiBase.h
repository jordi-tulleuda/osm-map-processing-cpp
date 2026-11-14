#pragma once
#include "pch.h"

#include "Common.h"
#include <vector>

using namespace std;

class CamiBase {
	public:
		virtual ~CamiBase() = default; // Portfolio safety fix: deleted through a CamiBase pointer.
		virtual vector<Coordinate> getCamiCoords() = 0;
		//virtual void afegeixCoord(const Coordinate& coord) = 0;
};