#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorType type)
{
	switch (type) {
		case ET_MEMORY:  
			printf("FATAL MEMORY ERROR!\n");
			exit(1);
		default:
			printf("UNKNOWN ERROR!\n");
			exit(1);
	}
}
