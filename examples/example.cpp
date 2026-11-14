#include "MapaSolucio.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Synthetic data: no copyrighted map data or original graphical framework required.
static CHILD_NODE tag(std::string key, std::string value) {
    return {"tag", {{"k", std::move(key)}, {"v", std::move(value)}}};
}

static XmlElement node(const std::string& id, const std::string& latitude,
                       const std::string& longitude, std::vector<CHILD_NODE> tags = {}) {
    return {"node", {{"id", id}, {"lat", latitude}, {"lon", longitude}}, std::move(tags)};
}

int main() {
    std::vector<XmlElement> data = {
        node("1", "41.387", "2.169", {tag("name", "Example Restaurant"),
              tag("amenity", "restaurant"), tag("cuisine", "pizza"), tag("wheelchair", "yes")}),
        node("2", "41.388", "2.170", {tag("name", "Example Market"),
              tag("shop", "supermarket")}),
        node("3", "41.389", "2.171"),
        {"way", {{"id", "99"}}, {{"nd", {{"ref", "1"}}}, {"nd", {{"ref", "2"}}},
                                    {"nd", {{"ref", "3"}}}, tag("highway", "residential")}}
    };

    MapaSolucio map;
    map.parsejaXmlElements(data);

    std::vector<PuntDeInteresBase*> pois;
    std::vector<CamiBase*> paths;
    map.getPdis(pois);
    map.getCamins(paths);

    std::cout << "Points of interest: " << pois.size() << "\n";
    for (auto* poi : pois) {
        auto coord = poi->getCoord();
        std::cout << "- " << poi->getName() << " (" << coord.lat << ", " << coord.lon
                  << ") color=0x" << std::hex << poi->getColor() << std::dec << "\n";
    }
    std::cout << "Paths: " << paths.size() << "\n";
    for (auto* path : paths)
        std::cout << "- path with " << path->getCamiCoords().size() << " coordinates\n";
}
