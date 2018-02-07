/*
 * github.com/nrizzo
 * src/graph/node/node.c
 *
 * Codice che implementa i nodi di G_T (e G_T^*) con le rispettive liste di
 * adiacenza e i dati ausiliari all'algoritmo risulivo e alla stampa dei
 * risultati.
 */

#include <stdlib.h> /* malloc e free */
#include <limits.h> /* INT_MAX */

#include "../../text/word/word.h"
#include "../../text/alpha/alpha.h"
#include "../cvector/cvector.h"
#include "node.h"
#include "../../list/list.h"

struct node *node_create(struct alphabet *S, struct word *w)
{
	struct node *x = malloc(sizeof(struct node));

	x->w = w;
	x->cv = cv_create(S,w);

	x->outdegree = 0;
	x->adj = dlln_create();

	/* valori predefiniti */
	x->n = 0;
	x->anagrams = dllw_create();

	x->llp = 0;

	x->pchildren = INT_MAX;
	x->pparents = INT_MAX;
	x->pile = NULL;
	x->elementi = NULL;
	x->min = NULL;
	x->max = NULL;

	return x;
}

void node_join(struct node *x, struct node *y)
{
	x->n++;
	x->anagrams = dllw_add(x->anagrams,y->w);
}

void node_addarc(struct node *x, struct node *y)
{
	x->outdegree++;
	x->adj = dlln_add(x->adj,y);
}

struct word *node_getword(struct node *x)
{
	return x->w;
}

struct cvector *node_getcv(struct node *x)
{
	return x->cv;
}

int node_outdegree(struct node *x)
{
	return x->outdegree;
}

struct dl_list_n *node_adj(struct node *x)
{
	return x->adj;
}

int node_n(struct node *x)
{
	return x->n;
}

struct dl_list_w *node_anagrams(struct node *x)
{
	return x->anagrams;
}

void node_setllp(struct node *x, int length)
{
	x->llp = length;
}

int node_getllp(struct node *x)
{
	return x->llp;
}

void node_setDOTindex(struct node *x, int i)
{
	x->DOTindex = i;
}

int node_getDOTindex(struct node *x)
{
	return x->DOTindex;
}

void node_destroy(struct node *x)
{
	dlln_destroy(x->adj);
	cv_destroy(x->cv);
	dllw_destroy(x->anagrams);
	free(x->pile);
	free(x->elementi);
	free(x);
}
