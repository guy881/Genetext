#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "n_gramy.h"
#include "wczyt.h" /*tylko do testow*/

#define bufsize 256
#define initial_size 32

slowo_s * wczytaj_slowa( FILE ** pliki, int pliki_n ){
	char * buffer = malloc( bufsize );
	int i;
	int size = initial_size;
	int ilosc_slow = 0;

	slowo_s * baza = malloc( initial_size * sizeof *baza ); 
	for( i = 0; i < pliki_n; i++ ){
		while( fgets( buffer, bufsize, pliki[i] ) != NULL )
			 printf( "%s\n", buffer );
	}

	free( buffer );
	return baza;
}

slowo_s * powieksz_baze( slowo_s * baza, int size ){
	slowo_s * n_baza = realloc( baza, 2*size * sizeof *n_baza );
	if( !n_baza ){
		free( baza );
		fprintf( stderr, "Brak pamieci\n" );
		exit( EXIT_FAILURE ); /*serio?*/
	}
	else{
		return n_baza;
	}
}
/*TODO
void zapisz_slowo( char * wyraz, slowo_s * baza, int * ilosc_slow, int * size ) //dodaje poszczegolne slowa, powieksza tablice
*/
int main( int argc, char ** argv ){

	slowo_s * slowa;
	int pliki_n = argc - 1;
	FILE ** pliki = wczytaj_pliki_txt( argv, &pliki_n );

	slowa = wczytaj_slowa( pliki, pliki_n );

	return 0;
}
