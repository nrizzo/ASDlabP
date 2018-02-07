/*
 * github.com/nrizzo
 * src/graph/node/node.h
 *
 * Intestazione del codice che implementa i nodi di G_T (e G_T^*) con le
 * rispettive liste di adiacenza e i dati ausiliari all'algoritmo risolutivo e
 * alla stampa dei risultati.
 */

#ifndef NDGUARD /* guardia */
#define NDGUARD

#include "../../list/list.h"

/* 
 * Struct che implementa un nodo del grafo G_T (e G_T^*) con lista di adiacenza
 * e dati ausiliari. 
 */
struct node {
	struct word *w; /* parola */
	struct cvector *cv; /* vettore dei caratteri */

	int outdegree; /* numero di figli */
	struct dl_list_n *adj; /* lista di adiacenza */

	/* Trasformazione in G_T^* */
	int n; /* numero di anagrammi */
	struct dl_list_w *anagrams; /* lista degli anagrammi */

	/* Gestione di ordinamenti topologici */
	int pchildren; /* figli possibili */
	int pparents; /* padri possibili */
	struct dll_list_n **pile; /* puntatori alle pile */
	struct dl_list_n **elementi; /* puntatori agli elementi nelle pile */
	struct dll_list_n *min; /* pila con il minore */
	struct dll_list_n *max; /* pila con il maggiore */

	/* Calcolo della lunghezza massima dei percorsi */
	int llp; /* lunghezza cammino massimo da questo nodo */

	/* Stampa dei risultati */
	int DOTindex; /* indice nel grafo DOT */
};

/*
 * node_create, dato l'alfabeto S=Sigma\{blank} di T e una parola w di T, crea
 * e restituisce il puntatore del nodo, senza archi, corrispondente alla parola
 * w, creando anche il suo vettore dei caratteri. Va accoppiata a node_destroy
 * per liberarne lo spazio.
 */
struct node *node_create(struct alphabet *S, struct word *w);

/*
 * node_join "unisce" due nodi x e y, eliminando il secondo e aggiungendo la
 * parola corrispondente agli anagrammi di y.
 */
void node_join(struct node *x, struct node *y);

/*
 * node_addarc aggiunge y nella lista di adiacenza di x.
 */
void node_addarc(struct node *x, struct node *y);

/*
 * node_getword restituisce la parola corrispondente al nodo x.
 */
struct word *node_getword(struct node *x);

/*
 * node_getcv restituisce il vettore dei caratteri corrispondente al nodo x.
 */
struct cvector *node_getcv(struct node *x);

/*
 * node_outdegree restituisce il numero di figli di x.
 */
int node_outdegree(struct node *x);

/*
 * node_adj restituisce la lista di adiacenza del nodo x.
 */
struct dl_list_n *node_adj(struct node *x);

/*
 * node_anagrams restituisce la lista di anagrammi della parola corrispondente
 * a x (che fa da rappresentante del gruppo di anagrammi).
 */
struct dl_list_w *node_anagrams(struct node *x);

/*
 * node_n restituisce la cardinalita' della lista di anagrammi.
 */
int node_n(struct node *x);

/*
 * node_setllp imposta l'intero rappresentante la lunghezza massima dei
 * percorsi da x nel grafo a length.
 */
void node_setllp(struct node *x, int length);

/*
 * node_getllp restituisce la lunghezza massima impostata dei percorsi da x nel
 * grafo.
 */
int node_getllp(struct node *x);

/*
 * node_setDOTindex imposta l'indice di x a i per la stampa del grafo in
 * formato DOT.
 */
void node_setDOTindex(struct node *x, int i);

/*
 * node_getDOTindex restituisce l'indice di x per la stampa del grafo in formato
 * DOT.
 */
int node_getDOTindex(struct node *x);

/*
 * node_destroy elimina il nodo e tutte le informazioni associate, tranne per la
 * sua parola.
 */
void node_destroy(struct node *x);

#endif /* NDGUARD */
