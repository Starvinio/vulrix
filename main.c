#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "+ 1 3"

// TODO: Allow for non-int exponents

static double square(double base, double exponent_d) {
    double result = base;
    int exponent = (int)exponent_d;
    for (int i = 0; i < exponent-1; i++) result *= base;
    return result;
}

static double arithmetic(char op, double res, double atom) {
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

void skip_whitespace(const char *input, size_t *ptr) {
    while (input[*ptr] == ' ') (*ptr)++; 
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

double c_to_double(char c) {
    return (double)(c - '0');
}

double parse_num(const char *input, size_t *start) {
    size_t ptr = *start + 1; // we already know first char is digit
    double output = c_to_double(input[*start]);

    while (is_digit(input[ptr])) {
        output = output * 10.0 + c_to_double(input[ptr++]);
    };

    if (input[ptr] != '.') {
        *start = ptr;
        printf("parsed %f (no floating point)\n", output);
        return output;
    }

    ptr++;

    double factor = 0.1;
    while (is_digit(input[ptr])) {
        double d = c_to_double(input[ptr++]);
        output += (d * factor); 
        factor *= 0.1;
    };

    printf("parsed %f (no floating point)\n", output);

    *start = ptr;
    return output;
}

int eval_input(const char *input) {
    size_t ptr = 0;
    size_t input_len = strlen(input);
    char op = input[ptr++];

    skip_whitespace(input, &ptr);
    char c = input[ptr];
    double result;
    if (is_digit(c)) {
        double c_int = parse_num(input, &ptr);

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
            double c_int = parse_num(input, &ptr);
            result = arithmetic(op, result, c_int);
        } else if (c == '\0') break;
        else {
            printf("reached non-digit atom %c\n", c);
            return -1;
        }
    }

    printf("(%c) result is %f\n", op, result);

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


