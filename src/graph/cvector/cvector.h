/*
 * github.com/nrizzo
 * src/graph/cvector/cvector.h
 *
 * Intestazione del codice che gestisce il vettore dei caratteri di una parola.
 */

#ifndef CVGUARD /* guardia */
#define CVGUARD

/* 
 * Struct che rappresenta il vettore dei caratteri di una parola.
 */
struct cvector {
	int length; /* lunghezza del vettore */
	int *count; /* array delle occorrenze */
};

/* 
 * cv_create, dati l'alfabeto S=Sigma\{blank} e la parola w, crea il
 * corrispondente vettore dei caratteri e ne restituisce il puntatore.
 */
struct cvector *cv_create(struct alphabet *S, struct word *w);

/* 
 * cv_rel, dati u1 e u2 vettori di caratteri di parole dello stesso testo,
 * restituisce 1 se per ogni campo u1[i] >= u2[i], 0 altrimenti.
 */
int cv_rel(struct cvector *u1, struct cvector *u2);

/* 
 * cv_get restituisce le occorrenze del carattere i+1-esimo.
 */
int cv_get(struct cvector *u, int i);

/* 
 * cv_equals restituisce 1 se i due vettori dei caratteri combaciano,
 * 0 altrimenti.
 */
int cv_equals(struct cvector *cv1, struct cvector *cv2);

/* 
 * cv_destroy cancella il vettore delle occorrenze e libera il suo spazio.
 */
void cv_destroy(struct cvector *u);

#endif /* CVGUARD */
