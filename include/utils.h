#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Utility functions for the calculator application
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// String utilities
char* trim_whitespace(char* str);
bool is_empty_string(const char* str);
int string_to_int(const char* str, int* result);
int string_to_double(const char* str, double* result);

// Input/Output utilities
void clear_input_buffer(void);
int get_user_input(char* buffer, size_t size);
void print_separator(void);
void print_header(const char* title);

// Memory utilities
void* safe_malloc(size_t size);
void* safe_realloc(void* ptr, size_t size);
void safe_free(void** ptr);

// Validation utilities
bool validate_input_range(double value, double min, double max);
bool is_integer(double value);
bool is_positive(double value);

// Debug utilities
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

#endif /* UTILS_H */