/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for ITU course Operating Systems and C.
 * A fork of the C programming lab developed at CMU for courses
 * 15-213/18-213/15-513 by R. E. Bryant, 2017 (extended w/ strings 2018)
 *
 * TODO: fill in your name and ITU alias
 * @author FIRSTNAME LASTNAME <ALIAS@itu.dk>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    /* What if malloc returned NULL? */

    queue_t *q = malloc(sizeof(queue_t));
    
    /* Test for malloc failure */
    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {

    /* Test for empty/no queue */
    if (q==NULL)
    {
        return;
    }
    list_ele_t* temp;
    list_ele_t* item = q->head;

    while (item != NULL)
    {
        temp = item->next;
        free(item->value);
        free(item);
        item = temp;
    }

    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {

    /* Test for empty/no queue */
    if (q == NULL)
    {
        return false;
    }

    list_ele_t *newh;

    newh = malloc(sizeof(list_ele_t)); 
    /* Test for malloc failure */
    if (newh==NULL)
    {
        return false;
    }

    //Allocate memory for each char in the input
    newh->value = malloc(sizeof(char) * strlen(s));
    /* Test for malloc failure */
    if (newh->value ==  NULL)
    {
        free(newh);
        return false;
    }
    //Copy string into theh node
    strcpy(newh->value, s);
    
    //Link new node to old head
    newh->next = q->head;
    //Point queue head at the new node
    q->head = newh;
    
    //If it's the first element, it's both the head and the tail, and points at NULL
    if (q->size == 0)
    {
        q->tail = newh;
        q->head->next = NULL;
    }
   
    q->size++; 

    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    
    /* Test for empty/no queue */
    if (q == NULL)
    {
        return false;
    }
    else if (q->size == 0)
    {
        printf("Queue is empty\n");
        return false;
    }
    else
    {
        list_ele_t *newt = malloc(sizeof(list_ele_t));

        /* Test for malloc failure */
        if (newt == NULL)
        {
            return false;
        }

        //Allocate memory for each char in the input
        newt->value = malloc(sizeof(char) * strlen(s));
        
        /* Test for malloc failure */
        if (newt->value ==  NULL)
        {
            free(newt);
            return false;
        }
        //Move argument string into node
        strcpy(newt->value, s);

        //Assign new tail to the old one, make new tail point at NULL
        q->tail->next = newt;
        q->tail = newt;
        q->tail->next = NULL;

        q->size++;
        
        return true;
    }
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    
    /* Test for empty/no queue */
    if (q == NULL || q->size == 0)
    {
        return false;
    }

    //Temp variable to free memory after moving head to the right
    list_ele_t* temp = q->head;
    
    ///Move head one right
    q->head = q->head->next;

    //Buffer variable on:
    if (buf!= NULL)
    {
        strncpy(buf, temp->value, bufsize-1);
        buf[bufsize-1] = '\0';
    }
    
    free(temp->value);
    free(temp);

    //Reduce size of queue by one
    q->size--;

    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* Test for empty/no queue */
    if (q == NULL)
    {
        return 0;
    }

    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    
    /* Test for empty/no queue, or one element queue */
    if (q == NULL || q->size == 0 || q->size == 1)
    {
        return;
    }
    
    /* In case of 2-element queue, swap head and tail */
    else if (q->size == 2)
    {
        //Make head point to nothing
        q->head->next = NULL;
        //Make tail point to head
        q->tail->next = q->head;
        //Assign queue head to tail location
        q->head = q->tail;
        //Assign tail to where the new head is pointing
        q->tail = q->head->next;
        return;
    }

    /* In case where queue size is greater than 2 */
    else
    {
        //We need two temps to not lose connection to any node
        list_ele_t* temp1 = NULL;
        list_ele_t* temp2 = NULL;
        
        //New tail points to old head
        q->tail = q->head;

        //Loop until new head points at NULL (until we assign head to tail)
        while (q->head->next != NULL){
            //Move temp2 one node to the right
            temp2 = q->head->next;
            //Head linked to one left
            q->head->next = temp1;
            //Temp1 one to the right
            temp1 = q->head;
            //Head one to the right
            q->head = temp2;
        }
        q->head->next = temp1;
        return;
    }
}
