#include "../bc.h"
#include "../regalloc.h"
#include <stdio.h>

void codegen_emit(FILE* out, Instruction* instr) {
    switch (instr->op) {
    case OP_LOAD_CONST:
        fprintf(out, "    mov %s, %d\n",
            physreg(instr->a),
            instr->b);
        break;

    case OP_ADD:
        fprintf(out, "    mov %s, %s\n",
            physreg(instr->a),
            physreg(instr->b));
        fprintf(out, "    add %s, %s\n",
            physreg(instr->a),
            physreg(instr->c));
        break;

    case OP_RET:
        fprintf(out, "    mov eax, %s\n", reg32(instr->a));
        fprintf(out, "    ret\n");
        break;

    default:
        fprintf(out, "    ; TODO: unimplemented opcode\n");
    }
}