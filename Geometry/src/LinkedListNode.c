/*
#include <Base/Foundation/Foundation.h>
#include <Base/IO/IO.h>
*/

#include "MemoryPool.h"
#include "units.h"
#include "types.h"
#include "QuadEdge.h"
#include "LinkedListNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char* /*Type*/ LinkedListNode_Type = "LinkedListNode";

LinkedListNode* LinkedListNode_New( void )
{
	LinkedListNode* self;
	
	/* Allocate memory */
	self = (LinkedListNode *) malloc(sizeof(LinkedListNode)); /*Memory_Alloc( LinkedListNode, "LinkedListNode" );*/
	memset ( self, 0, sizeof ( LinkedListNode ) );

	assert( self );
	/* General info */
	
	/* Virtual functions */
	
	self->next = NULL;
	_LinkedListNode_Init( self );
	
	return self;
}

void _LinkedListNode_Init( LinkedListNode* self ){
	
	/* General info */
	
	/* Virtual info */
	
	/* ListNode info */
		assert( self );
	self->data = NULL;
	self->sizeOfData = 0;
}


