/**
 * @file utils.c
 * @brief Implementation of utility functions
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <errno.h>
#include <limits.h>
#include <math.h>
#include "../include/utils.h"

/**
 * @brief Trim whitespace from beginning and end of string
 * @param str String to trim (modified in place)
 * @return Pointer to trimmed string
 */
char* trim_whitespace(char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    // Trim leading whitespace
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    if (*str == '\0') {
        return str; // String is all whitespace
    }
    
    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    
    *(end + 1) = '\0';
    return str;
}

/**
 * @brief Check if string is empty or contains only whitespace
 * @param str String to check
 * @return true if empty, false otherwise
 */
bool is_empty_string(const char* str) {
    if (str == NULL) {
        return true;
    }
    
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

/**
 * @brief Convert string to integer with error checking
 * @param str String to convert
 * @param result Pointer to store result
 * @return 0 on success, -1 on error
 */
int string_to_int(const char* str, int* result) {
    if (str == NULL || result == NULL || is_empty_string(str)) {
        return -1;
    }
    
    char* endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    // Check for conversion errors
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }
    
    // Check for integer overflow
    if (val > INT_MAX || val < INT_MIN) {
        return -1;
    }
    
    *result = (int)val;
    return 0;
}

/**
 * @brief Convert string to double with error checking
 * @param str String to convert
 * @param result Pointer to store result
 * @return 0 on success, -1 on error
 */
int string_to_double(const char* str, double* result) {
    if (str == NULL || result == NULL || is_empty_string(str)) {
        return -1;
    }
    
    char* endptr;
    errno = 0;
    double val = strtod(str, &endptr);
    
    // Check for conversion errors
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }
    
    *result = val;
    return 0;
}

/**
 * @brief Clear input buffer to handle extra characters
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Consume characters until newline or EOF
    }
}

/**
 * @brief Get user input with bounds checking
 * @param buffer Buffer to store input
 * @param size Size of buffer
 * @return Number of characters read (excluding null terminator)
 */
int get_user_input(char* buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return -1;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }
    
    // Remove trailing newline if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    return (int)len;
}

/**
 * @brief Print a separator line
 */
void print_separator(void) {
    printf("================================================\n");
}

/**
 * @brief Print a formatted header
 * @param title Header title
 */
void print_header(const char* title) {
    if (title == NULL) {
        return;
    }
    
    size_t title_len = strlen(title);
    size_t total_width = 48;
    
    if (title_len >= total_width - 4) {
        printf("| %s |\n", title);
        return;
    }
    
    size_t padding = (total_width - title_len - 2) / 2;
    printf("|");
    for (size_t i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (size_t i = 0; i < total_width - title_len - padding - 2; i++) {
        printf(" ");
    }
    printf("|\n");
}

/**
 * @brief Safe malloc with error checking
 * @param size Size to allocate
 * @return Pointer to allocated memory, or NULL on failure
 */
void* safe_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for %zu bytes\n", size);
    }
    
    return ptr;
}

/**
 * @brief Safe realloc with error checking
 * @param ptr Existing pointer
 * @param size New size
 * @return Pointer to reallocated memory, or NULL on failure
 */
void* safe_realloc(void* ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "Error: Memory reallocation failed for %zu bytes\n", size);
        // Original pointer is still valid
    }
    
    return new_ptr;
}

/**
 * @brief Safe free that sets pointer to NULL
 * @param ptr Pointer to pointer to free
 */
void safe_free(void** ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

/**
 * @brief Validate that value is within specified range
 * @param value Value to check
 * @param min Minimum allowed value
 * @param max Maximum allowed value
 * @return true if within range, false otherwise
 */
bool validate_input_range(double value, double min, double max) {
    return value >= min && value <= max;
}

/**
 * @brief Check if a double value represents an integer
 * @param value Value to check
 * @return true if integer, false otherwise
 */
bool is_integer(double value) {
    return value == floor(value);
}

/**
 * @brief Check if value is positive
 * @param value Value to check
 * @return true if positive, false otherwise
 */
bool is_positive(double value) {
    return value > 0.0;
}