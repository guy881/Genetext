#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "n_gramy.h"
#include "wczyt.h" /*tylko do testow*/
#include "zmienne.h"
#include "macierz.h"

#define bufsize 256
#define initial_size 64

slowo_s * wczytaj_slowa( FILE ** pliki, int pliki_n ){
	char buffer[bufsize];
	int i;
	int size = initial_size;
	ilosc_slow = 0;

	slowo_s * baza = malloc( initial_size * sizeof *baza ); 
	for( i = 0; i < pliki_n; i++ ){
		while( fgets( buffer, bufsize, pliki[i] ) != NULL ) /*wczytaj linie*/
			baza = zapisz_slowa( baza, buffer, &size ); /*podziel na slowa i wrzuc do struktury*/
	}
	return baza;
}

slowo_s * powieksz_baze( slowo_s * baza, int * size ){
	slowo_s * nbaza = realloc( baza, 2 * (*size) * sizeof *nbaza );
	if( !nbaza ){
		free( nbaza );
		fprintf( stderr, "Brak pamieci\n" );
		exit( EXIT_FAILURE ); /*serio?*/
	}
	else{
		(*size) *= 2;
		return nbaza;
	}
}

slowo_s * zapisz_slowa( slowo_s * baza, char * buffer, int * size ){ /*dodaje poszczegolne slowa, powieksza tablice*/
	int i;
	int j = 0;
	char slowo_tmp[bufsize];
	
	for( i = 0; i < strlen( buffer ); i++ ){ 
		if( !isspace( buffer[i] )){
			slowo_tmp[j] = buffer[i];
			j++;
		}
		else{
			if( j == 0 ) /*pomija puste linie*/
				continue;
			slowo_tmp[j] = '\0';
			if( ilosc_slow == *size ){
				baza = powieksz_baze( baza, size );
			}

			baza[ilosc_slow].dlugosc = strlen( slowo_tmp );
			baza[ilosc_slow].slowo = malloc( baza[ilosc_slow].dlugosc + 1 );	//wstaw slowo do struktury
			strncpy( baza[ilosc_slow].slowo, slowo_tmp, baza[ilosc_slow].dlugosc + 1 );
			ilosc_slow++;
			j = 0;
		}		
	}
	return baza;
}
void free_slowa( slowo_s * baza ){
	int i;
	for( i = 0; i < ilosc_slow; i++ )
		free( baza[i].slowo );
	
	free( baza );
}
n_gram * podziel( slowo_s * baza ){
	int i, j;
	ilosc_ngramy = ilosc_slow - (rzad - 1);
	n_gram * ngramy = malloc( ilosc_ngramy * sizeof * ngramy );
	for( i = 0; i < ilosc_ngramy; i++ ){
		ngramy[i].prefiks = malloc( (rzad - 1) * sizeof *ngramy[i].prefiks ); 
		for( j = 0; j < rzad - 1; j++)				//prefiks(rzad - 1) sufiks (1) (ilosc slow)
			if( (i + j) < ilosc_slow ) 			//uwzglednia niepelny, ostatni n-gram
				ngramy[i].prefiks[j] = baza[i + j];

		if( (i + (rzad - 1)) < ilosc_slow )			
			ngramy[i].sufiks = baza[i + (rzad-1)];	

	}
	
	return ngramy;
}
void drukuj_ngramy( n_gram * ngramy ){
	int i, j;
	for( i = 0; i < ilosc_ngramy; i++ ){
		for( j = 0; j < rzad - 1; j++)				
			if( (i + j) < ilosc_slow ) 			
				printf( "%s ", ngramy[i].prefiks[j].slowo );

		if( (i + (rzad - 1)) < ilosc_slow )			
			printf( "  %s\n", ngramy[i].sufiks.slowo );
	}
}
void free_ngramy( n_gram * ngramy ){
	int i;
	for( i = 0; i < ilosc_ngramy; i++ )
			free( ngramy[i].prefiks );
	free( ngramy );
}
