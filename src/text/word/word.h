/*
 * github.com/nrizzo
 * src/text/word/word.h
 *
 * Intestazione del codice per la creazione di parole, la loro gestione e
 * informazioni a riguardo. Le parole vengono composte un carattere UTF-8 alla
 * volta.
 *
 * Esempio di utilizzo:
 *  struct word *w = word_create(); // creazione parola vuota
 *  word_addchar(w,c); // concatenazione di un utf8char a w
 *  word_finalize(w); // finalizzazione
 *  int length = word_getlength(w);
 *  word_destroy(w);
 */

#ifndef WGUARD /* guardia */
#define WGUARD

#define DEFAULT_WBSIZE 8 /* maggiore di 0, meglio una potenza di 2 */

/* 
 * Struct che rappresenta una parola costituita da caratteri utf8.
 */
struct word{
	int write; /* indice del primo posto libero */
	int bsize; /* lunghezza del buffer */
	struct utf8_char **buffer;
};


/* 
 * word_create crea una parola vuota e ne restituisce il puntatore. Va
 * accoppiata a word_destroy per eliminarne lo spazio occupato.
 */
struct word *word_create();

/* 
 * word_addchar aggiunge il carattere c in coda alla parola w.
 */
void word_addchar(struct word *w, struct utf8_char *c);

/*
 * word_finalize finalizza una parola, liberando lo spazio occupato in eccesso.
 */
void word_finalize(struct word *w);

/* 
 * word_length restituisce la lunghezza della parola w.
 */
int word_length(struct word *w);

/* 
 * word_charat restituisce il puntatore all'i+1-esimo carattere
 */
struct utf8_char *word_charat(struct word *w, int i);

/* 
 * word_equals restituisce 1 se le due parole passatogli combaciano, 0
 * altrimenti.
 */
int word_equals(struct word *w1, struct word *w2);

/* 
 * word_print stampa su standard output la parola w.
 */
void word_print(struct word *w);

/* 
 * word_destroy cancella la parola w, liberando il suo spazio e anche quello dei
 * caratteri che la compongono.
 */
void word_destroy(struct word *w);

#endif /* WGUARD */
