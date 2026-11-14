#pragma once
#include "pch.h"

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"
#include "Util.h"

using namespace std;

class MapaBase {

	public:
		virtual void getPdis(vector<PuntDeInteresBase*>&) = 0;
		virtual void getCamins(vector<CamiBase*>&) = 0;
		virtual void parsejaXmlElements(vector<XmlElement>& xmlElements) = 0;
};
