// Copyright (c) 2020 Matthew Scroggs
// FEniCS Project
// SPDX-License-Identifier:    MIT

#pragma once

namespace basix
{

/// Finite elements

/// The functions in this namespace can be used to create finite elements.
namespace element
{
/// An enum defining the variants of a Lagrange space that can be created
enum class lagrange_variant
{
  equispaced = 0,
  gll_warped = 1,
  gll_isaac = 2,
  gll_centroid = 3,
  chebyshev_warped = 4,
  chebyshev_isaac = 5,
  chebyshev_centroid = 6,
  gl_warped = 7,
  gl_isaac = 8,
  gl_centroid = 9,
  vtk = 20,
  integral_legendre = 50,
  integral_chebyshev = 51,
};

/// An enum defining the sets of polynomials that moments can be taken against
enum class polynomial_moment_variant
{
  lagrange_equispaced = 0,
  lagrange_gll_warped = 1,
  lagrange_gll_isaac = 2,
  lagrange_gll_centroid = 3,
  lagrange_chebyshev_warped = 4,
  lagrange_chebyshev_isaac = 5,
  lagrange_chebyshev_centroid = 6,
  lagrange_gl_warped = 7,
  lagrange_gl_isaac = 8,
  lagrange_gl_centroid = 9,
  legendre = 10,
  chebyshev = 11,
};

/// Enum of available element families
enum class family
{
  custom = 0,
  P = 1,
  RT = 2,
  N1E = 3,
  BDM = 4,
  N2E = 5,
  CR = 6,
  Regge = 7,
  DPC = 8,
  bubble = 9,
  serendipity = 10
};

} // namespace element

} // namespace basix
