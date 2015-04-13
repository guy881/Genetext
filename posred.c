#include <stdio.h>
#include <stdlib.h>

#include "zmienne.h"
#include "n_gramy.h"// TODO

void stworz_posredni( FILE * posred, macierz_s * macierz ){
	int i, j, k;
	fprintf( posred, "%d %d ", wiersze, rzad );

	for( i = 0; i < wiersze; i++ ){
		fprintf( posred, "%d %d ", macierz[i].pref_wyst, macierz[i].ilosc_suf );
		for( j = 0; j < rzad - 1; j++ )
			fprintf( posred, "%d %s ", macierz[i].prefiks[j].dlugosc, macierz[i].prefiks[j].slowo );
		for( k = 0; k < macierz[i].ilosc_suf; k++ )
			fprintf( posred, "%d %s %d ", macierz[i].sufiksy[k].dlugosc, macierz[i].sufiksy[k].slowo, macierz[i].suf_wyst[k] );
	}

	fprintf( posred, "\n" );
}

macierz_s * wczytaj_posredni( FILE * posred_in ){
	int i, j, k;
	
	fscanf( posred_in, "%d %d", &wiersze, & rzad );		 
	macierz_s * macierz = malloc( wiersze * sizeof * macierz ); //free

	for( i = 0; i < wiersze; i++ ){
		fscanf( posred_in, "%d %d ", &macierz[i].pref_wyst, &macierz[i].ilosc_suf );
		macierz[i].prefiks = malloc( (rzad - 1) * sizeof * macierz[i].prefiks );	//free
		for( j = 0; j < rzad - 1; j++ ){
			fscanf( posred_in, "%d", &macierz[i].prefiks[j].dlugosc );
			macierz[i].prefiks[j].slowo = malloc( macierz[i].prefiks[j].dlugosc + 1 ); //free
			fscanf( posred_in, "%s", macierz[i].prefiks[j].slowo );
		}
		macierz[i].sufiksy = malloc( macierz[i].ilosc_suf * sizeof * macierz[i].sufiksy ); //free
		macierz[i].suf_wyst = malloc( macierz[i].ilosc_suf * sizeof * macierz[i].suf_wyst ); //free
		for( k = 0; k < macierz[i].ilosc_suf; k++ ){
			fscanf( posred_in, "%d ", &macierz[i].sufiksy[k].dlugosc );
			macierz[i].sufiksy[k].slowo = malloc( macierz[i].sufiksy[k].dlugosc + 1); //free
			fscanf( posred_in, "%s %d ", macierz[i].sufiksy[k].slowo, &macierz[i].suf_wyst[k] );
		}
	}
	
	return macierz;
}

void free_macierz_posred( macierz_s * macierz){
	int i, j, k;
	for( i = 0; i < wiersze; i++ ){
		for( j = 0; j < rzad - 1; j++ )
			free( macierz[i].prefiks[j].slowo ); 
		free( macierz[i].prefiks );
		for( k = 0; k < macierz[i].ilosc_suf; k++ )
			free( macierz[i].sufiksy[k].slowo );
		free( macierz[i].sufiksy );
		free( macierz[i].suf_wyst );
	}
	free( macierz );
}

	
