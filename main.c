#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "^ 0.33333333333 10 "

#define BLOCK_START_CAPACITY 256

#define GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, (sizeof(type) * old_count), \
             (sizeof(type) * new_count))

void* reallocate(void *pointer, size_t old_size, size_t new_size);

typedef enum {
    OPEN,
  	CLOSE,
  	NUM,
} OpCode;

typedef struct {
    size_t length;
  	size_t capacity;
  	uint8_t *data;
} Block;

// initialize directly with starting capacity
static void init_block(Block *b) {
	b->length = 0; 
	b->capacity = BLOCK_START_CAPACITY;
    b->data = malloc(sizeof(uint8_t) * BLOCK_START_CAPACITY);
    return;
}

/* Function used for nearly all memory management of the buffers */
void* reallocate(void *pointer, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, new_size);
    if (result == NULL) exit(1); // not enough memory safeguard
    return result;
}

static void append(Block *b, uint8_t byte) {
    if (b->length + 1 > b->capacity) {
        size_t old_capacity = b->capacity;
        b->capacity = GROW_CAPACITY(b->capacity);

        b->data = GROW_ARRAY(uint8_t, b->data, old_capacity, b->capacity);
    }

    b->data[b->length++] = byte;
    return;
}


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
    while (input[*ptr] == ' ' || input[*ptr] == '\n') (*ptr)++; 
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

    printf("parsed %f (floating point)\n", output);

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


