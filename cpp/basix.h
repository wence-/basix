
#include <Eigen/Core>
#include <utility>
#include <vector>

namespace basix
{

/// Create element in global registry and return handle
/// The element can be accessed by using the integer handle
///
/// @param family_name
/// @param cell_type
/// @param degree
/// @return handle - an integer identifier for the element
int register_element(const char* family_name, const char* cell_type,
                     int degree);

/// Delete from global registry
/// Frees a previously allocated element, with given handle
/// @param handle
///
void release_element(int handle);

/// Tabulates the finite element identified by "handle" at the points
/// given by "x". See FiniteElement::tabulate
/// @param handle
/// @param nd Number of derivatives
/// @param x coordinates of evaluation points
/// @return List of basis functions and derivatives
std::vector<Eigen::ArrayXXd> tabulate(int handle, int nd,
                                      const Eigen::ArrayXXd& x);

/// Cell type
/// @param handle
/// @return string representation of cell type
const char* cell_type(int handle);

/// Degree
/// @param handle
/// @return degree
int degree(int handle);

/// Value size = product(value_shape)
/// @param handle
/// @return value_size
int value_size(int handle);

/// Value shape
/// @param handle
/// @return value_shape
const std::vector<int>& value_shape(int handle);

/// Finite Element dimension
/// @param handle
/// @return dimension
int dim(int handle);

/// Family name
/// @param handle
/// @return string representation of the family name
const char* family_name(int handle);

/// Mapping name (affine, piola etc.)
/// @param handle
/// @return string representation of the mapping
const char* mapping_name(int handle);

/// Number of dofs per entity, ordered from vertex, edge, facet, cell
/// @param handle
/// @return entity_dofs
const std::vector<std::vector<int>>& entity_dofs(int handle);

/// Base permutations
/// @param handle
/// @return base permutations
const std::vector<Eigen::MatrixXd>& base_permutations(int handle);

/// Interpolation points
/// @param handle
/// @return interpolation points
const Eigen::ArrayXXd& points(int handle);

/// Interpolation matrix
/// @param handle
/// @return interpolation matrix
const Eigen::MatrixXd& interpolation_matrix(int handle);

/// Cell geometry
/// @param cell_type
/// @return Vertices of the cell geometry
Eigen::ArrayXXd geometry(const char* cell_type);

/// Cell topology
/// @param cell_type
/// @return List of vertices for each entity of each dimension
std::vector<std::vector<std::vector<int>>> topology(const char* cell_type);

/// Create quadrature points and weights
/// @param rule Quadrature rule name, use "default", "Gauss-Jacobi", "GLL"
/// @param cell_type
/// @param order
/// @return List of points, list of weights
std::pair<Eigen::ArrayXXd, Eigen::ArrayXd>
make_quadrature(const char* rule, const char* cell_type, int order);

} // namespace basix
