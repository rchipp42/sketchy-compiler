fe: fe.o lexer.o
	gcc -o fe fe.o lexer.o

fe.o: fe.c lexer.h
	gcc -c fe.c

lexer.o: lexer.c lexer.h
	gcc -c lexer.c


.PHONY clean:
	rm *.o
	rm fe
