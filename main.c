#include "ArrayList.h"
#include <stdio.h>

int main() {
    ArrayList *list = init(5);
    int a = 10, b = 20, c = 30;

    push_back(list, &a);
    push_back(list, &b);
    push_back(list, &c);

    printf("Number of elements: %zu\n", get_number_of_elements(list));
    printf("First element: %d\n", *(int *)list->arr[0]);

    freeArrayList(list);
    return 0;
}