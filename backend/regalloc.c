#include "regalloc.h"

const char *physreg(int vreg)
{
	switch (vreg) {
		case 0: return "rcx";
		case 1: return "rdx";
		case 2: return "r8";
		case 3: return "r9";
		case 4: return "rax";
		case 5: return "rbx";
		case 6: return "rsi";
		case 7: return "rdi";
		default: return "rax"; // TODO: real spilling
	}
}

const char *reg32(int vreg)
{
	switch (vreg) {
		case 0: return "ecx";
		case 1: return "edx";
		case 2: return "r8d";
		case 3: return "r9d";
		case 4: return "eax";
		case 5: return "ebx";
		case 6: return "esi";
		case 7: return "edi";
		default: return "eax";
	}
}