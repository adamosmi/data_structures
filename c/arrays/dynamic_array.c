#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* initialize_dynamic_array(int initial_capacity) {
    DynamicArray* dynamic_array = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamic_array->array = (int*)malloc(sizeof(int) * initial_capacity);
    dynamic_array->size = 0;
    dynamic_array->capacity = initial_capacity;
    return dynamic_array;
}

void add_element(DynamicArray* dynamic_array, int element) {
    if(dynamic_array->size == dynamic_array->capacity) {
        dynamic_array->capacity *= 2;
        dynamic_array->array = (int*)realloc(dynamic_array->array, sizeof(int) * dynamic_array->capacity);
    }
    dynamic_array->array[dynamic_array->size] = element;
    dynamic_array->size++;
}

int* get_element(DynamicArray* dynamic_array, int index) {
    if(index < 0 || index > dynamic_array->size-1) {
        printf("GET ERROR: Out of bounds index for array of capacity %d, index=%d\n", dynamic_array->capacity, index);
        return NULL;
    }
    return &dynamic_array->array[index];
}

void set_element(DynamicArray* dynamic_array, int index, int element) {
    if(index < 0 || index > dynamic_array->size-1) {
        printf("SET ERROR: Out of bounds index for array of capacity %d, index=%d\n", dynamic_array->capacity, index);
        return;
    }
    dynamic_array->array[index] = element;
}

int remove_element(DynamicArray* dynamic_array, int index) {
    if(index < 0 || index > dynamic_array->size-1) {
        printf("GET ERROR: Out of bounds index for array of capacity %d, index=%d\n", dynamic_array->capacity, index);
        return -1;
    }
    int removed_value = dynamic_array->array[index];
    for (int i=index; i<dynamic_array->size-1; i++) {
        dynamic_array->array[i] = dynamic_array->array[i+1];
    }
    if (dynamic_array->size <= dynamic_array->capacity / 2) {
        dynamic_array->capacity = dynamic_array->capacity / 2;
        dynamic_array->array = (int*)realloc(dynamic_array->array, sizeof(int) * dynamic_array->capacity);
    }
    dynamic_array->size--;
    return removed_value;
}

void free_array(DynamicArray* dynamic_array) {
    free(dynamic_array->array);
    free(dynamic_array);
}

int main() {

    // resize array starting at intitial capacity 1
    int array_size = 1000;

    DynamicArray* dynamic_array = initialize_dynamic_array(1);

    for (int i=0; i<array_size; i++) {
        add_element(dynamic_array, i * 2);
        printf("Element added to array: %d (check: %d)\n", dynamic_array->array[dynamic_array->size - 1], i);
        printf("DynamicArray size: %d\n", dynamic_array->size);
        printf("DynamicArray capacity: %d\n", dynamic_array->capacity);
    }

    // get elements at in bounds index
    int index = 10;
    int* el = get_element(dynamic_array, index);
    if (el != NULL) {
        printf("Getting the element at index %d: %d\n", index, *el);
    }

    // get elements at out of bounds index
    index = dynamic_array->capacity * 2;
    el = get_element(dynamic_array, index);
    if (el != NULL) {
        printf("Getting the element at index %d: %d\n", index, *el);
    }

    // set element at in bound index
    index = 1;
    int int_el = 123;
    set_element(dynamic_array, index, int_el);
    el = get_element(dynamic_array, index);
    if (el != NULL) {
        printf("Element at index %d set to %d (check: %d)\n", index, *el, int_el);
    }

    // set element at out of  bounds index
    index = dynamic_array->capacity * 3;
    int_el = 456;
    set_element(dynamic_array, index, int_el);

    // remove all elements from the array
    int removed_value;
    for (int i=dynamic_array->size-1; i>=0; i--) {
        printf("i: %d\n", i);
        removed_value = remove_element(dynamic_array, i);
        printf("Element removed from array: %d (index: %d)\n", removed_value, i);
        printf("DynamicArray size: %d\n", dynamic_array->size);
        printf("DynamicArray capacity: %d\n\n", dynamic_array->capacity);

        printf("Should fail on realloc: %d\n\n", dynamic_array->array[dynamic_array->capacity + 100]);
    }


    // clean memory
    free_array(dynamic_array);

    return 0;
}
