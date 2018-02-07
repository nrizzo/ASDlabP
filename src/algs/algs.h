/*
 * github.com/nrizzo
 * src/algs/algs.c
 *
 * Intestazione del codice contenente gli algoritmi piu' importanti utilizzati
 * per l'algoritmo risolutivo.
 */

#ifndef ALGSGUARD /* guardia */
#define ALGSGUARD

/* 
 * alg_removeduplicates, dato il testo T, ne estrae le parole e restituisce una
 * lista delle parole di T senza doppioni; non modifica T.
 */
struct dl_list_w *alg_removeduplicates(struct text *T);

/* 
 * alg_joinanagrams, dato l'alfabeto S di T e la lista V dei nodi di G_T,
 * trasforma questi ultimi in nodi di G_T^*, "unendo" gli anagrammi tra di loro
 * (vedi node_join); non crea una nuova lista ma modifica V e restituisce il
 * puntatore alla lista modificata.
 */
struct dl_list_n *alg_joinanagrams(struct alphabet *S, struct dl_list_n *V);

/* 
 * alg_topologicalsort, data una lista di nodi di G_T o G_T^*, restituisce
 * la lista ordinata in modo decrescente secondo la lunghezza delle parole
 * corrispondenti ai nodi (#); cancella la lista data. 
 */
struct dl_list_n *alg_topologicalsort(struct dl_list_n *V);

/* 
 * alg_findedges, dato G_T o G_T^* contenente i suoi nodi ordinati
 * topologicamente, aggiunge tutti gli archi tra nodi secondo la relazione >=
 * tra vettori di caratteri nelle appropriate liste di adiacenza.
 */
void alg_findedges(struct graph *G_T);

/*
 * alg_findedges_v2 e' una versione modificata di alg_findedges, in cui gli
 * ordinamenti topologici sono tutti quelli secondo ogni carattere e tutti
 * quelli secondo ogni coppia di caratteri.
 */
void alg_findedges_v2(struct graph *G_T);

/* 
 * alg_findllp, dato G_T, calcola per ogni nodo la lunghezza massima dei
 * percorsi che partono da esso (utilizza node_setllp e node_getllp).
 */
void alg_findllp(struct graph *G_T);

#endif /* ALGSGUARD */
