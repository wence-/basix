#include <pybind11/eigen.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

#include "cell.h"
#include "crouzeix-raviart.h"
#include "indexing.h"
#include "lagrange.h"
#include "nedelec.h"
#include "polynomial-set.h"
#include "quadrature.h"
#include "raviart-thomas.h"
#include "regge.h"
#include "tp.h"

namespace py = pybind11;
using namespace libtab;

const std::string tabdoc = R"(
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
)";

PYBIND11_MODULE(libtab, m)
{
  m.doc() = R"(
Libtab provides information about finite elements on the reference cell. It has support for
interval (1D), triangle and quadrilateral (2D), and tetrahedron, hexahedron, prism and pyramid (3D) reference cells.
Elements are available in several different types, typically as `ElementName(celltype, degree)`. Not all elements are available
on all cell types, and an error should be thrown if an invalid combination is requested.
Each element has a `tabulate` function which returns the basis functions and a number of their derivatives, as desired.

)";

  py::enum_<cell::Type>(m, "CellType")
      .value("interval", cell::Type::interval)
      .value("triangle", cell::Type::triangle)
      .value("tetrahedron", cell::Type::tetrahedron)
      .value("quadrilateral", cell::Type::quadrilateral)
      .value("hexahedron", cell::Type::hexahedron)
      .value("prism", cell::Type::prism)
      .value("pyramid", cell::Type::pyramid);

  m.def("topology", &cell::topology);
  m.def("geometry", &cell::geometry);
  m.def("sub_entity_geometry", &cell::sub_entity_geometry);

  m.def("simplex_type", &cell::simplex_type,
        "Simplex CellType of given dimension");
  m.def("create_lattice", &cell::create_lattice,
        "Create a uniform lattice of points on a reference cell");

  py::class_<Nedelec>(m, "Nedelec", "Nedelec Element (first kind)")
      .def(py::init<cell::Type, int>(), "Constructor")
      .def("tabulate", &Nedelec::tabulate, tabdoc.c_str());

  py::class_<Regge>(m, "Regge", "Regge Element")
      .def(py::init<cell::Type, int>(), "Constructor")
      .def("tabulate", &Regge::tabulate, tabdoc.c_str());

  py::class_<Lagrange>(m, "Lagrange", "Lagrange Element")
      .def(py::init<cell::Type, int>())
      .def("tabulate", &Lagrange::tabulate, tabdoc.c_str());

  py::class_<CrouzeixRaviart>(m, "CrouzeixRaviart", "CrouzeixRaviart Element")
      .def(py::init<cell::Type, int>())
      .def("tabulate", &CrouzeixRaviart::tabulate, tabdoc.c_str());

  py::class_<TensorProduct>(m, "TensorProduct", "TensorProduct Element")
      .def(py::init<cell::Type, int>())
      .def("tabulate", &TensorProduct::tabulate, tabdoc.c_str());

  py::class_<RaviartThomas>(m, "RaviartThomas", "Raviart-Thomas Element")
      .def(py::init<cell::Type, int>())
      .def("tabulate", &RaviartThomas::tabulate, tabdoc.c_str());

  m.def("tabulate_polynomial_set", &polyset::tabulate,
        "Tabulate orthonormal polynomial expansion set");

  m.def("compute_jacobi_deriv", &quadrature::compute_jacobi_deriv,
        "Compute jacobi polynomial and derivatives at points");

  m.def("make_quadrature",
        py::overload_cast<const Eigen::Array<double, Eigen::Dynamic,
                                             Eigen::Dynamic, Eigen::RowMajor>&,
                          int>(&quadrature::make_quadrature),
        "Compute quadrature points and weights on a simplex defined by points");

  m.def("index", py::overload_cast<int, int>(&libtab::idx),
        "Indexing for triangular arrays")
      .def("index", py::overload_cast<int, int, int>(&libtab::idx),
           "Indexing for tetrahedral arrays");
}
