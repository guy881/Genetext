#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "wczyt.h"

#define liczba_akapitow 2
#define rzad_n_gramu 3
#define plik_wyj "outText.txt" 
#define posred_nazwa "ind_text.ind"
#define stat_nazwa "stat"

/*	Użycie: ./genetext [tekstybazowe(.txt)]... [OPCJA]...
Opcje:
-s liczba słów [LICZBA] (opcjonalne, wyklucza -a)
-a liczba akapitów [LICZBA] (domyślnie 2)
-n rząd n-gramów [LICZBA] (domyślnie 3)
-w plik wyjściowy [NAZWA PLIKU] (domyślnie outText.txt)
-p generowanie plików pośrednich
-t generuje statystyki (opcjonalne)

*/
int main( int argc, char ** argv ){
	int opt;
	int n_slow;
	int n_akapitow;
	int rzad_n_gram;
	FILE * wyjsciowy;

	while( (opt = getopt( argc, argv, "s:a:n:w:p:t" )) != -1 )	//0bsługa opcji
	  switch( opt ){
	  case 's':
		n_slow = optarg;
		break;
	  case 'a':
		n_akapitow = optarg;
		break;		
	  case 'n':
	  	rzad_n_gram = optarg;
		break;
	  case 'w':
		wyjsciowy = fopen( optarg, "w" ); //nazwa domyslna TODO
		if( wyjsciowy == NULL)
			fprintf( stderr, "error\n" );
		break;
	  case 'p':
	  	FILE * posred = fopen( posred_nazwa, "w" );
		break;
	  case 't':
	  	FILE * stat = fopen( stat_nazwa, "w" );
		break;
	  default: 
	  	int ilosc_pliki = argc - 1;
		int format;
		format = format_plikow( argv, ilosc_pliki );
		if( format == 0 ){
			FILE ** pliki_txt = wczytaj_pliki_txt( argv, &ilosc_pliki );
			//TODO laduj_n_gramy()
		}
		else if( format == 1 ){
			FILE * posred_in; // = wczytaj_plik_posredni TODO
			//generuj_tekst_z_poredniego()
		}
		if( format == -1 )
			fprintf( stderr, "error\n" );
		break;
	  }

	wczytaj_pliki(); // pamietaj o posrednich, dodatkowa funkcja

	zainicjuj stuktury;
				//dynamiczny przydzial miejsca
	podziel_na_n_gramy();
				//wylicz prawdopodobienstwo
	wylosuj_i_wypisz();
	
	//generuj_stat();
	
	return 0;
}
