# Attribution and academic context

This is a **team assignment** from Laboratori de Programació (Computer Engineering, Universitat Autònoma de Barcelona). The university supplied an initial project structure, class interfaces / base code, and a Windows graphical application framework.

## Student-developed elements represented here

- `MapaSolucio.cpp` / `.h` — logic to extract points of interest and paths from the supplied `XmlElement` representation, manage map objects, and map node references to coordinates.
- `CamiSolucio.h` — path-coordinate storage based on the provided interface.
- `PuntDeInteresBotigaSolucio.*` and `PuntDeInteresRestaurantSolucio.*` — specialized POI types and tag-based color rules.

These are components from the **team submission**. The source archive does not distinguish each teammate's contribution or provide the untouched starter snapshot, so line-by-line authorship is not claimed.

## University-provided starting framework

The class contracts / base interfaces (`*Base.*`), shared structures in `Common.h`, utility code (`Util.*`), and Windows WPF integration were part of the provided project framework, according to the student's description. Required base and utility files are retained here to compile the core module, **not** claimed as original student implementations.

The original repository also included a C# WPF application, Windows DLL bridge, and bundled third-party Xerces-C++ headers and binaries. These are **not redistributed** in this source-only portfolio repository. No independent project license has been assigned to the contributed scaffold or team submission.

## Portfolio additions (after the academic submission)

- `CMakeLists.txt`, `examples/example.cpp`, `tests/test_map.cpp`, GitHub Actions CI, `.gitignore`, and the documentation were added to make the C++ core independently understandable and testable.
- One minimal safety fix was made to the provided `CamiBase.h` interface: a virtual destructor was added because `MapaSolucio` deletes derived path objects through a `CamiBase*` pointer. This is a **portfolio maintenance adjustment**, not part of the original academic implementation.

Before making the repository public, confirm that teammates and the university permit publication of the relevant shared source / starter material. If that cannot be confirmed, keep it private or replace protected components with authorized equivalents.
