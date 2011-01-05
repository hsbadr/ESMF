// $Id: ESMCI_Base.h,v 1.4 2011/01/05 20:05:41 svasquez Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2011, University Corporation for Atmospheric Research,
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

#ifndef ESMCI_BASE_H
#define ESMCI_BASE_H

#include "ESMCI_Macros.h"
class ESMC_Base;
#include "ESMCI_VM.h"
#include "ESMCI_Attribute.h"

//-----------------------------------------------------------------------------
//BOP
// !CLASS:  ESMC_Base - all ESMF classes inherit from ESMC_Base
//
// !DESCRIPTION:
// The code in this file implements the Base defined type
// and methods which operate on all derived types.
//
//-----------------------------------------------------------------------------
//
// !USES:

// !PUBLIC TYPES:
 class ESMC_Base;
 class Attribute;

class ESMC_Base
{
  protected:
    int             ID;           // unique ID for any object in this VM context
    ESMCI::VMId     *vmID;        // unique vmID for any VM in the system
    bool            vmIDCreator;  // responsible for deleting vmID allocation
    int             refCount;     // number of references to this instance
    ESMC_Status     baseStatus;   // status of the Base part of the object
    ESMC_Status     status;       // overall status of the derived class object
    ESMC_ProxyFlag  proxyflag;    // whether object is a proxy or not
    char            baseName[ESMF_MAXSTR];    // object name, unique over class 
    char            baseNameF90[ESMF_MAXSTR]; // same name, non-null terminated
    char            className[ESMF_MAXSTR];   // object class

  private:
    
  
    // prevent accidental copying
    //ESMC_Base& operator=(const ESMC_Base&);
    ESMC_Base(const ESMC_Base&);
  
  public:
    int           classID;      // unique ID relative to this class
    ESMCI::Attribute root;

    // required & optional standard interface methods for all ESMF classes.
    // should not instantiate a ESMC_Base object directly; must sub-class first.

    // accessors to unique ID
    void ESMC_BaseSetID(int id);
    int  ESMC_BaseGetID(void) const;

    // accessors to object's vmID    
    void ESMC_BaseSetVMId(ESMCI::VMId *vmID);
    ESMCI::VMId *ESMC_BaseGetVMId(void) const;
    
    // accessors to reference count
    void ESMC_BaseSetRefCount(int count);
    int  ESMC_BaseGetRefCount(void) const;

    // accessors to baseStatus
    void ESMC_BaseSetBaseStatus(ESMC_Status s){ baseStatus = s;}
    ESMC_Status ESMC_BaseGetBaseStatus()const{ return baseStatus;}
 
    // accessors to status
    void ESMC_BaseSetStatus(ESMC_Status s){ status = s;}
    ESMC_Status ESMC_BaseGetStatus()const{ return status;}
    
    // accessors to proxyFlag
    void ESMC_BaseSetProxyFlag(ESMC_ProxyFlag pf){ proxyflag = pf;}
    ESMC_ProxyFlag ESMC_BaseGetProxyFlag()const{ return proxyflag;}
    
    // accessors to base name
    int   ESMC_BaseSetName(const char *name, const char *classname);
    char *ESMC_BaseGetName(void) const;
    int   ESMC_BaseSetF90Name(char *name, int nlen);
    char *ESMC_BaseGetF90Name(void) const;

    // accessors to class name
    int   ESMC_BaseSetClassName(char *classname);
    char *ESMC_BaseGetClassName(void) const;
    int   ESMC_BaseSetF90ClassName(char *name, int nlen);
    int   ESMC_BaseGetF90ClassName(char *name, int nlen) const;

    // flatten an object into a byte stream, and reconstitute it again
    int ESMC_Serialize(char *buffer, int *length, int *offset, 
                      const ESMC_AttReconcileFlag &attreconflag,
                      const ESMC_InquireFlag &inquireflag) const;
    int ESMC_Deserialize(char *buffer, int *offset,
                        const ESMC_AttReconcileFlag &attreconflag);
    
    // optional Read/Write methods for any ESMF class
    virtual int ESMC_Read(void);
    virtual int ESMC_Write(void) const;

    // required Validate and Print methods
    //  (would be pure virtual =0; but some will be implemented in F90)
    virtual int ESMC_Validate(const char *options=0) const;
    virtual int ESMC_Print(const char *options=0) const;
    virtual int ESMC_Print(int level, const char *options=0) const;

    // constructors/destructor
    ESMC_Base(void);    // default constructor
    ESMC_Base(int id);  // explicit id, don't modify Base id counting
    ESMC_Base(char *superclass, char *name, int nattrs);
    virtual ~ESMC_Base(void);

};   // end class ESMC_Base

#endif  // ESMCI_BASE_H
