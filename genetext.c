#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "wczyt.h"
#include "zmienne.h"
#include "n_gramy.h"
#include "macierz.h"
#include "generuj.h"

#define liczba_akapitow 2
#define rzad_n_gramu 3
#define plik_wyj "outText.txt" 
#define posred_nazwa "ind_text.ind"
#define stat_nazwa "stat"

char * uzycie = "Użycie: ./genetext [tekstybazowe(.txt)]... [OPCJA]...\n"
"\tOpcje:\n"
"\t\t-s liczba słów [LICZBA] (opcjonalne, wyklucza -a)\n"
"\t\t-a liczba akapitów [LICZBA] (domyślnie 2)\n"
"\t\t-n rząd n-gramów [LICZBA] (domyślnie 3)\n"
"\t\t-w plik wyjściowy [NAZWA PLIKU] (domyślnie outText.txt)\n"
"\t\t-p generowanie plików pośrednich\n"
"\t\t-t generuje statystyki (opcjonalne)\n";

int main( int argc, char ** argv ){
	int opt;
	int n_slow;
	int n_akapitow;
        int pliki_n = argc - 1;

	FILE * wyjsciowy;
	FILE * posred; 
	FILE * stat;
	FILE ** pliki_txt;

	slowo_s * slowa;
        n_gram * ngramy;
        macierz_s * macierz;

	rzad = 7;

	while( (opt = getopt( argc, argv, "s:a:n:w:p:t" )) != -1 )	//0bsługa opcji
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
		if( wyjsciowy == NULL)
			 wyjsciowy = fopen( plik_wyj, "w" );
		break;
	  case 'p':
		posred = fopen( posred_nazwa, "w" );
		break;
	  case 't':
	  	stat = fopen( stat_nazwa, "w" );
		break;
	  default: 
		break;
	  }

	int format = format_plikow( argv, pliki_n );
	if( format == 0 ){
		pliki_txt = wczytaj_pliki_txt( argv, &pliki_n );
		if( pliki_txt == NULL ){
			fprintf( stderr, "%s\n", uzycie );
			exit( EXIT_FAILURE );
		}
	}
	else if( format == 1 ){
		FILE * posred_in; // = wczytaj_plik_posredni TODO
			//generuj_tekst_z_poredniego()
	}
	else if( format == -1 ){
		fprintf( stderr, "%s\n", uzycie );
		exit( EXIT_FAILURE );
	}

        slowa = wczytaj_slowa( pliki_txt, pliki_n );
        ngramy = podziel( slowa );
        //drukuj_ngramy( ngramy );
        macierz = zlicz( ngramy );
        //drukuj_macierz( macierz );
	wyjsciowy = fopen( plik_wyj, "w" );
	generuj_tekst( macierz, wyjsciowy, liczba_akapitow, 0 );
        free_slowa( slowa );
        free_pliki( pliki_txt, pliki_n );
        free_ngramy( ngramy );
        free_macierz( macierz );
//	fclose( posred );
//	fclose( stat );
//	fclose( wyjsciowy );

	//generuj_stat();
	
	return 0;
}
