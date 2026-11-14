# Scope, reproducibility, and known limitations

- The repository demonstrates **processing already-parsed OpenStreetMap elements**, not direct XML reading. In the original Windows environment, the provided Xerces-C++ / WPF integration supplied `XmlElement` objects.
- The original application included a `shortestPath` entry point, but its implementation in the supplied ZIP is **empty**. This is not an implemented route-finding application. In particular it does not implement Dijkstra, A*, traffic navigation, or turn-by-turn instructions.
- The included example and seven checks run against **small synthetic `XmlElement` fixtures**, without the original WPF interface, an OSM dataset, or a graphical screen.
- `MapaSolucio::parsejaXmlElements` processes elements in their given order. The sample and checks supply referenced nodes before ways; if a way references a missing node, the original code's `operator[]` may create a default coordinate.
- POI extraction recognizes named nodes with `amenity` or `shop` tags, and specific color rules. The original implementation classifies any named `amenity` as a restaurant; it is a simplified assignment model, not a complete OSM taxonomy.
- The original Windows project has not been rebuilt or tested in this Linux environment. Only the portable C++ subset has been compiled and exercised.
- The exercises in `LP-OSM-Tasca1-i-2.cpp` from the original ZIP are omitted from this focused portfolio release. They contained a hard-coded classroom fixture and a Windows-only `system("PAUSE")` call; the OSM model is the more substantial component.
