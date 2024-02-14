#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const size_t side_length = 5;

struct State {
    size_t x;
    size_t y;
    size_t array_length;
    bool ascending;
};

void init_array(bool*** array, size_t length); // Using an array of Bools isn't the most efficient. But just doing something with more ints is boring.
void free_array(bool** array, size_t length);
void check_array(const bool** array, size_t length);
void print_array(const bool** array, size_t length);