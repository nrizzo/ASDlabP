/*
 * github.com/nrizzo
 * src/text/text.c
 *
 * Codice per gestire un testo di parole separate da uno o piu' spazi.
 */

#include <stdlib.h> /* malloc, realloc e free */

#include "alpha/alpha.h"
#include "utf8char/utf8char.h"
#include "word/word.h"
#include "../list/list.h"
#include "text.h"

struct text *text_create()
{
	struct text *T = malloc(sizeof(struct text));
	
	T->S = alpha_create();
	T->n = 0;
	T->words = dllw_create();

	return T;
}

void text_retrieve(struct text *T)
{
	struct utf8_char *c = utf8_create(); /* carattere corrente */
	struct word *w = word_create(); /* parola corrente in costruzione */

	while (!utf8_getchar(c)) { /* finche' ci sono caratteri da leggere */
		if (!utf8_isblank(c)) {
			alpha_addchar(T->S,c);
			word_addchar(w,c);
		} else if (word_length(w)>0) {
			word_finalize(w);

			T->n++;
			T->words = dllw_add(T->words,w);

			w = word_create();
		}

		c = utf8_create();
	}
	utf8_destroy(c);
	
	if (word_length(w)>0) { /* se c'era ancora una parola in costruzione */
		word_finalize(w);
		
		T->n++;
		T->words = dllw_add(T->words,w);
	} else {
		word_destroy(w);
	}
}

int text_size(struct text *T)
{
	return T->n;
}

struct alphabet *text_getalpha(struct text *T)
{
	return T->S;
}

struct dl_list_w *text_get(struct text *T)
{
	return T->words;
}

void text_destroy(struct text *T)
{
	struct dl_list_w *scan;

	alpha_destroy(T->S);

	scan = T->words;
	while (!dllw_isempty(scan)) {
		word_destroy(dllw_get(scan));
		scan = dllw_next(scan);
	}

	dllw_destroy(T->words);
	free(T);
}
