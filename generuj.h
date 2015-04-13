#ifndef _GENERUJ_H_
#define _GENERUJ_H_

void generuj_tekst( macierz_s * macierz, FILE * wyjs, int ilosc_akapitow, int ilosc_slow );

int wylosuj_prefiks();

int dobierz_sufiks( macierz_s wiersz );

#endif
