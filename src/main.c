/*
 * github.com/nrizzo
 * src/main.c
 *
 * Codice dell'algoritmo risolutivo.
 */

#include "text/word/word.h"
#include "text/text.h"
#include "list/list.h"
#include "graph/graph.h"
#include "algs/algs.h"
#include "text/alpha/alpha.h"

int main()
{
	/* Creazione iniziale delle strutture */
	struct text *T = text_create(); /* testo (di parole) e alfabeto*/
	struct dl_list_w *words; /* lista delle parole */
	struct graph *G_T = graph_create(T); /* grafo G_T */

	/* Ottenimento del testo e dell'alfabeto */
	text_retrieve(T);
	/* Ottenimento lista delle parole senza doppioni */
	words = alg_removeduplicates(T);
	/* Immissione dei nodi nel grafo */
	graph_retrievenodes(G_T,words);
	/* Trasformazione di V_T in V_T^* (unione degli anagrammi) */
	graph_joinanagrams(G_T);
	/* Ordinamento topologico dei nodi di G_T^* */
	graph_topologicalsort(G_T);
	/* Calcolo degli archi */
	graph_findedges(G_T);
	/* Calcolo della lunghezza massima dei percorsi in G_T^* */
	graph_findllp(G_T);

	/* Output dei risultati */
	graph_printllp(G_T); /* lunghezza del percorso massimo */
	graph_printDOT(G_T); /* grafo in formato DOT */

	/* Distruzione delle strutture */
	graph_destroy(G_T);
	dllw_destroy(words);
	text_destroy(T);
}
