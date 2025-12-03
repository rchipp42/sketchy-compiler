fe: fe.o lexer.o error.o
	gcc -o fe fe.o lexer.o error.o

fe.o: fe.c lexer.h
	gcc -c fe.c

lexer.o: lexer.c lexer.h error.h
	gcc -c lexer.c

error.o: error.c error.h
	gcc -c error.c


.PHONY clean:
	rm *.o
	rm fe
