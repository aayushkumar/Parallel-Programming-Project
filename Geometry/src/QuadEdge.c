/*#include <mpi.h>*/
/*#include "StGermain/StGermain.h"*/


#include "MemoryPool.h"
#include "units.h"
#include "types.h"
#include "QuadEdge.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

	/*--------------------------------------------------------------------------------------------------------------------------
	** Constructors
	*/
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Virtual functions
	*/
	
	
	/*--------------------------------------------------------------------------------------------------------------------------
	** Private Member functions
	*/

QuadEdgeRef MakeQuadEdge( MemoryPool *qp )
{
	QuadEdge *qe = (QuadEdge*)NULL;
	QuadEdgeRef e = 0;

	qe = MemoryPool_NewObject( QuadEdge, qp );
	memset( qe, 0, sizeof( QuadEdge ) );
	e = (QuadEdgeRef) qe;
	SET_IN_USE( (QuadEdgeRef)e );
	
	if( e == 0 ){
		fprintf( stderr, "Out of memory..!\n Aborting..!\n" );
		assert( 0 );
	}
	
	ONEXT(e) = e;
	SYMDNEXT(e) = SYM(e);
	ROTRNEXT(e) = TOR(e);
	TORLNEXT(e) = ROT(e);
	COUNT(e) = 0;
	
	return e;
}

void DeleteQuadEdge( MemoryPool *qp, QuadEdgeRef e)
{
	QuadEdgeRef f = SYM(e);
	
	if (ONEXT(e) != e) SpliceQuadEdges(e, OPREV(e));
	if (ONEXT(f) != f) SpliceQuadEdges(f, OPREV(f));  
    
	/*MemoryPool_DeleteObject( qp, (QuadEdge*) ((e) & WORD) );*/ //TODO
}

void SpliceQuadEdges(QuadEdgeRef a, QuadEdgeRef b)
{
	QuadEdgeRef ta, tb;
	QuadEdgeRef alpha = ROT(ONEXT(a));
	QuadEdgeRef beta = ROT(ONEXT(b));

	ta = ONEXT(a);
	tb = ONEXT(b);
	ONEXT(a) = tb;
	ONEXT(b) = ta;
	ta = ONEXT(alpha);
	tb = ONEXT(beta);
	ONEXT(alpha) = tb;
	ONEXT(beta) = ta;    
}

QuadEdgeRef ConnectQuadEdges(MemoryPool *qp, QuadEdgeRef a, QuadEdgeRef b)
{
	QuadEdgeRef e;

	e = MakeQuadEdge( qp );
	ORG(e) = DEST(a);
	DEST(e) = ORG(b);
	
	SpliceQuadEdges(e, LNEXT(a));
	SpliceQuadEdges(SYM(e), b);
	
	return e;
}



