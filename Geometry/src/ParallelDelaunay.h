/** \file
**  Role:
**	Calculates the ParallelDelaunay triangulation and the voronoi diangram of a set of points.
**
** Assumptions:
**
** Comments:
**
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __StgDomain_Geometry_ParallelDelaunay_h__
#define __StgDomain_Geometry_ParallelDelaunay_h__

	/* Virtual function types */
	
	/** Textual name of this class */
	extern const char * /*Type*/ ParallelDelaunay_Type;

	/** ParallelDelaunay class contents (see Delaunay) */
	#define __ParallelDelaunay \
		__Delaunay \
		CoordF		*localPoints; \
		int			*initialOrder; \
		int			leftProc; \
		int			rightProc; \
		int			numProcs; \
		/*BTree		*haloSites[2]; */\
		int			numHaloSites[2]; \
		Delaunay	*localTriangulation; \
		int			*mappingTable[2]; \
		int			*mapGlobalToLocal; \
		int			*processor; \
		int			*processorLoad; \
		int			rank; \
		int			numLocalSites; \
		int			numTotalLocalSites; \
		MemoryPool	*sitePool; \
		MemoryPool	*coordPool; \
		MPI_Comm	*comm;
	struct ParallelDelaunay { __ParallelDelaunay };
	
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Constructors
	*/
	
	/** Create a ParallelDelaunay */
	ParallelDelaunay* ParallelDelaunay_DefaultNew( Name name );
	
	ParallelDelaunay* ParallelDelaunay_New(
		Name						name,
		/*Dictionary*					dictionary,*/
		CoordF						*sites,
		int							numSites,
		int							rank,
		int							numProcs,
		MPI_Comm					*comm,
		DelaunayAttributes	*attr );
	
	/** Initialise a ParallelDelaunay */
	void ParallelDelaunay_Init(
		ParallelDelaunay*					self,
		Name						name,
		/*Dictionary*					dictionary,*/
		CoordF						*sites,
		int							numSites,
		int							rank,
		int							numProcs,
		MPI_Comm					*comm,
		DelaunayAttributes			*attr );
	
	/** Creation implementation */
	
	#ifndef ZERO
	#define ZERO 0
	#endif

	#define PARALLELDELAUNAY_DEFARGS \
                DELAUNAY_DEFARGS, \
                int            rank, \
                int        numProcs, \
                MPI_Comm*      comm

	#define PARALLELDELAUNAY_PASSARGS \
                DELAUNAY_PASSARGS, \
	        rank,     \
	        numProcs, \
	        comm    

	ParallelDelaunay* _ParallelDelaunay_New(  PARALLELDELAUNAY_DEFARGS  );
	
	//void _ParallelDelaunay_Init( ParallelDelaunay* self );
    void _ParallelDelaunay_Init( ParallelDelaunay* self, CoordF* points, int leftProc, int rightProc, int rank, int numProcs, MPI_Comm* comm, int numSites, int numInputSites, /*Dictionary* dictionary, */Bool initFlag );
	
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Virtual functions
	*/
	
	/** Stg_Class_Delete() implementation */
	void _ParallelDelaunay_Delete( void* pd );
	
	/** Stg_Class_Print() implementation */
	/*void _ParallelDelaunay_Print( void* pd, Stream* stream );*/
	
    /*void *_ParallelDelaunay_Copy( void* pd, void* dest, Bool deep, Name nameExt, PtrMap* ptrMap );*/
/*	
	void _ParallelDelaunay_AssignFromXML( void* pd, Stg_ComponentFactory* cf, void* data );
*/	
	void _ParallelDelaunay_Build( void* pd, void* data );
	
	void _ParallelDelaunay_Initialise( void* pd, void* data );
	
	void _ParallelDelaunay_Execute( void* pd, void* data );
	
	void _ParallelDelaunay_Destroy( void* pd, void* data );

	/*--------------------------------------------------------------------------------------------------------------------------
	** Private Member functions
	*/
	typedef enum Direction_t{
		LEFT,
		RIGHT
	}Direction;

	void ParallelDelaunay_RetriangulateAfterMerge( ParallelDelaunay *pd, Direction d );
	void ParallelDelaunay_BuildTriangleIndices( ParallelDelaunay *pd );
	void ParallelDelaunaySendEdge( QuadEdgeRef edge, int rank, MPI_Comm *comm, MPI_Request *req );
	QuadEdgeRef ParallelDelaunayRecvEdge( ParallelDelaunay *pd, int rank, MPI_Comm *comm );

	QuadEdgeRef ParallelDelaunayFindLowestQuadEdge( ParallelDelaunay *pd, MPI_Comm *comm, int rank );
	void ParallelDelaunayMerge( ParallelDelaunay *pd, MPI_Comm *comm, int rank );
	int ParallelDelaunay_TranslateLocalToGlobal( ParallelDelaunay *self, int id );
	/*--------------------------------------------------------------------------------------------------------------------------
	** Public Member functions
	*/
	
	void ParallelDelaunay_GatherTriangulation( ParallelDelaunay *pd );
	
#endif /* __StgDomain_Geometry_ParallelDelaunay_h__ */

