/*
 * github.com/nrizzo
 * src/algs/algs.c
 *
 * Codice contenente gli algoritmi importanti per l'algoritmo risolutivo.
 */

#include <stdlib.h> /* malloc e free */

#include "../text/utf8char/utf8char.h"
#include "../text/word/word.h"
#include "../text/alpha/alpha.h"
#include "../text/text.h"
#include "../list/list.h"
#include "../graph/cvector/cvector.h"
#include "../graph/node/node.h"
#include "../graph/graph.h"
#include "algs.h"
#include "aux.h"

struct dl_list_w *alg_removeduplicates(struct text *T)
{
	int max; /* lunghezza massima di una parola */
	int clength; /* lunghezza della parola corrente */
	struct dl_list_w *result; /* lista da restituire */
	struct dl_list_w *scan; /* elemento corrente */
	struct dl_list_w **buckets; /* secchielli per ogni lunghezza */

	/* Ricerca della # massima */
	max = 0;
	scan = text_get(T);
	while (!dllw_isempty(scan)) {
		clength = word_length(dllw_get(scan));

		if (clength > max)
			max = clength;

		scan = dllw_next(scan);
	}

	/* Inizializzazione dei secchielli */
	buckets = malloc(sizeof(struct dl_list_w)*(max+1));
	for (int i=1; i <= max; i++)
		buckets[i] = dllw_create();

	/* Immissione degli elementi nei secchielli */
	scan = text_get(T);
	while (!dllw_isempty(scan)) {
		clength = word_length(dllw_get(scan));
		buckets[clength] = dllw_add(buckets[clength],dllw_get(scan));

		scan = dllw_next(scan);
	}


	/* Creazione della lista ordinata e lettura dai secchielli */
	result = dllw_create();
	for (int i=max; i >= 1; i--) {
		buckets[i] = lexicographicalsort(T,buckets[i],i);
		buckets[i] = uniq(buckets[i]);

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

struct dl_list_n *alg_joinanagrams(struct alphabet *S, struct dl_list_n *V)
{
	int s = alpha_size(S);
	struct dl_list_n *prev;

	for (int i = s-1; i >= 0; i--) {
		prev = V;
		V = sortbycvector(S,V,i);
		dlln_destroy(prev);
	}

	V = uniqcv(V);

	return V;
}

struct dl_list_n *alg_topologicalsort(struct dl_list_n *V)
{
	int max; /* lunghezza della parola piu' lunga */
	int clength; /* lunghezza della parola corrente */
	struct dl_list_n *result; /* lista da restituire */
	struct dl_list_n *scan; /* elemento corrente */
	struct dl_list_n **buckets; /* secchielli per ogni lunghezza */

	/* Ricerca del # massimo */
	max = 0;
	scan = V;
	while (!dlln_isempty(scan)) {
		clength = word_length(node_getword(dlln_get(scan)));

		if (clength > max)
			max = clength;

		scan = dlln_next(scan);
	}

	/* Inizializzazione dei secchielli */
	buckets = malloc(sizeof(struct dl_list_w)*(max+1));
	for (int i=1; i <= max; i++)
		buckets[i] = dlln_create();

	/* Immissione dei nodi nei secchielli */
	scan = V;
	while (!dlln_isempty(scan)) {
		clength = word_length(node_getword(dlln_get(scan)));

		buckets[clength] = dlln_add(buckets[clength],dlln_get(scan));

		scan = dlln_next(scan);
	}

	/* Creazione della lista ordinata e lettura dai secchielli */
	result = dlln_create();
	for (int i=max; i >= 1; i--) {
		scan = buckets[i];

		while (!dlln_isempty(scan)) {
			result = dlln_add(result,dlln_get(scan));
			scan = dlln_next(scan);
		}

		dlln_destroy(buckets[i]);
	}

	dlln_destroy(V);
	free(buckets);
	return result;
}

void alg_findedges(struct graph *G_T)
{
	struct alphabet *S = G_T->S; /* alfabeto S=Sigma\{blank} */
	struct tsort_list *tops; /* gli ordinamenti topologici */
	struct dl_list_n *sorted; /* lista in costruzione */
	struct node *x; /* nodo corrente */
	struct tsort_list *tscan; /* lista di ordinamenti topologici */
	struct dl_list_n *queue; /* coda di elaborazione dei nodi */

	/* Costruzione degli ordinamenti */
	tops = tsl_create();
	for (int i=0; i < alpha_size(S); i++) {
		tops = tsl_add(tops,top_char(G_T,i));
	}

	if (G_T->V != NULL)
		tops = tsl_add(tops,pileup(G_T->V));

	/* Indicizzazione dei puntatori in tops per ogni nodo */
	findpointers(G_T->V,tops);

	/* Calcolo di minimi figli e minimi genitori per ogni nodo e ogni
	 *  ordinamento topologico in tops */
	tscan = tops;
	while (!tsl_isempty(tscan)) {
		calcminchildren(tsl_get(tscan));
		calcminparents(tsl_get(tscan));
		tscan = tsl_next(tscan);
	}

	/* Creazione della coda secondo cui processare i nodi */
	queue = queueup(G_T->V);

	/* Computazione degli archi */
	while (!dlln_isempty(queue)) {
		x = dlln_get(queue);

		calcchildren(x);
		calcparents(x);
		topsremove(tops,x);
		
		queue = dlln_remove(queue,queue);
	}

	tsl_destroy(tops);
	dlln_destroy(queue);
}

void alg_findedges_v2(struct graph *G_T)
{
	struct alphabet *S = G_T->S; /* alfabeto S=Sigma\{blank} */
	struct tsort_list *tops; /* gli ordinamenti topologici */
	struct dl_list_n *sorted; /* lista in costruzione */
	struct node *x; /* nodo corrente */
	struct tsort_list *tscan; /* ordinamento topologico impilato corrente */
	struct dl_list_n *queue; /* coda di elaborazione dei nodi */

	/* Costruzione degli ordinamenti */
	tops = tsl_create();
	for (int i=0; i < alpha_size(S); i++) {
		tops = tsl_add(tops,top_char(G_T,i));
	}

	if (G_T->V != NULL)
		tops = tsl_add(tops,pileup(G_T->V));

	/* Le seguenti righe di codice aggiungono agli ordinamenti anche
	 *  quelli basati su min(i,j) e max(i,j), per ogni coppia NON
	 *  ordinata (i,j) con i,j in Sigma e i!=j */
	for (int i=0; i < alpha_size(S); i++){
		for (int j=i; j < alpha_size(S); j++){
			tops = tsl_add(tops,top_min(G_T,i,j));
		}
	}
	for (int i=0; i < alpha_size(S); i++){
		for (int j=i; j < alpha_size(S); j++){
			tops = tsl_add(tops,top_max(G_T,i,j));
		}
	}
	
	/* Indicizzazione dei puntatori in tops per ogni nodo */
	findpointers(G_T->V,tops);

	/* Calcolo di minimi figli e minimi genitori per ogni nodo e ogni
	 *  ordinamento topologico in tops */
	tscan = tops;
	while (!tsl_isempty(tscan)) {
		calcminchildren(tsl_get(tscan));
		calcminparents(tsl_get(tscan));
		tscan = tsl_next(tscan);
	}

	/* Creazione della coda secondo cui processare i nodi */
	queue = queueup(G_T->V);

	/* Computazione degli archi */
	while (!dlln_isempty(queue)) {
		x = dlln_get(queue);

		calcchildren(x);
		calcparents(x);
		topsremove(tops,x);
		
		queue = dlln_remove(queue,queue);
	}

	tsl_destroy(tops);
	dlln_destroy(queue);
}

void alg_findllp(struct graph *G_T)
{
	struct dl_list_n *s; /* elemento della lista di V_T^* corrente */
	struct node *x; /* nodo corrente */
	struct dl_list_n *j; /*elemento della lista di adiacenza corrente*/
	struct node *y; /* figlio di x corrente */
	int c; /* lunghezza massima corrente */

	s = dlln_last(G_T->V);
	while (!dlln_isempty(s)) {
		x = dlln_get(s);

		node_setllp(x,0);

		j = node_adj(x);
		while (!dlln_isempty(j)) {
			y = dlln_get(j);

			c = node_getllp(y);
			if (c >= node_getllp(x))
				node_setllp( x, c+1 );

			j = dlln_next(j);
		}

		s = dlln_prev(s);
	}
}
