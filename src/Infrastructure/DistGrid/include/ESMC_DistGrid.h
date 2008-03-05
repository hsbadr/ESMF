// $Id: ESMC_DistGrid.h,v 1.36 2008/03/05 05:50:40 theurich Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2007, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.
//
//-------------------------------------------------------------------------
// (all lines below between the !BOP and !EOP markers will be included in
//  the automated document processing.)
//-------------------------------------------------------------------------
// these lines prevent this file from being read more than once if it
// ends up being included multiple times

#ifndef ESMC_DistGrid_H
#define ESMC_DistGrid_H

//-----------------------------------------------------------------------------
//BOPI
// !CLASS:  ESMC_DistGrid - Public C interface to the ESMF DistGrid class
//
// !DESCRIPTION:
//
// The code in this file defines the public C DistGrid class and declares method
// signatures (prototypes).  The companion file {\tt ESMC\_DistGrid.C} contains
// the definitions (full code bodies) for the DistGrid methods.
//
//EOPI
//-----------------------------------------------------------------------------


#include "ESMC_Interface.h"

extern "C" {

// Class declaration type
typedef struct{
  void *ptr;
}ESMC_DistGrid;

// Class API
ESMC_DistGrid ESMC_DistGridCreate(ESMC_InterfaceInt minIndexInterfaceArg, 
  ESMC_InterfaceInt maxIndexInterfaceArg, int *rc); //TODO: complete this API
int ESMC_DistGridPrint(ESMC_DistGrid distgrid);
int ESMC_DistGridDestroy(ESMC_DistGrid *distgrid);


}; // extern "C"


#endif  // ESMC_DistGrid_H
