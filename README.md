# Calculator Application - Code Review Demo

A comprehensive C calculator application designed for code review practice and demonstration purposes. This project showcases best practices in C programming, project structure, and build systems.

## Features

### Basic Operations
- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`) with zero-division protection
- Power/Exponentiation (`^`)
- Modulo (`%`)

### Advanced Operations
- Square root
- Factorial (0-20)
- Trigonometric functions (sin, cos, tan)
- Natural logarithm

### Code Quality Features
- Comprehensive error handling
- Input validation
- Memory safety utilities
- Debug macros
- Static analysis support
- Test framework ready

## Project Structure

```
copilot-codereview-poc/
├── src/                    # Source files
│   ├── main.c             # Main application entry point
│   ├── calculator.c       # Calculator operations implementation
│   └── utils.c            # Utility functions
├── include/               # Header files
│   ├── calculator.h       # Calculator function declarations
│   └── utils.h            # Utility function declarations
├── tests/                 # Test files
├── docs/                  # Documentation
├── build/                 # Build artifacts (created during build)
├── Makefile              # Build configuration
└── README.md             # This file
```

## Building the Project

### Prerequisites
- GCC compiler with C99 support
- Make utility
- Math library (libm)

### Quick Start
```bash
# Clone or navigate to the project directory
cd copilot-codereview-poc

# Build release version
make

# Run the application
make run
```

### Build Options

```bash
# Release build (optimized)
make release

# Debug build (with debug symbols and DEBUG macro)
make debug

# Coverage build (for test coverage analysis)
make coverage

# Run debug version
make run-debug

# Build and run tests
make test

# Show all available targets
make help
```

## Usage Examples

### Basic Calculator Mode
```
Enter your choice: 1
Enter first number: 15
Enter operator (+, -, *, /, ^, %): +
Enter second number: 25
Result: 15.00 + 25.00 = 40.000000
```

### Advanced Calculator Mode
```
Enter your choice: 2
1. Square Root
2. Factorial
3. Sine
4. Cosine
5. Tangent
6. Natural Logarithm
Enter choice (1-6): 1
Enter number: 16
Result: sqrt(16.00) = 4.000000
```

## Development Tools

### Code Analysis
```bash
# Static analysis (requires cppcheck)
make analyze

# Memory leak detection (requires valgrind)
make memcheck

# Code formatting (requires clang-format)
make format
```

### Test Coverage
```bash
# Build with coverage instrumentation
make coverage

# Run tests and generate coverage data
make test

# Generate coverage report
make coverage-report
```

## Installation

### System Installation
```bash
# Install to /usr/local/bin (requires root privileges)
sudo make install

# Run from anywhere
calculator

# Uninstall
sudo make uninstall
```

## Code Review Focus Areas

This project is designed to demonstrate various aspects commonly reviewed in C code:

### 1. **Memory Management**
- Safe allocation/deallocation functions
- Pointer validation
- Buffer overflow prevention
- Memory leak prevention

### 2. **Error Handling**
- Comprehensive error codes
- Graceful error recovery
- Input validation
- Edge case handling

### 3. **Code Organization**
- Clear separation of concerns
- Modular design
- Proper header usage
- Consistent naming conventions

### 4. **Best Practices**
- const correctness
- Static functions where appropriate
- Comprehensive documentation
- Defensive programming

### 5. **Build System**
- Multiple build configurations
- Dependency management
- Tool integration
- Cross-platform considerations

## Common Code Review Points

### Issues to Look For:
1. **Buffer Overflows**: Check array bounds and string operations
2. **Memory Leaks**: Verify malloc/free pairs
3. **Integer Overflow**: Validate arithmetic operations
4. **Null Pointer Dereference**: Check pointer validation
5. **Format String Vulnerabilities**: Review printf usage
6. **Resource Leaks**: Check file handle management
7. **Race Conditions**: Look for threading issues (if applicable)

### Good Practices Demonstrated:
1. **Input Validation**: All user inputs are validated
2. **Error Propagation**: Errors are properly returned and handled
3. **Documentation**: Functions are well-documented
4. **Testing**: Framework ready for unit tests
5. **Debugging**: Debug macros for development
6. **Standards Compliance**: C99 standard compliance

## Testing

### Manual Testing
Run the application and test various scenarios:
- Valid inputs
- Invalid inputs
- Edge cases (division by zero, large numbers)
- Error conditions

### Automated Testing
```bash
# Run test suite
make test

# Add your own tests in tests/ directory
```

## Contributing

This is a demo project for code review practice. When reviewing:

1. Check for memory safety issues
2. Validate error handling paths
3. Review input validation
4. Assess code readability
5. Verify documentation completeness
6. Test edge cases

## Common Improvements

Areas where this code could be enhanced (good for code review practice):

1. **More robust input parsing** (handle scientific notation, etc.)
2. **Extended test coverage** 
3. **Configuration file support**
4. **Internationalization**
5. **Plugin architecture for operations**
6. **GUI interface**
7. **Expression parsing** (infix notation)
8. **History functionality**

## Build System Features

The Makefile includes:
- Multiple build configurations (release, debug, coverage)
- Automatic dependency generation
- Static analysis integration
- Code formatting support
- Memory checking with valgrind
- Coverage reporting
- Installation/uninstallation

## Version Information

- **Version**: 1.0.0
- **C Standard**: C99
- **Compiler**: GCC
- **Platform**: Linux/Unix
- **Dependencies**: libm (math library)

## License

This is a demonstration project for educational purposes.

---

*This project is designed as a code review playground. Feel free to modify, break, and improve it for learning purposes!*