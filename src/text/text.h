/*
 * github.com/nrizzo
 * src/text/text.h
 *
 * Intestazione del codice per gestire un testo di parole separate da uno o piu'
 * whitespace. In particolare, si occupa di ottenere il testo da standard input
 * fino ad esaurimento (EOF), salvandone sia le parole che l'alfabeto
 * S=Sigma\{blank}.
 *
 * Esempio di utilizzo:
 *
 *  struct text *T = text_create(); // creazione
 *  text_retrieve(T); // ottenimento
 *
 *  int t = text_size(T); // t cardinalita' di T
 *  struct alphabet *S = text_getalpha(T); // ottenimento dell'alfabeto S
 *
 *  struct dl_list_w *scan = text_get(T); // iterazione sulle parole di T
 *  while (!dllw_isempty) {
 *  	struct word *w = dllw);
 *  	...
 *  	scan = dllw_next(scan);
 *  }
 *
 *  text_destroy(T); // distruzione
 */

#ifndef TGUARD /* guardia */
#define TGUARD

#include "../list/list.h"

/* 
 * Struct che rappresenta il testo T. E' composta dall'alfabeto S=Sigma\{blank}
 * e da un vettore delle parole.
 */
struct text{
	struct alphabet *S;

	int n; /* numero di parole */
	struct dl_list_w *words;
};

/* 
 * text_create crea un testo senza parole e con alfabeto vuoto e ne restituisce
 * il puntatore.
 */
struct text *text_create();

/* 
 * text_retrieve legge lo standard input fino ad esaurimento (EOF), raccogliendo
 * le parole e l'alfabeto.
 */
void text_retrieve(struct text *T);

/* 
 * text_size restituisce il numero di parole del testo T.
 */
int text_size(struct text *T);

/* 
 * text_getalpha restituisce l'alfabeto S con cui sono composte le parole del
 * testo T.
 */
struct alphabet *text_getalpha(struct text *T);

/* 
 * text_get restituisce la lista delle parole che compongono il testo T.
 */
struct dl_list_w *text_get(struct text *T);

/* 
 * text_destroy libera lo spazio di T, del suo alfabeto e di tutte le parole
 * raccolte.
 */
void text_destroy(struct text *T);

#endif /* TGUARD */
