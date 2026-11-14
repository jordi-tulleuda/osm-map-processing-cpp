# Scope of the portfolio release, reproducibility, and limitations

The original OpenStreetMap map-processing coursework was completed as a team assignment. This repository is a reduced, portable presentation of the implemented C++ model, **not** an archive of every university-provided graphical component.

- The repository demonstrates **processing already-parsed OpenStreetMap elements**, not direct XML reading. In the original Windows environment, the provided Xerces-C++ / WPF integration supplied `XmlElement` objects.
- The original **instructor-provided Windows bridge** includes an empty `shortestPath` entry point marked `DO NOT TOUCH`; the accompanying WPF code labels shortest-path initialization as `2nd part`. This does not demonstrate an unfinished map-processing submission. This source-only release is **not** a route planner and makes no claim to implement shortest-path algorithms.
- The included example and seven checks run against **small synthetic `XmlElement` fixtures**, without the original WPF interface, an OSM dataset, or a graphical screen.
- `MapaSolucio::parsejaXmlElements` processes elements in their given order. The sample and checks supply referenced nodes before ways; if a way references a missing node, the original code's `operator[]` may create a default coordinate.
- POI extraction recognizes named nodes with `amenity` or `shop` tags, and specific color rules. The original implementation classifies any named `amenity` as a restaurant; it is a simplified assignment model, not a complete OSM taxonomy.
- The original Windows project has not been rebuilt or tested in this Linux environment. Only the portable C++ subset has been compiled and exercised.
- The exercises in `LP-OSM-Tasca1-i-2.cpp` from the original ZIP are omitted from this focused portfolio release. They contained a hard-coded classroom fixture and a Windows-only `system("PAUSE")` call; the OSM model is the more substantial component.
