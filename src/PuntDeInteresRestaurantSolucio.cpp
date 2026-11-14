#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"

string PuntDeInteresRestaurantSolucio::getName()
{
	return PuntDeInteresBase::getName();
}

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	if (m_cuisine == "pizza" && m_wheelchair == "yes")
	{
		return 0x7FFFD4;
	}
	else if (m_cuisine == "chinese")
	{
		return 0x00FFFF;
	}
	else if (m_cuisine != "" && m_wheelchair == "yes")
	{
		return 0x5D3FD3;
	}
	return PuntDeInteresBase::getColor();
}