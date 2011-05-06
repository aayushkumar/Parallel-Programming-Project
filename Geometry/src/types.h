/** \file
**  Role:
**	Basic framework types.
**
** Assumptions:
**	None as yet.
**
** Comments:
**	None as yet.
**
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __StgDomain_Geometry_types_h__
#define __StgDomain_Geometry_types_h__

    typedef enum Bool { False=0, True=1 } Bool;	
    typedef unsigned int Index;
	typedef Index		NeighbourIndex;

	/** Describes a plane in 3D space, ie. Ax + By + Cz = d */
	typedef double		Plane[4];             
	/** Type used for indexing into lists of planes */ 
	typedef Index		Plane_Index;
	typedef Plane*		Plane_List;


	/** Stores three indices per triangle, each index refering to a coordinate stored in an external list */
	typedef Index		Triangle[3];
	/** Type used for indexing into lists of triangles */
	typedef Index		Triangle_Index;
	/** A type used to point to the head of a list of triangles */
	typedef Triangle*	Triangle_List;
	
	/** Stores the three planes needed to describe the 3D boundary of a triangle */
	typedef Plane		TriangleBoundary[3];

	/** Describes an edge between two points. Stored as two indices into an external coordinate list */
	typedef Index		Edge[2];
	/** Type used for indexing into lists of edges */
	typedef Index		Edge_Index;
	/** A type used to point to the head of a list of edges */
	typedef Edge*		Edge_List;

	/** Every edge can be touching at most two faces/elements/triangles. This type consists of two indices into
	 an external list of faces/elements/triangles describing the faces touched by an edge. */	
	typedef Index		EdgeFaces[2];
	typedef EdgeFaces*	EdgeFaces_List;
	typedef Index		EdgeFaces_Index;

	typedef double		Stg_Line[4];
	typedef Index		Line_Index;
	typedef Stg_Line*	Stg_Line_List;

	typedef Coord		Line3[2];
	
	
	typedef double		RMatrix[9];
	
	typedef Index		Dimension_Index;
	typedef Index		IJK[3];				/* ijk indices, positive, not constrained */
	typedef Index*		Indices;			/* array/list of indices */
	typedef enum Axis { I_AXIS=0, J_AXIS=1, K_AXIS=2 } Axis;

	typedef Coord*				Coord_List;
	typedef Index				Coord_Index;
	typedef long int 			QuadEdgeRef;

	typedef struct QuadEdge			QuadEdge;
	typedef struct QuadEdgePool		QuadEdgePool;
	typedef struct VoronoiVertexPool		VoronoiVertexPool;
	typedef struct Delaunay			Delaunay;
	typedef struct ParallelDelaunay	ParallelDelaunay;

	
#endif /* __StgDomain_Geometry_types_h__ */

