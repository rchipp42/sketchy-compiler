#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "error.h"
#include "lexer.h"

// this is the lexer / tokeniser

static char look;

static void next_char(void)
{
	look = getchar();
}

static void skip_space(void)
{
	while(isspace(look)) next_char();
}

void lexer_init(void)
{
	next_char();
	skip_space();
}

static char *get_ident(void)
{
    char buffer[256];
    int pos = 0;

    // while name characters
    while (isalpha(look) || isdigit(look) || look == '_') {
        buffer[pos++] = (char)look;
        next_char();
    }

    buffer[pos] = '\0';

    char *result = malloc(pos + 1);
    if (!result) error(ET_MEMORY);
    strcpy(result, buffer);

    skip_space();
    return result;
}

static char *get_number(void)
{
    char buffer[256];
    int pos = 0;

    // while number characters
    while (isdigit(look)) {
        buffer[pos++] = (char)look;
        next_char();
    }

    buffer[pos] = '\0';

    char *result = malloc(pos + 1);
    if (!result) error(ET_MEMORY);
    strcpy(result, buffer);

    skip_space();
    return result;
}

Token *next_token(void)
{
    Token *ret_val = malloc(sizeof(Token));
    if (!ret_val) error(ET_MEMORY);

    ret_val->text = NULL;

    // EOF check
    if (look == EOF) {
        ret_val->type = TT_EOF;
        return ret_val;
    }

    // Identifier
    if (isalpha(look)) {
        ret_val->text = get_ident();
        ret_val->type = TT_IDENT;
    }
    // Number
    else if (isdigit(look)) {
        ret_val->text = get_number();
        ret_val->type = TT_NUMBER;
    }
    // Semicolon
    else if (look == ';') {
        ret_val->text = malloc(2);
        if (!ret_val->text) error(ET_MEMORY);
        ret_val->text[0] = look;
        ret_val->text[1] = '\0';

        ret_val->type = TT_SEMICOLON;
        next_char();  // consume semicolon
        skip_space();
    }
    // Unknown character
    else {
        ret_val->text = malloc(2);
        if (!ret_val->text) error(ET_MEMORY);
        ret_val->text[0] = look;
        ret_val->text[1] = '\0';

        ret_val->type = TT_UNKNOWN;
        next_char();  // consume it
        skip_space();
    }

    return ret_val;
}
