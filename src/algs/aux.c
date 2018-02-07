/*
 * github.com/nrizzo
 * src/algs/aux.c
 *
 * Codice delle procedure ausiliarie di algs.c.
 */

#include <stdlib.h>

#include "../text/utf8char/utf8char.h"
#include "../text/word/word.h"
#include "../text/alpha/alpha.h"
#include "../text/text.h"
#include "../list/list.h"
#include "../graph/cvector/cvector.h"
#include "../graph/node/node.h"
#include "../graph/graph.h"
#include "aux.h"

/* 
 * math_min e math_max restituiscono rispettivamente il minimo e il massimo tra
 * due interi.
 */
int math_min(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}
int math_max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

struct dl_list_w *lexicographicalsort(struct text *T, struct dl_list_w *list,
		int length)
{	/* list va eliminata */
	struct dl_list_w *prev;

	for (int j = length-1; j>=0; j--) {
		prev = list;
		list = sortbychar(T,list,j);
		dllw_destroy(prev);
	}

	return list;
}

struct dl_list_w *sortbychar(struct text *T, struct dl_list_w *list, int j)
{
	struct alphabet *S = text_getalpha(T); /* Sigma\{blank} */
	int maxchar; /* indice massimo di un carattere in S */
	int c; /* indice del carattere corrente in S */
	struct dl_list_w **buckets; /* secchielli per ogni carattere */
	struct dl_list_w *scan; /* elemento corrente */
	struct dl_list_w *result; /* risultato da restituire */
	struct word *tword; /* parola corrente */
	
	/* Ricerca della chiave massima */	
	maxchar = alpha_size(S);

	/* Inizializzazione dei secchielli */
	buckets = malloc(sizeof(struct dl_list_w)*(maxchar+1));
	for (int i=0; i <= maxchar; i++)
		buckets[i] = dllw_create();

	/* Immissione degli elementi nei secchielli */
	scan = list;
	while (!dllw_isempty(scan)) {
		tword = dllw_get(scan);

		c = alpha_indexof(S,word_charat(tword,j));
		buckets[c] = dllw_add(buckets[c],tword);

		scan = dllw_next(scan);
	}

	/* Creazione della lista ordinata e lettura dai secchielli */
	result = dllw_create();
	for (int i=0; i <= maxchar; i++) {
		scan = buckets[i];
		while (!dllw_isempty(scan)) {
			result = dllw_add(result,dllw_get(scan));
			scan = dllw_next(scan);
		}
		dllw_destroy(buckets[i]);
	}

	free(buckets);
	return result;
}

struct dl_list_w *uniq(struct dl_list_w *list)
{
	if (dllw_isempty(list))
		return list;

	struct dl_list_w *scan = list;
	struct dl_list_w *next;
	while (!dllw_istail(scan)) { /* finche' scan non e' la coda */
		next = dllw_next(scan);

		if (word_equals(dllw_get(scan),dllw_get(next)))
			scan = dllw_remove(list,next);
		else
			scan = next;
	}

	return list;
}

struct dl_list_n *sortbycvector(struct alphabet *S, struct dl_list_n *nodes,
		int i)
{
	struct dl_list_n *result;
	struct dl_list_n *scan;
	struct dl_list_n **buckets;
	int max = 0;
	int current;
	struct node *x;
	
	scan = nodes;
	while (!dlln_isempty(scan)) {
		current = cv_get(node_getcv(dlln_get(scan)),i);

		if (current > max)
			max = current;

		scan = dlln_next(scan);
	}

	buckets = malloc(sizeof(struct dl_list_n)*(max+1));
	for (int i=0; i <= max; i++)
		buckets[i] = dlln_create();

	scan = nodes;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		current = cv_get(node_getcv(x),i);
		buckets[current] = dlln_add(buckets[current],x);

		scan = dlln_next(scan);
	}

	result = dlln_create();
	for (int i=max; i >= 0; i--) {
		scan = buckets[i];
		while (!dlln_isempty(scan)) {
			x = dlln_get(scan);
			result = dlln_add(result,x);
			scan = dlln_next(scan);
		}
		dlln_destroy(buckets[i]);
	}

	free(buckets);
	return result;
}

struct dl_list_n *sortbycvectormin(struct alphabet *S, struct dl_list_n *nodes,
		int i, int j)
{
	struct dl_list_n *result;
	struct dl_list_n *scan;
	struct dl_list_n **buckets;
	int max = 0;
	int current;
	struct node *x;
	
	scan = nodes;
	while (!dlln_isempty(scan)) {
		current = math_min( cv_get(node_getcv(dlln_get(scan)),i),
			            cv_get(node_getcv(dlln_get(scan)),j) );
		if (current > max)
			max = current;

		scan = dlln_next(scan);
	}

	buckets = malloc(sizeof(struct dl_list_n)*(max+1));
	for (int a=0; a <= max; a++)
		buckets[a] = dlln_create();

	scan = nodes;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		current = math_min( cv_get(node_getcv(dlln_get(scan)),i),
			            cv_get(node_getcv(dlln_get(scan)),j) );
		buckets[current] = dlln_add(buckets[current],x);

		scan = dlln_next(scan);
	}

	result = dlln_create();
	for (int b=max; b >= 0; b--) {
		scan = buckets[b];
		while (!dlln_isempty(scan)) {
			x = dlln_get(scan);
			result = dlln_add(result,x);
			scan = dlln_next(scan);
		}
		dlln_destroy(buckets[b]);
	}

	free(buckets);
	return result;
}

struct dl_list_n *sortbycvectormax(struct alphabet *S, struct dl_list_n *nodes,
		int i, int j)
{
	struct dl_list_n *result;
	struct dl_list_n *scan;
	struct dl_list_n **buckets;
	int max = 0;
	int current;
	struct node *x;
	
	scan = nodes;
	while (!dlln_isempty(scan)) {
		current = math_max( cv_get(node_getcv(dlln_get(scan)),i),
			            cv_get(node_getcv(dlln_get(scan)),j) );
		if (current > max)
			max = current;

		scan = dlln_next(scan);
	}

	buckets = malloc(sizeof(struct dl_list_n)*(max+1));
	for (int a=0; a <= max; a++)
		buckets[a] = dlln_create();

	scan = nodes;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		current = math_max( cv_get(node_getcv(dlln_get(scan)),i),
			            cv_get(node_getcv(dlln_get(scan)),j) );
		buckets[current] = dlln_add(buckets[current],x);

		scan = dlln_next(scan);
	}

	result = dlln_create();
	for (int b=max; b >= 0; b--) {
		scan = buckets[b];
		while (!dlln_isempty(scan)) {
			x = dlln_get(scan);
			result = dlln_add(result,x);
			scan = dlln_next(scan);
		}
		dlln_destroy(buckets[b]);
	}

	free(buckets);
	return result;
}

struct dl_list_n *uniqcv(struct dl_list_n *V)
{
	struct dl_list_n *scan;
	struct dl_list_n *next;
	struct cvector *xcv, *ycv;

	if (dlln_isempty(V))
		return V;

	scan = V;
	while (!dlln_istail(scan)) {
		next = dlln_next(scan);
		xcv = node_getcv(dlln_get(scan));
		ycv = node_getcv(dlln_get(next));
		if (cv_equals(xcv,ycv)) {
			node_join(dlln_get(scan),dlln_get(next));
			node_destroy(dlln_get(next));
			V = dlln_remove(V,next);
		} else {
			scan = dlln_next(scan);
		}
	}

	return V;
}

struct dll_list_n *top_char(struct graph *G_T, int i)
{
	struct dl_list_n *p; /* risultato parziale */
	struct dll_list_n *res; /* risultato */

	p = sortbycvector(G_T->S,G_T->V,i);
	res = pileup(p);
	dlln_destroy(p);

	return res;
}

struct dll_list_n *top_min(struct graph *G_T, int i, int j)
{
	struct dl_list_n *p;
	struct dll_list_n *res;

	p = sortbycvectormax(G_T->S,G_T->V,i,j);
	res = pileup(p);
	dlln_destroy(p);

	return res;
}

struct dll_list_n *top_max(struct graph *G_T, int i, int j)
{
	struct dl_list_n *p;
	struct dll_list_n *res;

	p = sortbycvectormin(G_T->S,G_T->V,i,j);
	res = pileup(p);
	dlln_destroy(p);

	return res;
}

void findpointers(struct dl_list_n *V, struct tsort_list *tops)
{
	struct tsort_list *ssscan;
	struct dll_list_n *sscan;
	struct dl_list_n *scan;
	struct node *x;

	int k = 0;
	ssscan = tops;
	while (!tsl_isempty(ssscan)) {
		k++;
		ssscan = tsl_next(ssscan);
	}
	
	scan = V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);
		x->pile = malloc(sizeof(struct dll_list_n)*(k));
		x->elementi = malloc(sizeof(struct dl_list_n)*(k));
		scan = dlln_next(scan);
	}

	ssscan = tops;
	int i=0;
	while (!tsl_isempty(ssscan)) {
		sscan = tsl_get(ssscan);
		while (!dllln_isempty(sscan)) {
			scan = dllln_get(sscan);
			while (!dlln_isempty(scan)) {
				x = dlln_get(scan);
				x->pile[i] = sscan;
				x->elementi[i] = scan;

				scan = dlln_next(scan);
			}
			sscan = dllln_next(sscan);
		}
		ssscan = tsl_next(ssscan);
		i++;
	}
}

struct dll_list_n *pileup(struct dl_list_n *sorted)
{
	struct dll_list_n *result;
	struct dl_list_n *scan;
	int last = 0;
	struct node *x;

	result = dllln_create();
	scan = sorted;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);

		if (word_length(node_getword(x)) != last) {
			result = dllln_newpile(result,x);
			last = word_length(node_getword(x));
		} else {
			result = dllln_add(result,x);
		}

		scan = dlln_next(scan);
	}

	return result;
}

void calcminchildren(struct dll_list_n *top)
{	/* top ordinamento topologico "impilato" */
	struct dll_list_n *sscan; /* pila corrente */
	struct dl_list_n *scan; /* elemento corrente */
	struct node *x; /* nodo corrente */
	int children; /* nodi a destra in top */
	int pila; /* nodi nella pila corrente */

	children = 0;
	pila = 0;
	sscan = dllln_last(top);
	while (!dllln_isempty(sscan)) {
		scan = dllln_get(sscan);

		while (!dlln_isempty(scan)) {
			x = dlln_get(scan);

			if (children < x->pchildren) {
				x->pchildren = children;
				x->max = sscan;
			}

			pila++;
			scan = dlln_next(scan);
		}

		children = children + pila;

		pila = 0;
		sscan = dllln_prev(sscan);
	}
}

void calcminparents(struct dll_list_n *top)
{	/* top ordinamento topologico "impilato" */
	struct dll_list_n *sscan; /* pila corrente */
	struct dl_list_n *scan; /* elemento corrente */
	struct node *x; /* nodo corrente */
	int parents; /* nodi a sinistra in top */
	int pila; /* nodi nella pila corrente */

	parents = 0;
	pila = 0;
	sscan = top;
	while (!dllln_isempty(sscan)) {
		scan = dllln_get(sscan);

		while (!dlln_isempty(scan)) {
			x = dlln_get(scan);

			if (parents < x->pparents) {
				x->pparents = parents;
				x->min = sscan;
			}

			pila++;
			scan = dlln_next(scan);
		}

		parents = parents + pila;

		pila = 0;
		sscan = dllln_next(sscan);
	}
}
struct dl_list_n *queueup(struct dl_list_n *V)
{
	int max; /* somma massima di possibili figli e genitori */
	int c; /* somma corrente */
	struct dl_list_n *result; /* lista da restituire */
	struct dl_list_n *scan; /* elemento corrente */
	struct node *x; /* nodo dell'elemento corrente */
	struct dl_list_n **buckets; /* secchielli per ogni somma */

	/* Ricerca della somma massima */
	max = 0;
	scan = V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);
		c = x->pchildren + x->pparents;

		if (c > max)
			max = c;

		scan = dlln_next(scan);
	}

	/* Inizializzazione dei secchielli */
	buckets = malloc(sizeof(struct dl_list_n)*(max+1));
	for (int i=0; i <= max; i++)
		buckets[i] = dlln_create();

	/* Immissione degli elementi nei secchielli */
	scan = V;
	while (!dlln_isempty(scan)) {
		x = dlln_get(scan);
		c = x->pchildren + x->pparents;

		buckets[c] = dlln_add(buckets[c],x);

		scan = dlln_next(scan);
	}

	/* Creazione della lista ordinata e lettura dai secchielli */
	result = dlln_create();
	for (int i=0; i <= max; i++) {
		scan = buckets[i];

		while (!dlln_isempty(scan)) {
			result = dlln_add(result,dlln_get(scan));
			scan = dlln_next(scan);
		}

		dlln_destroy(buckets[i]);
	}
	
	free(buckets);
	return result;
}

void calcchildren(struct node *x)
{
	struct dll_list_n *sscan;
	struct dl_list_n *scan;
	struct node *y;
	int xlength, ylength;
	struct cvector *xcv, *ycv;

	sscan = dllln_next(x->max);
	while (!dllln_isempty(sscan)) {
		scan = dllln_get(sscan);

		while (!dlln_isempty(scan)) {
			y = dlln_get(scan);
			xlength = word_length(node_getword(x));
			ylength = word_length(node_getword(y));
			xcv = node_getcv(x);
			ycv = node_getcv(y);

			if (xlength > ylength && cv_rel(xcv,ycv))
				node_addarc(x,y);

			scan = dlln_next(scan);
		}

		sscan = dllln_next(sscan);
	}
}

void calcparents(struct node *x)
{
	struct dll_list_n *sscan;
	struct dl_list_n *scan;
	struct node *y;
	int xlength, ylength;
	struct cvector *xcv, *ycv;

	sscan = dllln_prev(x->min);
	while (!dllln_isempty(sscan)) {
		scan = dllln_get(sscan);

		while (!dlln_isempty(scan)) {
			y = dlln_get(scan);
			xlength = word_length(node_getword(x));
			ylength = word_length(node_getword(y));
			xcv = node_getcv(x);
			ycv = node_getcv(y);

			if (xlength < ylength && cv_rel(ycv,xcv))
				node_addarc(y,x);

			scan = dlln_next(scan);
		}

		sscan = dllln_prev(sscan);
	}
}

void topsremove(struct tsort_list *tops, struct node *x)
{
	struct dll_list_n *current;
	
	int i = 0;
	while (!tsl_isempty(tops)) {
		current = tsl_get(tops);

		current = dllln_remove(current,x->pile[i],x->elementi[i]);
		tsl_set(tops,current);

		i++;
		tops = tsl_next(tops);
	}
}
