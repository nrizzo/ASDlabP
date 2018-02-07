/*
 * github.com/nrizzo
 * src/tcalc/talgs/talgs.c
 *
 * Codice che genera testi e calcola i tempi dell'algoritmo risolutivo su
 * questi.
 */

#include "taux.h"
#include "talgs.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>


void preparecorpus2()
{
	taux_preparecorpus2();
}

void preparecorpus3()
{
	taux_preparecorpus3();
}

struct result *misurazione1(int length, int c, double za, double maxreldelta)
{
	__clock_t t = 0;
	__clock_t sum2 = 0;
	int cn = 0;

	__clock_t m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara1(length);
			m = calcolaTempo();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	struct result *r = malloc(sizeof(struct result));
	r->e = e;
	r->delta = delta;
	return r;
}

struct result *misurazione2(int words, int c, double za, double maxreldelta)
{
	__clock_t t = 0;
	__clock_t sum2 = 0;
	int cn = 0;

	__clock_t m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara2(words);
			m = calcolaTempo();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	struct result *r = malloc(sizeof(struct result));
	r->e = e;
	r->delta = delta;
	return r;
}

struct result *misurazione2_v2(int words, int c, double za, double maxreldelta)
{
	__clock_t t = 0;
	__clock_t sum2 = 0;
	int cn = 0;

	__clock_t m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara2(words);
			m = calcolaTempo_v2();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	struct result *r = malloc(sizeof(struct result));
	r->e = e;
	r->delta = delta;
	return r;
}

struct result *misurazione3(int words, int c, double za, double maxreldelta)
{
	__clock_t t = 0;
	__clock_t sum2 = 0;
	int cn = 0;

	__clock_t m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara3(words);
			m = calcolaTempo();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	struct result *r = malloc(sizeof(struct result));
	r->e = e;
	r->delta = delta;
	return r;
}

struct result *misurazione3_v2(int words, int c, double za, double maxreldelta)
{
	__clock_t t = 0;
	__clock_t sum2 = 0;
	int cn = 0;

	__clock_t m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara3(words);
			m = calcolaTempo_v2();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	struct result *r = malloc(sizeof(struct result));
	r->e = e;
	r->delta = delta;
	return r;
}

double nodi1(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara1(length);
			m = calcolaNodi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}

double nodi2(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara2(length);
			m = calcolaNodi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}

double nodi3(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara3(length);
			m = calcolaNodi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}

double archi1(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara1(length);
			m = calcolaArchi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}

double archi2(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara2(length);
			m = calcolaArchi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}

double archi3(int length, int c, double za, double maxreldelta)
{
	double t = 0;
	double sum2 = 0;
	int cn = 0;

	double m;
	double s,e,delta;

	do {
		for (int i=0; i<c; i++) {
			prepara3(length);
			m = calcolaArchi();
			t = t + m;
			sum2 = sum2 + (m*m);
		}
		cn = cn + c;
		e = (double)t/(double)cn;
		s = sqrt(sum2/(double)cn - (e*e));
		delta = (1.0/sqrt((double)cn))*za*s;
	} while ( delta/e > maxreldelta );

	return e;
}
