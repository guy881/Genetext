CC=gcc -Wall -ggdb -g -o Genetext

genetext.o: macierz.c wczyt.c wwczyt_do_struktur.c genetext.c generuj.c posred.c
	$(CC) macierz.c wczyt.c wwczyt_do_struktur.c genetext.c generuj.c posred.c

clean: 
	rm -f *.o
