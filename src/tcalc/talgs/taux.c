/*
 * github.com/nrizzo
 * src/tcalc/talgs/taux.h
 *
 * Codice delle funzioni ausiliarie di talgs.
 */

#include "../../text/word/word.h"
#include "../../text/text.h"
#include "../../list/list.h"
#include "../../graph/graph.h"
#include "../../algs/algs.h"
#include "../../text/alpha/alpha.h"
#include "prng/prng.h"
#include "options.h"
#include "taux.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

/* 
 * Variabili globali per i corpus del caso 2 e caso 3.
 */
int csize2 = 0; /* numero di entry */
struct entry **corpus2 = NULL; /* array di entry */
unsigned long tot2 = 0; /* frequenza totale */

int csize3 = 0; /* numero di entry */
struct entry **corpus3 = NULL; /* array di entry */
unsigned long tot3 = 0; /* frequenza totale*/

void taux_preparecorpus2()
{
	int fd = open("corpus2.txt", O_RDONLY);

	for (struct entry *e = readentry(fd); e!=NULL; e = readentry(fd)) {
		/* finche' ci sono entry da leggere */
		corpus2 = realloc(corpus2,(csize2+1)*sizeof(struct entry));
		corpus2[csize2++] = e;
		tot2 += e->freq;
	}

	close(fd);
}

void taux_preparecorpus3()
{
	int fd = open("corpus3.txt", O_RDONLY);

	for (struct entry *e = readentry(fd); e!=NULL; e = readentry(fd)) {
		/* finche' ci sono entry da leggere */
		corpus3 = realloc(corpus3,(csize3+1)*sizeof(struct entry));
		corpus3[csize3++] = e;
		tot3 += e->freq;
	}

	close(fd);
}

struct entry *readentry(int fd)
{
	struct entry *e = malloc(sizeof(struct entry));

	e->word = readword(fd);
	if (e->word == NULL) { /* se il testo e' finito */
		free(e);
		return NULL;
	}
	e->freq = readfreq(fd);

	return e;
}

char *readword(int fd)
{
	int write = 0; /* indice primo posto libero */
	char *word = malloc(sizeof(char)*2); /* buffer dinamico */

	if (read(fd,&word[write++],1) == 0) { /* se il testo e' finito */
		free(word);
		return NULL;
	}

	while (read(fd,&word[write],1)!=0 && word[write++]!='\t') {
		/* finche' non viene letto tab */
		word = realloc(word,sizeof(char)*(write+1));
	}
	word[write-1] = '\0'; /* terminatore stringa */

	return word;
}

unsigned long readfreq(int c)
{
	int write = 0; /* indice primo posto libero */
	char *word = malloc(sizeof(char)*2); /* buffer dinamico */

	read(c,&word[write++],1);
	while (read(c,&word[write],1)!=0 && word[write++]!='\n') {
		/* finche' non viene letto newline */
		word = realloc(word,sizeof(char)*(write+1));
	}
	word[write-1] = '\0';

	unsigned long result = atol(word); /* trasformazione a intero */
	free(word);

	return result;
}



void writerandomchar(int fd)
{
	int r = rrandom() * ALPHA_SIZE;
	write(fd,&ALPHA[r],1); /* scrivo l'r+1-esimo carattere */
}

void writerandomword2(int fd)
{
	long extracted = (long)(rrandom()*(tot2-1)); /* biglietto estratto */

	int i = 0; /* i-esima parola */
	long p = corpus2[0]->freq; /* somma frequenze alla i-esima (inclusa) */
	while (i<csize2-1 && extracted>=p) {
		i++;
		p += corpus2[i]->freq;
	}

	dprintf(fd,"%s ",corpus2[i]->word);
}

void writerandomword3(int fd)
{
	long extracted = (long)(rrandom()*(tot3-1));

	int i = 0; /* i-esima parola */
	long p = corpus3[0]->freq; /* somma frequenze alla i-esima (inclusa) */
	while (i<csize3-1 && extracted>=p) {
		i++;
		p += corpus3[i]->freq;
	}

	dprintf(fd,"%s ",corpus3[i]->word);
}

void prepara1(int length)
{
	/* scrittura */
	int fd = open(INPUT_TEXT_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	for (int i=0; i<length; i++) {
		writerandomchar(fd);
	}
	close(fd);

	/* apertura e sostituzione allo stdin */
	fd = open(INPUT_TEXT_FILE,O_RDONLY);
	dup2(fd,STDIN_FILENO);
}

void prepara2(int words)
{
	/* scrittura */
	int fd = open(INPUT_TEXT_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	for (int i=0; i<words; i++){
		writerandomword2(fd);
	}
	close(fd);

	/* apertura e sostituzione allo stdin */
	fd = open(INPUT_TEXT_FILE,O_RDONLY);
	dup2(fd,STDIN_FILENO);
}
void prepara3(int words)
{
	/* scrittura */
	int fd = open(INPUT_TEXT_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	for (int i=0; i<words; i++){
		writerandomword3(fd);
	}
	close(fd);

	/* apertura e sostituzione allo stdin */
	fd = open(INPUT_TEXT_FILE,O_RDONLY);
	dup2(fd,STDIN_FILENO);
}

void execute()
{
        struct text *T = text_create(); /* testo (di parole) e alfabeto*/
        struct dl_list_w *words; /* lista delle parole */
        struct graph *G_T = graph_create(T); /* grafo G_T */
        text_retrieve(T);
        words = alg_removeduplicates(T);
        graph_retrievenodes(G_T,words);
        graph_joinanagrams(G_T);
        graph_topologicalsort(G_T);
        graph_findedges(G_T);
        graph_findllp(G_T);
        graph_printllp(G_T); /* lunghezza del percorso massimo */
        graph_printDOT(G_T); /* grafo in formato DOT */
	graph_destroy(G_T);
	dllw_destroy(words);
	text_destroy(T);
}

void execute_v2()
{
        struct text *T = text_create(); /* testo (di parole) e alfabeto*/
        struct dl_list_w *words; /* lista delle parole */
        struct graph *G_T = graph_create(T); /* grafo G_T */
        text_retrieve(T);
        words = alg_removeduplicates(T);
        graph_retrievenodes(G_T,words);
        graph_joinanagrams(G_T);
        graph_topologicalsort(G_T);
        graph_findedges_v2(G_T);
        graph_findllp(G_T);
        graph_printllp(G_T); /* lunghezza del percorso massimo */
        graph_printDOT(G_T); /* grafo in formato DOT */
	graph_destroy(G_T);
	dllw_destroy(words);
	text_destroy(T);
}

int calcolaNodi()
{
	struct text *T = text_create(); /* testo (di parole) e alfabeto*/
        struct dl_list_w *words; /* lista delle parole */
        struct graph *G_T = graph_create(T); /* grafo G_T */
	int result;
        text_retrieve(T);
        words = alg_removeduplicates(T);
        graph_retrievenodes(G_T,words);
        //graph_joinanagrams(G_T);
	result = graph_vertices(G_T);
	graph_destroy(G_T);
	dllw_destroy(words);
	text_destroy(T);
	return result;
}

int calcolaArchi()
{
	struct text *T = text_create(); /* testo (di parole) e alfabeto*/
        struct dl_list_w *words; /* lista delle parole */
        struct graph *G_T = graph_create(T); /* grafo G_T */
	int result;
        text_retrieve(T);
        words = alg_removeduplicates(T);
        graph_retrievenodes(G_T,words);
        graph_joinanagrams(G_T);
	graph_topologicalsort(G_T);
	graph_findedges(G_T);
	graph_calcedges(G_T);
	result = graph_edges(G_T);
	graph_destroy(G_T);
	dllw_destroy(words);
	text_destroy(T);
	return result;
}

void riavvolgi()
{
	lseek(STDIN_FILENO,0,SEEK_SET);
}

__clock_t granularity()
{
	__clock_t t0, t1;

	t0 = clock();
	t1 = clock();

	while (t0 == t1)
		t1 = clock();

	return t1 - t0;
}

int calcolaRip(__clock_t tMin)
{
	__clock_t t0, t1;
	int rip;

	/* Prima esecuzione */
	rip = 1;
	t0 = clock();
	execute();
	riavvolgi();
	t1 = clock();

	/* Ricerca per bisezione */
	while (t1 - t0 <= tMin) {
		rip *= 2;

		t0 = clock();
		for (int i=0; i<rip; i++) {
			execute();
			riavvolgi();
		}
		t1 = clock();
	}

	/* Raffinamento delle ripetizioni a 5 cicli */
	int max = rip;
	int min = rip/2;

	while (max - min >= 5) {
		rip = (max + min)/2; /* valore mediano */
		t0 = clock();
		for (int i=0; i<rip; i++) {
			execute();
			riavvolgi();
		}
		t1 = clock();

		if (t1 - t0 <= tMin)
			min = rip;
		else
			max = rip;
	}

	return max;
}

__clock_t calcolaTempo()
{
	__clock_t g = granularity();
	int rip = calcolaRip((int)((double)g/MAX_RELATIVE_MEASUREMENT_ERROR));
	__clock_t t0, t1, res;

	t0 = clock();
	for (int i=0; i<rip; i++) {
		execute();
		riavvolgi();
	}
	t1 = clock();

	res = (t1 - t0)/rip;

	return res;
}
__clock_t calcolaTempo_v2()
{
	__clock_t g = granularity();
	int rip = calcolaRip((int)((double)g/MAX_RELATIVE_MEASUREMENT_ERROR));
	__clock_t t0, t1, res;

	t0 = clock();
	for (int i=0; i<rip; i++) {
		execute_v2();
		riavvolgi();
	}
	t1 = clock();

	res = (t1 - t0)/rip;

	return res;
}



