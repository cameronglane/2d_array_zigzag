#include "cantor.h"

int main() {
  bool** array = NULL;
  struct State state = { 0,
                         0,
                         side_length,
                         false
                       };

  init_array(&array, side_length);
  print_array((const bool**)array, side_length);
  printf("\n");

  while (state.x < side_length && state.y < side_length) {
    array[state.x][state.y] = true;

    if (state.ascending) {
        if (state.y == 0 || state.x == side_length - 1) {
             state.ascending = false; // Change direction to move down/left
             if (state.x == side_length - 1) {
                 state.y++; // Move down if at the right edge
             } else {
                 state.x++; // Move right if not at the right edge
             }
         } else {
             state.x++; // Move diagonally up/right
             state.y--;
         }
     } else {
         if (state.x == 0 || state.y == side_length - 1) {
             state.ascending = true; // Change direction to move up/right
             if (state.y == side_length - 1) {
                 state.x++; // Move right if at the bottom edge
             } else {
                 state.y++; // Move down if not at the bottom edge
             }
         } else {
             state.x--; // Move diagonally down/left
             state.y++;
         }
     }
  }

  check_array((const bool**)array, side_length);
  print_array((const bool**)array, side_length);

  free_array(array, side_length);

  exit(EXIT_SUCCESS);
}

void init_array(bool*** array, size_t length){
    // Check if the array is already allocated
    if (*array != NULL) {
        fprintf(stderr, "Fatal error: array is not NULL.\n");
        exit(EXIT_FAILURE); // Exit if the array is already allocated
    }

    // Allocate memory for the array of row pointers
    *array = (bool**)malloc(length * sizeof(bool*));
    if (*array == NULL) {
        fprintf(stderr, "Failed to allocate memory for array\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row
    for (size_t i = 0; i < length; i++) {
        (*array)[i] = (bool*)malloc(length * sizeof(bool));
        if ((*array)[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for array row\n");
            // Free previously allocated memory before exiting
            for (size_t j = 0; j < i; j++) {
                free((*array)[j]);
            }
            free(*array);
            exit(EXIT_FAILURE);
        }
        // Initialize each element of the row to false
        for (size_t j = 0; j < length; j++) {
            (*array)[i][j] = false;
        }
    }
    printf("Great succeed!\n");
}

void free_array(bool** array, size_t length) {
    // Free memory for each row
    for (size_t i = 0; i < length; i++) {
        free(array[i]);
    }
    // Free memory for the array of row pointers
    free(array);

    printf("All those moments were lost in time, like tears in rain.\n");
}

void check_array(const bool** array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length; j++) {
            if (array[i][j] == false) {
                fprintf(stderr, "Error: array[%zu][%zu] is false\n", i, j);
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Array is correct\n");
}

void print_array(const bool** array, size_t length) {
    // Print column indices as headers
    printf("   ");
    for (size_t j = 0; j < length; j++) {
        printf("%-2zu ", j);
    }
    printf("\n");

    // Print array elements with row indices as headers
    for (size_t i = 0; i < length; i++) {
        printf("%-2zu ", i); // Row index as header
        for (size_t j = 0; j < length; j++) {
            printf("%-2d ", array[i][j] ? 1 : 0); // Print array element
        }
        printf("\n");
    }
}