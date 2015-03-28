#ifndef _N_GRAMY_
#define _N_GRAMY_
	typedef struct slowo_t{
		char * slowo;
		int dlugosc;
		int wystapienia;
	}slowo_s;

	typedef struct n_gram_t{
		char ** prefiks;
		char * sufiks;
		int pmi;
		int wystapeinia_prefiks;
		int wystapienia_sufiks;
	}n_gram;								

/* trzeba wczytywac cale linie, dzielic, ladowac do struktur, zliczac wystapienia*/

slowo_s * zapisz_slowa( slowo_s * baza, char * buffer, int * size );

slowo_s * wczytaj_slowa( FILE ** pliki, int pliki_n );

slowo_s * powieksz_baze( slowo_s * baza, int * size );

void free_slowa( slowo_s * baza );


#endif
