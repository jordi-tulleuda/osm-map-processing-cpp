#include "MapaSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "Util.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

#define CHECK(expression) do { if (!(expression)) { \
    std::cerr << "FAIL: " << #expression << " at line " << __LINE__ << "\n"; \
    std::exit(EXIT_FAILURE); \
} } while (false)
#include <string>
#include <utility>
#include <vector>

static CHILD_NODE tag(const std::string& key, const std::string& value) {
    return {"tag", {{"k", key}, {"v", value}}};
}
static XmlElement node(const std::string& id, const std::string& lat, const std::string& lon,
                       std::vector<CHILD_NODE> children = {}) {
    return {"node", {{"id", id}, {"lat", lat}, {"lon", lon}}, std::move(children)};
}
static XmlElement way(const std::string& id, std::vector<std::string> references, bool highway) {
    std::vector<CHILD_NODE> children;
    for (const auto& ref : references) children.push_back({"nd", {{"ref", ref}}});
    if (highway) children.push_back(tag("highway", "residential"));
    return {"way", {{"id", id}}, children};
}
static void approx(double a, double b) { CHECK(std::abs(a - b) < 1e-8); }

int main() {
    { // 1. Utility extracts k=v even when attributes are reversed.
        std::vector<PAIR_ATTR_VALUE> attributes = {{"v", "restaurant"}, {"k", "amenity"}};
        auto pair = Util::kvDeTag(attributes);
        CHECK(pair.first == "amenity" && pair.second == "restaurant");
    }
    std::cout << "PASS 1: OSM tag lookup\n";
    { // 2. Coordinate and point-of-interest extraction.
        MapaSolucio map;
        std::vector<XmlElement> elements = {
            node("7", "41.500", "2.150", {tag("name", "Cafe A"), tag("amenity", "restaurant"),
                                           tag("cuisine", "pizza"), tag("wheelchair", "yes")}),
            node("8", "41.501", "2.151", {tag("name", "Store B"), tag("shop", "supermarket")}),
            node("9", "41.502", "2.152")
        };
        map.parsejaXmlElements(elements);
        std::vector<PuntDeInteresBase*> pois;
        map.getPdis(pois);
        CHECK(pois.size() == 2);
        CHECK(pois[0]->getName() == "Cafe A");
        approx(pois[0]->getCoord().lat, 41.5);
        approx(pois[1]->getCoord().lon, 2.151);
    }
    std::cout << "PASS 2: POI extraction and coordinates\n";
    { // 3. Restaurant classification by tags.
        PuntDeInteresRestaurantSolucio restaurant("pizza", "yes", {0,0}, "Example");
        CHECK(restaurant.getColor() == 0x7FFFD4);
        PuntDeInteresRestaurantSolucio chinese("chinese", "no", {0,0}, "Example");
        CHECK(chinese.getColor() == 0x00FFFF);
    }
    std::cout << "PASS 3: Restaurant colors\n";
    { // 4. Shop classification by tags.
        PuntDeInteresBotigaSolucio store("supermarket", "", "", {0,0}, "Example");
        CHECK(store.getColor() == 0xDFFF00);
        PuntDeInteresBotigaSolucio bakery("bakery", "yes", "06:00-22:00", {0,0}, "Example");
        CHECK(bakery.getColor() == 0x4CBB17);
    }
    std::cout << "PASS 4: Shop colors\n";
    { // 5. Only highway-tagged ways become paths, preserving coordinate order.
        MapaSolucio map;
        std::vector<XmlElement> elements = {
            node("1", "41.1", "2.1"), node("2", "41.2", "2.2"), node("3", "41.3", "2.3"),
            way("100", {"1", "2", "3"}, true), way("101", {"1", "3"}, false)
        };
        map.parsejaXmlElements(elements);
        std::vector<CamiBase*> paths;
        map.getCamins(paths);
        CHECK(paths.size() == 1);
        auto coords = paths[0]->getCamiCoords();
        CHECK(coords.size() == 3);
        approx(coords[0].lat, 41.1);
        approx(coords[2].lon, 2.3);
    }
    std::cout << "PASS 5: Highway paths\n";
    { // 6. Parsing a new batch clears previously extracted content.
        MapaSolucio map;
        std::vector<XmlElement> first = {
            node("1", "41.1", "2.1", {tag("shop", "supermarket"), tag("name", "A")})
        };
        map.parsejaXmlElements(first);
        std::vector<PuntDeInteresBase*> pois;
        map.getPdis(pois);
        CHECK(pois.size() == 1);
        std::vector<XmlElement> second = {node("2", "41.2", "2.2")};
        map.parsejaXmlElements(second);
        pois.clear();
        map.getPdis(pois);
        CHECK(pois.empty());
    }
    std::cout << "PASS 6: Repeated parsing clears model\n";
    { // 7. Haversine distance from existing utility.
        auto d = Util::DistanciaHaversine(41.387, 2.169, 41.388, 2.169);
        CHECK(d > 0.1 && d < 0.12);
    }
    std::cout << "PASS 7: Haversine utility\n";
    std::cout << "All 7 checks passed.\n";
}
