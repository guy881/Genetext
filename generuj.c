#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "n_gramy.h"
#include "zmienne.h"
#include "macierz.h"
#define ROZMIAR_AKAPITU 63

int wylosuj_prefiks(){
	int i;
	i = rand() % wiersze;
	return i;
}

int dobierz_sufiks( macierz_s wiersz ){
	int ilosc_suf = wiersz.ilosc_suf;
	int los;
	int i, wystapienia = 0;
	int wystapienia2 = 0;

	for( i = 0; i < ilosc_suf; i++ )
		wystapienia += wiersz.suf_wyst[i];
	los = rand() % wystapienia;

	i = 0;
	while( los > wystapienia2 && i < ilosc_suf - 1 ){
		wystapienia2 += wiersz.suf_wyst[i];
		i++;
	}

	return i;
}

void generuj_tekst( macierz_s * macierz, FILE * wyjs, int ilosc_akapitow, int ilosc_slow ){
	int i, j, los_pref, los_suf, akapit; 
	srand( time( NULL ) );
	
	if( wiersze == 0 ){
		fprintf( stderr, "Nie udalo sie wczytac n_gramow z pliku.\n" );
		exit( EXIT_FAILURE );
	}

    if( ilosc_slow == 0 ){ // wybrano -a

	for( akapit = 0; akapit < ilosc_akapitow; akapit++ ){
	   for( i = 0; i < ROZMIAR_AKAPITU; i++ ){
		los_pref = wylosuj_prefiks();
		if( i % 15 == 0 )
			fprintf( wyjs, "\n" );
		for( j = 0; j < rzad - 1; j++ )
			fprintf( wyjs, "%s ", macierz[los_pref].prefiks[j].slowo );
		los_suf = dobierz_sufiks( macierz[los_pref] );
		fprintf( wyjs, "%s ", macierz[los_pref].sufiksy[los_suf].slowo );
	   }
	   fprintf( wyjs, "\n" );
 	}
    }else{ 						//wybrano -s
	   for( i = 0; i < ilosc_slow / rzad; i++ ){
		los_pref = wylosuj_prefiks();
		if( i % 15 == 0 )
			fprintf( wyjs, "\n" );
		for( j = 0; j < rzad - 1; j++ )
			fprintf( wyjs, "%s ", macierz[los_pref].prefiks[j].slowo );
		los_suf = dobierz_sufiks( macierz[los_pref] );
		fprintf( wyjs, "%s ", macierz[los_pref].sufiksy[los_suf].slowo ); 
    		}
	  fprintf( wyjs, "\n" );
    }
}
