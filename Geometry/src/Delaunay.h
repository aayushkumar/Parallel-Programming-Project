/** \file
**  Role:
**	Calculates the delaunay triangulation and the voronoi diangram of a set of points.
**
** Assumptions:
**
** Comments:
**
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __StgDomain_Geometry_Delaunay_h__
#define __StgDomain_Geometry_Delaunay_h__

	/* Virtual function types */
	
	/** Textual name of this class */
	extern const char* Delaunay_Type;

	typedef struct DelaunayAttributes_t{
		int	BuildBoundingTriangle;
		int BuildTriangleIndices;
		int BuildTriangleNeighbours;
		int CreateVoronoiVertices;
		int CalculateVoronoiSides;
		int CalculateVoronoiSurfaceArea;
		int FindNeighbours;
	}DelaunayAttributes;

	typedef struct Site_t{
		CoordF *coord;
		int id;
	}Site;

	/** Delaunay class contents (see Delaunay) */
	#define __Delaunay \
		/*__Stg_Component */\
		/*AbstractContext*		context; */\
		/*Dictionary			*dictionary; */\
		MemoryPool			*qp; \
		MemoryPool			*vp; \
		int					numSites; \
		int					numInputSites; \
		CoordF				*points; \
		Site				*sites; \
		int					idOffset; \
		CoordF				boundingTriangle[3]; \
		int					numEdges; \
		int					numVoronoiSites; \
		int					numTriangles; \
		int					numFaces; \
		unsigned int		**triangleIndices; \
		unsigned int		**triangleNeighbours; \
		int					numVoronoiVertices; \
		unsigned int		*numNeighbours; \
		unsigned int		**neighbours; \
		float				**voronoiSides; \
		float				*voronoiArea; \
		int					*hull; \
		QuadEdgeRef			rightMost; \
		QuadEdgeRef			leftMost; \
		DelaunayAttributes *attributes;
	
	struct Delaunay { __Delaunay };
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Constructors
	*/
    typedef char* Name;
	/** Create a Delaunay */
	Delaunay* Delaunay_DefaultNew( Name name );
	
	Delaunay* Delaunay_New(
		Name						name,
		/*Dictionary*					dictionary,*/
		CoordF						*sites,
		int							numSites,
		int							idOffset,
		DelaunayAttributes			*attr );
	
	/** Initialise a Delaunay */
	void Delaunay_Init(
		Delaunay*					self,
		Name						name,
		/*Dictionary*					dictionary,*/
		CoordF						*sites,
		int							numSites,
		int							idOffset,
		DelaunayAttributes			*attr );
	
	/** Creation implementation */
	
	#ifndef ZERO
	#define ZERO 0
	#endif

	#define DELAUNAY_DEFARGS \
                /*STG_COMPONENT_DEFARGS, */\
                Bool                   initFlag, \
                /*Dictionary*          dictionary,*/ \
                CoordF*                   sites, \
                int                    numSites, \
                int                    idOffset, \
                DelaunayAttributes*        attr

	#define DELAUNAY_PASSARGS \
            /*    STG_COMPONENT_PASSARGS, */\
	        initFlag,   \
	        dictionary, \
	        sites,      \
	        numSites,   \
	        idOffset,   \
	        attr      

	Delaunay* _Delaunay_New(  DELAUNAY_DEFARGS  );
	
    //void _Delaunay_Init( Delaunay* self );
    void _Delaunay_Init( Delaunay* self, CoordF* points, DelaunayAttributes* attr, int numSites, int idOffset, /*Dictionary* dictionary, */Bool initFlag );
	
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Virtual functions
	*/
	
	/** Stg_Class_Delete() implementation */
	void _Delaunay_Delete( void* delaunay );
	
	/** Stg_Class_Print() implementation */
	/*void _Delaunay_Print( void* delaunay, Stream* stream );*/
	
/*	void *_Delaunay_Copy( void* delaunay, void* dest, Bool deep, Name nameExt, PtrMap* ptrMap );*/
	
/*	void _Delaunay_AssignFromXML( void* delaunay, Stg_ComponentFactory* cf, void* data );*/
	
	void _Delaunay_Build( void* delaunay, void* data );
	
	void _Delaunay_Initialise( void* delaunay, void* data );
	
	void _Delaunay_Execute( void* delaunay, void* data );
	
	void _Delaunay_Destroy( void* delaunay, void* data );

	unsigned int **Delaunay_GetTriangleIndices( Delaunay *delaunay );
	float **Delaunay_GetVoronoiSides( Delaunay *delaunay );
	float *Delaunay_GetSurfaceArea( Delaunay *delaunay );
	unsigned int *Delaunay_GetNumNeighbours( Delaunay *delaunay );
	unsigned int **Delaunay_GetNeighbours( Delaunay *delaunay );
	int *Delaunay_GetHull( Delaunay *delaunay );
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Private Member functions
	*/
	void Delaunay_SortSites(Site *sites, int numSites );
	int RightOf(Site *s, QuadEdgeRef e);
	int LeftOf(Site *s, QuadEdgeRef e);
	int InCircle(Site *a, Site *b, Site *c, Site *d);
	void Delaunay_Recurse( Delaunay *delaunay, int sl, int sh, QuadEdgeRef *le, QuadEdgeRef *re );
	void Delaunay_FindHull( Delaunay *delaunay );
	void Delaunay_BuildTriangleIndices( Delaunay *delaunay );
	void Delaunay_BuildVoronoiVertices( Delaunay *delaunay );
	void Delaunay_FindNeighbours( Delaunay *delaunay );
	void Delaunay_FindMinMax( Site *sites, int count, float *minX, float *minY, float *maxX, float *maxY );
	
#endif /* __StgDomain_Geometry_Delaunay_h__ */

