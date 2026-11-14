#pragma once

#include "MapaBase.h"
#include <unordered_map>

class MapaSolucio : public MapaBase
{
public:
	~MapaSolucio() { neteja(); }

	void getPdis(vector<PuntDeInteresBase*>& pdis) override;
	void getCamins(vector<CamiBase*>& camins) override;
	void parsejaXmlElements(vector<XmlElement>& xmlElements) override;

	Coordinate getCoord(const string& id) { return m_nodes[id]; }
private:
	unordered_map<string, Coordinate> m_nodes;
	vector<PuntDeInteresBase*> m_pdis;
	vector<CamiBase*> m_camins;

	void neteja();

	void parsejaNodes(const XmlElement& xmlElement);
	void parsejaWays(XmlElement xmlElement);
	Coordinate parsejaAtributs(const XmlElement& xmlElement);
	void parsejaFills(XmlElement xmlElement, Coordinate coord);
};