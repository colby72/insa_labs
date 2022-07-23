pile : pile.o vehicule.o
	gcc pile.o vehicule.o -o pile
pile.o : pile.c
	gcc -c pile.c -o pile.o
vehicule.o : vehicule.c
	gcc -c vehicule.c -o vehicule.o
clean :
	rm -rf *.o
