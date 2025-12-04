#ifndef BC_H
#define BC_H

typedef enum {
	OP_LOAD_CONST,   // load_const rX, imm
	OP_ADD,		  // add rA = rB + rC
	OP_RET,		  // ret rX
} OpCode;

typedef struct {
	OpCode op;
	int a, b, c;
} Instruction;

typedef struct {
	Instruction* code;
	int code_len;
} Function;

#endif