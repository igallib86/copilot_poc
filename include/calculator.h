#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * @file calculator.h
 * @brief Header file for calculator operations
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constants
#define MAX_INPUT_LENGTH 256
#define PI 3.14159265359
#define E 2.71828182846

// Error codes
typedef enum {
    CALC_SUCCESS = 0,
    CALC_ERROR_DIVISION_BY_ZERO,
    CALC_ERROR_INVALID_INPUT,
    CALC_ERROR_OVERFLOW,
    CALC_ERROR_UNDERFLOW,
    CALC_ERROR_INVALID_OPERATION
} calc_error_t;

// Operation types
typedef enum {
    OP_ADD = '+',
    OP_SUBTRACT = '-',
    OP_MULTIPLY = '*',
    OP_DIVIDE = '/',
    OP_POWER = '^',
    OP_MODULO = '%'
} operation_t;

// Calculator result structure
typedef struct {
    double value;
    calc_error_t error;
    bool is_valid;
} calc_result_t;

// Basic arithmetic operations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
calc_result_t divide(double a, double b);
calc_result_t power(double base, double exponent);
calc_result_t modulo(double a, double b);

// Advanced operations
double square_root(double x);
double factorial(int n);
double sine(double x);
double cosine(double x);
double tangent(double x);
double logarithm(double x);

// Utility functions
calc_result_t evaluate_expression(double a, double b, operation_t op);
bool is_valid_number(const char* str);
void print_result(calc_result_t result);
const char* get_error_message(calc_error_t error);

#endif /* CALCULATOR_H */