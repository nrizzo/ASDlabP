/*
 * github.com/nrizzo
 * src/graph/graph.h
 *
 * Intestazione del codice che si occupa della costruzione e manipolazione di
 * G_T e G_T^*.
 */

#ifndef GGUARD /* guardia */
#define GGUARD

/* 
 * Struct che rappresenta G_T o G_T^*, a cui e' associato l'alfabeto di T
 * S=Sigma\{blank}. Gli archi del grafo sono contenuti nelle liste di adiacenza
 * dei singoli nodi.
 */
struct graph{
	struct alphabet *S;
	int v; /* cardinalita' di V */
	int e; /* numero di archi */
	struct dl_list_n *V;

	int maxllp; /* lunghezza del percorso massimo */
};

/* 
 * graph_create crea e restituisce il puntatore di un grafo vuoto ma collegato
 * all'alfabeto di T. Va accoppiata a graph_destroy per liberarne lo spazio
 * occupato.
 */
struct graph *graph_create(struct text *T);

/* 
 * graph_retrievenodes, dato G_T e la lista delle parole di T senza doppioni
 * words, costruisce per ogni parola di words un nodo di G_T.
 */
void graph_retrievenodes(struct graph *G_T, struct dl_list_w *words);

/* 
 * graph_joinanagrams, dato il grafo in costruzione G_T contenente solo nodi,
 * "unisce" i gruppi di anagrammi in un nodo solo, trasformando G_T in G_T^*.
 */
void graph_joinanagrams(struct graph *G_T);

/*
 * graph_topologicalsort, dato G_T o G_T^*, mette in ordine i nodi in V_T o
 * V_T^* in modo che siano in ordinamento topologico secondo la relazione tra
 * vettori di caratteri.
 */
void graph_topologicalsort(struct graph *G_T);

/* 
 * graph_findedges, dato G_T o G_T^* contenente solo nodi, trova tutti gli archi
 * di G_T e li aggiunge nelle corrette liste di adiacenza.
 */
void graph_findedges(struct graph *G_T);
void graph_findedges_v2(struct graph *G_T);

/* 
 * graph_findllp, dato G_T o G_T^*, trova (e salva) la lunghezza massima di un
 * percorso in G_T o G_T^*.  
 */
void graph_findllp(struct graph *G_T);

/*
 * graph_printllp stampa la lunghezza massima di un percorso in G_T o G_T^*
 * trovata da graph_findllp.
 */
void graph_printllp(struct graph *G_T);

/* 
 * graph_printDOT, dato G_T o G_T^*, stampa il grafo G_T in formato DOT.
 */
void graph_printDOT(struct graph *G_T);

/*
 * graph_debug_print, dato G_T o G_T^*, stampa tutti i suoi archi con il formato
 * "parola1 -> parola2".
 */
void graph_debug_print(struct graph *G_T);

/* 
 * graph_destroy elimina il grafo, liberando anche lo spazio occupato dai nodi,
 * ma non quello occupato dall'alfabeto di T o da T.
 */
void graph_destroy(struct graph *G_T);

/*
 * graph_calcedges scorre tutti i nodi di G_T o G_T^* e le loro liste di
 * adiacenza per calcolare il numero di archi di G_T, che salva nella variabile
 * G_T->e.
 */
void graph_calcedges(struct graph *G_T);

/*
 * graph_edges restituisce il numero di archi trovato da graph_calcedges.
 */
int graph_edges(struct graph *G_T);

/*
 * graph_vertices, dato G_T o G_T^*, restituisce il numero di nodi di G_T.
 */
int graph_vertices(struct graph *G_T);

#endif /* GGUARD */
