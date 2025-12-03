fe: fe.o
	gcc -o fe fe.o

fe.o: fe.c
	gcc -c fe.c

.PHONY clean:
	rm *.o
	rm fe
