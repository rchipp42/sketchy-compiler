CC = gcc
CFLAGS = -I. -Ibackend -std=c99

all: fe aot test_backend

fe: fe.o lexer.o error.o
	$(CC) -o fe fe.o lexer.o error.o

aot: backend/bc_reader.o backend/regalloc.o backend/util.o backend/win64/main.o backend/win64/codegen_win64.o backend/win64/emitter.o
	$(CC) -o aot backend/bc_reader.o backend/regalloc.o backend/util.o backend/win64/main.o backend/win64/codegen_win64.o backend/win64/emitter.o

test_backend: tests/test_backend.o
	$(CC) -o test_backend tests/test_backend.o

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

tests/test_backend.o: tests/test_backend.c
	$(CC) -c tests/test_backend.c -o tests/test_backend.o $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o */*.o */*/*.o fe aot test_backend
