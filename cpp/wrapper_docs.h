#include <map>
#include <string>

std::map<std::string, const char*> docs
    = {{"cell::topology", R"(
Topological description of a cell. 

Parameters
==========
celltype : CellType
   
Returns
=======
List[List[List[int]]]
    Cell topology. For each topological dimension, a list of entities, 
    and for each entity a list of point indices. For example, a triangle 
    has vertices, edges and a face, so the topology is vertices: [[0],[1],[2]], 
    edges: [[1, 2], [0, 2], [0, 1]], face: [0, 1, 2].
)"},
       {"cell::geometry", R"(Geometric points of a cell)"},
       {"FiniteElement::tabulate",
        R"(
Tabulate the finite element basis function and derivatives at points.
If no derivatives are required, use nderiv=0. In 2D and 3D, the derivatives are ordered
in triangular (or tetrahedral) order, i.e. (0,0),(1,0),(0,1),(2,0),(1,1),(0,2) etc. in 2D.

Parameters
==========
nderiv : int
    Number of derivatives required

points : numpy.ndarray
    Array of points

Returns
=======
List[numpy.ndarray]
    List of basis values and derivatives at points. Returns a list of length `(n+d)!/(n!d!)`
    where `n` is the number of derivatives and `d` is the topological dimension.
)"}};
