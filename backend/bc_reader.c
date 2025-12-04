#include "bc.h"
#include <stdio.h>
#include <stdlib.h>

Function *read_bytecode(const char *path)
{
	FILE *f = fopen(path, "rb");
	if (!f) return NULL;

	Function *func = malloc(sizeof(Function));
	if (!func) {
		fclose(f);
		return NULL;
	}

	if (fread(&func->code_len, sizeof(int), 1, f) != 1) {
		free(func);
		fclose(f);
		return NULL;
	}

	func->code = malloc(sizeof(Instruction) * func->code_len);
	if (!func->code) {
		free(func);
		fclose(f);
		return NULL;
	}

	if (fread(func->code, sizeof(Instruction), func->code_len, f) != (size_t)func->code_len) {
		free(func->code);
		free(func);
		fclose(f);
		return NULL;
	}

	fclose(f);
	return func;
}