#include "pch.h"
#include "MapaSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
#include "Util.h"

void MapaSolucio::getPdis(vector<PuntDeInteresBase*>& pdis)
{
	for (int i = 0; i < m_pdis.size(); i++)
		pdis.push_back(m_pdis[i]);
}

void MapaSolucio::getCamins(vector<CamiBase*>& camins)
{
	for (int i = 0; i < m_camins.size(); i++)
		camins.push_back(m_camins[i]);
}

void MapaSolucio::parsejaXmlElements(vector<XmlElement>& xmlElements)
{
	neteja();
	for (int i = 0; i < xmlElements.size(); i++)
	{
		if (xmlElements[i].id_element == "node")
		{
			parsejaNodes(xmlElements[i]);
		}
		else if (xmlElements[i].id_element == "way")
		{
			parsejaWays(xmlElements[i]);
		}
	}
}

void MapaSolucio::neteja()
{
	for (int i = 0; i < m_pdis.size(); i++)
		delete m_pdis[i];
	for (int i = 0; i < m_camins.size(); i++)
		delete m_camins[i];
	m_pdis.clear();
	m_camins.clear();
	m_nodes.clear();
}

void MapaSolucio::parsejaNodes(const XmlElement& xmlElement)
{
	Coordinate coord = parsejaAtributs(xmlElement);
	parsejaFills(xmlElement, coord);
}

void MapaSolucio::parsejaWays(XmlElement xmlElement)
{
	int j = 0;
	CamiSolucio camiSol;
	while (j < xmlElement.fills.size())
	{
		if (xmlElement.fills[j].first == "tag")
		{
			pair<string, string> kv = Util::kvDeTag(xmlElement.fills[j].second);
			if (kv.first == "highway")
			{
				for (int k = 0; k < xmlElement.fills.size(); k++)
				{
					if (xmlElement.fills[k].first == "nd")
						camiSol.afegeixCoord(m_nodes[xmlElement.fills[k].second[0].second]);
				}
				CamiBase* cami = new CamiSolucio(camiSol);
				m_camins.push_back(cami);
				break;
			}
		}
		j++;
	}
}

void MapaSolucio::parsejaFills(XmlElement xmlElement, Coordinate coord)
{
	string amenity = "", cuisine = "", name = "", wheelchair = "", openingHours = "", shop = "";
	int j = 0;
	while (j < xmlElement.fills.size())
	{
		if (xmlElement.fills[j].first == "tag")
		{
			pair<string, string> kv = Util::kvDeTag(xmlElement.fills[j].second);
			if (kv.first == "amenity")
				amenity = kv.second;
			else if (kv.first == "cuisine")
				cuisine = kv.second;
			else if (kv.first == "name")
				name = kv.second;
			else if (kv.first == "wheelchair")
				wheelchair = kv.second;
			else if (kv.first == "opening_hours")
				openingHours = kv.second;
			else if (kv.first == "shop")
				shop = kv.second;
		}
		j++;
	}
	if (amenity != "" && name != "")
	{
		PuntDeInteresBase* pdib = new PuntDeInteresRestaurantSolucio(cuisine, wheelchair, coord, name);
		m_pdis.push_back(pdib);
	}
	else if (shop != "" && name != "")
	{
		PuntDeInteresBase* pdib = new PuntDeInteresBotigaSolucio(shop, wheelchair, openingHours, coord, name);
		m_pdis.push_back(pdib);
	}
}

Coordinate MapaSolucio::parsejaAtributs(const XmlElement& xmlElement)
{
	string id = "";
	double lat = -1, lon = -1;
	int j = 0;
	while ((id == "" || lat == -1 || lon == -1) && j < xmlElement.atributs.size())
	{
		if (xmlElement.atributs[j].first == "id")
		{
			id = xmlElement.atributs[j].second;
		}
		else if (xmlElement.atributs[j].first == "lat")
		{
			lat = stod(xmlElement.atributs[j].second);
		}
		else if (xmlElement.atributs[j].first == "lon")
		{
			lon = stod(xmlElement.atributs[j].second);
		}
		j++;
	}
	Coordinate coord = { lat, lon };
	m_nodes[id] = coord;
	return coord;
}
