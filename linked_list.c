#include <stdlib.h>
#include "linked_list.h"

// Creates and returns a new list
// If compare is NULL, list_insert just inserts at the head
list_t* list_create(compare_fn compare)
{
    /* IMPLEMENT THIS */

    list_t* nl = (list_t*)malloc(sizeof(list_t));
    nl->head = NULL;
    nl->tail = NULL;
    nl->count = 0;
    nl->compare = compare;
    /*
    if (compare == NULL) //not sure how to insert at the head
    {
        nl->head->next = nl->head; //only insert so can point to head
        nl->tail->prev = nl->tail; //only insert so can only point to tail
        nl->count = 1; //inserts at head so only 1 element
    }
    */
    return nl;
}

// Destroys a list
void list_destroy(list_t* list)
{
    /* IMPLEMENT THIS */

    list_node_t* destroy;

    //checks for number of nodes and makes sure it is not at the end of the list
    while (list->head != NULL && list->count >= 1)
    {
        destroy = list->head; //place holder
        list->head = list->head->next; //goes to next in data

        free(destroy); //destory the data
    }
    free(list);
}

// Returns head of the list
list_node_t* list_head(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->head;
}

// Returns tail of the list
list_node_t* list_tail(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->tail;
}

// Returns next element in the list
list_node_t* list_next(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->next;
}

// Returns prev element in the list
list_node_t* list_prev(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->prev;
}

// Returns end of the list marker
list_node_t* list_end(list_t* list)
{
    /* IMPLEMENT THIS */
    //dont need according to TA    
    return list->tail;
}

// Returns data in the given list node
void* list_data(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->data;
}

// Returns the number of elements in the list
size_t list_count(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->count;
}

// Finds the first node in the list with the given data
// Returns NULL if data could not be found
list_node_t* list_find(list_t* list, void* data)
{
    /* IMPLEMENT THIS */

    //loop through to find the node    
    list_node_t* first = list->head;

    while (first != NULL)
    {
        if (first->data == data) //if data is what we are looking for
        {
            return first;
        }
        else //we iterate to next node
        {
            first = first->next;
        }
    }
    
    
    return NULL;
}

// Inserts a new node in the list with the given data
// Returns new node inserted
list_node_t* list_insert(list_t* list, void* data)
{
    /* IMPLEMENT THIS */
    //if there is a compare function else no compare function. they do seperate things
    
    list_node_t* nnode = (list_node_t*) malloc(sizeof(list_node_t));

    nnode->data = data;
    list->count = list->count +1;


     if (list->compare == NULL) //if compare is NULL, then it unsorted, insert at head
     {
        if (list->head  == NULL) //TA said case for no head
        {
            nnode->prev = NULL;
            nnode->next = NULL;
            //nnode->data = data;
            list->head = nnode;
            list->tail = nnode;
            //list->count = list->count + 1;

            return list->head;
        }
        else //there is head and insert
        {
            list->head->prev = nnode;
            nnode->next = list->head;
            nnode->prev = NULL;
            //nnode->data = data;
            list->head = nnode;
            //list->count = list->count + 1; //increase count by one

            return nnode;
        }

    }
    else //list is sorted when compare function is given
    {
        //do a while loop inside so that we iterate through linked list and compare old data and new node data, then it returns a value and we insert based on that
        //int value = compare(list->next->data, data); // if compare is 1, that means list next data is bigger and data should be inserted before list next data
        
        //ta said corner case no head
        if(list->head == NULL)
        {
            nnode->prev = NULL;
            nnode->next = NULL;
            //nnode->data = data;
            list->head = nnode;
            list->tail = nnode;
            //list->count = list->count + 1;

            return list->head;
        }

        list_node_t* curr = list->head;

        while (curr != NULL) //while not at end of the list
        {
             int value = list->compare(nnode->data, curr->data); // if compare is -1, that means list next data is bigger and data should be inserted before list next data
             //list_node_t* temp = list->head->next;

             //insert at head ta said corner cases
             if (value == -1 || value == 0)
                {
                    //insert at head ta said corner cases
                    if(curr == list->head)
                    {
                        nnode->prev = curr->prev; //points new head to curr
                        nnode->next = curr; //makes curr prev to new head
                        curr->prev = nnode; //since new head, prev has to be null
                        list->head = nnode; //make new head
                        //nnode->data = data;
                        //list->count = list->count + 1;

                        return nnode;
                    }

                    else //insert data before because list next data is bigger
                    {
                        nnode->prev = curr->prev; //get the curr next prev to point to nnode
                        nnode->next = curr; //point nnode next to curr next
                        curr->prev->next = nnode; //move curr next pointer to nnode
                        curr->prev = nnode; //make nnode prev to curr
                     //nnode->data = data;
                     //list->count = list->count + 1;


                        return nnode; //to exit after insertion

                    }
                }
             else //move to the next node in list, should i remove
             {
                 curr = curr->next; //move to next in list to next in list
             }
            
        }
        //if nothing gets inserted, insert at end
        list->tail->next = nnode; //make nnode after tail
        nnode->prev = list->tail; //nnode last, so make prev point to tail
        list->tail = nnode; //set the new tail to nnode
        nnode->next = NULL; //nnode next points to null, since it is last
        //nnode->data = data;
        //list->count = list->count + 1;
        
        return nnode;
        
        //list->count = list->count +1;
        //restore head
    }
    
    return NULL;
}

// Removes a node from the list and frees the node resources
void list_remove(list_t* list, list_node_t* node)
{
    /* IMPLEMENT THIS */
    //3 cases, when it is in the head, when ndoe is in middle, when node is at the tail
    //just need to change two links each time
    if (node != NULL)
    {
         if(node->prev == NULL) //at head because prev is null and there is a next
         {
             //list->head->next->prev = NULL; //becomes the first node
             list->head = node->next; //new head 
         }
         else if (node->prev != NULL)//at middle because there is next node and prev node
         { 
             node->prev->next = node->next; //skips over the node deleted
             //node->next->prev = node->prev; //skips over the node delted
         }
         //else if (node->next != NULL) //at middle because there is next node and prev node
         //{
             //node->prev->next = node->next; //skips over the node deleted
             //node->next->prev = node->prev; //skips over the node delted
         //}
         if (node->next == NULL)//at the end because next is null
         {
             list->tail = node->prev; //becomes the new tail node
             //list->tail->next = NULL; //need to point to null
         }
         else if(node->next != NULL)//at middle because there is next node and prev node
         {
             //node->prev->next = node->next; //skips over the node deleted
             node->next->prev = node->prev; //skips over the node delted
         }
    
         free(node);
         list->count = list->count -1;
    }
}
