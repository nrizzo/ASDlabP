/*
 * github.com/nrizzo
 * src/tcalc/prng/prng.c
 *
 * Codice del generatore di numeri pseudo-casuali.
 */

#include <math.h> /* ceil */

#include "prng.h"

double seed = DEFAULT_SEED; /* variabile globale per il seme */

void set_seed(double s)
{
	seed = s;
}

double rrandom()
{
	int a = 16807;
	int m = 2147483647;
	int q = 127773;
	int r = 2836;

	double lo,hi,test;

	hi = floor(seed /  q);
	lo = seed - (q * hi);
	test = a*lo - r*hi;

	if (test < 0.0)
		seed = test + m;
	else
		seed = test;

	return seed/m;
}
