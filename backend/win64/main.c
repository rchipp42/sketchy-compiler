#include "../bc_reader.h"
#include "emitter.h"
#include "codegen_win64.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("usage: aot <input.bc> <output.asm>\n");
		return 1;
	}

	Function *f = read_bytecode(argv[1]);

	FILE *out = fopen(argv[2], "w");

	emit_prologue(out);

	for (int i = 0; i < f->code_len; i++) {
		codegen_emit(out, &f->code[i]);
	}

	emit_epilogue(out);

	fclose(out);

	return 0;
}