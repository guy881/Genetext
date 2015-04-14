CC=gcc -Wall -ggdb -g -o Genetext

genetext.o: macierz.c wczyt.c wwczyt_do_struktur.c genetext.c generuj.c posred.c statystyki.c
	$(CC) macierz.c wczyt.c wwczyt_do_struktur.c genetext.c generuj.c posred.c statystyki.c

clean: 
	rm -f *.o
