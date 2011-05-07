/*#include <Base/Foundation/Foundation.h>
#include <Base/IO/IO.h>
*/
#include "types.h"
#include "LinkedListNode.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char * /*Type*/ LinkedListIterator_Type = "LinkedListIterator";

LinkedListIterator *_LinkedListIterator_New(  LINKEDLISTITERATOR_DEFARGS  )
{
	LinkedListIterator *self = NULL;

	/** LinkedListIterator using Class_New, because  Memory module has been initialized */
	
	self = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));/*_Stg_Class_New(  STG_CLASS_PASSARGS  );*/
	/* Custom added coz of Stg_class_new*/
    memset(self, 0, sizeof(LinkedListIterator));
	return self;
}

LinkedListIterator *LinkedListIterator_New( LinkedList *list )
{
	/* Variables set in this function */
	SizeT                      _sizeOfSelf = sizeof(LinkedListIterator);
	Type                              type = LinkedListIterator_Type;
	/*Stg_Class_DeleteFunction*      _delete = _LinkedListIterator_DeleteFunc;
	Stg_Class_PrintFunction*        _print = _LinkedListIterator_PrintFunc;
	Stg_Class_CopyFunction*          _copy = NULL;
    */
	
	LinkedListIterator* self;
	
	assert( list );
	self = _LinkedListIterator_New(  LINKEDLISTITERATOR_PASSARGS  );
	/* General info */
	
	/* Virtual functions */
	assert( list );
	self->list = list;
	
	_LinkedListIterator_Init( self );	
	return self;
}

void _LinkedListIterator_Init( LinkedListIterator* self )
{

}

void _LinkedListIterator_DeleteFunc( void *self )
{
	/*if( self ){
		_Stg_Class_Delete( self );
	}
    */
}

/*
void _LinkedListIterator_PrintFunc( void *self, Stream *myStream )
{
	LinkedListIterator *iterator = NULL;

	iterator = (LinkedListIterator*) self;
	assert( iterator );

*/	/* print parent */
/*	_Stg_Class_Print( (void*) iterator, myStream );
*/
	/* general info */
/*	Journal_Printf( myStream, "LinkedListIterator (ptr): (%p)\n", iterator );
	Journal_Printf( myStream, "\tlist (ptr): (%p)\n", iterator->list );
}
*/

