#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT "5 8 12 1 1 22"

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

    return output;
}

int eval_input(const char *input) {
    size_t ptr = 0;
    size_t input_len = strlen(input);

    int sum = 0;

    while (ptr < input_len) {
        skip_whitespace(input, &ptr);
        if (is_digit(input[ptr])) {
            sum += parse_int(input, &ptr);
        } else {
            return -1;
        }
    }

    printf("sum is %d\n", sum);

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


