#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "wczyt.h"
#include "zmienne.h"
#include "n_gramy.h"
#include "macierz.h"
#include "generuj.h"
#include "posred.h"
#include "statystyki.h"
#include <time.h>

#define liczba_akapitow 2
#define rzad_n_gramu 3
#define plik_wyj "outText.txt" 
#define stat_nazwa "stat"

int main( int argc, char ** argv ){
	int opt;
	int n_slow = 0;
	int n_akapitow = liczba_akapitow;
        int pliki_n = argc - 1;
	int opt_posred = 0;
	int opt_posred_in = 0;
	int opt_stat = 0;

	clock_t timer = clock();

	FILE * wyjsciowy = NULL;
	FILE * posred = NULL; 
	FILE * posred_in = NULL;
	FILE * stat;
	FILE ** pliki_txt;

	slowo_s * slowa;
        n_gram * ngramy;
        macierz_s * macierz;

	rzad = rzad_n_gramu;

	uzycie = "Użycie: ./genetext [tekstybazowe(.txt)]... [OPCJA]...\n"
	"\tOpcje:\n"
	"\t\t-s liczba słów [LICZBA] (opcjonalne, wyklucza -a)\n"
	"\t\t-a liczba akapitów [LICZBA] (domyślnie 2)\n"
	"\t\t-n rząd n-gramów [LICZBA] (domyślnie 3)\n"
	"\t\t-w plik wyjściowy [NAZWA PLIKU] (domyślnie outText.txt)\n"
	"\t\t-p generowanie pliku pośredniego\n"
	"\t\t-i wczytywanie pliku pośredniego\n"
	"\t\t-t generuje statystyki (opcjonalne)\n";

	while( (opt = getopt( argc, argv, "s:a:n:w:p:i:t::" )) != -1 )	//0bsługa opcji
	  switch( opt ){
	  case 's':
		n_slow = atoi( optarg );
		break;
	  case 'a':
		n_akapitow = atoi( optarg );
		break;		
	  case 'n':
	  	rzad = atoi( optarg );
		break;
	  case 'w':
		wyjsciowy = fopen( optarg, "w" ); 
		break;
	  case 'p':
		posred = fopen( optarg, "w" );
		if( posred == NULL )
			return EXIT_FAILURE;
		opt_posred = 1;
		break;
	  case 'i':
	  	posred_in = fopen( optarg, "r" );
		opt_posred_in = 1;
		break;
	  case 't':
	  	stat = fopen( stat_nazwa, "w" );
		if( stat != NULL )
			opt_stat = 1;
		break;
	  default: 
		break;
	  }
	
	if( n_akapitow != liczba_akapitow && n_slow != 0 ){
		fprintf( stderr, "Opcja -s wyklucza -a\n%s\n", uzycie );
		return EXIT_FAILURE; 
	}
	
	if( wyjsciowy == NULL )
		wyjsciowy = fopen( plik_wyj, "w" );

	if( opt_posred_in == 1 ){ // generowanie tekstu z pliku posredniego
		macierz = wczytaj_posredni( posred_in );
		generuj_tekst( macierz, wyjsciowy, n_akapitow, n_slow );

		free_macierz_posred( macierz );
		fclose( wyjsciowy );
		fclose( posred_in );
		printf( "Czas wykonywania: %lu ms\n", clock() - timer);
		return 0;
	}
	pliki_txt = wczytaj_pliki_txt( argv, &pliki_n );

	if( pliki_txt == NULL ){
		fprintf( stderr, "%s\n", uzycie );
		return EXIT_FAILURE; 
	}

        slowa = wczytaj_slowa( pliki_txt, pliki_n );
        ngramy = podziel( slowa );
       	 	//drukuj_ngramy( ngramy );
        macierz = zlicz( ngramy );
        	//drukuj_macierz( macierz );
	
	if( opt_posred == 1 ){ 		//generowanie pliku posredniego
		stworz_posredni( posred, macierz ); 
		fclose( posred );	
	}
	generuj_tekst( macierz, wyjsciowy, n_akapitow, n_slow );

	if( opt_stat == 1 ){ 		//generowanie pliku statystycznego
		stat_wejsc( stat, macierz ); 
		stat_wyjsc( stat, n_slow, n_akapitow );
	}
        	free_pliki( pliki_txt, pliki_n );
		fclose( wyjsciowy );
        	free_slowa( slowa );
        	free_ngramy( ngramy );
        	free_macierz( macierz );
	printf( "Czas wykonywania: %lu ms\n", clock() - timer);
	return 0;
}
