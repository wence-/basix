# Copyright (c) 2020 Matthew Scroggs
# FEniCS Project
# SPDX-License-Identifier: MIT

import pytest
from basix import ElementFamily, CellType, LagrangeVariant


def parametrize_over_elements(degree, reference=None):
    elementlist = []

    for k in range(1, degree + 1):
        # Elements on all cells
        for c in [CellType.interval, CellType.triangle, CellType.tetrahedron, CellType.quadrilateral,
                  CellType.hexahedron, CellType.prism, CellType.pyramid]:
            if k < 4:
                elementlist.append((c, ElementFamily.P, k, [LagrangeVariant.equispaced]))

        # Elements on all cells except pyramid
        for c in [CellType.interval, CellType.triangle, CellType.tetrahedron, CellType.quadrilateral,
                  CellType.hexahedron, CellType.prism]:
            elementlist.append((c, ElementFamily.P, k, [LagrangeVariant.gll_isaac]))
            elementlist.append((c, ElementFamily.P, k, [LagrangeVariant.gll_warped]))

        # Elements on all cells except prism and pyramid
        for c in [CellType.interval, CellType.triangle, CellType.tetrahedron, CellType.quadrilateral,
                  CellType.hexahedron]:
            elementlist.append((c, ElementFamily.P, k, [LagrangeVariant.integral_legendre]))

        # Elements on all cells except prism, pyramid and interval
        for c in [CellType.triangle, CellType.tetrahedron, CellType.quadrilateral, CellType.hexahedron]:
            elementlist.append((c, ElementFamily.N1E, k, []))
            elementlist.append((c, ElementFamily.N2E, k, []))
            elementlist.append((c, ElementFamily.RT, k, []))
            elementlist.append((c, ElementFamily.BDM, k, []))

        # Elements on simplex cells
        for c in [CellType.triangle, CellType.tetrahedron]:
            if k == 1:
                elementlist.append((c, ElementFamily.CR, k, []))
            elementlist.append((c, ElementFamily.Regge, k, []))

        # Elements on all cells except tensor product cells
        for c in [CellType.interval, CellType.quadrilateral, CellType.hexahedron]:
            elementlist.append((c, ElementFamily.P, k, [LagrangeVariant.integral_chebyshev]))
            elementlist.append((c, ElementFamily.serendipity, k, []))

        # Bubble elements
        if k >= 2:
            elementlist.append((CellType.interval, ElementFamily.bubble, k, []))
            elementlist.append((CellType.quadrilateral, ElementFamily.bubble, k, []))
            elementlist.append((CellType.hexahedron, ElementFamily.bubble, k, []))
        if k >= 3:
            elementlist.append((CellType.triangle, ElementFamily.bubble, k, []))
        if k >= 4:
            elementlist.append((CellType.tetrahedron, ElementFamily.bubble, k, []))

    if reference is None:
        if len(elementlist) == 0:
            raise ValueError(f"No elements will be tested with reference: {reference}")
        return pytest.mark.parametrize("cell_type, element_type, degree, element_args", elementlist)
    else:
        elementlist = [(b, c, d) for a, b, c, d in elementlist if a == reference]
        if len(elementlist) == 0:
            raise ValueError(f"No elements will be tested with reference: {reference}")
        return pytest.mark.parametrize("element_type, degree, element_args", elementlist)
