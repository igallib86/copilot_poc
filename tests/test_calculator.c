/**
 * @file test_calculator.c
 * @brief Unit tests for calculator operations
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "../include/calculator.h"
#include "../include/utils.h"

// Simple test framework macros
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 0; \
        } else { \
            printf("PASS: %s\n", message); \
        } \
    } while(0)

#define EPSILON 1e-9
#define DOUBLE_EQUALS(a, b) (fabs((a) - (b)) < EPSILON)

// Test function prototypes
int test_basic_arithmetic(void);
int test_division_operations(void);
int test_power_operations(void);
int test_advanced_operations(void);
int test_error_handling(void);
int test_utility_functions(void);
int run_all_tests(void);

/**
 * @brief Test basic arithmetic operations
 * @return 1 on success, 0 on failure
 */
int test_basic_arithmetic(void) {
    printf("\n=== Testing Basic Arithmetic ===\n");
    
    // Test addition
    TEST_ASSERT(DOUBLE_EQUALS(add(2.5, 3.5), 6.0), "Addition: 2.5 + 3.5 = 6.0");
    TEST_ASSERT(DOUBLE_EQUALS(add(-5, 3), -2.0), "Addition with negative: -5 + 3 = -2");
    TEST_ASSERT(DOUBLE_EQUALS(add(0, 0), 0.0), "Addition of zeros: 0 + 0 = 0");
    
    // Test subtraction
    TEST_ASSERT(DOUBLE_EQUALS(subtract(10, 4), 6.0), "Subtraction: 10 - 4 = 6");
    TEST_ASSERT(DOUBLE_EQUALS(subtract(-5, -3), -2.0), "Subtraction of negatives: -5 - (-3) = -2");
    TEST_ASSERT(DOUBLE_EQUALS(subtract(5, 5), 0.0), "Subtraction equal numbers: 5 - 5 = 0");
    
    // Test multiplication
    TEST_ASSERT(DOUBLE_EQUALS(multiply(3, 4), 12.0), "Multiplication: 3 * 4 = 12");
    TEST_ASSERT(DOUBLE_EQUALS(multiply(-2, 5), -10.0), "Multiplication with negative: -2 * 5 = -10");
    TEST_ASSERT(DOUBLE_EQUALS(multiply(0, 100), 0.0), "Multiplication by zero: 0 * 100 = 0");
    
    return 1;
}

/**
 * @brief Test division operations
 * @return 1 on success, 0 on failure
 */
int test_division_operations(void) {
    printf("\n=== Testing Division Operations ===\n");
    
    calc_result_t result;
    
    // Test normal division
    result = divide(10, 2);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, 5.0), 
                "Division: 10 / 2 = 5");
    
    result = divide(7, 3);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, 7.0/3.0), 
                "Division with remainder: 7 / 3 = 2.333...");
    
    // Test division by zero
    result = divide(5, 0);
    TEST_ASSERT(!result.is_valid && result.error == CALC_ERROR_DIVISION_BY_ZERO, 
                "Division by zero error handling");
    
    // Test negative division
    result = divide(-10, 2);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, -5.0), 
                "Negative division: -10 / 2 = -5");
    
    return 1;
}

/**
 * @brief Test power operations
 * @return 1 on success, 0 on failure
 */
int test_power_operations(void) {
    printf("\n=== Testing Power Operations ===\n");
    
    calc_result_t result;
    
    // Test normal power
    result = power(2, 3);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, 8.0), 
                "Power: 2^3 = 8");
    
    result = power(5, 0);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, 1.0), 
                "Power of zero: 5^0 = 1");
    
    result = power(0, 5);
    TEST_ASSERT(result.is_valid && DOUBLE_EQUALS(result.value, 0.0), 
                "Zero to power: 0^5 = 0");
    
    // Test error case: 0^(-1)
    result = power(0, -1);
    TEST_ASSERT(!result.is_valid && result.error == CALC_ERROR_DIVISION_BY_ZERO, 
                "Zero to negative power error");
    
    return 1;
}

/**
 * @brief Test advanced mathematical operations
 * @return 1 on success, 0 on failure
 */
int test_advanced_operations(void) {
    printf("\n=== Testing Advanced Operations ===\n");
    
    // Test square root
    TEST_ASSERT(DOUBLE_EQUALS(square_root(16), 4.0), "Square root: sqrt(16) = 4");
    TEST_ASSERT(DOUBLE_EQUALS(square_root(0), 0.0), "Square root of zero: sqrt(0) = 0");
    TEST_ASSERT(isnan(square_root(-1)), "Square root of negative returns NaN");
    
    // Test factorial
    TEST_ASSERT(DOUBLE_EQUALS(factorial(0), 1.0), "Factorial: 0! = 1");
    TEST_ASSERT(DOUBLE_EQUALS(factorial(5), 120.0), "Factorial: 5! = 120");
    TEST_ASSERT(isnan(factorial(-1)), "Factorial of negative returns NaN");
    
    // Test trigonometric functions (approximate checks)
    TEST_ASSERT(DOUBLE_EQUALS(sine(0), 0.0), "Sine: sin(0) = 0");
    TEST_ASSERT(DOUBLE_EQUALS(cosine(0), 1.0), "Cosine: cos(0) = 1");
    TEST_ASSERT(fabs(sine(PI/2) - 1.0) < EPSILON, "Sine: sin(π/2) ≈ 1");
    
    // Test logarithm
    TEST_ASSERT(DOUBLE_EQUALS(logarithm(1), 0.0), "Natural log: ln(1) = 0");
    TEST_ASSERT(fabs(logarithm(E) - 1.0) < EPSILON, "Natural log: ln(e) ≈ 1");
    TEST_ASSERT(isnan(logarithm(-1)), "Log of negative returns NaN");
    TEST_ASSERT(isnan(logarithm(0)), "Log of zero returns NaN");
    
    return 1;
}

/**
 * @brief Test error handling
 * @return 1 on success, 0 on failure
 */
int test_error_handling(void) {
    printf("\n=== Testing Error Handling ===\n");
    
    calc_result_t result;
    
    // Test invalid operation
    result = evaluate_expression(5, 3, '?');
    TEST_ASSERT(!result.is_valid && result.error == CALC_ERROR_INVALID_OPERATION, 
                "Invalid operation error");
    
    // Test modulo by zero
    result = modulo(10, 0);
    TEST_ASSERT(!result.is_valid && result.error == CALC_ERROR_DIVISION_BY_ZERO, 
                "Modulo by zero error");
    
    // Test error message retrieval
    const char* msg = get_error_message(CALC_ERROR_DIVISION_BY_ZERO);
    TEST_ASSERT(strcmp(msg, "Division by zero") == 0, 
                "Error message retrieval");
    
    return 1;
}

/**
 * @brief Test utility functions
 * @return 1 on success, 0 on failure
 */
int test_utility_functions(void) {
    printf("\n=== Testing Utility Functions ===\n");
    
    // Test string validation
    TEST_ASSERT(is_empty_string(""), "Empty string detection");
    TEST_ASSERT(is_empty_string("   "), "Whitespace-only string detection");
    TEST_ASSERT(!is_empty_string("test"), "Non-empty string detection");
    
    // Test number validation
    TEST_ASSERT(is_integer(5.0), "Integer detection: 5.0 is integer");
    TEST_ASSERT(!is_integer(5.5), "Non-integer detection: 5.5 is not integer");
    
    TEST_ASSERT(is_positive(5.0), "Positive number detection");
    TEST_ASSERT(!is_positive(-5.0), "Negative number detection");
    TEST_ASSERT(!is_positive(0.0), "Zero is not positive");
    
    // Test range validation
    TEST_ASSERT(validate_input_range(5.0, 0.0, 10.0), 
                "Range validation: 5 in range [0,10]");
    TEST_ASSERT(!validate_input_range(15.0, 0.0, 10.0), 
                "Range validation: 15 not in range [0,10]");
    
    // Test string conversion
    int int_result;
    TEST_ASSERT(string_to_int("123", &int_result) == 0 && int_result == 123, 
                "String to int conversion");
    TEST_ASSERT(string_to_int("abc", &int_result) != 0, 
                "Invalid string to int conversion");
    
    double double_result;
    TEST_ASSERT(string_to_double("123.45", &double_result) == 0 && 
                DOUBLE_EQUALS(double_result, 123.45), 
                "String to double conversion");
    
    return 1;
}

/**
 * @brief Run all test suites
 * @return Number of test suites passed
 */
int run_all_tests(void) {
    int passed = 0;
    int total = 6;
    
    printf("Calculator Test Suite\n");
    printf("=====================\n");
    
    if (test_basic_arithmetic()) passed++;
    if (test_division_operations()) passed++;
    if (test_power_operations()) passed++;
    if (test_advanced_operations()) passed++;
    if (test_error_handling()) passed++;
    if (test_utility_functions()) passed++;
    
    printf("\n=== Test Summary ===\n");
    printf("Passed: %d/%d test suites\n", passed, total);
    
    if (passed == total) {
        printf("All tests PASSED! ✓\n");
        return EXIT_SUCCESS;
    } else {
        printf("Some tests FAILED! ✗\n");
        return EXIT_FAILURE;
    }
}

/**
 * @brief Main test runner
 * @return Exit status
 */
int main(void) {
    return run_all_tests();
}