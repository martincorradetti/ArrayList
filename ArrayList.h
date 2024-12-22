/**
 * @file ArrayList.h
 * @brief A generic dynamic array implementation in C.
 *
 * This file provides the declaration of the ArrayList structure and
 * its associated operations, such as adding, removing, resizing, and
 * finding elements.
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

/**
 * @struct ArrayList
 * @brief Represents a generic dynamic array.
 *
 * This structure holds the dynamic array, its size, and its capacity.
 */
typedef struct ArrayList {
    void **arr;     /**< Pointer to the array of elements. */
    size_t n;       /**< Number of elements in the array. */
    size_t length;  /**< Total capacity of the array. */
} ArrayList;

/**
 * @brief Initializes an ArrayList.
 *
 * Allocates memory for an ArrayList and initializes its fields.
 *
 * @param length Initial capacity of the ArrayList.
 * @return Pointer to the initialized ArrayList.
 */
ArrayList* init(const size_t length);

/**
 * @brief Frees the memory used by an ArrayList.
 *
 * Frees both the dynamic array and the ArrayList structure itself.
 *
 * @param list Pointer to the ArrayList.
 */
void freeArrayList(ArrayList *list);

/**
 * @brief Adds an element to the end of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to add.
 */
void push_back(ArrayList *list, const void *element);

/**
 * @brief Removes the last element of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 */
void pop_back(ArrayList *list);

/**
 * @brief Shrinks the ArrayList to the number of existing elements.
 *
 * Optimizes memory usage by reducing capacity to match the size.
 *
 * @param list Pointer to the ArrayList.
 */
void shrink_to_fit(ArrayList *list);

/**
 * @brief Returns the total capacity of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @return Total capacity of the ArrayList.
 */
size_t get_length(const ArrayList *list);

/**
 * @brief Returns the number of elements in the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @return Number of elements currently in the ArrayList.
 */
size_t get_number_of_elements(const ArrayList *list);

/**
 * @brief Resizes the ArrayList to a new capacity.
 *
 * Increases the total capacity of the array. The new capacity must be
 * greater than or equal to the current number of elements.
 *
 * @param list Pointer to the ArrayList.
 * @param size New capacity for the ArrayList.
 */
void resize(ArrayList *list, const size_t size);

/**
 * @brief Inserts an element at a specific index in the ArrayList.
 *
 * Shifts existing elements to the right to make space.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to insert.
 * @param index Position at which to insert the element.
 */
void insert_at(ArrayList *list, const void *element, const size_t index);

/**
 * @brief Removes an element at a specific index in the ArrayList.
 *
 * Reorders the elements to fill the gap left by the removed element.
 *
 * @param list Pointer to the ArrayList.
 * @param index Index of the element to remove.
 */
void remove_at(ArrayList *list, const size_t index);

/**
 * @brief Finds an element in the ArrayList using a comparator function.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to find.
 * @param cmp Comparator function to compare elements.
 * @return Index of the element if found, -1 otherwise.
 */
ssize_t find(const ArrayList *list, const void *element, int (*cmp)(const void *, const void *));

#endif // ARRAYLIST_H