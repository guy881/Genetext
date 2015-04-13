#ifndef _POSRED_H_
#define _POSRED_H_

void stworz_posredni( FILE * posredni, macierz_s* macierz );

macierz_s * wczytaj_posredni( FILE * posred_in );

void free_macierz_posred( macierz_s * macierz);
#endif
