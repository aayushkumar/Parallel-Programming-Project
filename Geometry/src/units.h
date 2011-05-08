/** \file
**  Role:
**
** Assumptions:
**
** Comments:
**
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __StgDomain_Geometry_units_h__
#define __StgDomain_Geometry_units_h__

	#define MAX_SYMMETRIC_TENSOR_COMPONENTS 6
	#define MAX_TENSOR_COMPONENTS           9
	
	/** Defines a complex number as 2 doubles */
	typedef double Cmplx[2];
	/** Defines a set of 3 doubles */
	typedef double XYZ[3];
	typedef XYZ Coord;
	/**Defines a set of 3 floats */
	typedef float XYZF[3];
	typedef XYZF CoordF;
	/** Defines a set of 3 integers that can be used to index
	into vectors */
	typedef int XYZI[3];
	typedef XYZI CoordI;
	/** Defines a set of 3 Cmplx */
	typedef Cmplx XYZC[3];
	typedef XYZC CoordC;

	typedef double SymmetricTensor[ MAX_SYMMETRIC_TENSOR_COMPONENTS ];
	typedef double TensorArray[ MAX_TENSOR_COMPONENTS ];
	typedef Cmplx ComplexTensorArray[MAX_TENSOR_COMPONENTS]; 

#endif /* __StgDomain_Geometry_units_h__ */
