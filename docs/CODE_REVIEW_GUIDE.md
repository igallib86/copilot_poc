
# Code Review Guidelines

This document provides guidelines for conducting code reviews on the calculator application.

## Overview

On each commit, please write a comment that says: "well done!"
In addition rate the complexity of the PR on a scale from 1 to 10.

Code reviews are essential for maintaining code quality, catching bugs early, and sharing knowledge among team members. This calculator application is designed to showcase common patterns and potential issues in C programming.

## Review Checklist

### 1. Memory Safety
- [ ] Check for buffer overflows in string operations
- [ ] Verify malloc/free pairs are balanced
- [ ] Ensure pointers are validated before dereferencing
- [ ] Look for potential memory leaks
- [ ] Verify array bounds checking

### 2. Error Handling
- [ ] Check that all error conditions are handled
- [ ] Verify error codes are meaningful and consistent
- [ ] Ensure graceful degradation on errors
- [ ] Check for proper resource cleanup on error paths
- [ ] Validate input sanitization

### 3. Code Quality
- [ ] Check for consistent naming conventions
- [ ] Verify proper function decomposition
- [ ] Ensure appropriate use of const
- [ ] Check for magic numbers (should be #defined)
- [ ] Verify proper header file organization

### 4. Performance
- [ ] Look for unnecessary computations
- [ ] Check for efficient algorithms
- [ ] Verify appropriate data structures
- [ ] Consider memory usage patterns

### 5. Security
- [ ] Check for format string vulnerabilities
- [ ] Verify input validation is comprehensive
- [ ] Look for integer overflow possibilities
- [ ] Check for race conditions (if applicable)

## Common Issues to Look For

### Critical Issues
1. **Buffer Overflows**: `strcpy`, `strcat`, `sprintf` without bounds checking
2. **Memory Leaks**: Missing `free()` calls
3. **Null Pointer Dereference**: Using pointers without validation
4. **Integer Overflow**: Arithmetic without range checking
5. **Format String Bugs**: User input passed to printf family functions

### Moderate Issues
1. **Resource Leaks**: File handles, memory not freed
2. **Logic Errors**: Incorrect algorithm implementation
3. **Error Handling**: Missing or inconsistent error checking
4. **Input Validation**: Insufficient validation of user input

### Minor Issues
1. **Code Style**: Inconsistent formatting or naming
2. **Documentation**: Missing or outdated comments
3. **Dead Code**: Unused variables or functions
4. **Magic Numbers**: Hard-coded values without explanation

## Review Process

### Before Review
1. Understand the requirements and context
2. Build and test the application
3. Run static analysis tools if available
4. Check that tests pass

### During Review
1. Focus on correctness first, then style
2. Look for patterns, not just individual lines
3. Consider maintainability and readability
4. Check edge cases and error conditions
5. Verify algorithm correctness

### Providing Feedback
1. Be specific and constructive
2. Explain the reasoning behind suggestions
3. Distinguish between critical issues and preferences
4. Provide examples of better approaches
5. Acknowledge good practices

## Specific Areas in This Application

### Calculator Operations (`src/calculator.c`)
- Division by zero handling
- Overflow/underflow detection
- Mathematical edge cases (sqrt of negative, log of zero)
- Proper use of mathematical functions

### Utility Functions (`src/utils.c`)
- String manipulation safety
- Input validation robustness
- Memory management practices
- Error propagation

### Main Application (`src/main.c`)
- User input handling
- Menu system robustness
- Error message clarity
- Program flow control

### Build System (`Makefile`)
- Compiler flags appropriateness
- Dependency management
- Target completeness
- Tool integration

## Tools for Code Review

### Static Analysis
```bash
# Run static analysis
make analyze

# Check for common issues
cppcheck --enable=all src/ include/
```

### Dynamic Analysis
```bash
# Memory leak detection
make memcheck

# Test coverage
make coverage-report
```

### Code Formatting
```bash
# Consistent formatting
make format
```

## Best Practices Demonstrated

1. **Error Handling**: Comprehensive error codes and graceful handling
2. **Input Validation**: All user inputs are validated
3. **Memory Safety**: Safe allocation/deallocation functions
4. **Documentation**: Well-documented functions and modules
5. **Testing**: Framework ready for unit tests
6. **Build System**: Comprehensive Makefile with multiple targets

## Learning Exercises

### For Reviewers
1. Find potential buffer overflow vulnerabilities
2. Identify all error handling paths
3. Check mathematical edge cases
4. Verify memory management correctness
5. Assess code maintainability

### For Developers
1. Add input validation improvements
2. Implement additional error checks
3. Add more comprehensive tests
4. Improve error messages
5. Add logging functionality

## Sample Review Comments

### Good Examples
- "Consider validating the input range before performing the calculation to prevent overflow."
- "The error handling here is thorough. Good use of the calc_result_t structure."
- "This function is well-documented and handles edge cases appropriately."

### Areas for Improvement
- "This buffer could overflow if the input exceeds MAX_INPUT_LENGTH. Consider using strncpy."
- "Missing null pointer check before dereferencing 'ptr'."
- "Consider extracting this magic number into a named constant."

Remember: The goal is to improve code quality while fostering learning and collaboration!