#ifndef _WCZYT_H_
#define _WCZYT_H_
FILE ** wczytaj_pliki_txt( char ** argv, int * n );

void free_pliki( FILE ** pliki, int n ); 

int format_plikow( char ** argv, int n );       /*zwraca 0 w przypadku plikow txt, 1 - pliki posrednie (format ind), -1 zly format*/

#endif
