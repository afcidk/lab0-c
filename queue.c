/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
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
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *tmp = NULL;

    while (q->head) {
        tmp = q->head;
        q->head = q->head->next;

        free(tmp->value);
        free(tmp);
    }

    /* Free queue structure */
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
    list_ele_t *newh;
    if (!q) {
        return false;
    }

    ++q->size;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    char *value = malloc((strlen(s) + 1) * sizeof(char));
    if (!value) {
        free(newh);
        return false;
    }
    memset(value, 0, strlen(s) + 1);
    strcpy(value, s);

    newh->value = value;
    newh->next = q->head;
    q->head = newh;

    if (q->size == 1)
        q->tail = newh;

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
    list_ele_t *newh;
    if (!q) {
        return false;
    }

    ++q->size;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    char *value = malloc((strlen(s) + 1) * sizeof(char));
    if (!value) {
        free(newh);
        return false;
    }
    memset(value, 0, strlen(s) + 1);
    strcpy(value, s);
    newh->value = value;


    if (q->size == 1) {
        q->tail = newh;
        q->head = newh;
    }

    q->tail->next = newh;
    q->tail = newh;
    q->tail->next = NULL;

    if (q->size == 1)
        q->head = newh;

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
    if (!q || !q->head)
        return false;

    if (bufsize != 0) {
        if (strlen(q->head->value) > bufsize) {
            strncpy(sp, q->head->value, bufsize);
            sp[bufsize - 1] = 0;
        } else {
            strcpy(sp, q->head->value);
        }
    }


    list_ele_t *tmp = q->head;

    /* You need to fix up this code. */
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    --q->size;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q || !q->head)
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
    if (!q || !q->head || !q->head->next)
        return;

    list_ele_t *prev = q->head;
    list_ele_t *cur = q->head->next;
    list_ele_t *nxt;
    q->tail = prev;

    while (cur->next != NULL) {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }

    cur->next = prev;
    q->head = cur;
    q->tail->next = NULL;
}
