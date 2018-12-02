all:main.o
	gcc main.o

main.o: main.c main.h
	gcc -c main.c

clean:
	rm *.o

run:
	./a.out
