#ifndef _N_GRAMY_
#define _N_GRAMY_
	typedef struct slowo_t{
		char * slowo;
		int dlugosc;
		int wystapienia;
	}slowo_s;

	typedef struct n_gram_t{
		slowo_s * prefiks;
		slowo_s sufiks;
		int pmi;
	}n_gram;								

	typedef struct macierz_t{
		slowo_s * prefiks;
		slowo_s * sufiksy;
		int * suf_wyst;			//jeden wiersz macierzy przejsc
		int  pref_wyst;		//macierz sklada sie z prefiksu oraz ewentualnych sufiksow
		int ilosc_suf;
	}macierz_s;			
	

n_gram * podziel( slowo_s * baza );

void drukuj_ngramy( n_gram * ngramy );

void free_ngramy( n_gram * ngramy );

slowo_s * zapisz_slowa( slowo_s * baza, char * buffer, int * size );

slowo_s * wczytaj_slowa( FILE ** pliki, int pliki_n );

slowo_s * powieksz_baze( slowo_s * baza, int * size );

void free_slowa( slowo_s * baza );

#endif
