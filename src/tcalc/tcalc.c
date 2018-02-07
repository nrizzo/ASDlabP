/*
 * github.com/nrizzo
 * src/tcalc/tcalc.c
 *
 * Codice relativo al calcolo sperimentale dei tempi dell'algoritmo risolutivo.
 */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "talgs/talgs.h"
#include "talgs/taux.h" /* debug */

#define MIN_SAMPLE 5
#define ZA 1.96
#define MAX_RELATIVE_DELTA 0.05

int main()
{
	int output, realstdout; /* file descriptor */
	struct result *t; /* risultati */
	double r,secs, delta;

	/* Sostituzione di /dev/null allo standard output */
	output = open("/dev/null",O_WRONLY); /* apertura di /dev/null in scrittura */
	realstdout = dup(STDOUT_FILENO); /* copia dello standard output */
	dup2(output,STDOUT_FILENO); /* sostituzione dello stdandard output */

	dprintf(realstdout,"Caso 1: caratteri casuali\n");
	dprintf(realstdout,"Calcolo dei nodi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = nodi1(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}
	dprintf(realstdout,"Calcolo degli archi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = archi1(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}
	dprintf(realstdout,"Calcolo dei tempi\n");
	for (int words=1250; words<=50000; words+=1250) {
		t = misurazione1(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		secs = (double)t->e/(double)CLOCKS_PER_SEC;
		delta = (double)t->delta/(double)CLOCKS_PER_SEC;
		dprintf(realstdout,"%d\t%f\n",words,secs);
		free(t);
	}

	//preparecorpus2();
	/*dprintf(realstdout,"Caso 2: nessun arco\n");
	dprintf(realstdout,"Calcolo dei nodi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = nodi2(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}
	dprintf(realstdout,"Calcolo degli archi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = archi2(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}
	dprintf(realstdout,"Calcolo dei tempi\n");
	for (int words=1250; words<=50000; words+=1250) {
		t = misurazione2(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		secs = (double)t->e/(double)CLOCKS_PER_SEC;
		delta = (double)t->delta/(double)CLOCKS_PER_SEC;
		dprintf(realstdout,"%d\t%f\n",words,secs);
		free(t);
	}
	dprintf(realstdout,"Calcolo dei tempi v2\n");
	for (int words=1250; words<=50000; words+=1250) {
		t = misurazione2_v2(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		secs = (double)t->e/(double)CLOCKS_PER_SEC;
		delta = (double)t->delta/(double)CLOCKS_PER_SEC;
		dprintf(realstdout,"%d\t%f\n",words,secs);
		free(t);
	}*/


	preparecorpus3();
	dprintf(realstdout,"Caso 3: un testo in italiano\n");
	/*dprintf(realstdout,"Calcolo dei nodi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = nodi3(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}*/
	dprintf(realstdout,"Calcolo degli archi\n");
	for (int words=1250; words<=50000; words+=1250) {
		r = archi3(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		dprintf(realstdout,"%d\t%f\n",words,r);
	}
	/*dprintf(realstdout,"Calcolo dei tempi\n");
	for (int words=1250; words<=50000; words+=1250) {
		t = misurazione3(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		secs = (double)t->e/(double)CLOCKS_PER_SEC;
		delta = (double)t->delta/(double)CLOCKS_PER_SEC;
		dprintf(realstdout,"%d\t%f\n",words,secs);
		free(t);
	}
	dprintf(realstdout,"Calcolo dei tempi v2\n");
	for (int words=1250; words<=50000; words+=1250) {
		t = misurazione3_v2(words,MIN_SAMPLE,ZA,MAX_RELATIVE_DELTA);
		secs = (double)t->e/(double)CLOCKS_PER_SEC;
		delta = (double)t->delta/(double)CLOCKS_PER_SEC;
		dprintf(realstdout,"%d\t%f\n",words,secs);
		free(t);
	}*/

	return 0;
}
