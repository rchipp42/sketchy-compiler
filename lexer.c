#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// this is the lexer / tokeniser

typedef enum {
    TT_IDENT,
    TT_NUMBER,
    TT_SEMICOLON,
    TT_EOF
    // add more whern needed
} TokenType;

typedef struct {
    TokenType type; // type of token
    char *text;   // allocated string for IDENT/NUMBER
} Token; // Token structure

// dynamic array of tokens
typedef struct {
    Token *data; // pointer to array of tokens
    size_t count; // number of tokens currently stored
    size_t cap;   // capacity of the data array
} TokenList;

// add a token to the list
void add_token(TokenList *list, Token tok) {
    // resize if needed
    if (list->count == list->cap) {
        // double capacity
        list->cap = (list->cap == 0) ? 8 : list->cap * 2;
        list->data = realloc(list->data, list->cap * sizeof(Token));
    }
    // add token to the list
    list->data[list->count++] = tok;
}

// TODO: helper function to copy text from input buffer

// TODO: lexer function that scans input and adds tokens

// TODO: complete main() function 
 int main() {
    // TODO: Test the lexer with some input
    return 0;
}