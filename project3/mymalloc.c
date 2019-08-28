/****************************************************************
*author: Matt Stropkey/mas682					*
*file: mymalloc.c						*
*This program implements malloc using the best fit approach.	*
*The best fit approach allocates space by finding the free	*
*space that most closely matches the size of the space that	*
*you wish to allocate.  If a perfect match is found, the	*
*address is choosen immediately.				*
****************************************************************/

#include <stdlib.h>
#include <stdio.h>

static struct double_node *header_node;			//used to hold the head node of the list	


static void *empty_node(int size);			//function prototype for empty node

//struct for a node in the linked list
struct double_node{
	int size;				//size of the number of bytes reserved
	struct double_node *next_ptr;		//forward link
	struct double_node *previous_ptr;	//backward link
	char open;				//used as a boolean to see if in use
};

//this function is used to place a new node within the linked list
static void double_enter(struct double_node *new_item_ptr, int item)
{
	struct double_node *insert_ptr;		//insert before this element

	insert_ptr = header_node;			//insert_ptr = head
	while(1)
	{
		if(insert_ptr->next_ptr == NULL)	//if insert_ptr's next node is null break as at end of list
		{
			break;
		}//if we have reached the end
		insert_ptr = insert_ptr->next_ptr;	//if insert_ptr's next node not null, set insert_ptr to this node	
	}
	new_item_ptr->next_ptr = NULL;		//set the new ptr's next node to null
	new_item_ptr->previous_ptr = insert_ptr;	//set the previous node of new node to insert
	insert_ptr->next_ptr = new_item_ptr;		//set insert ptr's next node to the new one
	new_item_ptr->size = item;
	new_item_ptr->open = 1;
}


//my version of malloc
void *my_bestfit_malloc(int size)
{	
	if(size == 0)				//if size is 0, do not add to heap
	{
		return (void *)sbrk(size);	//just return the address of brk
	}
	else
	{	
		struct double_node *temp;		//used for a new node entry in list
		if(header_node == NULL)			//if no nodes in list, create a head node
		{
			temp = (struct double_node*)sbrk(size+sizeof(struct double_node));	//node temp placed at newly allocated space
			if(-1 == (int)temp)				//if allocation too large
			{
				printf("Out of space on heap.\n");
				return temp;
			}
			header_node = temp;					//store the head node of the list
			temp->size = size+sizeof(struct double_node);		//store the size of the data allocation in the node
			temp->next_ptr = NULL;					//set the next node to null as there should be no other nodes at this point
			temp->previous_ptr = NULL;
			temp->open = 1;
			return (void *)(header_node)+sizeof(struct double_node);	//return the address that headernode holds + the size of the node as this is where the newly allocated space should be
		}//end of inner if
		else if(header_node != NULL)//if a node exists in the list
		{
			temp =(struct double_node*)empty_node(size);		//see if there are any open spaces in memory
			if(temp == NULL)		//temp did not find a open space, so add more space to heap
			{	
				temp = (struct double_node*)sbrk(size+sizeof(struct double_node));	//node placed at newly allocated space
				if(-1 == (int)temp)				//no more space on available
				{
					printf("Out of space on heap.\n");
                                	return temp;
				}
				double_enter(temp, size+sizeof(struct double_node));			//used to enter the node into the list
			}
			else				//temp found a open space just just update that space in use
			{
				
				if(temp->size > (size+sizeof(struct double_node)+sizeof(struct double_node)))
				{//split the node if room for another node plus at least one byte
					int new_node_size = temp->size-(size+sizeof(struct double_node));	//hold the size for the new empty node
                                	struct double_node *split;						//pointer for the new empty node
                                	struct double_node *old_next = temp->next_ptr;				//used to hold address to next node
					int new_add = (int)temp + size + sizeof(struct double_node);		//this used to add value to new address
					split = (struct double_node*)new_add;					//split assigned address
					temp->size = size+sizeof(struct double_node);				//temp given new size
					temp->next_ptr = split;							//point to the empty node
					temp->open = 1;								//set temp to in use
					split->size = new_node_size;						//set the empty nodes size
					split->previous_ptr = temp;						//set the empty nodes previous node
					split->next_ptr = old_next;						//set the empty nodes next node
					split->open = 0;							//set the empty node to not in use
					if(old_next != NULL)							//if next node is not empty
					{
						old_next->previous_ptr = split;					//set next nodes previous node to the empty node
					}//end if
				}//end of if
				else					//do this if perfect fit or not big enough to split
				{		
					temp->open = 1;			//just set the node to in use
				}//end of else
			}
			return (void *)(temp)+sizeof(struct double_node);
		}//end of else if
	}//end of else

}

//this function used to find a empty node in the list
static void *empty_node(int size)
{
	struct double_node *t = header_node;				//used to go through list
	struct double_node *best = NULL;		//used as a holder of current best location
	int full_size = size+sizeof(struct double_node);	//used to hold actual size needed
	int current_best = 0; 				//holds the current best fit byte value
	while(1)
	{
		if(t->open == 0)
		{
			if(t->size == full_size)	//if perfect match, return t
			{
				return t;
			}//end of if
			else if(t->size > full_size && current_best == 0)	//if no current best size
			{
				best = t;
				current_best = t->size;
			}//end of else if
			else if(t->size < current_best && t->size > full_size)	//if better than current best
			{
				best = t;
				current_best = t->size;
			}//end of else if
		}//end of outter if
		if(t->next_ptr != NULL)			//check the next node
		{
			t = t->next_ptr;		//set t to the next node
		}
		else
		{
			break;
		}
	}//end of while loop
	return best;			//return either the best available node or NULL if no avaiable nodes
}

//my version of free
void my_free(void *ptr)
{
	int free_node = (int)ptr - sizeof(struct double_node);		//get address of node to free
	struct double_node *temp = (struct double_node*)free_node;				//set temp to the address
	temp->open = 0;							//set the node to free
	
	if(temp->next_ptr != NULL && temp->next_ptr->open == 0)		//if next node is open, combine temp and next node
	{
		struct double_node *old = temp->next_ptr;		//old = the next node
		if(old->next_ptr != NULL)				//if olds next node is not null
		{
			old->next_ptr->previous_ptr = temp;		//set olds next nodes previous node to temp
		}
		int x = temp->size + old->size;				//x = temp size + olds size
		temp->size = x;						//set temps size to x
		old->previous_ptr = NULL;				//setld olds previous ptr to null
		temp->next_ptr = old->next_ptr;				//set temps next node to olds next node
		old->size = 0;						//set olds size to 0
		old->next_ptr = NULL;					//set olds next node value to null
		old = NULL;						//set old to NULL
	}
	if(temp->previous_ptr != NULL && temp->previous_ptr->open == 0)	//if previous node is open, combine temp and previous
        {
                struct double_node *old = temp->previous_ptr;		//set the previous node to old
                int x = temp->size + old->size;				//x = temp size + old size
                old->size = x;						//set old size to x
		old->next_ptr = temp->next_ptr;				//set olds next ptr to temps next node
		if(temp->next_ptr != NULL)				//if temps next node not null
                {
			temp->next_ptr->previous_ptr = old;		//set temps next nodes previous pointer to old
		}
		temp->next_ptr = NULL;					//temps next pointer = NULL
		temp->previous_ptr = NULL;				//temps previous pointer = NULL
		temp->size = 0;						//temps size = 0
		temp = NULL;						
                temp = old;						//temp now equals old
        }
	if(temp->next_ptr == NULL)					//if at the last node in the list, shrink heap
	{	
		if(temp == header_node)					//if at the header node
                {
			int x = temp->size;				//x = header nodes size
			x = ~x+1;					//negate x
			temp = NULL;					//set temp to NULL
			temp = (struct double_node *)sbrk(x);		//shrink heap
			temp = NULL;					//temp = NULL
			header_node = NULL;				//header = NULL
                }//end of if
		else
		{
			int x = temp->size;				//set x to temps size
			temp->previous_ptr->next_ptr = NULL;		//set temps previous nodes next node to null
			temp->size = 0;					//set temps size to 0
			temp->previous_ptr = NULL;			//set temps previous node to null
			temp = NULL;					//set temp to null
			x = ~x +1;					//used to negate the size of the node
			temp = (struct double_node *)sbrk(x);		//shrink size of heap
		}
		//printf("brk: %d\n", sbrk(0));				//for testing
	}//end of if	 
}//end of my free

