/*
 * github.com/nrizzo
 * src/list/list.h
 *
 * Intestazione del codice che implementa liste doppiamente concatenate con
 * puntatore all'ultimo elemento (aggiornato solo in testa) e procedure per
 * gestirle.
 * 
 * Tutte le liste sono rappresentate dal loro elemento in testa. La lista vuota
 * e l'elemento vuoto sono rappresentati da NULL. In generale supportano le
 * seguenti procedure:
 *
 *  - create() restituisce una lista vuota
 *  - add(list,a) aggiunge a in coda alla lista list
 *  - remove(list,el) rimuove l'elemento el dalla lista list e restituisce
 *     il nuovo puntatore a list
 *  - get(el) restituisce i dati satellite dell'elemento el
 *  - isempty(list) restituisce 1 se list e' vuota
 *  - ishead(el) restituisce 1 se el e' in testa alla lista
 *  - istail(el) restituisce 1 se el e' in coda alla lista
 *  - next(el) restituisce l'elemento successivo a el; lista vuota se el e'
 *     in coda
 *  - prev(el) restituisce l'elemento precedente a el; lista vuota se el e'
 *     in testa
 *  - last(list) data una lista restituisce l'ultimo elemento
 *  - destroy(list) elimina la lista list (ma non i dati satellite!)
 */

#ifndef LISTGUARD /* guardia */
#define LISTGUARD

/* 
 * dl_list_w sta per doubly linked list of words. Struct per rappresentare una
 * lista doppiamente concatenata di parole.
 */
struct dl_list_w{
	struct word *word;

	struct dl_list_w *next;
	struct dl_list_w *prev;
	struct dl_list_w *last;
};
struct dl_list_w *dllw_create();
struct dl_list_w *dllw_add(struct dl_list_w *list, struct word *w);
struct dl_list_w *dllw_remove(struct dl_list_w *list, struct dl_list_w *el);
struct word *dllw_get(struct dl_list_w *el);
int dllw_isempty(struct dl_list_w *list);
int dllw_ishead(struct dl_list_w *list);
int dllw_istail(struct dl_list_w *list);
struct dl_list_w *dllw_next(struct dl_list_w *list);
struct dl_list_w *dllw_prev(struct dl_list_w *list);
struct dl_list_w *dllw_last(struct dl_list_w *list);
void dllw_destroy(struct dl_list_w *list);

/* 
 * dl_list_n sta per doubly linked list of nodes. Struct per rappresentare una
 * lista doppiamente concatenata di nodi di G_T (o G_T^*).
 */
struct dl_list_n{
	struct node *node;

	struct dl_list_n *next;
	struct dl_list_n *prev;
	struct dl_list_n *last;
};
struct dl_list_n *dlln_create();
struct dl_list_n *dlln_add(struct dl_list_n *list, struct node *x);
struct dl_list_n *dlln_remove(struct dl_list_n *list, struct dl_list_n *el);
struct node *dlln_get(struct dl_list_n *el);
int dlln_isempty(struct dl_list_n *list);
int dlln_ishead(struct dl_list_n *list);
int dlln_istail(struct dl_list_n *list);
struct dl_list_n *dlln_next(struct dl_list_n *list);
struct dl_list_n *dlln_prev(struct dl_list_n *list);
struct dl_list_n *dlln_last(struct dl_list_n *list);
void dlln_destroy(struct dl_list_n *list);

/* 
 * dll_list_n sta per doubly linked list of lists of nodes. Chiamando le liste
 * piu' interne "pile", le operazioni add, newpile e remove agiscono sugli
 * elementi delle pile e non sulle pile stesse. Le pile non sono mai vuote.
 */
struct dll_list_n{
	struct dl_list_n *pl; /* pila di nodi */

	struct dll_list_n *next;
	struct dll_list_n *prev;
	struct dll_list_n *last;

};
struct dll_list_n *dllln_create();
/* 
 * dllln_newpile crea una nuova pila contenente solo x e mette questa in coda
 * alla lista di pile di ll.
 */
struct dll_list_n *dllln_newpile(struct dll_list_n *ll, struct node *x);
/* 
 * dllln_add aggiunge x all'ultima pila di ll (ll deve avere almeno una pila).
 * Restituisce la nuova lista di pile.
 */
struct dll_list_n *dllln_add(struct dll_list_n *ll, struct node *x);
/* 
 * dllln_remove toglie l'elemento el dalla pila p della lista di pile ll. Se la
 * pila rimane vuota la elimina. Restituisce la nuova lista di pile.
 */
struct dll_list_n *dllln_remove(struct dll_list_n *ll, struct dll_list_n *p,
		struct dl_list_n *el);
int dllln_isempty(struct dll_list_n *ll);
int dllln_ishead(struct dll_list_n *p);
int dllln_istail(struct dll_list_n *p);
struct dl_list_n *dllln_get(struct dll_list_n *p);
struct dll_list_n *dllln_next(struct dll_list_n *p);
struct dll_list_n *dllln_prev(struct dll_list_n *p);
struct dll_list_n *dllln_last(struct dll_list_n *ll);
void dllln_destroy(struct dll_list_n *list);

/* 
 * tsort_list sta per topological sort list. Struct per rappresentare una lista
 * di dllln, cioe' di ordinamenti topologici "impilati".
 */
struct tsort_list{
	struct dll_list_n *l;

	struct tsort_list *next;
	struct tsort_list *prev;
	struct tsort_list *last;
};
struct tsort_list *tsl_create();
struct tsort_list *tsl_add(struct tsort_list *list, struct dll_list_n *x);
struct tsort_list *tsl_remove(struct tsort_list *list, struct tsort_list *el);
struct dll_list_n *tsl_get(struct tsort_list *el);
void tsl_set(struct tsort_list *el,struct dll_list_n *x);
int tsl_isempty(struct tsort_list *list);
int tsl_ishead(struct tsort_list *el);
int tsl_istail(struct tsort_list *el);
struct tsort_list *tsl_next(struct tsort_list *el);
struct tsort_list *tsl_prev(struct tsort_list *el);
struct tsort_list *tsl_last(struct tsort_list *list);
void tsl_destroy(struct tsort_list *list);

#endif
