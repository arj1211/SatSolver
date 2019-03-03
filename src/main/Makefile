run: main
	./main ../../samples/test*
fulltest: main
	./main ../../samples/*

main: main.o ../dimacs/dimacs_reader.o
	gcc -o main main.o ../dimacs/dimacs_reader.o

main.o: main.c ../../inc/dimacs_reader.h
	gcc -c main.c -I ../../inc

clean:
	rm -f main *.o
