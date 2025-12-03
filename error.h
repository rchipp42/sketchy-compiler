#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ET_MEMORY
} ErrorType;

// Declare the error function
void error(ErrorType type);

#endif
