#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "n_gramy.h"
#include "zmienne.h"
#include "macierz.h"

macierz_s * zlicz( n_gram * ngramy ){
        int i, j, k;
        macierz_s * macierz = malloc( ilosc_ngramy * sizeof * macierz );

        if( ilosc_ngramy > 0 ){
                dodaj_prefiks_i_sufiks( macierz, ngramy[0], 0 );
                wiersze++;
        }
	
	if( rzad == 1 ){
		fprintf( stderr, "Program uniemozliwia generowanie tekstu za pomocą unigramow\n" );
		exit( EXIT_FAILURE );	
	}	
        for( i = 1; i < ilosc_ngramy; i++ ) 
                for( j = 0 ; j < wiersze; j++ )	
                       for( k = 0; k < rzad - 1; k++ ){ // szuka powtarzajacych sie prefiksow
                                if( strcmp( ngramy[i].prefiks[k].slowo, macierz[j].prefiks[k].slowo ) != 0 ){ // j-ty prefiks jest inny od porownywanego  
                                        if( j == wiersze - 1 ){ // w macierzy nie ma takiego prefiksu
                                                dodaj_prefiks_i_sufiks( macierz, ngramy[i], wiersze );
                                                wiersze++;
						j = wiersze; // nie porównuj dalej, prefiks juz dodany
					}
					break;
                                }
                                else{
                                        if( k == rzad - 2 ){		// indentyczny prefiks juz wystapil w macierzy
                                                dopisz_sufiks_do_macierzy( macierz, ngramy[i], j );
						j = wiersze; // zakończ operacje na prefiksie
						break;
					}
                                }
                        }
        return macierz;
}

void dodaj_prefiks_i_sufiks( macierz_s * macierz, n_gram gram, int i ){
	int j;
        macierz[i].prefiks = malloc( (rzad - 1) * sizeof * macierz[i].prefiks ); 
	for( j = 0; j < rzad - 1; j++ )
        	macierz[i].prefiks[j] = gram.prefiks[j];
        macierz[i].sufiksy = malloc( sizeof * macierz[i].sufiksy );
        macierz[i].sufiksy[0] = gram.sufiks;

        macierz[i].pref_wyst = 1;
        macierz[i].suf_wyst = malloc( sizeof * macierz[i].suf_wyst );
        macierz[i].suf_wyst[0] = 1;
        macierz[i].ilosc_suf = 1;
}
void dopisz_sufiks_do_macierzy( macierz_s * macierz, n_gram gram, int j ){
        int i;
        macierz[j].pref_wyst++;

        for( i = 0; i < macierz[j].ilosc_suf; i++ ){
                if( strcmp( macierz[j].sufiksy[i].slowo, gram.sufiks.slowo ) == 0 ){ // jesli sufiks juz wystapil
                        macierz[j].suf_wyst[i]++; // dodaj jedno wystapienie
                        break;
                }
                else{           //dodaj nowy sufiks
			if( i == macierz[j].ilosc_suf - 1 ){
                        	macierz[j].ilosc_suf++;
                        	macierz[j].sufiksy = realloc( macierz[j].sufiksy, macierz[j].ilosc_suf * sizeof * macierz[j].sufiksy );
                        	macierz[j].sufiksy[macierz[j].ilosc_suf - 1] = gram.sufiks;
                        	macierz[j].suf_wyst = realloc( macierz[j].suf_wyst, macierz[j].ilosc_suf * sizeof * macierz[j].suf_wyst );
                        	macierz[j].suf_wyst[macierz[j].ilosc_suf - 1]++;
			}	
                }
        }
}
void free_macierz( macierz_s * macierz ){
	int i;
	for( i = 0; i < wiersze; i++ ){
			free( macierz[i].suf_wyst );
			free( macierz[i].sufiksy );
			free( macierz[i].prefiks );
	}
	
	free( macierz );		
}

void drukuj_macierz( macierz_s * macierz ){
        int j;

        for( j = 0; j < wiersze; j++ )
                printf( "%d: %s %s\t%s\t%d\t%d\n", j, macierz[j].prefiks[0].slowo, macierz[j].prefiks[1].slowo, macierz[j].sufiksy[0].slowo, macierz[j].pref_wyst, macierz[j].suf_wyst[0]  );

}


