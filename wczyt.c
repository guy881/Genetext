#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE ** wczytaj_pliki_txt( char ** argv, int * n ) /*Wczytuje n plików*/
{
	int i, dlugosc;
	int dobre_pliki = 0;

	FILE ** pliki = malloc( (*n) * sizeof( FILE * )); /*tablica plików*/

	for( i = 1; i < *n + 1; i++ )
	{
		dlugosc = strlen( argv[i] );
		if( dlugosc < 4 ){ //z pewnoscia, nie jest to plik
			continue;
		}
		if( argv[i][dlugosc -1] == 't' &&  argv[i][dlugosc -2] == 'x' &&  argv[i][dlugosc -3] == 't' && argv[i][dlugosc -4] == '.' ){
			pliki[dobre_pliki] = fopen( argv[i], "r" );
			if( pliki[dobre_pliki] != NULL ) /*jesli sie nie powiodlo, otworz nastepny plik*/
				dobre_pliki++;
		}
	}

	if( dobre_pliki == 0 ){
		fprintf( stderr, "Nie udalo sie poprawnie wczytac plikow wejsciowych.\n" );
		free( pliki );
		return NULL;
	}

	*n = dobre_pliki;

	return pliki;
}

void free_pliki( FILE ** pliki, int n )
{
	int i;
	for( i = 0; i < n; i++ ){
		if( pliki[i] != NULL )	
			fclose( pliki[i] );
	}
	free( pliki );
}
