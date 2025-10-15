/**
 * @file main.c
 * @brief Main entry point for the calculator application
 * @author Code Review Demo
 * @date 2025-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/calculator.h"
#include "../include/utils.h"

// Menu options
typedef enum {
    MENU_BASIC_CALC = 1,
    MENU_ADVANCED_CALC,
    MENU_CONSTANTS,
    MENU_HELP,
    MENU_EXIT = 0
} menu_option_t;

// Function prototypes
void show_main_menu(void);
void handle_basic_calculator(void);
void handle_advanced_calculator(void);
void show_constants(void);
void show_help(void);
int get_menu_choice(void);

/**
 * @brief Main function - entry point of the application
 * @return Exit status
 */
int main(void) {
    int choice;
    bool running = true;
    
    printf("=== Calculator Application - Code Review Demo ===\n");
    printf("Version 1.0.0\n");
    printf("Compiled: %s %s\n\n", __DATE__, __TIME__);
    
    while (running) {
        show_main_menu();
        choice = get_menu_choice();
        
        switch (choice) {
            case MENU_BASIC_CALC:
                handle_basic_calculator();
                break;
            case MENU_ADVANCED_CALC:
                handle_advanced_calculator();
                break;
            case MENU_CONSTANTS:
                show_constants();
                break;
            case MENU_HELP:
                show_help();
                break;
            case MENU_EXIT:
                printf("Thank you for using the calculator!\n");
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        
        if (running) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
        }
    }
    
    return EXIT_SUCCESS;
}

/**
 * @brief Display the main menu
 */
void show_main_menu(void) {
    print_separator();
    print_header("MAIN MENU");
    printf("1. Basic Calculator\n");
    printf("2. Advanced Calculator\n");
    printf("3. Show Constants\n");
    printf("4. Help\n");
    printf("0. Exit\n");
    print_separator();
}

/**
 * @brief Get menu choice from user
 * @return User's menu choice
 */
int get_menu_choice(void) {
    char input[MAX_INPUT_LENGTH];
    int choice;
    
    printf("Enter your choice: ");
    fflush(stdout);
    if (get_user_input(input, sizeof(input)) > 0) {
        if (string_to_int(trim_whitespace(input), &choice) == 0) {
            return choice;
        }
    }
    return -1; // Invalid input
}

/**
 * @brief Handle basic calculator operations
 */
void handle_basic_calculator(void) {
    char input[MAX_INPUT_LENGTH];
    double num1, num2;
    char operator;
    calc_result_t result;
    
    print_header("BASIC CALCULATOR");
    
    // Get first number
    printf("Enter first number: ");
    if (get_user_input(input, sizeof(input)) <= 0 || 
        string_to_double(trim_whitespace(input), &num1) != 0) {
        printf("Error: Invalid first number\n");
        return;
    }
    
    // Get operator
    printf("Enter operator (+, -, *, /, ^, %%): ");
    if (get_user_input(input, sizeof(input)) <= 0) {
        printf("Error: Invalid operator\n");
        return;
    }
    operator = trim_whitespace(input)[0];
    
    // Get second number
    printf("Enter second number: ");
    if (get_user_input(input, sizeof(input)) <= 0 || 
        string_to_double(trim_whitespace(input), &num2) != 0) {
        printf("Error: Invalid second number\n");
        return;
    }
    
    // Perform calculation
    result = evaluate_expression(num1, num2, (operation_t)operator);
    
    printf("\nResult: %.2f %c %.2f = ", num1, operator, num2);
    print_result(result);
}

/**
 * @brief Handle advanced calculator operations
 */
void handle_advanced_calculator(void) {
    char input[MAX_INPUT_LENGTH];
    double number;
    int choice;
    
    print_header("ADVANCED CALCULATOR");
    printf("1. Square Root\n");
    printf("2. Factorial\n");
    printf("3. Sine\n");
    printf("4. Cosine\n");
    printf("5. Tangent\n");
    printf("6. Natural Logarithm\n");
    printf("Enter choice (1-6): ");
    
    if (get_user_input(input, sizeof(input)) <= 0 || 
        string_to_int(trim_whitespace(input), &choice) != 0) {
        printf("Error: Invalid choice\n");
        return;
    }
    
    printf("Enter number: ");
    if (get_user_input(input, sizeof(input)) <= 0 || 
        string_to_double(trim_whitespace(input), &number) != 0) {
        printf("Error: Invalid number\n");
        return;
    }
    
    printf("\nResult: ");
    switch (choice) {
        case 1:
            if (number < 0) {
                printf("Error: Cannot calculate square root of negative number\n");
            } else {
                printf("sqrt(%.2f) = %.6f\n", number, square_root(number));
            }
            break;
        case 2:
            if (!is_integer(number) || number < 0 || number > 20) {
                printf("Error: Factorial requires non-negative integer <= 20\n");
            } else {
                printf("factorial(%.0f) = %.0f\n", number, factorial((int)number));
            }
            break;
        case 3:
            printf("sin(%.2f) = %.6f\n", number, sine(number));
            break;
        case 4:
            printf("cos(%.2f) = %.6f\n", number, cosine(number));
            break;
        case 5:
            printf("tan(%.2f) = %.6f\n", number, tangent(number));
            break;
        case 6:
            if (number <= 0) {
                printf("Error: Logarithm requires positive number\n");
            } else {
                printf("ln(%.2f) = %.6f\n", number, logarithm(number));
            }
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

/**
 * @brief Show mathematical constants
 */
void show_constants(void) {
    print_header("MATHEMATICAL CONSTANTS");
    printf("PI (π)  = %.15f\n", PI);
    printf("E       = %.15f\n", E);
    printf("\nUseful for trigonometric and logarithmic calculations.\n");
}

/**
 * @brief Show help information
 */
void show_help(void) {
    print_header("HELP");
    printf("This calculator supports:\n\n");
    printf("Basic Operations:\n");
    printf("  + : Addition\n");
    printf("  - : Subtraction\n");
    printf("  * : Multiplication\n");
    printf("  / : Division\n");
    printf("  ^ : Power (exponentiation)\n");
    printf("  %% : Modulo (remainder)\n\n");
    printf("Advanced Operations:\n");
    printf("  Square Root, Factorial\n");
    printf("  Trigonometric: sin, cos, tan\n");
    printf("  Natural Logarithm\n\n");
    printf("Notes:\n");
    printf("  - Angles for trig functions are in radians\n");
    printf("  - Factorial is limited to integers 0-20\n");
    printf("  - Division by zero is handled gracefully\n");
}