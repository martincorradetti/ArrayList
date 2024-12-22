/**
 * @file ArrayList.c
 * @brief Implementation of the ArrayList functions.
 */

#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Macro for throwing an error and terminating the program.
 *
 * This macro prints an error message to `stderr` with the function name
 * where the error occurred, and then exits the program with a failure code.
 *
 * @param msg A string describing the error.
 *
 * @note This macro uses `fprintf` and `exit`, so it immediately terminates
 *       the program. Use with caution in critical or multi-threaded contexts.
 */
#define THROW_ERROR(msg) fprintf(stderr, "[ERROR] %s in function: %s\n", msg, __func__), exit(EXIT_FAILURE)

/**
 * @brief Initializes an ArrayList.
 *
 * Allocates memory for an ArrayList and initializes its fields.
 *
 * @param length Initial capacity of the ArrayList.
 * @return Pointer to the initialized ArrayList.
 */
ArrayList* init(const size_t length) {
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL) THROW_ERROR("out of memory");
    list->arr = calloc(length + 1, sizeof(void *)); // +1 for the nullptr terminator
    if (list->arr == NULL) {
        free(list);
        THROW_ERROR("out of memory");
    }
    list->n = 0;
    list->length = length;
    list->arr[list->n] = NULL; // Initial terminator
    return list;
}

/**
 * @brief Frees the memory used by an ArrayList.
 *
 * Frees both the dynamic array and the ArrayList structure itself.
 *
 * @param list Pointer to the ArrayList.
 */
void freeArrayList(ArrayList *list) {
    free(list->arr);
    free(list);
}

/**
 * @brief Adds an element to the end of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to add.
 */
void push_back(ArrayList *list, const void *element) {
    if (list->n == list->length) {
        resize(list, list->length * 2 + 1);
    }
    list->arr[list->n] = (void *)element;
    list->n++;
    list->arr[list->n] = NULL;
}

/**
 * @brief Removes the last element of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 */
void pop_back(ArrayList *list) {
    if (list->n == 0) {
        fprintf(stderr, "[ERROR] Empty list in function: %s\n", __func__);
        return;
    }
    list->n--;
    list->arr[list->n] = NULL;
}

/**
 * @brief Shrinks the ArrayList to the number of existing elements.
 *
 * Optimizes memory usage by reducing capacity to match the size.
 *
 * @param list Pointer to the ArrayList.
 */
void shrink_to_fit(ArrayList *list) {
    if (list->n == list->length) return; // Already optimal
    void **newArr = realloc(list->arr, (list->n + 1) * sizeof(void *));
    if (newArr == NULL) THROW_ERROR("out of memory");
    list->arr = newArr;
    list->length = list->n;
}

/**
 * @brief Returns the total capacity of the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @return Total capacity of the ArrayList.
 */
size_t get_length(const ArrayList *list) {
    return list->length;
}

/**
 * @brief Returns the number of elements in the ArrayList.
 *
 * @param list Pointer to the ArrayList.
 * @return Number of elements currently in the ArrayList.
 */
size_t get_number_of_elements(const ArrayList *list) {
    return list->n;
}

/**
 * @brief Resizes the ArrayList to a new capacity.
 *
 * Increases the total capacity of the array. The new capacity must be
 * greater than or equal to the current number of elements.
 *
 * @param list Pointer to the ArrayList.
 * @param size New capacity for the ArrayList.
 */
void resize(ArrayList *list, const size_t size) {
    if (size <= list->n) return;
    void **newArr = realloc(list->arr, (size + 1) * sizeof(void *)); // +1 for nullptr terminator
    if (newArr == NULL) THROW_ERROR("out of memory");
    list->arr = newArr;
    list->length = size;
}

/**
 * @brief Inserts an element at a specific index in the ArrayList.
 *
 * Shifts existing elements to the right to make space.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to insert.
 * @param index Position at which to insert the element.
 */
void insert_at(ArrayList *list, const void *element, const size_t index) {
    if (index > list->n) {
        THROW_ERROR("Index out of range");
    }
    if (list->n == list->length) {
        resize(list, list->length * 2 + 1);
    }
    memmove(&list->arr[index + 1], &list->arr[index], (list->n - index) * sizeof(void *));
    list->arr[index] = (void *)element;
    list->n++;
    list->arr[list->n] = NULL;
}

/**
 * @brief Removes an element at a specific index in the ArrayList.
 *
 * Reorders the elements to fill the gap left by the removed element.
 *
 * @param list Pointer to the ArrayList.
 * @param index Index of the element to remove.
 */
void remove_at(ArrayList *list, const size_t index) {
    if (index >= list->n) {
        THROW_ERROR("Index out of range");
    }
    for (size_t i = index; i < list->n - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }
    list->n--;
    list->arr[list->n] = NULL;
}

/**
 * @brief Finds an element in the ArrayList using a comparator function.
 *
 * @param list Pointer to the ArrayList.
 * @param element Pointer to the element to find.
 * @param cmp Comparator function to compare elements.
 * @return Index of the element if found, -1 otherwise.
 */
ssize_t find(const ArrayList *list, const void *element, int (*cmp)(const void *, const void *)) {
    for (size_t i = 0; i < list->n; i++) {
        if (cmp(list->arr[i], element) == 0) {
            return (ssize_t)i;
        }
    }
    return -1; // Element not found
}
