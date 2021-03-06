/**
 * @file    linkedlist.h
 * @author  Jarryd Tilbrook
 * @date    24 May 2016
 * @brief   TODO add description
 */


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdlib.h>
/* Conditional includes for unit testing the library */
#ifdef UNIT_TESTING
    #include <stdarg.h>
    #include <stddef.h>
    #include <setjmp.h>
    #include <cmocka.h>
#endif

/* TRUE/FALSE values for C89 */
#ifndef FALSE
    #define FALSE 0
#endif
#ifndef TRUE
    #define TRUE !FALSE
#endif


/***** CONDITIONAL COMPILATION *****/
/* The macros below allow the user to modify the behaviour of the list as
 * compile time.
 * Uncomment as desired. */

/**
 * This enables the length of the list to be instantly accessible from the list
 * `struct`, as opposed to being calculated by traversing the list.
 */
/*#define INSTANT_LENGTH*/
/*#ifdef INSTANT_LENGTH
    #error "Instant length not yet supported"
#endif*/

/**
 * This enables a double ended linked list.
 */
/*#define DOUBLE_ENDED*/
/*#ifdef DOUBLE_ENDED
    #error "Double ended not yet supported"
#endif*/

/**
 * This enables a doubly linked linked list.
 */
/*#define DOUBLY_LINKED*/
/*#ifdef DOUBLY_LINKED
    #error "Doubly linked not yet supported"
#endif*/

/**
 * This enables logging information to be printed to `stderr`.
 */
/*#define LOG_ERRORS*/

/*#ifdef LOG_ERRORS*/
/**
 * If logging is enabled, this will enable a colourised output.
 */
/*#define COLOURISE_ERRORS*/
/* TODO add logging level macro. Or include a switch at run time when constructing the list */
/*#endif*/


/***** DATATYPE DEFINITIONS *****/
/* This section defines the datatypes used within the list, ranging from the
 * `struct`s to the function callback types. */

/**
 * A pointer to any kind of data suitable for storage in the linked list.
 */
typedef void* DataPointer;


/**
 * @brief A function pointer type that takes a pointer to the type stored in the
 * 		  list and frees the memory pointed to.
 *
 * The user can define a function of this type that is used to free non-standard
 * data when deleting an element or the entire list. eg: freeing the contents of
 * a dynamically allocated `struct`.
 */
/*typedef void (* FreeDataFunc)(LinkedListData);*/


/**
 * @brief A function pointer type that takes two values of the type stored in
 *        the list and compares them for equality.
 *
 * The user can define a function of this type that is used to compare two
 * elements from a list that cannot be used in a boolean expression directly.
 * The defined function should return 0 for equal comparison, < 0 if the first
 * argument is less than the second, and > 0 if the first is larger than the
 * second.
 */
/*typedef int (* DifferenceFunc)(LinkedListData, LinkedListData);*/


/**
 * @brief A function pointer type that takes a pointer to an item to store in
 *        the list, allocates memory for it, and copies the item across.
 *
 * The user may define a function of this type that will be used to allocate and
 * copy an item into the list. Helps to enforce better modularisation of code.
 * The function should return a pointer to the newly allocated memory, or `NULL`
 * on error.
 *
 * @deprecated
 */
/*typedef LinkedListData (* AllocFunc)(LinkedListData);*/


/**
 * @brief A function pointer type used to reduce a linked list to a single
 *        value.
 *
 * The user may define a function of this type that will be used to perform
 * a reduce operation on the linked list. The first argument is the current
 * item in the list being evaluated, and the second is the carry over from
 * previous invocations.
 */
typedef void *(* Reducer)(DataPointer, void *);


/**
 * A `struct` representing a node within a linked list.
 */
typedef struct ListNode {
    DataPointer data;
    struct ListNode *next;
} ListNode;


/**
 * A `struct` representing an array of the same data stored in a list.
 */
/*typedef struct ArrayList {
    DataPointer element;
    unsigned long length;
} ArrayList;*/


/**
 * A `struct` representing a single linked list.
 */
typedef struct LinkedList {
    ListNode *head;
} LinkedList;


/***** INSERTION & MODIFICATION FUNCTIONS *****/
/* The functions below provide methods of creating a new list and inserting
 * elements at specific positions. A converter function is also provided that
 * performs linked list to array conversion to decrease access times. */

/**
 * @brief Create a new empty linked list.
 *
 * Allocates and initilises a new linked list.
 *
 * @return A pointer to a new empty linked list or `NULL` on error.
 */
LinkedList* createList();


/**
 * @brief Convert a linked list into an array.
 *
 * Creates an array from the elements stored in @p list. This is a convenience
 * function provided to help reduce element access times. The ordering of @p
 * list remains consistent. The memory associated with @p list will be freed. If
 * an error occurs, the list is left unmodified and `NULL` is returned,
 * otherwise an `ArrayList` is returned containing a pointer to the contiguous
 * data and it's length.
 *
 * TODO: export in sorted order
 * TODO: this needs more thinking/designing... ie single 'chunk' of memory, how to allocate -> lists alloc func won't work, array of pointers to list elements?
 *
 * @param list The list to convert, containing the data to include in the
 *             array.
 * @return A pointer to a new `ArrayList` structure containing the elements and
 *         the length.
 */
/*ArrayList* list2Array(LinkedList *list);*/


/**
 * Perform a reduce operation on the list to produce a single value and return it.
 *
 * This function iterates over the list calling the provided callback passing each node in turn along with the value
 * returned from the previous invocations. The value of seed is passed on the first invocation.
 *
 * @param list A list to reduce to a single value.
 * @param callback A function called for each node in the list which takes a pointer to the current value of previous
 *                  reductions and the next node. This method should perform whatever is necessary to convert the
 *                  current node to a single value and add it to the current value.
 * @param seed An initial value to pass to the callback for the first invocation.
 * @return A pointer to the result of reducing the list.
 */
void *reduceList(LinkedList *list, Reducer callback, void *seed);


/**
 * @brief Insert an element at the top of a list.
 *
 * This expects @p value to be a valid pre-allocated pointer as no checks are
 * performed. This @p value is inserted at the head of the list.
 * TODO: return new head?
 *
 * @param list The list to add to.
 * @param data The data to copy into the list.
 * @return Positive integer for successful insertion, zero otherwise.
 */
int insertTop(LinkedList *list, DataPointer data);


/**
 * @brief Insert an element at the end of a list.
 *
 * Similar to insertTop(), but will add the element to the end of @p list.
 *
 * @param list The list to add to.
 * @param data The data to insert into the list.
 * @return Positive integer for successful insertion, zero otherwise.
 */
int insertTail(LinkedList *list, DataPointer data);


/**
 * @brief Insert a value into a list at a given index.
 *
 * This expects @p value to be a valid pre-allocated pointer as no checks are
 * performed. After excecution, @p value will be at @p index within the list.
 * Note that negative indexing is supported.
 *
 * @param list The list to add to.
 * @param value The data to insert into the list.
 * @param index The index to insert at (starting at 0).
 * @return Positive integer for successful insertion, zero otherwise. (eg.
 *         index out of bounds)
 */
/*int insertIndex(LinkedList *list, LinkedListData value, long index);*/


/**
 * @brief Insert a value in sorted order into the list.
 *
 * Using the defined difference function field in @p list, inserts @p value in
 * sorted order into the list. If the field is `NULL`, @p value will be inserted
 * at the top of the list and a negative integer returned.
 *
 * @param  list  The list to add to.
 * @param  value The data to insert into the list.
 * @return Positive integer for successful insertion, negative if no sort
 *         function was used, and zero otherwise.
 */
/*int insertSorted(LinkedList *list, LinkedListData value);*/


/**
 * @brief Sorts a list inplace using a difference function.
 *
 * Sorts @p list inplace using either the defined difference function field in
 * @p list, or another difference function passed in to @p compare. Use this
 * parameter to override the existing difference function.
 *
 * @param  list    The list to sort.
 * @param  diff The overriding compare function to use to determine ordering.
 */
/*void sortList(LinkedList *list, DifferenceFunc diff);*/


/***** REMOVAL & DELETION FUNCTIONS *****/
/* The functions below provide methods to remove elements from a list, or delete
 * an entire list itself. */

/**
* @brief Delete an entire list.
*
* Frees all the memory associated with @p list. This includes every node and
* each node's associated data.
*
* @param list The list to delete.
*/
void destroyList(LinkedList *list);


/**
 * @brief Delete an array converted from a list.
 *
 * Frees the contents of @p array. Delegates freeing to @p freeData to ensure
 * `structs` are properly deallocated. If @p freeData is `NULL` it is freed
 * internally.
 *
 * @param array The array to delete.
 * @param freeData The user defined callback to free the data stored in the
 *                 list.
 */
/*int destroyArray(ArrayList *array, FreeDataFunc freeData);*/


/**
 * @brief Delete the element at the top of a list.
 *
 * If it exists, the top element in @p list is removed. This function will also
 * call the standard implementation of `free()` on the data within the the node.
 *
 * @param list The list to remove from.
 */
void removeTop(LinkedList *list);


/**
 * @brief Delete the element at the end of a list.
 *
 * If it exists, the last element in @p list is removed. This function will also
 * call the standard implementation of `free()` on the data within the the node.
 *
 * @param list The list to remove from.
 */
void removeTail(LinkedList *list);


/**
 * @brief Delete the element at a given index within a list.
 *
 * If it exists, the element at @p index is removed from the list. Delegates to
 * the `free` field of @p list to ensure all contents of the node are freed. If
 * this field. Negative indexing is supported.
 *
 * @param list The list to remove from.
 * @param index The index to remove (starting from 0).
 * @return Positive integer for successful removal, zero otherwise.
 */
/*int removeIndex(LinkedList *list, long index);*/


/**
 * @brief Remove a node that matches a specified value.
 *
 * Use this to remove an element from @p list that matches @p value. This
 * delegates the comparison to @p diff, or if `NULL` defaults to the difference
 * function pointer stored in @p list. Use this to override the comparison (eg.
 * to loosen the constraints).
 *
 * @param  list    The list to remove from.
 * @param  element The compared element to find and remove.
 * @param  compare The overriding comparison function to use.
 * @return Positive integer for successful removal, zero otherwise.
 */
/*int removeElement(LinkedList *list, LinkedListData value,
        DifferenceFunc diff);*/


/***** FINDING & SEARCHING FUNCTIONS *****/
/* The functions below will not modify the linked list in any way. They are used
 * to obtain information about the list, eg; the length, whether a specific
 * element is present and retrieving a specific element. */

/**
 * @brief Calculate the length of a list.
 *
 * Calculates the length of @p list.
 * TODO: document list length limitation
 *
 * @param list The list to determine the length of.
 * @return The size of the supplied list.
 */
unsigned long listLength(LinkedList *list);


/**
 * @brief Find whether an element exists in the list.
 *
 * This function traverses @p list checking whether at least one element is
 * present that is equivalent to @p needle. This delegates the comparison to
 * @p diff or the difference function supplied in @p list if `NULL`. @p diff
 * therefore overrides it's counterpart in @p list. This is useful to loosen the
 * comparing constraints on the list elements compared to that used for
 * inserting. Returns a pointer to the first found element or `NULL` if one is
 * not found.
 *
 * @param list The list to search through.
 * @param needle The element to search for.
 * @param diff Overriding comparison function to use.
 * @return A pointer to the found element, or `NULL` if not found.
 */
/*LinkedListData findElement(LinkedList *list, LinkedListData needle,
        DifferenceFunc diff);*/


/**
 * @brief Retrieves, but does not remove, the element at the top of a list.
 *
 * This is a convenience function provided so the user does not need to know the
 * list implementation details.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the first element, or `NULL` if empty.
 */
DataPointer peekTop(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at the end of a list.
 *
 * This is a convenience function provided so the user does not need to know the
 * list implementation details.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the last element, or `NULL` if empty.
 */
DataPointer peekTail(LinkedList *list);


/**
 * @brief Retrieves, but does not remove, the element at a given index of a
 *        list.
 *
 * Negative indexing is supported.
 *
 * @param list The list to retrieve from.
 * @return A pointer to the element, or `NULL` if out of bounds.
 */
/*LinkedListData peekIndex(LinkedList *list, long index);*/


 #endif /* end of include guard: LINKEDLIST_H */
