/*
 * github.com/nrizzo
 * src/text/word/word.c
 *
 * Codice per la creazione di parole, la loro gestione e informazioni a
 * riguardo. Le parole vengono composte un carattere UTF-8 alla volta.
 */

#include <stdlib.h> /* free e malloc */

#include "../utf8char/utf8char.h"
#include "word.h"

struct word *word_create()
{
	struct word *w = malloc(sizeof(struct word));

	w->write = 0;
	w->bsize = DEFAULT_WBSIZE;
	w->buffer = malloc(w->bsize * sizeof(struct utf8_char));

	return w;
}

void word_addchar(struct word *w, struct utf8_char *c)
{
	if (w->write >= w->bsize) { /* se il buffer e' pieno */
		w->bsize = w->bsize * 2;
		w->buffer=realloc(w->buffer,w->bsize*sizeof(struct utf8_char));
	}
	w->buffer[w->write] = c;
	w->write++;
}

void word_finalize(struct word *w)
{
	if (w->write == w->bsize-1)
		return;

	w->buffer = realloc(w->buffer,(w->write+1)*sizeof(struct utf8_char));
	w->bsize = -1;
}

int word_length(struct word *w)
{
	return w->write;
}

struct utf8_char *word_charat(struct word *w, int i)
{
	return w->buffer[i];
}

int word_equals(struct word *w1, struct word *w2)
{
	if (word_length(w1)!=word_length(w2)) /* se hanno lunghezza diversa */
		return 0;

	for (int i=0; i<word_length(w1); i++) {
		if (!utf8_equals(w1->buffer[i],w2->buffer[i]))
			/* se i loro i-esimi caratteri differiscono */
			return 0;
	}

	return 1;
}

void word_print(struct word *w)
{
	for (int i=0; i < word_length(w); i++)
		utf8_putchar(w->buffer[i]);
}

void word_destroy(struct word *w)
{
	for (int i=0; i < w->write; i++)
		utf8_destroy(w->buffer[i]);

	free(w->buffer);
	free(w);
}
