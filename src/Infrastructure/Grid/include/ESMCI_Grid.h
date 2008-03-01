// $Id: ESMCI_Grid.h,v 1.37 2008/03/01 00:37:01 theurich Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2007, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.

// ESMCI Grid include file for C++

// (all lines below between the !BOP and !EOP markers will be included in
//  the automated document processing.)
//-------------------------------------------------------------------------
// these lines prevent this file from being read more than once if it
// ends up being included multiple times

#ifndef ESMCI_Grid_H
#define ESMCI_Grid_H

//-------------------------------------------------------------------------
//BOP
// !CLASS: ESMCI_Grid - Grid
//
// !DESCRIPTION:
//
// The code in this file defines the C++ {\tt Grid} members and method
// signatures (prototypes).  The companion file {\tt ESMC\_Grid.C}
// contains the full code (bodies) for the {\tt Grid} methods.
//
///EOP
//-------------------------------------------------------------------------


#include "ESMC_Base.h"
#include "ESMCI_DistGrid.h"
#include "ESMCI_Array.h"


// Eventually move this to ESMCI_Util.h
enum ESMC_GridStatus {ESMC_GRIDSTATUS_NOT_READY=1,
		      ESMC_GRIDSTATUS_PROXY_READY,
		      ESMC_GRIDSTATUS_SHAPE_READY
};


// Start name space
namespace ESMCI {  

class Grid;
class ProtoGrid;

// class definition
class Grid : public ESMC_Base {    // inherits from ESMC_Base class
  private:

  // holder for set/commit data
  ProtoGrid *proto;

  // Grid Status
  ESMC_GridStatus status;

  // global information
  ESMC_TypeKind typekind;
  
  int distDimCount;

  int *distgridToGridMap;    // size of distgridToGridMap = distDimCount, entries are 0-based

  int undistDimCount;
  int *undistLBound; // size of undistLBound = undistDimCount
  int *undistUBound; // size of undistUBound = undistDimCount
  
  int dimCount;
  
  // information about edge widths of the Grid
  int *gridEdgeLWidth; // size of grid dimCount
  int *gridEdgeUWidth; // size of grid dimCount
  int *gridAlign; // size of grid dimCount

  // User info about coord dimCounts and distgridToGridMap
  int *coordDimCount; // size of coordDimCount = dimCount
  int **coordDimMap; // size of coordDimMap = dimCountxdimCount  [coord][dim of coord array], 0-based

  int staggerLocCount;
  Array ***coordArrayList; // size of coordArrayList = staggerLocCountxdimCount [staggerLoc][coord]
  int   **staggerAlignList;     // hold alignment info [staggerloc][dim]
  int   **staggerEdgeLWidthList;     // hold LWidth info [staggerloc][dim]
  int   **staggerEdgeUWidthList;     // hold UWidth info [staggerloc][dim]
  bool  **didIAllocList;        // if true, I allocated this Array [staggerloc][coord]

  // map grid dim to distgrid dim and grid bounds dim
  bool *gridIsDist;  // size=dimCount [grid-dim]
  int *gridMapDim;   // size=dimCount [grid-dim]

  // map coord dim to distgrid dim and coord array bounds dim
  bool **coordIsDist; // size=dimCountxdimCount [coord][coord-dim]
  int **coordMapDim; // size=dimCountxdimCount [coord][coord-dim]

  // if bit d in isDELBnd[localde] is 1, then localde is on the
  // lower boundary of dimension d
  char *isDELBnd;
 
 // if bit d in isDEUBnd[localde] is 1, then localde is on the
  // upper boundary of dimension d
  char *isDEUBnd;

  ESMC_IndexFlag indexflag;
  DistGrid *distgrid;


  // Private methods:
  // Set internal array
  int setCoordArrayInternal(
		    int _staggerloc, // (in)
		    int _coord,      // (in)
		    Array *_array,   // (in)
		    bool _self_alloc // (in)
		    );

  // Get Array holding coordinates
 int getCoordArrayInternal(
		    int _staggerloc, // (in)
		    int _coord,      // (in)
		    Array **_array   // (in)
		    );

  // add/delete protogrid  
  int addProtoGrid();
  int delProtoGrid();

  // make grid usable
  int constructInternal(
       char *name,                            // (in)
       ESMC_TypeKind typekindArg,              // (in)
       DistGrid *distgridArg,                  // (in)
       int distDimCountArg,                        // (in)
       int *distgridToGridMapArg,                         // (in)
       int undistDimCountArg,                      // (in)
       int *undistLBoundArg,                        // (in)
       int *undistUBoundArg,                        // (in)
       int dimCountArg,                            // (in)
       int *gridEdgeLWidth,
       int *gridEdgeUWidth,
       int *gridAlign,
       int *coordDimCountArg,                     // (in)
       int **coordDimMapArg,                   // (in)
       ESMC_IndexFlag indexflagArg             // (in)
       );

  // set information about a stagger location
  int setStaggerInfo(
		    int _staggerloc, // (in)
		    int *staggerAlign,  // (in)
		    int *staggerEdgeLWidth,  // (in)
		    int *staggerEdgeUWidth  // (in)
		    );


 public:

  // accessor methods
  // NOTE: For efficiencies sake the following functions don't error check
  //       so be sure to error check the grid or any input before using.  
  const ESMC_GridStatus getStatus(void) const {return status;}
  const int getDimCount(void) const {return dimCount;}
  const int getDistDimCount(void) const {return distDimCount;}
  const int getUndistDimCount(void) const {return undistDimCount;}
  const int getTileCount(void) const {return distgrid->getPatchCount();}
  const int getStaggerLocCount(void) const {return staggerLocCount;}
  const ESMC_IndexFlag getIndexFlag(void) const {return indexflag;}
  const ESMC_TypeKind getTypeKind(void) const {return typekind;}
  const DistGrid *getDistGrid(void) const {return distgrid;}
  const int *getDistgridToGridMap(void) const {return distgridToGridMap;}
  const int *getUndistLBound(void) const {return undistLBound;}
  const int *getUndistUBound(void) const {return undistUBound;}
  const int *getCoordDimCount(void) const {return coordDimCount;}
  const int *getGridEdgeLWidth(void) const {return gridEdgeLWidth;}
  const int *getGridEdgeUWidth(void)  const {return gridEdgeUWidth;}
  const int *getGridAlign(void) const {return gridAlign;}

        int **getCoordDimMap(void) const {return coordDimMap;}
  const char *getName(void)  const {return ESMC_BaseGetName();}
        bool *getGridIsDist(void) const {return gridIsDist;} 
        int  *getGridMapDim(void) const {return gridMapDim;} 
        bool **getCoordIsDist(void) const {return coordIsDist;} 
        int  **getCoordMapDim(void) const {return coordMapDim;} 
  const int   *getStaggerEdgeLWidth(int staggerloc) const {return staggerEdgeLWidthList[staggerloc];}
  const int   *getStaggerEdgeUWidth(int staggerloc) const {return staggerEdgeUWidthList[staggerloc];}

  bool isLBnd(int localDE, int dim) {return (isDELBnd[localDE] & (0x1 << dim))?true:false;}
  bool isUBnd(int localDE, int dim) {return (isDEUBnd[localDE] & (0x1 << dim))?true:false;}


  // detect if a given staggerloc is present in the Grid
  bool hasStaggerLoc(int staggerloc);

  // Set data in an empty grid before commit
  int set(
	  int _nameLen,                                // (in)
	  char *_name,                                 // (in)
	  ESMC_TypeKind *_typekind,                    // (in)
	  DistGrid *_distgrid,                    // (in)
	  InterfaceInt *gridEdgeLWidth,          // (in)
	  InterfaceInt *gridEdgeUWidth,          // (in)
	  InterfaceInt *gridAlign,          // (in)
	  InterfaceInt *_distgridToGridMap,                  // (in)
	  InterfaceInt *_undistLBound,                 // (in)
	  InterfaceInt *_undistUBound,                 // (in)
	  InterfaceInt *_coordDimCount,              // (in)
	  InterfaceInt *_coordDimMap,             // (in)
	  ESMC_IndexFlag *_indexflag                  // (in)
	  );

  // serialize Grid info into bytestream
  int serialize(
                char *buffer,   // inout - byte stream to fill
                int *length,    // inout - buf length
                int *offset);   // inout - original offset, updated to point 
                                //         to first free byte after current obj info

  int deserialize(
                  char *buffer,          // in - byte stream to read
                  int *offset);          // inout - original offset, updated to point 

  // attributes
  int attpackcreate(char *name, char *convention, char *purpose, char *object);
  int attpackset(char *name, char *value, char *convention, char *purpose, char *object);
  int attpackwrite(char *convention, char *purpose, char *object) const;
  int attributeget(char *name, ESMC_TypeKind *tk, int *count, void *value) const;
  int attributeget(char *name, char *value) const;
  int attributeget(int num, char *name, ESMC_TypeKind *tk, int *count, void *value) const;
  int attributegetcount(void) const;
  int attributeset(char *name, ESMC_TypeKind tk, int count, void *value);
  int attributeset(char *name, char *value);

  // create fully formed grid
 static Grid *create(int nameLen,                                // (in)
	       char *name,                                 // (in)
	       ESMC_TypeKind *typekind,                    // (in)
	       DistGrid *distgrid,                  // (in)
	       InterfaceInt *gridEdgeLWidth,          // (in)
	       InterfaceInt *gridEdgeUWidth,          // (in)
	       InterfaceInt *gridAlign,          // (in)
	       InterfaceInt *distgridToGridMap,                  // (in)
	       InterfaceInt *undistLBound,                 // (in)
	       InterfaceInt *undistUBound,                 // (in)
	       InterfaceInt *coordDimCount,              // (in)
	       InterfaceInt *coordDimMap,             // (in)
	       ESMC_IndexFlag *indexflag,                  // (in)
	       int *rc                                     // (out) return code
	       );

 // create an empty grid for use with set/commit
  static Grid *create(int *rc);


  // make a create empty grid usable
  int commit();


  // deallocate a grid and all internal structures
  static int destroy(Grid **grid);

  // Grid Construct (grid NOT usable after construction)
  Grid();

  // Grid Destruct
  ~Grid();

  // get lower stagger offset for a particular localDe and staggerloc
  int getLDEStaggerUOffset(
		       int _staggerloc,
		       int _localDE, 
		       int *_UWidth // should be size>=grid dimCount
		       );

  // get upper stagger offset for a particular localDe and staggerloc
  int getLDEStaggerLOffset(
		     int _staggerloc,
		     int _localDE, 
		     int *_LWidth // should be size>=grid dimCount
		     );


int getDistExclusiveLBound(
                           int localDEArg, 
                           int *lBndArg    
                           );


int getDistExclusiveUBound(
                           int localDEArg, 
                           int *lBndArg    
                           );

int getExclusiveLBound(
                       int localDEArg, 
                       int *lBndArg    
                       );

int getExclusiveUBound(
                       int localDEArg, 
                       int *uBndArg    
                       );

int getComputationalLBound(
                           int staggerloc, 
                           int localDEArg, 
                           int *lBndArg    
                           );

int getComputationalUBound(
                           int staggerloc, 
                           int localDEArg, 
                           int *uBndArg    
                           );


 // Set Array for holding coordinates
 int setCoordArray(
                   int *_staggerloc,
                   int *_coord,
                   Array *_array,
                   ESMC_DataCopy *_docopy
                   );

 // Allocate coordinate Arrays for every coord in a staggerloc
 int allocCoordArray(
                     int *_staggerloc,
                     InterfaceInt *_staggerEdgeLWidthArg,
                     InterfaceInt *_staggerEdgeUWidthArg,
                     InterfaceInt *_staggerAlign
                     );

 // Get the Array containing the coordinates
 Array *getCoordArray(
                      int *_staggerloc,
                      int _coord,
                      ESMC_DataCopy *_docopy,
                      int *rcArg
                      );


 // Get data from a specific coordinate location
 template <class TYPE> int getCoord(
                                     int staggerloc, // (in)
                                     int localDE,    // (in)
                                     int *index,     // (in)  needs to be of size Grid rank
                                     TYPE *coord     // (out) needs to be of size Grid rank
                                     );

 // Get data from a specific coordinate location without error checking 
 template <class TYPE> void getCoordInternal(
                                 int staggerloc, // (in)
                                 int localDE,    // (in)
                                 int *index,     // (in)  needs to be of size Grid rank
                                 TYPE *coord     // (out) needs to be of size Grid rank
                                 );
 

 // setup internal structures in _grid based on parameters
 friend int construct(
		      Grid *_grid, 
		      int _nameLen,
		      char *_name, 
		      ESMC_TypeKind *_typekind,
		      DistGrid *_distgrid,     
                      InterfaceInt *gridEdgeLWidthArg,
                      InterfaceInt *gridEdgeUWidthArg,
                      InterfaceInt *gridAlignArg,
		      InterfaceInt *_distgridToGridMap,   
		      InterfaceInt *_undistLBound,  
		      InterfaceInt *_undistUBound,  
		      InterfaceInt *_coordDimCount,
		      InterfaceInt *_coordDimMap,
		      ESMC_IndexFlag *_indexflag 
		      );
  
};  // end class ESMC_Grid

  // set defaults for LWidth, UWidth, and Align based on user input
  int setGridDefaultsLUA(
                       int dimCount,                // Size of the input arrays
                       InterfaceInt *gridEdgeLWidthIn,  // (in) optional
                       InterfaceInt *gridEdgeUWidthIn,  // (in) optional
                       InterfaceInt *gridAlignIn,   // (in) optional
                       int *gridEdgeLWidthOut,          // (out)
                       int *gridEdgeUWidthOut,          // (out)
                       int *gridAlignOut            // (out)
                       );


  // class for iterating through the indices in a grid stagger location
  class GridIter {
  private:
    Grid *grid;     // grid being iterated through
    int staggerloc; // staggerloc in grid being iterated through
    
    int rank; // rank of grid and number of valid entires in the below
    int curInd[ESMF_MAXDIM];  // current position in index space

    int lBndInd[ESMF_MAXDIM]; // start position for allon this local DE  
    int uBndInd[ESMF_MAXDIM]; // end position on this local DE  
    int exLBndInd[ESMF_MAXDIM]; // start position on exlusive region on this DE

    int dimOff[ESMF_MAXDIM]; // Offset for each dimension for computing lid
    int lOff;                // lower bound offset
    
    int curDE; // current local DE
    int uBndDE; // end local DE on this PET (the lower bnd is 0)

    int numDE; // the number of DE's on this PET


    bool done; // are we done yet?

    bool cellNodes; // include all the nodes attached to cells on this PET's Grid


    void setDEBnds(int localDE);
    void getDEBnds(int localDE,int *uBnd,int *lBnd);

  public:

  const bool isDone(void) const {return done;}
  GridIter(Grid *gridArg, int  staggerlocArg, bool cellNodesArg);
  ~GridIter();
  GridIter *toBeg();
  GridIter *adv();
  GridIter *moveToLocalID(int localID);
  int getGlobalID();
  int getLocalID();
  bool isLocal();
  bool isShared();
  int getCount();
  int getDE();
  template <class TYPE> void getCoord(TYPE *coord);
  template <class TYPE> void getArrayData(Array *array, TYPE *data);
  }; 


  // class for iterating through the cells in a grid stagger location
  class GridCellIter {
  private:
    Grid *grid;     // grid being iterated through
    int staggerloc; // staggerloc in grid being iterated through
    
    int rank; // rank of grid and number of valid entires in the below
    int curInd[ESMF_MAXDIM];  // current position in index space

    int lBndInd[ESMF_MAXDIM]; // start position for allon this local DE  
    int uBndInd[ESMF_MAXDIM]; // end position on this local DE  
    int exLBndInd[ESMF_MAXDIM]; // start position on exlusive region on this DE

    int dimOff[ESMF_MAXDIM]; // Offset for each dimension for computing lid
    int lOff;                // lower bound offset
    
    int curDE; // current local DE
    int uBndDE; // end local DE on this PET (the lower bnd is 0)

    int numDE; // the number of DE's on this PET

    bool done; // are we done yet?

    void setDEBnds(int localDE);
    void getDEBnds(int localDE,int *uBnd,int *lBnd);

  public:

  const bool isDone(void) const {return done;}
  GridCellIter(Grid *gridArg, int  staggerlocArg);
  ~GridCellIter();
  GridCellIter *toBeg();
  GridCellIter *adv();
  GridCellIter *moveToLocalID(int localID);
  int getGlobalID();
  int getLocalID();
  int getCount();
  int getDE();
  void getCornersCellNodeLocalID(int *cnrCount, int *cnrList);
  }; 


 // Class for holding data set after grid empty creation, but before grid is finally created.
class ProtoGrid { 
 public:
  int nameLen; 
  char *name;  
  ESMC_TypeKind *typekind;
  DistGrid *distgrid;     
  InterfaceInt *gridEdgeLWidth;
  InterfaceInt *gridEdgeUWidth;
  InterfaceInt *gridAlign;   
  InterfaceInt *distgridToGridMap;   
  InterfaceInt *undistLBound;  
  InterfaceInt *undistUBound;  
  InterfaceInt *coordDimCount;  
  InterfaceInt *coordDimMap; 
  ESMC_IndexFlag *indexflag; 

  // Proto Grid Construct
  ProtoGrid();

  // Proto Grid Destruct
  ~ProtoGrid();
         
}; // end class ProtoGrid

 
} // END ESMCI namespace

#endif  // ESMC_GridI_H

