#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
	return NULL; /* placeholder */
}

static char *get_number(void)
{
	return NULL; /* placeholder */
}

Token *next_token(void)
{
	Token *ret_val;

	ret_val = malloc(sizeof(Token));
	if (!ret_val) exit(1);

	ret_val->text = NULL;

	if (isalpha(look)) {
		ret_val->text = get_ident();
		ret_val->type = TT_IDENT;
	} else if (isdigit(look)) {
		ret_val->text = get_number();
		ret_val->type = TT_NUMBER;
	}

	return ret_val;
}