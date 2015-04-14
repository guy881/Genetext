#include <stdio.h>
#include <stdlib.h>

#include "n_gramy.h"
#include "macierz.h"
#include "zmienne.h"
#define N_NAJCZESTSZE_N_GRAMY 20
#define N_NAJCZESTSZE_SLOWA 20

void stat_wejsc( FILE * stat, macierz_s * macierz ){
	int i, j;
	int n_naj = 0; // ilosc znalezionych 
	int max_wyst = 0;
	int * naj = malloc( N_NAJCZESTSZE_N_GRAMY * sizeof * naj );
	fprintf( stat, "I. Statystyki plikow wejsciowych\n\n" );
	fprintf( stat, "%d najczesciej powtarzajace sie n_gramy:\n", N_NAJCZESTSZE_N_GRAMY );

	for( i = 0; i < 1; i++ ){
		for( j = 0; j < wiersze; j++ ){ 
			if( max_wyst < macierz[j].pref_wyst ){
				max_wyst = macierz[j].pref_wyst;
				naj[i] = j;
			}
		}
	}

	for( i = 1; i < N_NAJCZESTSZE_N_GRAMY; i++ ){
		max_wyst = 0;
		for( j = 0; j < wiersze; j++ ){ 
			if( max_wyst < macierz[j].pref_wyst && naj[i-1] != j && macierz[j].pref_wyst < macierz[naj[i-1]].pref_wyst ){
				max_wyst = macierz[j].pref_wyst;
				naj[i] = j;
			}
		}
		n_naj++;
	}

	for( i = 0; i < N_NAJCZESTSZE_N_GRAMY; i++ ){ //wypisanie do pliku
		fprintf( stat, "%d.)  ", macierz[naj[i]].pref_wyst );
		for( j = 0; j < rzad - 1; j++ ){
			fprintf( stat, "%s ", macierz[naj[i]].prefiks[j].slowo );
		}
		for( j = 0; j < macierz[naj[i]].ilosc_suf; j++ ){
			fprintf( stat, "%s ;", macierz[naj[i]].sufiksy[j].slowo );
		}
			fprintf( stat, "\n" );

	}
	free( naj );
}

void stat_wyjsc( FILE * stat, int ilosc_slow, int ilosc_akapitow ){
	fprintf( stat, "\nII. Statystyki plikow wyjsciowych\n\n" );
	if( ilosc_slow != 0 )
		fprintf( stat, "Ilosc wygenerowanych slow: %d\n", ilosc_slow );
	else
		fprintf( stat, "Ilosc wygenerowanych akapitow: %d\n", ilosc_akapitow );
}
