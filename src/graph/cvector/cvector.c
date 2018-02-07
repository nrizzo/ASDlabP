/*
 * github.com/nrizzo
 * src/graph/cvector/cvector.c
 *
 * Codice che gestisce il vettore dei caratteri di una parola.
 */

#include <stdlib.h>

#include "../../text/word/word.h"
#include "../../text/alpha/alpha.h"
#include "cvector.h"

struct cvector *cv_create(struct alphabet *S, struct word *w)
{
	struct cvector *wcv = malloc(sizeof(struct cvector));

	wcv->length = alpha_size(S);
	wcv->count = malloc(sizeof(int)*wcv->length);

	for (int i=0; i < wcv->length; i++)
		wcv->count[i] = 0;

	for (int i=0; i < word_length(w); i++)
		wcv->count[ alpha_indexof(S,word_charat(w,i)) ]++;

	return wcv;
}

int cv_rel(struct cvector *u1, struct cvector *u2)
{
	for (int i=0; i < u1->length; i++) {
		if (u1->count[i] < u2->count[i])
			return 0;
	}

	return 1;
}

int cv_get(struct cvector *u, int c)
{
	return u->count[c];
}

int cv_equals(struct cvector *cv1, struct cvector *cv2)
{
	for (int i=0; i < cv1->length; i++) {
		if (cv1->count[i] != cv2->count[i])
			return 0;
	}

	return 1;
}

void cv_destroy(struct cvector *u)
{
	free(u->count);
	free(u);	
}
