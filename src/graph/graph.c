/*
 * github.com/nrizzo
 * /src/graph/graph.c
 *
 * Codice che si occupa della costruzione e manipolazione di G_T e G_T^*.
 */

#include <stdlib.h> /* malloc e free */
#include <stdio.h> /* printf */

#include "../text/word/word.h"
#include "../text/text.h"
#include "node/node.h"
#include "../list/list.h"
#include "graph.h"
#include "../algs/algs.h"

struct graph *graph_create(struct text *T)
{
	struct graph *G_T = malloc(sizeof(struct graph));

	G_T->S = text_getalpha(T);
	G_T->v = 0;
	G_T->e = 0;
	G_T->V = dlln_create();
	G_T->maxllp = 0;

	return G_T;
}

void graph_retrievenodes(struct graph *G_T, struct dl_list_w *words)
{
	struct node *x; /* vertice corrente */
	struct dl_list_w *scan; /* elemento corrente di words */

	scan = words;
	while (!dllw_isempty(scan)) {

		x = node_create(G_T->S,dllw_get(scan));
		G_T->V = dlln_add(G_T->V, x );
		G_T->v++;

		scan = dllw_next(scan);
	}
}

void graph_joinanagrams(struct graph *G_T)
{
	G_T->V = alg_joinanagrams(G_T->S,G_T->V);
}

void graph_topologicalsort(struct graph *G_T)
{
	G_T->V = alg_topologicalsort(G_T->V);
}

void graph_findedges(struct graph *G_T)
{
	alg_findedges(G_T);
}

void graph_findedges_v2(struct graph *G_T)
{
	alg_findedges_v2(G_T);
}

void graph_findllp(struct graph *G_T)
{
	int maxllp = 0; /* massimo */
	int c; /* llp corrente */
	struct dl_list_n *scan; /* vertice di G_T */

	if (dlln_isempty(G_T->V))
		return;

	alg_findllp(G_T);

	scan = G_T->V;
	while (!dlln_isempty(scan))
	{
		c = node_getllp(dlln_get(scan));

		if (c > maxllp)
			maxllp = c;

		scan = dlln_next(scan);
	}

	G_T->maxllp = maxllp;
}

void graph_printllp(struct graph *G_T)
{
	printf("%d\n",G_T->maxllp);
}

void graph_printDOT(struct graph *G_T)
{
	int i = 0; /* indice del vertice e anche il suo nome nel formato DOT */
	struct dl_list_n *scan; /* elemento corrente della lista dei vertici */
	struct dl_list_n *t,*u; /* elemento corrente della lista di adiacenza */
	struct dl_list_w *w; /* elemento corrente della lista di anagrammi */
	struct node *x,*y; /* vertice corrente */

	printf("digraph G_T {\n");

	/* stampa V_T */
	scan = G_T->V;
	while (!dlln_isempty(scan)) {

		x = dlln_get(scan);

		/* rappresentante */
		node_setDOTindex(x,i);
		printf("%d [label=\"", i++ );
		word_print(node_getword(x));
		printf("\"];\n");

		/* anagrammi */
		w = node_anagrams(x);
		while (!dllw_isempty(w)) {

			printf("%d [label=\"", i++ );
			word_print(dllw_get(w));
			printf("\"];\n");

			w = dllw_next(w);
		}

		scan = dlln_next(scan);
	}

	/* stampa E_T */
	scan = G_T->V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		t = node_adj(x);
		while (!dlln_isempty(t)) {
			y = dlln_get(t);

			for (int j=0; j<=node_n(x); j++) {
				for (int k=0; k<=node_n(y); k++) {
					printf("%d",node_getDOTindex(x)+j);
					printf(" -> ");
					printf("%d",node_getDOTindex(y)+k);
					printf(";\n");
				}
			}

			t = dlln_next(t);
		}

		scan = dlln_next(scan);
	}

	printf("}\n");
}

void graph_debug_print(struct graph *G_T)
{
	int i = 0; /* indice del vertice (e anche il suo nome) */
	struct dl_list_n *scan; /* elemento corrente della lista dei vertici */
	struct dl_list_n *t,*u; /* elemento corrente della lista di adiacenza */
	struct dl_list_w *w,*z; /* elemento corrente della lista di anagrammi */
	struct node *x,*y; /* vertice corrente */

	scan = G_T->V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		t = node_adj(x);
		while (!dlln_isempty(t)) {
			y = dlln_get(t);

			/* arco x -> y */
			word_print(node_getword(x));
			printf(" -> ");
			word_print(node_getword(y));
			printf("\n");

			/* ogni arco x -> y* */
			w = node_anagrams(y);
			while (!dllw_isempty(w)) {
				word_print(node_getword(x));
				printf(" -> ");
				word_print(dllw_get(w));
				printf("\n");

				w = dllw_next(w);
			}

			/* ogni arco x* -> y */
			w = node_anagrams(x);
			while (!dllw_isempty(w)) {
				word_print(dllw_get(w));
				printf(" -> ");
				word_print(node_getword(y));
				printf("\n");

				w = dllw_next(w);
			}

			/* ogni arco x* -> y* */
			w = node_anagrams(x);
			while (!dllw_isempty(w)) {

				z = node_anagrams(y);
				while (!dllw_isempty(z)) {

					word_print(dllw_get(w));
					printf(" -> ");
					word_print(dllw_get(z));
					printf("\n");

					z = dllw_next(z);
				}

				w = dllw_next(w);
			}

			t = dlln_next(t);
		}

		scan = dlln_next(scan);
	}
}

void graph_destroy(struct graph *G_T)
{
	struct dl_list_n *scan; /* vertice corrente */

	scan = G_T->V;
	while (!dlln_isempty(scan)) {
		node_destroy(dlln_get(scan));
		scan = dlln_remove(scan,scan);
	}

	dlln_destroy(scan);
	free(G_T);
}

void graph_calcedges(struct graph *G_T)
{
	/* I nodi sono quelli di G_T^*! */
	struct dl_list_n *scan; /* per scandire la lista */
	struct node *x;

	G_T->e = 0;

	scan = G_T->V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		G_T->e = G_T->e + (node_outdegree(x)*(1+node_n(x)));

		scan = dlln_next(scan);
	}
}

int graph_edges(struct graph *G_T)
{
	return G_T->e;
}

int graph_vertices(struct graph *G_T)
{
	int result = 0;
	struct dl_list_n *scan;

	scan = G_T->V;
	while (!dlln_isempty(scan)) {
		result = result + 1 + node_n(dlln_get(scan));
		scan = dlln_next(scan);
	}

	return result;
}
