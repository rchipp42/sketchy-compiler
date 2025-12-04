#include "../backend/bc.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
	// Create bytecode: 5 + 6 = 11, ret 11
	Instruction code[] = {
		{OP_LOAD_CONST, 0, 5, 0},  // r0 = 5
		{OP_LOAD_CONST, 1, 6, 0},  // r1 = 6
		{OP_ADD, 2, 0, 1},		 // r2 = r0 + r1
		{OP_RET, 2, 0, 0}		  // ret r2
	};
	int code_len = 4;

	// Write bytecode to file
	FILE *bc_file = fopen("test.bc", "wb");
	assert(bc_file);
	fwrite(&code_len, sizeof(int), 1, bc_file);
	fwrite(code, sizeof(Instruction), code_len, bc_file);
	fclose(bc_file);

	// Run aot compiler
	int ret = system("..\\backend\\Debug\\aot.exe test.bc test.asm");
	assert(ret == 0);

	// Assemble with nasm
	ret = system("nasm -f win64 test.asm");
	assert(ret == 0);

	// Link
	ret = system("link /entry:main /subsystem:console test.obj");
	assert(ret == 0);

	// Run and check exit code
	ret = system("test.exe");
	int exit_code = ret;
	assert(exit_code == 11);

	printf("Test passed!\n");
	return 0;
}