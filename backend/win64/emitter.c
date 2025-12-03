#include "emitter.h"

void emit_prologue(FILE* out) {
    fprintf(out,
        "global main\n"
        "\n"
        "section .text\n"
        "\n"
        "main:\n"
    );
}

void emit_epilogue(FILE* out) {
    // No epilogue needed for NASM
}