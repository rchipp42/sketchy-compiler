fe: fe.o lexer.o
	gcc -o fe fe.o lexer.o

fe.o: fe.c
	gcc -c fe.c

lexer.o: lexer.c
	gcc -c lexer.c


.PHONY clean:
	rm *.o
	rm fe
