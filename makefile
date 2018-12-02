all:main.o
	gcc main.o

main.o: main.c main.h
	gcc -c main.c main.h

clean:
	rm *.o

run:
	./a.out
