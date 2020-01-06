/* Fill in your Name and GNumber in the following two comment fields
 * Name: Indrika Roy
 * GNumber: G01210152
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clock.h"
#include "structs.h"
#include "constants.h"

/* Schedule Count
 * - Return the number of Processes in the list.
 */
int schedule_count(Process *list) {
	int counter=0;
	Process *walker = list;
	while(walker!=NULL)
	{
		counter++;
		walker= walker->next;
	}
  return counter;
}

/* Schedule Insert
 * - Insert the Process into the List with the Following Constraints
 *   list is a pointer to the head pointer for a singly linked list.
 *   It may begin as NULL
 *   1) Insert in the order of Ascending PIDs
 *   (eg. 1, 13, 14, 20, 32, 55)
 * Remember to set list to the new head if it changes!
 */
void schedule_insert(Process **list, Process *node) {
  /* Complete this Function */
	Process *walker=*list;
	Process *walker1=walker;
	if(*list==NULL)								//Condition for if the list is empty
	{
		*list=node;
	}
	else if(((*list)->next) == NULL||((*list)->pid)>(node->pid))		//Condition for if there is only one node in the list or PID 											//of the incoming node is more than PID of list 
	{
		if(((*list)->pid)<(node->pid))
		{
			(*list)->next=node;
		}
		else
		{       walker = *list;
			*list = node;
			(*list)->next = walker;
		}
	}
	else 
		{ walker = *list;
			while(walker!=NULL)					//Condition for if the node is to be inserted in between the 											//list or at the end of the list
			{ 
				walker1=walker;
				walker=walker->next;       			//to traverse the linked list
			
				if((walker->pid)>(node->pid))
				{
					node->next=walker1->next;
					walker1->next=node;
					break;
				
				}
				else if (walker->next==NULL)
				{
				walker->next=node;
				break;
				}
			}
		}
  return;
}

/* Schedule Terminate
 * - Unallocate the Memory for the given Node
 */
void schedule_terminate(Process *node) {
 	free(node);
	node= NULL;
  return;
}

/* Schedule Generate
 * - Allocate the Memory and Create the Process from the given Variables
 *   Remember to initialize all values, including next!
 */
Process *schedule_generate(const char *name, int pid, int time_remaining, int time_last_run) {
	Process *new=malloc(sizeof(Process));
	if(new==NULL)								//to check whether heap is full or not
	{
	return NULL;
	}
	else
	{
	new->next= NULL;
	strncpy(new->name, name, strlen(name)+1); 
	new->pid= pid;
	new->time_remaining= time_remaining;
	new->time_last_run= time_last_run;
	return new;
	}
}

void schedule_remove(Process ***list, Process *node){
	Process *walker=**list;
	Process *walker1=walker;						//to set a counter to the previous node
	
	while(walker!=NULL)
	{ 
		walker1 = walker;						
		walker = walker->next;
	if((**list)->next==NULL)						//if there is only one node in the list
	{
       		**list=NULL; 
                break;
	}
	else if(((**list)->pid==node->pid) && ((**list)->next!=NULL))		//if given node to be removed is same as list and list has 											//more than one node
	{
		**list=(**list)->next;						
		break;
	}
	else if(walker->pid==node->pid)
	{
		walker=walker->next;
		walker1->next=walker;
		break;
	}
	}
return;	
}


/* Schedule Select
 * - Select the next Process to be run using the following conditions:
 *   1) The Process with the lowest time_remaining should run next.
 *   - If there are any ties, select the Process with the lowest PID
 *   2) If there is a Process that has not run in >= TIME_STARVATION, then
 *   select that one instead.
 *      (Use the function clock_get_time() to get the current time)
 *   - If there are any ties, select the Process with the lowest PID
 *   3) If the list is NULL, return NULL
 * - Remove the selected Process from the list
 * - Return the selected Process
 */
Process *schedule_select(Process **list) {
	int flag=0;								//to check whether starving node is present or not
	int ct = clock_get_time();
	
	if (*list == NULL)
       	{ return NULL;
	} 
        else{ 
	Process *walker= *list;
	Process *node= NULL;
	
	while(walker!=NULL)
	{
	if((ct-(walker->time_last_run))>=5)					//condition to check starving node
	{
		if(node==NULL)
		{
		node=walker;
		flag=1;
		}
		else if((ct-(walker->time_last_run))>(ct-(node->time_last_run)))
		{
		node=walker;
		flag=1;
		}
	}
	walker=walker->next;
	}
	if(flag==1)
	{
		schedule_remove(&list, node);
		return node;
	}
	else
	{	
	walker=*list;
	node=walker;
	while(walker!=NULL)
	{
	if((node->time_remaining)>(walker->time_remaining))			//condition to check node with the shortest remaining time
	{
		node=walker;
	}
		walker=walker->next;
	}
	schedule_remove(&list, node);
	return node;
	}
}
}

