/*
 * github.com/nrizzo
 * src/text/alpha/alpha.h
 *
 * Intestazione del codice che gestisce l'alfabeto S = Sigma\{blank}.
 *
 * Esempio di utilizzo:
 *  struct alphabet *S = alpha_create(); // creazione dell'alfabeto
 *
 *  alpha_addchar(S,c1); // aggiunta di utf8char (spazi e doppioni vengono
 *  alpha_addchar(S,c1); //  ignorati).
 *  alpha_addchar(S,c2);
 *  alpha_addchar(S,c3);
 *
 *  int i = alpha_indexof(S,c1); // 0 perche' c1 e' stato aggiunto per primo
 *  int j = alpha_indexof(S,c2); // 1 perche' c2 e' stato aggiunto per secondo
 *  int k = alpha_indexof(S,c4); // -1 perche' c4 non appartiene all'alfabeto
 *
 *  alpha_destroy(S); // distruzione dell'alfabeto
 */

#ifndef AGUARD /* guardia */
#define AGUARD

#include "../utf8char/utf8char.h"

/* 
 * Struct che rappresenta l'alfabeto S=Sigma\{blank}.
 */
struct alphabet {
	int size; /* cardinalita' di S */
	struct utf8_char **chars; /* array dei caratteri di S */
};

/* 
 * alpha_create crea un alfabeto vuoto e ne restituisce il puntatore.
 */
struct alphabet *alpha_create();

/* 
 * alpha_addchar, se c non e' gia' presente in S e se non e' un whitespace
 * secondo utf8_isspace(), ne crea una copia e lo aggiunge a S.
 */
void alpha_addchar(struct alphabet *S, struct utf8_char *c);

/* 
 * alpha_size restituisce la cardinalita' di S.
 */
int alpha_size(struct alphabet *S);

/* 
 * alpha_indexof restituisce l'indice di c in S (compreso in [0,|S|-1]) se
 * questo e' presente, -1 altrimenti.
 */
int alpha_indexof(struct alphabet *S, struct utf8_char *c);

/* 
 * alpha_belongs restituisce 1 se c appartiene a S, 0 altrimenti
 */
int alpha_belongs(struct alphabet *S, struct utf8_char *c);

/* 
 * alpha_destroy libera lo spazio occupato da S e da tutti i suoi caratteri.
 */
void alpha_destroy(struct alphabet *S);

#endif /* AGUARD */
