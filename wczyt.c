#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256
#define txt 0 /*format plikow*/
#define ind 1 /*-||-*/
#define zly_format -1

int format_plikow( char ** argv, int n )	/*zwraca 0 w przypadku plikow txt, 1 - pliki posrednie (format ind), -1 zly format*/
{						
	int i, dlugosc;
	int n_posrednie = 0;
	int n_txt = 0;

	for( i = 1; i < n + 1; i++ )
	{	
		dlugosc = strlen( argv[i] );
		if( argv[i][dlugosc -1] == 't' &&  argv[i][dlugosc -2] == 'x' &&  argv[i][dlugosc -3] == 't' && argv[i][dlugosc -4] == '.' )
			n_txt++;
	 	else if( argv[i][dlugosc -1] == 'd' &&  argv[i][dlugosc -2] == 'n' &&  argv[i][dlugosc -3] == 'i' && argv[i][dlugosc -4] == '.' ) 
			n_posrednie++;
		else
			return zly_format;
	}
	
	if( n_txt == n )
		return txt;
	else if( n_posrednie == n ) /*wszystkie pliki musza byc tego samego typu */
		return ind;
	else
		return zly_format;
}		
FILE ** wczytaj_pliki_txt( char ** argv, int * n ) /*Wczytuje n plików*/
{
	int i; /*TODO zadaj pliku txt!*/

	FILE ** pliki = malloc( (*n) * sizeof( FILE * )); /*tablica plików*/

	for( i = 0; i < (*n); i++ )
	{
		pliki[i] = fopen( argv[i + 1], "r" );
		if( pliki[i] == NULL ) /*jesli sie nie powiodlo, otworz nastepny plik*/
		{	
			(*n)--;
			i--;
		}
	}
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
/*
int main( int argc, char ** argv )
{
	int n = argc - 1;
	int * dobre_pliki = &n; 
	int i;
	FILE ** pliki;
	char bufor[BUFSIZE];	

	if( format_plikow( argv, *dobre_pliki ) == 0 )
		pliki = wczytaj_pliki_txt( argv, dobre_pliki );
	else
	{	printf("niet!\n");					*/
	/*wczytaj_plik_ind*/
	/*	return 1;
	}
	n = *dobre_pliki;
	for( i = 0; i < n; i++ )
		while( fgets( bufor, BUFSIZE, pliki[i] ))
			printf( "%s \n", bufor );
	free_pliki( pliki, n );

	return 0;
}*/
