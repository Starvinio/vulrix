#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "^ 12 2"

static int square(int base, int exponent) {
    int result = base;
    for (int i = 0; i < exponent-1; i++) result *= base;
    return result;
}

static int arithmetic(char op, int res, int atom) {
    switch (op) {
            case '+': return res + atom;
            case '-': return res - atom;
            case '*': return res * atom;
            case '^': return square(res,atom);
            case '/': {
                if (atom != 0) return res / atom;

                fprintf(stderr, "Division by zero error.\n");
                exit(44); 
            }
            default: {
                fprintf(stderr, "Unknown Operator.\n");
                exit(22); 
            }
    }
}

static char next_char(const char *input, size_t *ptr) {
    return input[(*ptr)++];
}

void skip_whitespace(const char *input, size_t *ptr) {
    while (input[*ptr] == ' ') (*ptr)++; 
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int c_to_int(char c) {
    return c - '0';
}

int parse_int(const char *input, size_t *start) {
    size_t ptr = *start + 1; // we already know first char is digit
    int output = c_to_int(input[*start]);

    while (is_digit(input[ptr])) {
        output *= 10;
        output += c_to_int(input[ptr++]);
    };

    *start = ptr;

    printf("parsed %d\n", output);
    return output;
}

int eval_input(const char *input) {
    size_t ptr = 0;
    size_t input_len = strlen(input);
    char op = input[ptr++];

    skip_whitespace(input, &ptr);
    char c = input[ptr];
    int result;
    if (is_digit(c)) {
        int c_int = parse_int(input, &ptr);

        // if minus, we want to start negative
        // [allows direct negation]
        if (op == '-') result = -c_int; 
        else result = c_int;

    } else {
        return 0;
    }
    
    
    while (ptr < input_len) {
        skip_whitespace(input, &ptr);
        c = input[ptr];
        if (is_digit(c)) {
            int c_int = parse_int(input, &ptr);
            result = arithmetic(op, result, c_int);
        } else if (c == '\0') break;
        else {
            printf("reached non-digit atom %c\n", c);
            return -1;
        }
    }

    printf("(%c) result is %d\n", op, result);

    return 0;
}

int main(void) {
    const char* input = INPUT;

    if (eval_input(input) != 0) {
        fprintf(stderr, "Unknown Syntax Error");
        exit(-1);
    }
    return 0;
}


