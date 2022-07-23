main : main.o matrice_io.o matrice_calcul.o alloc.o
	gcc main.o matrice_io.o matrice_calcul.o alloc.o -o main
main.o : main.c
	gcc -c main.c -o main.o
matrice_io.o : matrice_io.c
	gcc -c matrice_io.c -o matrice_io.o
matrice_calcul.o : matrice_calcul.c
	gcc -c matrice_calcul.c -o matrice_calcul.o
alloc.o : alloc.c
	gcc -c alloc.c -o alloc.o
clean :
	rm -rf *.o
