/**
 * @file calculator.c
 * @brief Implementation of calculator operations
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <math.h>
#include <float.h>
#include "../include/calculator.h"
#include "../include/utils.h"

/**
 * @brief Add two numbers
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 */
double add(double a, double b) {
    return a + b;
}

/**
 * @brief Subtract two numbers
 * @param a First operand (minuend)
 * @param b Second operand (subtrahend)
 * @return Difference of a and b
 */
double subtract(double a, double b) {
    return a - b;
}

/**
 * @brief Multiply two numbers
 * @param a First operand
 * @param b Second operand
 * @return Product of a and b
 */
double multiply(double a, double b) {
    return a * b;
}

/**
 * @brief Divide two numbers with error handling
 * @param a Dividend
 * @param b Divisor
 * @return calc_result_t containing result or error
 */
calc_result_t divide(double a, double b) {
    calc_result_t result = {0.0, CALC_SUCCESS, false};
    
    if (b == 0.0) {
        result.error = CALC_ERROR_DIVISION_BY_ZERO;
        return result;
    }
    
    result.value = a / b;
    result.is_valid = true;
    
    // Check for overflow/underflow
    if (isinf(result.value)) {
        result.error = CALC_ERROR_OVERFLOW;
        result.is_valid = false;
    }
    
    return result;
}

/**
 * @brief Calculate power (base^exponent)
 * @param base Base number
 * @param exponent Exponent
 * @return calc_result_t containing result or error
 */
calc_result_t power(double base, double exponent) {
    calc_result_t result = {0.0, CALC_SUCCESS, false};
    
    // Handle special cases
    if (base == 0.0 && exponent < 0.0) {
        result.error = CALC_ERROR_DIVISION_BY_ZERO;
        return result;
    }
    
    if (base < 0.0 && !is_integer(exponent)) {
        result.error = CALC_ERROR_INVALID_INPUT;
        return result;
    }
    
    result.value = pow(base, exponent);
    result.is_valid = true;
    
    // Check for overflow/underflow
    if (isinf(result.value) || isnan(result.value)) {
        result.error = CALC_ERROR_OVERFLOW;
        result.is_valid = false;
    }
    
    return result;
}

/**
 * @brief Calculate modulo (remainder of division)
 * @param a Dividend
 * @param b Divisor
 * @return calc_result_t containing result or error
 */
calc_result_t modulo(double a, double b) {
    calc_result_t result = {0.0, CALC_SUCCESS, false};
    
    if (b == 0.0) {
        result.error = CALC_ERROR_DIVISION_BY_ZERO;
        return result;
    }
    
    result.value = fmod(a, b);
    result.is_valid = true;
    
    return result;
}

/**
 * @brief Calculate square root
 * @param x Input value
 * @return Square root of x
 */
double square_root(double x) {
    if (x < 0.0) {
        DEBUG_PRINT("Warning: square_root called with negative value: %f", x);
        return NAN;
    }
    return sqrt(x);
}

/**
 * @brief Calculate factorial (iterative implementation for better code review examples)
 * @param n Input integer
 * @return Factorial of n
 */
double factorial(int n) {
    if (n < 0) {
        DEBUG_PRINT("Warning: factorial called with negative value: %d", n);
        return NAN;
    }
    
    if (n > 20) {
        DEBUG_PRINT("Warning: factorial called with large value: %d", n);
        return INFINITY;
    }
    
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    
    return result;
}

/**
 * @brief Calculate sine
 * @param x Angle in radians
 * @return Sine of x
 */
double sine(double x) {
    return sin(x);
}

/**
 * @brief Calculate cosine
 * @param x Angle in radians
 * @return Cosine of x
 */
double cosine(double x) {
    return cos(x);
}

/**
 * @brief Calculate tangent
 * @param x Angle in radians
 * @return Tangent of x
 */
double tangent(double x) {
    return tan(x);
}

/**
 * @brief Calculate natural logarithm
 * @param x Input value
 * @return Natural logarithm of x
 */
double logarithm(double x) {
    if (x <= 0.0) {
        DEBUG_PRINT("Warning: logarithm called with non-positive value: %f", x);
        return NAN;
    }
    return log(x);

/**
 * @brief Calculate logarithm base 10
 * @param x Input value
 * @return Base-10 logarithm of x
 */
double log10_custom(double x) {
    if (x <= 0.0) {
        DEBUG_PRINT("Warning: log10 called with non-positive value: %f", x);
        return NAN;
    }
    return log10(x);
}

/**
 * @brief Calculate logarithm base 2
 * @param x Input value
 * @return Base-2 logarithm of x
 */
double log2_custom(double x) {
    if (x <= 0.0) {
        DEBUG_PRINT("Warning: log2 called with non-positive value: %f", x);
        return NAN;
    }
    return log2(x);
}

/**
 * @brief Calculate logarithm with custom base
 * @param x Input value
 * @param base Logarithm base
 * @return Logarithm of x with specified base
 */
double log_base(double x, double base) {
    if (x <= 0.0 || base <= 0.0 || base == 1.0) {
        DEBUG_PRINT("Warning: log_base called with invalid values: x=%f, base=%f", x, base);
        return NAN;
    }
    return log(x) / log(base);
}
}

/**
 * @brief Evaluate mathematical expression
 * @param a First operand
 * @param b Second operand
 * @param op Operation to perform
 * @return calc_result_t containing result or error
 */
calc_result_t evaluate_expression(double a, double b, operation_t op) {
    calc_result_t result = {0.0, CALC_SUCCESS, false};
    
    switch (op) {
        case OP_ADD:
            result.value = add(a, b);
            result.is_valid = true;
            break;
        case OP_SUBTRACT:
            result.value = subtract(a, b);
            result.is_valid = true;
            break;
        case OP_MULTIPLY:
            result.value = multiply(a, b);
            result.is_valid = true;
            break;
        case OP_DIVIDE:
            return divide(a, b);
        case OP_POWER:
            return power(a, b);
        case OP_MODULO:
            return modulo(a, b);
        default:
            result.error = CALC_ERROR_INVALID_OPERATION;
            break;
    }
    
    return result;
}

/**
 * @brief Print calculation result
 * @param result The calculation result to print
 */
void print_result(calc_result_t result) {
    if (result.is_valid) {
        printf("%.6f\n", result.value);
    } else {
        printf("Error: %s\n", get_error_message(result.error));
    }
}

/**
 * @brief Get error message string
 * @param error Error code
 * @return String description of the error
 */
const char* get_error_message(calc_error_t error) {
    switch (error) {
        case CALC_SUCCESS:
            return "Success";
        case CALC_ERROR_DIVISION_BY_ZERO:
            return "Division by zero";
        case CALC_ERROR_INVALID_INPUT:
            return "Invalid input";
        case CALC_ERROR_OVERFLOW:
            return "Numerical overflow/underflow";
        case CALC_ERROR_UNDERFLOW:
            return "Numerical underflow";
        case CALC_ERROR_INVALID_OPERATION:
            return "Invalid operation";
        default:
            return "Unknown error";
    }
}