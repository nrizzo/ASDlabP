/*
 * github.com/nrizzo
 * src/tcalc/talgs/talgs.h
 *
 * Intestazione del codice che genera testi e calcola i tempi dell'algoritmo
 * risolutivo su questi.
 */

#ifndef TALGSGUARD /* guardia */
#define TALGSGUARD

#include <time.h> /* __clock_t */

/* 
 * preparecorpu2 e preparecorpus3 leggono i file dei corpus testuali per il caso
 * 2 (un grafo senza archi) e per il caso 3 (un testo in italiano) e generano le
 * strutture dati appropriate.
 */
void preparecorpus2();
void preparecorpus3();

/* 
 * struct che rappresenta l'intervallo di confidenza [e-delta,e+delta] per una
 * misurazione con l'orologio di sistema.
 */
struct result{
	__clock_t e;
	__clock_t delta;
};

/* 
 * misurazione calcola il tempo medio necessario all'esecuzione dell'algoritmo
 * risolutivo per un campione pseudo-casuale del caso 1 (ogni carattere e'
 * casuale), del caso 2 (un grafo senza archi) o del caso 3 (un testo in
 * italiano) e restituisce l'intervallo di confidenza imposto da za con un
 * errore relativo minore di deltapercent.
 *
 * misurazione_v2 utilizza la versione potenziata dell'algoritmo (vedi
 * alg_findedges_v2).
 *
 * (Alg. 9 dispensa)
 */
struct result *misurazione1(int length, int c, double za, double deltapercent);
struct result *misurazione2(int words, int c, double za, double deltapercent);
struct result *misurazione2_v2(int words,int c,double za,double deltapercent);
struct result *misurazione3(int words, int c, double za, double deltapercent);
struct result *misurazione3_v2(int words,int c,double za,double deltapercent);

/* 
 * nodi calcola il numero medio di nodi di G_T per un campione pseudo-casuale
 * del caso 1 (ogni carattere e' casuale), del caso 2 (G_T non ha archi) o del
 * caso 3 (un testo in italiano) e restituisce il punto nel mezzo dell'
 * intervallo di confidenza imposto da za con un errore relativo minore di
 * deltapercent. (Alg. 9 dispensa)
 */
double nodi1(int length, int c, double za, double deltapercent);
double nodi2(int length, int c, double za, double deltapercent);
double nodi3(int length, int c, double za, double deltapercent);

/* 
 * archi calcola il numero medio di archi di G_T per un campione pseudo-casuale
 * del caso 1 (ogni carattere e' casuale), del caso 2 (G_T non ha archi) o del
 * caso 3 (un testo in italiano) e restituisce il punto nel mezzo dell'
 * intervallo di confidenza imposto da za con un errore relativo minore di
 * deltapercent. (Alg. 9 dispensa)
 */
double archi1(int length, int c, double za, double deltapercent); 
double archi2(int length, int c, double za, double deltapercent); 
double archi3(int length, int c, double za, double deltapercent); 

#endif /* TALGSGUARD */
