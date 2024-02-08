/**
 * @file queue.h
 * @brief Header file for implementing queue operations.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for ITU course Operating Systems and C.
 * A fork of the C programming lab developed at CMU for courses
 * 15-213/18-213/15-513 by R. E. Bryant, 2017 (extended w/ strings 2018)
 *
 * TODO: fill in your name and ITU alias
 * @author FIRSTNAME LASTNAME <ALIAS@itu.dk>
 */

#include <stdbool.h>
#include <stddef.h>

/************** Data structure declarations ****************/

/**
 * @brief Linked list element containing a string.
 *
 * You shouldn't change this struct.
 */
typedef struct list_ele {
    /**
     * @brief Pointer to a char array containing a string value.
     *
     * The memory for this string should be explicitly allocated and freed
     * whenever an element is inserted and removed from the queue.
     */
    char *value;

    /**
     * @brief Pointer to the next element in the linked list.
     */
    struct list_ele *next;
} list_ele_t;

/**
 * @brief Queue structure representing a list of elements
 */
typedef struct {
    /**
     * @brief Pointer to the first element in the queue, or NULL if the
     *        queue is empty.
     */
    list_ele_t *head;
    /*
     * TODO: You will need to add more fields to this structure
     *       to efficiently implement q_size and q_insert_tail
     */
} queue_t;

/************** Operations on queue ************************/

/* Create empty queue. */
queue_t *queue_new(void);

/* Free ALL storage used by queue. */
void queue_free(queue_t *q);

/* Attempt to insert element at head of queue. */
bool queue_insert_head(queue_t *q, const char *s);

/* Attempt to insert element at tail of queue. */
bool queue_insert_tail(queue_t *q, const char *s);

/* Attempt to remove element from head of queue. */
bool queue_remove_head(queue_t *q, char *sp, size_t bufsize);

/* Return number of elements in queue. */
size_t queue_size(queue_t *q);

/* Reverse elements in queue */
void queue_reverse(queue_t *q);
