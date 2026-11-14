#pragma once

#include "CamiBase.h"

class CamiSolucio : public CamiBase
{
public:
	void afegeixCoord(const Coordinate& coord) { m_coords.push_back(coord); }
	vector<Coordinate> getCamiCoords() override { return m_coords; }
private:
	vector<Coordinate> m_coords;
};