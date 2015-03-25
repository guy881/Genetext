#ifndef _N_GRAMY_
#define _N_GRAMY_
	typedef struct string{
		char ** lan;
		int dlugosc;
	}string_t;
				// trzeba wczytywac cale linie, dzielic, ladowac do struktur, zliczac wystapienia
	typedef struct n_gram{
		char **lan;
		int wystapienia;
		struct n_gram * next;
	}

#endif
