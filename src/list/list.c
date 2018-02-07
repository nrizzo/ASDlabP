/*
 * github.com/nrizzo
 * src/list/list.c
 *
 * Codice che implementa liste doppiamente concatenate con puntatore all'ultimo
 * elemento (aggiornato solo in testa) e procedure per gestirle.
 */

#include <stdlib.h> /* malloc e free */

#include "../text/word/word.h"
#include "../text/alpha/alpha.h"
#include "../graph/node/node.h"
#include "list.h"

struct dl_list_w *dllw_create()
{
	return NULL; /* NULL rappresenta la lista vuota */
}

struct dl_list_w *dllw_add(struct dl_list_w *list, struct word *w)
{
	struct dl_list_w *newtail = malloc(sizeof(struct dl_list_w));

	newtail->word = w;
	newtail->next = NULL;

	if (list != NULL) { /* newtail va in coda a list */
		newtail->prev = list->last;
		list->last->next = newtail;
		list->last = newtail;
		return list;
	} else { /* newtail e' l'unico nodo */
		newtail->prev = NULL;
		newtail->last = newtail;
		return newtail;
	}
}

struct dl_list_w *dllw_remove(struct dl_list_w *list, struct dl_list_w *el)
{
	/* el e list devono essere != NULL */
	/* el deve essere un elemento di list */
	if (el->prev == NULL && el->next == NULL) { /* el e' l'unico elemento */
		free(el);
		return NULL;
	} else if (el->prev == NULL) { /* el e' in testa (list==el) */
		list = el->next;
		list->prev = NULL;
		list->last = el->last;

		free(el);
		return list;
	} else if (el->next == NULL) { /* el e' in coda */
		list->last = el->prev;
		el->prev->next = NULL;
		
		free(el);
		return list;
	} else {
		el->prev->next = el->next;
		el->next->prev = el->prev;

		free(el);
		return list;
	}
}

struct word *dllw_get(struct dl_list_w *el)
{
	return el->word;
}

int dllw_isempty(struct dl_list_w *list)
{
	return (list == NULL);
}

int dllw_ishead(struct dl_list_w *el)
{
	if (el->prev == NULL)
		return 1;
	else
		return 0;
}

int dllw_istail(struct dl_list_w *el)
{
	if (el->next == NULL)
		return 1;
	else
		return 0;
}

struct dl_list_w *dllw_next(struct dl_list_w *el)
{
	return el->next;
}

struct dl_list_w *dllw_prev(struct dl_list_w *el)
{
	return el->prev;
}

struct dl_list_w *dllw_last(struct dl_list_w *list){
	return list->last;
}

void dllw_destroy(struct dl_list_w *list)
{
	struct dl_list_w *temp;
	while (list != NULL) {
		temp = list->next;
		free(list);
		list = temp;
	}
}


struct dl_list_n *dlln_create()
{
	return NULL; /* NULL rappresenta la lista vuota */
}

struct dl_list_n *dlln_add(struct dl_list_n *list, struct node *x)
{
	struct dl_list_n *newtail = malloc(sizeof(struct dl_list_n));

	newtail->node = x;
	newtail->next = NULL;

	if (list != NULL) { /* newtail va in coda a list */
		newtail->prev = list->last;
		list->last->next = newtail;
		list->last = newtail;
		return list;
	} else { /* newtail e' l'unico nodo */
		newtail->prev = NULL;
		newtail->last = newtail;
		return newtail;
	}
}

struct dl_list_n *dlln_remove(struct dl_list_n *list, struct dl_list_n *el)
{
	/* el e list devono essere != NULL */
	/* el deve essere un elemento di list */
	if (el->prev == NULL && el->next == NULL) { /* el e' l'unico elemento */
		free(el);
		return NULL;
	} else if (el->prev == NULL) { /* el e' in testa (list==el) */
		list = el->next;
		list->prev = NULL;
		list->last = el->last;

		free(el);
		return list;
	} else if (el->next == NULL) { /* el e' in coda */
		list->last = el->prev;
		el->prev->next = NULL;
		
		free(el);
		return list;
	} else {
		el->prev->next = el->next;
		el->next->prev = el->prev;

		free(el);
		return list;
	}
}

struct node *dlln_get(struct dl_list_n *el)
{
	return el->node;
}

int dlln_isempty(struct dl_list_n *list)
{
	return (list == NULL);
}

int dlln_ishead(struct dl_list_n *el)
{
	if (el->prev == NULL)
		return 1;
	else
		return 0;
}

int dlln_istail(struct dl_list_n *el)
{
	if (el->next == NULL)
		return 1;
	else
		return 0;
}

struct dl_list_n *dlln_next(struct dl_list_n *el)
{
	return el->next;
}

struct dl_list_n *dlln_prev(struct dl_list_n *el)
{
	return el->prev;
}

struct dl_list_n *dlln_last(struct dl_list_n *list)
{
	return list->last;
}

void dlln_destroy(struct dl_list_n *list)
{
	struct dl_list_n *temp;
	while (list != NULL){
		temp = list->next;
		free(list);
		list = temp;
	}
}


struct dll_list_n *dllln_create()
{
	return NULL; /* NULL e' la lista di pile vuota */
}

struct dll_list_n *dllln_newpile(struct dll_list_n *ll, struct node *x)
{
	struct dll_list_n *newtail;
	newtail = malloc(sizeof(struct dll_list_n));
	newtail->pl = dlln_create();
	newtail->pl = dlln_add(newtail->pl,x);

	if (dllln_isempty(ll)) {
		newtail->next = NULL;
		newtail->prev = NULL;
		newtail->last = newtail;
	
		return newtail;
	} else {
		newtail->next = NULL;
		newtail->prev = ll->last;
		ll->last->next = newtail;
		ll->last = newtail;
		
		return ll;
	}
}

struct dll_list_n *dllln_add(struct dll_list_n *ll, struct node *x)
{	/* ll != NULL */
	ll->last->pl = dlln_add(ll->last->pl,x);
	return ll;
}

struct dll_list_n *dllln_remove(struct dll_list_n *ll, struct dll_list_n *p,
		struct dl_list_n *el) {
	/* el appartiene a p, p appartiene a ll */
	p->pl = dlln_remove(p->pl,el);

	if (!dlln_isempty(p->pl))
		return ll;

	/* la pila e' stata svuotata */
	if (dllln_ishead(p) && dllln_istail(p)) { /* se era l'unica pila */
		free(p);
		return NULL;
	} else if (dllln_ishead(p)) { /* se era in testa */
		ll->next->last = ll->last;
		ll = dllln_next(p);
		ll->prev = NULL;
		free(p);
		return ll;
	} else if (dllln_istail(p)){ /* se era in coda */
		p->prev->next = NULL;
		ll->last = p->prev;
		free(p);
		return ll;
	} else { /* ne' in coda ne' in testa */
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
		return ll;
	}
}

int dllln_isempty(struct dll_list_n *ll)
{
	return (ll == NULL);
}

int dllln_ishead(struct dll_list_n *p)
{
	return (p->prev == NULL);
}

int dllln_istail(struct dll_list_n *p)
{
	return (p->next == NULL);
}

struct dl_list_n *dllln_get(struct dll_list_n *p)
{
	return p->pl;
}

struct dll_list_n *dllln_next(struct dll_list_n *p)
{
	return p->next;
}

struct dll_list_n *dllln_prev(struct dll_list_n *p)
{
	return p->prev;
}

struct dll_list_n *dllln_last(struct dll_list_n *ll)
{
	return ll->last;
}


struct tsort_list *tsl_create()
{
	return NULL;
}

struct tsort_list *tsl_add(struct tsort_list *list, struct dll_list_n *x)
{
	struct tsort_list *newtail = malloc(sizeof(struct tsort_list));

	newtail->l = x;
	newtail->next = NULL;

	if (list != NULL) {
		newtail->prev = list->last;
		list->last->next = newtail;
		list->last = newtail;
		return list;
	} else {
		newtail->prev = NULL;
		newtail->last = newtail;
		return newtail;
	}
}

struct tsort_list *tsl_remove(struct tsort_list *list, struct tsort_list *el)
{
	/* el e list devono essere != NULL */
	/* el deve essere un elemento di list */
	if (el->prev == NULL && el->next == NULL) { /* el e' l'unico elemento */
		free(el);
		return NULL;
	} else if (el->prev == NULL) { /* el e' in testa (list==el) */
		list = el->next;
		list->prev = NULL;
		list->last = el->last;

		free(el);
		return list;
	} else if (el->next == NULL) { /* el e' in coda */
		list->last = el->prev;
		el->prev->next = NULL;
		
		free(el);
		return list;
	} else {
		el->prev->next = el->next;
		el->next->prev = el->prev;

		free(el);
		return list;
	}
}

struct dll_list_n *tsl_get(struct tsort_list *el) {
	return el->l;
}

void tsl_set(struct tsort_list *el,struct dll_list_n *x) {
	el->l = x;
}

int tsl_isempty(struct tsort_list *list)
{
	if (list == NULL)
		return 1;
	else
		return 0;
}

int tsl_ishead(struct tsort_list *el)
{
	if (el->prev == NULL)
		return 1;
	else
		return 0;
}

int tsl_istail(struct tsort_list *el)
{
	if (el->next == NULL)
		return 1;
	else
		return 0;
}

struct tsort_list *tsl_next(struct tsort_list *el)
{
	return el->next;
}

struct tsort_list *tsl_prev(struct tsort_list *el)
{
	return el->prev;
}

struct tsort_list *tsl_last(struct tsort_list *list)
{
	return list->last;
}

void tsl_destroy(struct tsort_list *list)
{
	struct tsort_list *el = list;
	while (el != NULL) {
		el = tsl_remove(el,el);
	}
}
