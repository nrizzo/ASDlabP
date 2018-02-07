/*
 * github.com/nrizzo
 * src/tcalc/prng/prng.h
 *
 * Intestazione del codice del generatore di numeri pseudo-casuali.
 */

#ifndef PRNGGUARD /* guardia */
#define PRNGGUARD

#define DEFAULT_SEED 987654321

/* 
 * set_seed imposta il seme (variabile globale di prng.c) del generatore di
 * numeri pseudo-casuali a s.
 */
void set_seed(double s);

/* 
 * rrandom restituisce un numero pseudo-casuale, in base al seme con cui e'
 * stata chiamata set_seed e al numero di volte che rrandom e' stata
 * successivamente chiamata. (Algoritmo 8 dispensa)
 */
double rrandom();

#endif /* PRNGGUARD */
