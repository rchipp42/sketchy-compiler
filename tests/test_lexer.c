#define _CRT_SECURE_NO_WARNINGS // Required for MSVC (Windows) to allow fopen/freopen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../lexer.h"
#include "../error.h"

// Use Token_Type for type checking

// --- Platform Specific Includes and Definitions ---
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #define unlink _unlink
    #define strdup _strdup
#else
    #include <unistd.h>
    #include <fcntl.h>
#endif

// Global variable to track the file currently open in stdin
static char *g_last_temp_filename = NULL;

// Helper function to free token
void free_token(Token *token) {
    if (token) {
        free(token->text);
        free(token);
    }
}

// Helper: Generates a unique temp file, writes input, and returns the filename.
// The caller is responsible for freeing the returned string.
char* create_temp_file_with_content(const char *content) {
    char *filename = NULL;

#ifdef _WIN32
    // WINDOWS 
    char temp_path[MAX_PATH];
    char temp_file[MAX_PATH];

    // Get the temporary directory path (e.g., C:\Users\User\AppData\Local\Temp\)
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        perror("GetTempPath failed");
        exit(1);
    }

    // Generate a unique temporary filename
    if (GetTempFileNameA(temp_path, "LEX", 0, temp_file) == 0) {
        perror("GetTempFileName failed");
        exit(1);
    }

    filename = strdup(temp_file);

    // Open file to write content
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen temp file failed");
        free(filename);
        exit(1);
    }
    fputs(content, fp);
    fclose(fp);

#else
    // POSIX 
    char template[] = "/tmp/test_lexer_XXXXXX";
    int fd = mkstemp(template); // Creates and opens the file uniquely
    if (fd == -1) {
        perror("mkstemp failed");
        exit(1);
    }

    // Write content directly to file descriptor
    ssize_t len = strlen(content);
    if (write(fd, content, len) != len) {
        perror("write failed");
        close(fd);
        exit(1);
    }
    close(fd);
    
    // Duplicate the filename so we can track it
    filename = strdup(template);
#endif

    return filename;
}

// Test helper: setup input safely using temporary files
void setup_input(const char *input) {
    
    char *new_filename = create_temp_file_with_content(input);

   
    if (freopen(new_filename, "r", stdin) == NULL) {
        perror("freopen failed");
        unlink(new_filename); // Attempt to clean up new file
        free(new_filename);
        exit(1);
    }

   
    if (g_last_temp_filename != NULL) {
        unlink(g_last_temp_filename);
        free(g_last_temp_filename);
    }

    // Update the tracker
    g_last_temp_filename = new_filename;
}

// Cleanup function to be called at end of main
void cleanup_final_temp_file() {
    if (g_last_temp_filename != NULL) {
        
#ifdef _WIN32
        fclose(stdin); 
#else
        
        fclose(stdin);
#endif
        unlink(g_last_temp_filename);
        free(g_last_temp_filename);
        g_last_temp_filename = NULL;
    }
}

// --- TESTS ---

void test_identifier() {
    setup_input("hello");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_IDENT);
    assert(strcmp(token->text, "hello") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_identifier passed\n");
}

void test_number() {
    setup_input("123");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_NUMBER);
    assert(strcmp(token->text, "123") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_number passed\n");
}

void test_semicolon() {
    setup_input(";");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_SEMICOLON);
    assert(strcmp(token->text, ";") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_semicolon passed\n");
}

void test_unknown() {
    setup_input("@");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_UNKNOWN);
    assert(strcmp(token->text, "@") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_unknown passed\n");
}

void test_whitespace() {
    setup_input("  \t\nhello\n  ");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_IDENT);
    assert(strcmp(token->text, "hello") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_whitespace passed\n");
}

void test_mixed() {
    setup_input("var x = 42;");
    lexer_init();

    Token *token = next_token();
    assert(token->type == TT_IDENT);
    assert(strcmp(token->text, "var") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_IDENT);
    assert(strcmp(token->text, "x") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_UNKNOWN);
    assert(strcmp(token->text, "=") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_NUMBER);
    assert(strcmp(token->text, "42") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_SEMICOLON);
    assert(strcmp(token->text, ";") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_mixed passed\n");
}

void test_empty() {
    setup_input("");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_empty passed\n");
}

void test_ident_underscore() {
    setup_input("_var123");
    lexer_init();
    Token *token = next_token();
    assert(token->type == TT_IDENT);
    assert(strcmp(token->text, "_var123") == 0);
    free_token(token);

    token = next_token();
    assert(token->type == TT_EOF);
    free_token(token);
    printf("test_ident_underscore passed\n");
}

int main() {
    test_identifier();
    test_number();
    test_semicolon();
    test_unknown();
    test_whitespace();
    test_mixed();
    test_empty();
    test_ident_underscore();
    
    // Explicit cleanup for the very last temporary file used
    cleanup_final_temp_file();
    
    printf("All tests passed!\n");
    return 0;
}