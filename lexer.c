#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "lexer.h"

// Lexer configuration
#define BUFFER_SIZE 4096
#define TOKEN_TEXT_SIZE 256

// Tokenizer state
static char input_buf[BUFFER_SIZE];
static size_t buf_pos = 0;
static size_t buf_len = 0;
static int look;

// optimised ASCII checks
static inline int is_alpha(int c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static inline int is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline int is_alnum(int c)
{
	return is_alpha(c) || is_digit(c);
}

static inline int is_space(int c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Buffered input
static void next_char(void)
{
	if (buf_pos >= buf_len) {
		buf_len = fread(input_buf, 1, BUFFER_SIZE, stdin);
		buf_pos = 0;
		if (buf_len == 0) {
			look = EOF;
			return;
		}
	}
	//  Cast to unsigned char.
	// Without this, byte 0xFF (255) becomes -1 (EOF) on signed char systems.
	look = (unsigned char)input_buf[buf_pos++];
}

// Skip whitespace
static void skip_space(void)
{
	while (is_space(look)) next_char();
}

// Lexer init
void lexer_init(void)
{
	buf_pos = buf_len = 0;
	next_char();
	// Pre-skip spaces
	skip_space();
}

// Get identifier or keyword
static char *get_ident(void)
{
	char buffer[TOKEN_TEXT_SIZE];
	int pos = 0;

	// this loop prevents buffer overflow
	while (is_alnum(look) || look == '_') {
		if (pos < TOKEN_TEXT_SIZE - 1) {
			buffer[pos++] = (char)look;
		}
		next_char();
	}
	buffer[pos] = '\0';

	// Allocate exact size
	char *result = malloc(pos + 1);
	if (!result) error(ET_MEMORY);
	memcpy(result, buffer, pos + 1);

	// return
	return result;
}

// Get number
static char *get_number(void)
{
	char buffer[TOKEN_TEXT_SIZE];
	int pos = 0;

	// this loop prevents buffer overflow
	while (is_digit(look)) {
		if (pos < TOKEN_TEXT_SIZE - 1) {
			buffer[pos++] = (char)look;
		}
		next_char();
	}
	buffer[pos] = '\0';

	char *result = malloc(pos + 1);
	if (!result) error(ET_MEMORY);
	memcpy(result, buffer, pos + 1);


	return result;
}

// Generate next token
Token *next_token(void)
{

	skip_space();

	Token *ret_val = malloc(sizeof(Token));
	if (!ret_val) error(ET_MEMORY);
	ret_val->text = NULL;

	if (look == EOF) {
		ret_val->type = TT_EOF;
		return ret_val;
	}

   // Identifier or keyword
	if (is_alpha(look) || look == '_') {
		ret_val->text = get_ident();
		ret_val->type = TT_IDENT;
	} else if (is_digit(look)) {
		ret_val->text = get_number();
		ret_val->type = TT_NUMBER;
	} else {
		// Single-character token
		ret_val->text = malloc(2);
		if (!ret_val->text) error(ET_MEMORY);
		ret_val->text[0] = (char)look;
		ret_val->text[1] = '\0';

		switch (look) {
			case ';': ret_val->type = TT_SEMICOLON; break;
			default:  ret_val->type = TT_UNKNOWN; break;
		}
		next_char();
	}

	return ret_val;
}
