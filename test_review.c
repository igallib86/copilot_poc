// Test function with code review issues
int unsafe_function(char* input) {
    char buffer[10];
    strcpy(buffer, input);  // Buffer overflow risk
    return strlen(input) * 100;  // Magic number
}
