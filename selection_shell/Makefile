all: item.o pilha.o main.o
	gcc item.o pilha.o main.o -o main -std=c99 -Wall

item.o:
	gcc -c ../../alg1/item/item.c

pilha.o:
	gcc -c pilha_seq.c -o pilha.o

main.o:
	gcc -c main.c

run: all
	./main

clean:
	rm *.o main