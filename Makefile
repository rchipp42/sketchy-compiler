CC = gcc
CFLAGS = -I. -Ibackend -std=c99

all: fe aot win_x86_backend_test

fe: fe.o lexer.o error.o
	$(CC) -o fe fe.o lexer.o error.o

aot: backend/bc_reader.o backend/regalloc.o backend/util.o backend/win64/main.o backend/win64/codegen_win64.o backend/win64/emitter.o
	$(CC) -o aot backend/bc_reader.o backend/regalloc.o backend/util.o backend/win64/main.o backend/win64/codegen_win64.o backend/win64/emitter.o

win_x86_backend_test: tests/win_x86_backend_test.o
	$(CC) -o win_x86_backend_test tests/win_x86_backend_test.o

fe.o: fe.c lexer.h
	$(CC) -c fe.c $(CFLAGS)

lexer.o: lexer.c lexer.h error.h
	$(CC) -c lexer.c $(CFLAGS)

error.o: error.c error.h
	$(CC) -c error.c $(CFLAGS)

backend/bc_reader.o: backend/bc_reader.c backend/bc_reader.h backend/bc.h
	$(CC) -c backend/bc_reader.c -o backend/bc_reader.o $(CFLAGS)

backend/regalloc.o: backend/regalloc.c backend/regalloc.h
	$(CC) -c backend/regalloc.c -o backend/regalloc.o $(CFLAGS)

backend/util.o: backend/util.c backend/util.h
	$(CC) -c backend/util.c -o backend/util.o $(CFLAGS)

backend/win64/main.o: backend/win64/main.c
	$(CC) -c backend/win64/main.c -o backend/win64/main.o $(CFLAGS)

backend/win64/codegen_win64.o: backend/win64/codegen_win64.c backend/win64/codegen_win64.h
	$(CC) -c backend/win64/codegen_win64.c -o backend/win64/codegen_win64.o $(CFLAGS)

backend/win64/emitter.o: backend/win64/emitter.c backend/win64/emitter.h
	$(CC) -c backend/win64/emitter.c -o backend/win64/emitter.o $(CFLAGS)

tests/win_x86_backend_test.o: tests/win_x86_backend_test.c
	$(CC) -c tests/win_x86_backend_test.c -o tests/win_x86_backend_test.o $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o */*.o */*/*.o fe aot win_x86_backend_test
