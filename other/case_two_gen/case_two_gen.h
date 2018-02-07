char *ALPHA = "abcdefghijklmnopqrstuwxyz0123456789[]{}.,;:-";
#define BLANK '$'
#define ERASER '_'
#define FILLER '*'
#define MAX_CONCAT 4

/*
 * create_masks, data la lunghezza l delle stringhe da generare, genera
 * tutte le stringhe lunghe l contenenti l/2 $ (blank) e i restanti _ (eraser),
 * restituendo il puntatore all'array di stringhe, terminato da NULL.
 */
char **create_masks(int l);

/*
 * fill_masks, data la lunghezza l e l'array di stringhe masks (terminato da
 * NULL), "riempie" le maschere, cambiando i blank con la lettera corrispondente
 * dell'alfabeto ALPHA. Poi restituisce il puntatore all'array di stringhe.
 */
char **fill_masks(int l, char **masks);

/*
 * shuffle_lengths, data la lunghezza l e l'array di stringhe lunghe l terminato
 * da NULL, modifica la lunghezza delle stringhe, aggiungendo da 0 a
 * DEFAULT_SHUFFLE caratteri FILLER in coda alle stringhe. Restituisce il
 * puntatore all'array di stringhe.
 */
char **shuffle_lengths(int l, char **masks);

/*
 * print_masks, dato il puntatore ad un array di stringhe terminato da NULL,
 * stampa su standard output le stringhe, separate da spazi.
 */
void print_masks(char **masks);

/* FUNZIONI AUSILIARIE DI create_masks */
/*
 * permutotion, dato il buffer temp di lunghezza l+1, riempito fino all'i-esimo
 * carattere con blanks caratteri "blank" e erasers caratteri "eraser", chiama
 * ricorsivamente se' stessa fino ad aggiungere a result tutte le possibili
 * stringhe, a partire dalla condizione data, contenenti blanks/2 caratteri
 * "blank" e i restanti erasers.  
 */
char **permutotion(int l, char **result, char *temp, int i,
		int blanks, int erasers);
