#ifndef _MACIERZ_H_
#define _MACIERZ_H_
macierz_s * zlicz( n_gram * ngramy );

void dodaj_prefiks_i_sufiks( macierz_s * macierz, n_gram gram, int j );

void dopisz_sufiks_do_macierzy( macierz_s * macierz, n_gram gram, int j );

void drukuj_macierz( macierz_s * macierz );

void free_macierz( macierz_s * macierz );

#endif
