/*
 * github.com/nrizzo
 * src/text/alpha/alpha.h
 *
 * Codice che gestisce l'alfabeto S = Sigma\{blank}.
 */

#include <stdlib.h> /* malloc e free */

#include "../utf8char/utf8char.h"
#include "alpha.h"

struct alphabet *alpha_create()
{
	struct alphabet *S = malloc(sizeof(struct alphabet));
	S->size = 0;
	S->chars = NULL;

	return S;
}

void alpha_addchar(struct alphabet *S, struct utf8_char *c)
{
	if (alpha_belongs(S,c) || utf8_isblank(c))
		return;

	S->size++;
	S->chars = realloc(S->chars,sizeof(struct utf8_char)*S->size);
	S->chars[S->size-1] = utf8_copy(c);
}

int alpha_size(struct alphabet *S)
{
	return S->size;
}

int alpha_indexof(struct alphabet *S, struct utf8_char *c)
{
	for (int i=0; i < S->size; i++) {
		if (utf8_equals(S->chars[i],c))
			return i;
	}

	return -1;
}

int alpha_belongs(struct alphabet *S, struct utf8_char *c)
{
	if (alpha_indexof(S,c) >= 0) /* se l'indice di c non e' negativo*/
		return 1;
	else 
		return 0;
}

void alpha_destroy(struct alphabet *S)
{
	for (int i=0; i < S->size; i++)
		utf8_destroy(S->chars[i]);

	free(S->chars);
	free(S);
}
