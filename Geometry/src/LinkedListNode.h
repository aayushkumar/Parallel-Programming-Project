/** \file
** <b>Role:</b>
**	Linked List class for objects.
**
** <b>Assumptions:</b>
**	None
**
** <b>Comments:</b>
**	None
**
**
**/

#ifndef __StGermain_Base_Container_LinkedListNode_h__
#define __StGermain_Base_Container_LinkedListNode_h__

	/** Textual name for ListNode class. */
	extern const char* /*Type*/ LinkedListNode_Type;

	/** \def __ListNode See ListNode */
	#define __LinkedListNode \
		/* General info */ \
		\
		/* Virtual info */ \
		\
		/* ListNode info */ \
		void 				*data; \
		SizeT				sizeOfData; \
		struct LinkedListNode		*next; 

	struct LinkedListNode { __LinkedListNode };
    typedef struct LinkedListNode LinkedListNode;

	/** Constructor interface. */
	LinkedListNode *LinkedListNode_New ( void );
	
	/** Init interface. */
	void _LinkedListNode_Init( LinkedListNode *self );
	
	/** Stg_Class_Delete interface. */
	
	/** Print interface. */

#endif /* __StGermain_Base_Container_LinkedListNode_h__ */

