/*
 * github.com/nrizzo
 * src/tcalc/talgs/taux.h
 *
 * Intestazione del codice delle funzioni ausiliarie di talgs.
 */

#ifndef TAUXGUARD /* guardia */
#define TAUXGUARD


#include <time.h> /* __clock_t */

/* PREPARAZIONE DELL'INPUT */

/* 
 * taux_preparecorpus2 e taux_preparecorpus3 leggono i file di testo dei corpus
 * per il caso 2 e 3 e generano le strutture dati appropriate di supporto per la
 * generazione di testo pseudo-casuale. 
 */
void taux_preparecorpus2();
void taux_preparecorpus3();

/* 
 * struct rappresentante una parola di un corpus di testo, con la corrispondente
 * frequenza.
 */
struct entry {
	char *word;
	unsigned long freq;
};

/* 
 * readentry, datogli il file descriptor del corpus testuale in input, ne legge
 * una riga e restituisce l'entry corrispondente, NULL se il testo e' finito.
 */
struct entry *readentry(int fd);

/* 
 * readword, datogli il file descripto del corpus testuale in input, ne legge
 * una parola (seguita da un '\t' che viene ignorato) e restituisce il
 * puntatore alla stringa corrispondente, NULL se il testo e' finito.
 */
char *readword(int fd);

/* 
 * readfreq, datogli il file descriptor del corpus testuale aperto in lettura, 
 * legge il primo numero (seguita da un '\n' che viene ignorato) e lo
 * restituisce.
 */
unsigned long readfreq(int fd);

/* 
 * writerandomchar, datogli il file descriptor di un file aperto in scrittura,
 * vi scrive un carattere pseudo-casuale (con il PRNG in prng) scelto tra quelli * dell'alfabeto ALPHA definito in options.h.
 */
void writerandomchar(int fd);

/* 
 * writerandomword2, datogli il file descriptor di un file aperto in scrittura,
 * vi scrive una parola pseudo-casuale (con il PRNG in prng) scelta con
 * estrazione a lotteria (pesata) tra quelle calcolate da preparecorpus2 e
 * salvate nelle variabili globali per il caso 2.
 */
void writerandomword2(int fd);

/* 
 * writerandomword3, datogli il file descriptor di un file aperto in scrittura,
 * vi scrive una parola pseudo-casuale (con il PRNG in prng) scelta con
 * estrazione a lotteria (pesata) tra quelle calcolate da preparecorpus3 e
 * salvate nelle variabili globali per il caso 3.
 */
void writerandomword3(int fd);

/* 
 * prepara1 scrive un testo pseudo-casuale secondo il caso 1 (ogni carattere
 * e' casuale), salvandolo nel file indicato in options.h (lo crea se non
 * esiste, ne cancella il contenuto se esiste), di lunghezza length.
 */
void prepara1(int length);

/* 
 * prepara2 scrive un testo pseudo-casuale secondo il caso 2 (un grafo senza
 * alcun arco), salvandolo nel file indicato in options.h (lo crea se non
 * esiste, ne cancella il contenuto se esiste), di words parole.
 */
void prepara2(int words);

/* 
 * prepara3 scrive un testo pseudo-casuale secondo il caso 3 (un testo in
 * italiano), salvandolo nel file indicato in options.h (lo crea se non
 * esiste, ne cancella il contenuto se esiste), di words parole.
 */
void prepara3(int words);

/* 
 * execute, una volta preparato l'input (con prepara1, prepara2 o prepara3),
 * esegue l'algoritmo risolutivo sui dati preparati.
 */
void execute();

/* 
 * execute_v2 si comporta come execute, ma esegue l'algoritmo risolutivo
 * con il calcolo degli archi potenziato (vedi alg_findedges_v2).
 */
void execute_v2();

/* 
 * calcolaNodi, una volta preparato l'input (con prepara1, prepara2 o prepara3),
 * esegue l'algoritmo risolutivo sui dati preparati fino ad avere e restituisce
 * il numero di nodi di G_T.
 */
int calcolaNodi();

/* 
 * calcolaArchi, una volta preparato l'input (con prepara1, prepara2 o
 * prepara3), esegue l'algoritmo risolutivo sui dati preparati fino ad
 * avere e restituire il numero di archi di G_T.
 */
int calcolaArchi();

/* 
 * riavvolgi, dopo l'esecuzione di execute, execute_v2, calcolaNodi o
 * calcolaArchi, riprepara l'esecuzione sugli stessi dati, riavvolgendo il file
 * di input; puo' essere considerata trascurabile.
 */
void riavvolgi();

/*
 * granularity calcola il piu' piccolo intervallo misurabile dal calcolatore con
 * l'orologio di sistema. (Alg. 4 dispensa)
 */
__clock_t granularity();

/* 
 * calcolaRip, dato l'intervallo tMin, calcola il minor numero di ripetizioni
 * dell'algoritmo risolutivo necessarie per garantire che l'errore dovuto
 * all'orologio di sistema sia minore di tMin (specialmente su input piccoli,
 * approssimato a 5 ripetizioni). (Alg. 5 dispensa)
 */
int calcolaRip(__clock_t tMin);

/* 
 * calcolaTempo usa granularity e calcolaRip per calcolare il tempo di
 * esecuzione dell'algoritmo risolutivo con massimo errore percentuale
 * definito da MAX_RELATIVE_MEASUREMENT_ERROR in options.h. (Alg. 6 dispensa)
 */
__clock_t calcolaTempo();

/*
 * calcolaTempo_v2 si comporta come calcolaTempo, ma esegue l'algoritmo
 * risolutivo con il calcolo degli archi potenziato (vedi alg_findedges_v2).
 */
__clock_t calcolaTempo_v2();

#endif /* TAUXGUARD */
