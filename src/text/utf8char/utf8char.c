/*
 * github.com/nrizzo
 * src/text/utf8char/utf8char.c
 *
 * Codice della piccola libreria per la lettura da standard
 * input, la gestione e il confronto di caratteri codificati in UTF-8.
 */

#include <stdio.h> /* getchar e putchar */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */

#include "utf8char.h"

struct utf8_char *utf8_create()
{
	struct utf8_char *c = malloc(sizeof(struct utf8_char));
	c->bytes = 0;
	c->chr = NULL;
	return c;
}

struct utf8_char *utf8_copy(struct utf8_char *c)
{
	struct utf8_char *newcopy = malloc(sizeof(struct utf8_char));

	newcopy->bytes = c->bytes;
	newcopy->chr = malloc(sizeof(char)*newcopy->bytes);
	strncpy(newcopy->chr,c->chr,newcopy->bytes);

	return newcopy;
}

int utf8_getchar(struct utf8_char *c)
{
	int current; /* byte corrente */
	current = getchar();

	if (current == EOF) /* se il testo e' finito */
		return -1;

	/* altrimenti current e' il primo byte di un carattere */
	c->bytes = 1;
	c->chr = malloc(sizeof(char));
	c->chr[0] = current;

	/* se il primo bit e' 0 allora e' ASCII */
	if ((c->chr[0]&128)>>7 == 0)
		return 0;

	/* altrimenti e' UTF-8 e per ogni altro bit (successivo al primo) uguale
	 * a 1 c'e' un altro byte da leggere */
	for (int i=1; (c->chr[0]<<i>>7)&1; i++) { /* l'i+1-esimo bit */
		current = getchar();

		if (current == EOF)/* il testo e' finito prematuramente, ci */
			return -2; /* deve essere un errore nella codifica! */

		c->chr = realloc(c->chr,(c->bytes+1)*sizeof(char));
		c->chr[c->bytes] = current;
		c->bytes++;
	}

	return 0;
}

void utf8_putchar(struct utf8_char *c)
{
	for (int i=0; i<c->bytes; i++)
		putchar(c->chr[i]);
}

int utf8_isblank(struct utf8_char *c)
{
	return (c->bytes==1 && c->chr[0]==' ');
}

int utf8_equals(struct utf8_char *a, struct utf8_char *b)
{
	if (a->bytes != b->bytes)
		return 0;

	for (int i=0; i<a->bytes; i++) {
		if (a->chr[i] != b->chr[i])
			return 0;
	}

	return 1;
}

void utf8_destroy(struct utf8_char *c)
{
	free(c->chr);
	free(c);
}
