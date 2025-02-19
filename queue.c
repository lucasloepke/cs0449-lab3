/* >​< >‌‌‌<
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;
    
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    
    list_ele_t *current = q->head;
    while (current != NULL) {
        list_ele_t *temp = current;
        current = current->next;
        free(temp->value); // string
        free(temp); // list element
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL || s == NULL)
        return false;
    
    list_ele_t *new = malloc(sizeof(list_ele_t));
    if (new == NULL)
        return false;
    
    new->value = malloc(strlen(s) + 1);  // null terminator
    if (new->value == NULL) {
        free(new); // if fails, clean new
        return false;
    }
    strcpy(new->value, s);
    
    // link new node
    new->next = q->head;
    q->head = new;
    
    // if first element, set as tail
    if (new->next == NULL)
        q->tail = new;
        
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL || s == NULL)
        return false;
    
    list_ele_t *new = malloc(sizeof(list_ele_t));
    if (new == NULL)
        return false;
    
    new->value = malloc(strlen(s) + 1);  // null terminator
    if (new->value == NULL) {
        free(new); // if fails, clean new
        return false;
    }
    strcpy(new->value, s);
    
    new->next = NULL;
    
    // if empty, set head and tail to new
    if (q->head == NULL) {
        q->head = new;
        q->tail = new;
    } else {
        q->tail->next = new;
        q->tail = new;
    }
    
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;
    
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    
    // if empty, update tail
    if (q->head == NULL)
        q->tail = NULL;
    
    // if sp not null, copy string to buffer
    if (sp != NULL) {
        strncpy(sp, temp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';  // null termination check
    }
    
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;
    
    list_ele_t *prev = NULL;
    list_ele_t *current = q->head;
    list_ele_t *next = NULL;
    
    q->tail = q->head;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    q->head = prev;
}

