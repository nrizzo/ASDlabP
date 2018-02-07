/*
 * github.com/nrizzo
 * src/text/utf8char/utf8char.h
 *
 * Intestazione della piccola libreria per la lettura da standard
 * input, la gestione e il confronto di caratterieri codificati in UTF-8.
 *
 * Esempio di utilizzo:
 *  struct utf8_char c = utf8_create(); // creazione
 *  int i = utf8_getchar(c); // lettura, i==1 se e' stato letto un carattere
 *  utf8_putchar(c); // scrittura su standard output
 *  utf8_destroy(c); // distruzione
 */

#ifndef UTFGUARD /* guardia */
#define UTFGUARD

/* 
 * Struct che rappresenta un singolo carattere UTF-8. La codifica e' multibyte
 * quindi lo e' anche lo spazio occupato dalla struct.
 */
struct utf8_char { 
	unsigned char bytes; /* lunghezza in byte */
	char *chr; /* stringa dei byte (senza terminatore) */
};

/* 
 * utf8_create crea una nuovo utf8_char vuoto e ne restituisce il puntatore; va
 * accoppiato a utf8_destroy per liberarne lo spazio.
 */
struct utf8_char *utf8_create();

/* 
 * utf8_copy, dato c, crea un nuovo utf8_char e vi copia lo stato di c;
 * restituisce il puntatore al nuovo struct utf8_char; va accoppiato a
 * utf8_destroy per liberarne lo spazio.
 */
struct utf8_char *utf8_copy(struct utf8_char *c);

/* 
 * utf8_get legge da standard input il primo carattere UTF-8 e lo salva in c;
 * restituisce 0 se e' stato letto un carattere con successo, -1 se il testo
 * e' finito, -2 se il testo e' finito con un carattere fuori codifica.
 */
int utf8_getchar(struct utf8_char *c);

/* 
 * utf8_putchar stampa sullo standard output il carattere salvato in c (con 
 * printf)
 */
void utf8_putchar(struct utf8_char *c);

/* 
 * utf8_isblank restituisce 1 se il carattere e' blank (' '), 0 altrimenti.
 */
int utf8_isblank(struct utf8_char *c);

/* 
 * utf8_equals restituisce 1 se i due caratteri coincidono, 0 altrimenti.
 */
int utf8_equals(struct utf8_char *a, struct utf8_char *b);

/* 
 * utf8_destroy libera lo spazio dello struct utf8_char c creato con
 * utf8_create
 */
void utf8_destroy(struct utf8_char *c);

#endif /* UTFGUARD */
