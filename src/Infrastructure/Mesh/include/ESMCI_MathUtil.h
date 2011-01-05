// $Id: ESMCI_MathUtil.h,v 1.3 2011/01/05 20:05:44 svasquez Exp $
// Earth System Modeling Framework
// Copyright 2002-2011, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.

//
//-----------------------------------------------------------------------------
#ifndef ESMCI_MathUtil_h
#define  ESMCI_MathUtil_h


#include <Mesh/include/ESMCI_MeshDB.h>
#include <Mesh/include/ESMCI_MeshObj.h>
#include <Mesh/include/ESMCI_MEField.h>
#include <Mesh/include/ESMCI_MasterElement.h>
#include <Mesh/include/ESMCI_Exception.h>
#include <Mesh/include/ESMCI_MCoord.h>

#include <vector>

namespace ESMCI {


  bool invert_matrix_3x3(double m[], double m_inv[]);

  bool intersect_quad_with_line(const double *q, const double *l1, const double *l2, double *p,
				double *t);

  bool intersect_tri_with_line(const double *tri, const double *l1, const double *l2, double *p,
			       double *t);

  double area_of_flat_2D_polygon(int num, double *coords);

  double great_circle_area(int n, double *pnts);

  void get_elem_coords(const MeshObj *elem, MEField<>  *cfield, int sdim, int max_num_nodes, int *num_nodes, double *coords);

  void remove_0len_edges3D(int *num_p, double *p);

} // namespace

#endif
