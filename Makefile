# Makefile for Calculator Application - Code Review Demo
# Author: Code Review Demo
# Date: 2025-10-15

# Project configuration
PROJECT_NAME = calculator
VERSION = 1.0.0

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = tests
DOC_DIR = docs

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
CFLAGS_DEBUG = $(CFLAGS) -g -DDEBUG -O0
CFLAGS_RELEASE = $(CFLAGS) -O2 -DNDEBUG
CFLAGS_COVERAGE = $(CFLAGS_DEBUG) --coverage

# Libraries
LIBS = -lm

# Include paths
INCLUDES = -I$(INCLUDE_DIR)

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJECTS_DEBUG = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/debug/%.o)
OBJECTS_COVERAGE = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/coverage/%.o)

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/test/%.o)

# Executables
TARGET = $(BUILD_DIR)/$(PROJECT_NAME)
TARGET_DEBUG = $(BUILD_DIR)/$(PROJECT_NAME)_debug
TARGET_COVERAGE = $(BUILD_DIR)/$(PROJECT_NAME)_coverage
TEST_TARGET = $(BUILD_DIR)/test_runner

# Default target
.PHONY: all
all: release

# Release build
.PHONY: release
release: $(TARGET)

# Debug build
.PHONY: debug
debug: $(TARGET_DEBUG)

# Coverage build
.PHONY: coverage
coverage: $(TARGET_COVERAGE)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/debug:
	@mkdir -p $(BUILD_DIR)/debug

$(BUILD_DIR)/coverage:
	@mkdir -p $(BUILD_DIR)/coverage

$(BUILD_DIR)/test:
	@mkdir -p $(BUILD_DIR)/test

# Release target
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking release executable..."
	$(CC) $(OBJECTS) -o $@ $(LIBS)
	@echo "Build complete: $@"

# Debug target
$(TARGET_DEBUG): $(OBJECTS_DEBUG) | $(BUILD_DIR)/debug
	@echo "Linking debug executable..."
	$(CC) $(OBJECTS_DEBUG) -o $@ $(LIBS)
	@echo "Debug build complete: $@"

# Coverage target
$(TARGET_COVERAGE): $(OBJECTS_COVERAGE) | $(BUILD_DIR)/coverage
	@echo "Linking coverage executable..."
	$(CC) $(OBJECTS_COVERAGE) -o $@ $(LIBS) --coverage
	@echo "Coverage build complete: $@"

# Compile release objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES) -c $< -o $@

# Compile debug objects
$(BUILD_DIR)/debug/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/debug
	@echo "Compiling $< (debug)..."
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

# Compile coverage objects
$(BUILD_DIR)/coverage/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/coverage
	@echo "Compiling $< (coverage)..."
	$(CC) $(CFLAGS_COVERAGE) $(INCLUDES) -c $< -o $@

# Test compilation
$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)/test
	@echo "Compiling test $<..."
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

# Test runner (excluding main.c from the build)
$(TEST_TARGET): $(filter-out $(BUILD_DIR)/debug/main.o, $(OBJECTS_DEBUG)) $(TEST_OBJECTS) | $(BUILD_DIR)/test
	@echo "Linking test executable..."
	$(CC) $^ -o $@ $(LIBS)
	@echo "Test build complete: $@"

# Run the application
.PHONY: run
run: release
	@echo "Running $(PROJECT_NAME)..."
	./$(TARGET)

# Run debug version
.PHONY: run-debug
run-debug: debug
	@echo "Running $(PROJECT_NAME) (debug)..."
	./$(TARGET_DEBUG)

# Run tests
.PHONY: test
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Generate coverage report
.PHONY: coverage-report
coverage-report: coverage test
	@echo "Generating coverage report..."
	gcov $(SOURCES) -o $(BUILD_DIR)/coverage/
	@echo "Coverage files generated. Use 'lcov' for HTML reports."

# Static analysis with cppcheck (if available)
.PHONY: analyze
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 $(SRC_DIR)/ $(INCLUDE_DIR)/; \
	else \
		echo "cppcheck not found. Skipping static analysis."; \
	fi

# Format code (if clang-format is available)
.PHONY: format
format:
	@echo "Formatting source code..."
	@if command -v clang-format >/dev/null 2>&1; then \
		find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -name "*.c" -o -name "*.h" | xargs clang-format -i; \
		echo "Code formatting complete."; \
	else \
		echo "clang-format not found. Skipping code formatting."; \
	fi

# Check for memory leaks with valgrind
.PHONY: memcheck
memcheck: debug
	@echo "Running memory check..."
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET_DEBUG); \
	else \
		echo "valgrind not found. Skipping memory check."; \
	fi

# Install to system (requires root)
.PHONY: install
install: release
	@echo "Installing $(PROJECT_NAME)..."
	install -d /usr/local/bin
	install -m 755 $(TARGET) /usr/local/bin/$(PROJECT_NAME)
	@echo "Installation complete. Run '$(PROJECT_NAME)' from anywhere."

# Uninstall from system
.PHONY: uninstall
uninstall:
	@echo "Uninstalling $(PROJECT_NAME)..."
	rm -f /usr/local/bin/$(PROJECT_NAME)
	@echo "Uninstallation complete."

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR)
	rm -f *.gcov *.gcda *.gcno
	@echo "Clean complete."

# Deep clean (including coverage files)
.PHONY: distclean
distclean: clean
	@echo "Deep cleaning..."
	find . -name "*.gcov" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	@echo "Deep clean complete."

# Show project information
.PHONY: info
info:
	@echo "Project: $(PROJECT_NAME)"
	@echo "Version: $(VERSION)"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Sources: $(SOURCES)"
	@echo "Includes: $(INCLUDES)"

# Show help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all          - Build release version (default)"
	@echo "  release      - Build optimized release version"
	@echo "  debug        - Build debug version with symbols"
	@echo "  coverage     - Build with coverage instrumentation"
	@echo "  test         - Build and run tests"
	@echo "  run          - Run the release application"
	@echo "  run-debug    - Run the debug application"
	@echo "  analyze      - Run static analysis (requires cppcheck)"
	@echo "  format       - Format source code (requires clang-format)"
	@echo "  memcheck     - Check for memory leaks (requires valgrind)"
	@echo "  coverage-report - Generate coverage report"
	@echo "  install      - Install to /usr/local/bin (requires root)"
	@echo "  uninstall    - Remove from /usr/local/bin (requires root)"
	@echo "  clean        - Remove build artifacts"
	@echo "  distclean    - Remove all generated files"
	@echo "  info         - Show project information"
	@echo "  help         - Show this help message"

# Prevent make from treating files as targets
.PHONY: $(SOURCES) $(TEST_SOURCES)