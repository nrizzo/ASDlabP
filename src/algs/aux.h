/*
 * github.com/nrizzo
 * src/algs/aux.h
 *
 * Intestazione del codice delle procedure ausiliarie di algs.c.
 */

#ifndef AUXGUARD /* guardia */
#define AUXGUARD

/* 
 * lexicographicalsort, dato il testo T e data la lista delle sue parole list di
 * lunghezza length, restituisce una nuova lista delle stesse parole ordinate
 * lessicograficamente (secondo l'alfabeto S); elimina list.
 */
struct dl_list_w *lexicographicalsort(struct text *T, struct dl_list_w *list,
		int length);

/* 
 * sortbychar, dato il testo T e una lista di sue parole list di lunghezza
 * maggiore o uguale a j+1, restituisce una nuova lista delle stesse parole
 * ordinate lessicograficamente secondo il loro j+1-esimo carattere.
 */
struct dl_list_w *sortbychar(struct text *T, struct dl_list_w *list, int j);

/* 
 * uniq, data una lista di parole list, cancella gli elementi adiacenti con
 * uguali parole (lasciandone uno per gruppo); non cancella le parole e
 * modifica list, restituendo poi il suo nuovo puntatore.
 */
struct dl_list_w *uniq(struct dl_list_w *list);

/*
 * sortbycvector, sortbycvectormin e sortbycvectormax, dato l'alfabeto S di T e
 * la lista dei nodi di G_T o G_T^* nodes, ordina i nodi in modo decrescente
 * rispetto a, rispettivamente, il campo i-esimo del vettore dei caratteri, il
 * minore tra il campo i-esimo e il j-esimo, il maggiore tra i due; a parita' di * valori, viene seguito l'ordine con cui sono dati. Non modificano la lista
 * passata come argomento e restituiscono una nuova lista.
 */
struct dl_list_n *sortbycvector(struct alphabet *S, struct dl_list_n *nodes,
		int i);
struct dl_list_n *sortbycvectormin(struct alphabet *S, struct dl_list_n *nodes,
		int i, int j);
struct dl_list_n *sortbycvectormax(struct alphabet *S, struct dl_list_n *nodes,
		int i, int j);

/* 
 * uniqcv, data la lista dei nodi di G_T, raccoglie gli anagrammi adiacenti
 * nella lista (con node_join), distruggendo i nodi non necessari. 
 */
struct dl_list_n *uniqcv(struct dl_list_n *V);

/*
 * top_char, top_min e top_max, dato il grafo G_T o G_T^*, restituiscono
 * l'ordinamento topologico "impilato" rispettivamente secondo la cardinalita'
 * dell'i-esimo carattere, secondo la cardinalita' del minore tra l'i-esimo e il
 * j-esimo e secondo la cardinalita' del maggiore tra i due.
 */
struct dll_list_n *top_char(struct graph *G_T, int i);
struct dll_list_n *top_min(struct graph *G_T, int i, int j);
struct dll_list_n *top_max(struct graph *G_T, int i, int j);

/*
 * findpointers, dati la lista dei nodi di G_T o G_T^* V e la lista di alcuni
 * suoi ordinamenti topologici "impilati" tops, indicizza per ogni nodo tutti i
 * puntatori alla lista, pila ed elemento corrispondente in tops.
 */
void findpointers(struct dl_list_n *V, struct tsort_list *tops);

/* 
 * pileup, data una lista ordinata di nodi di G_T o G_T^* nodes, crea la lista
 * di pile corrispondente, raggruppando in pile i nodi adiacenti collegati a
 * parole della stessa lunghezza (#).
 */
struct dll_list_n *pileup(struct dl_list_n *nodes);

/*
 * calcminchildren e calcminparents, dato l'ordinamento topologico "impilato"
 * top, trovano per ogni nodo il minor numero di, rispettivamente, figli e
 * genitori possibili, assieme al puntatore alla pila corrispondente.
 */
void calcminchildren(struct dll_list_n *top);
void calcminparents(struct dll_list_n *top);

/*
 * queueup, data la lista dei nodi di G_T o G_T^*, dopo la chiamata di
 * calcminchildren e calcminparents su degli ordinamenti topologici, crea e
 * restituisce il puntatore della lista ordinata secondo la somma dei figli e
 * dei genitori possibili; a parita' di valori viene seguito l'ordine di nodes.
 */
struct dl_list_n *queueup(struct dl_list_n *nodes);

/*
 * calcchildren e calcparents, dopo aver chiamato findpointers, calcminchildren
 * e calcminparents su degli ordinamenti topologici "impilati", dato un nodo x
 * calcolano, rispettivamente, i suoi figli e i suoi genitori, aggiungendo gli
 * archi nelle corrette liste di adiacenza.
 */
void calcchildren(struct node *x);
void calcparents(struct node *x);

/*
 * topsremove, dopo aver chiamato findpointers su tops, dato un nodo x lo
 * elimina da tutti gli ordinamenti, liberando anche lo spazio occupato da
 * questo.
 */
void topsremove(struct tsort_list *tops, struct node *x);

#endif /* AUXGUARD */
