// Copyright (c) 2020 Chris Richardson
// FEniCS Project
// SPDX-License-Identifier:    MIT

#include "polynomial.h"
#include <Eigen/Dense>
#include <vector>

#pragma once

class FiniteElement
{
public:
  // Element of given dimension (1, 2 or 3) and degree.
  FiniteElement(int dim, int degree);

  // Compute basis values at set of points
  Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
  tabulate_basis(const Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic,
                                    Eigen::RowMajor>& pts) const;

protected:
  void apply_dualmat_to_basis(
      const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                          Eigen::RowMajor>& coeffs,
      const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                          Eigen::RowMajor>& dualmat,
      const std::vector<Polynomial>& basis, int ndim);

  int _dim;
  int _degree;
  std::vector<Polynomial> poly_set;
};
