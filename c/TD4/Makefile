main: main.o liste.o vehicule.o
	gcc main.o liste.o vehicule.o -o main
main.o: main.c
	gcc -c main.c
liste.o: liste.c
	gcc -c liste.c
vehicule.o: vehicule.c
	gcc -c vehicule.c
clean:
	rm -rf *.o
