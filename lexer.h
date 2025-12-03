#ifndef LEXER_H
#define LEXER_H

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

void lexer_init(void);

Token *next_token(void);

#endif