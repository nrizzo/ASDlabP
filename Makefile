SHELL = /bin/sh

CC = clang
CFLAGS = -pedantic
OBJECTS = obj/algs.o \
	  obj/aux.o \
          obj/graph.o \
          obj/cvector.o \
          obj/node.o \
          obj/list.o \
          obj/text.o \
          obj/word.o \
          obj/utf8char.o \
          obj/alpha.o
CTOBJECTS = obj/talgs.o \
	    obj/taux.o \
	    obj/prng.o
MKDR = mkdir

.PHONY: all clean

all: algoritmo_risolutivo calcolo_tempi

algoritmo_risolutivo: obj obj/main.o $(OBJECTS)
	$(CC) obj/main.o $(OBJECTS) -o $@ $(CFLAGS)
calcolo_tempi: obj obj/tcalc.o  $(CTOBJECTS) 
	$(CC) obj/tcalc.o $(OBJECTS) $(CTOBJECTS) -o $@ -lm $(CFLAGS)

obj:
	$(MKDR) $@
obj/main.o: src/main.c
	$(CC) -c src/main.c -o $@ $(CFLAGS)
obj/algs.o: src/algs/algs.h src/algs/algs.c
	$(CC) -c src/algs/algs.c -o $@ $(CFLAGS)
obj/aux.o: src/algs/aux.h src/algs/aux.c
	$(CC) -c src/algs/aux.c -o $@ $(CFLAGS)
obj/graph.o: src/graph/graph.h src/graph/graph.c
	$(CC) -c src/graph/graph.c -o $@ $(CFLAGS)
obj/node.o: src/graph/node/node.h src/graph/node/node.c
	$(CC) -c src/graph/node/node.c -o $@ $(CFLAGS)
obj/cvector.o: src/graph/cvector/cvector.h src/graph/cvector/cvector.c
	$(CC) -c src/graph/cvector/cvector.c -o $@ $(CFLAGS)
obj/list.o: src/list/list.h src/list/list.c
	$(CC) -c src/list/list.c -o $@ $(CFLAGS)
obj/text.o: src/text/text.h src/text/text.c
	$(CC) -c src/text/text.c -o $@ $(CFLAGS)
obj/word.o: src/text/word/word.h src/text/word/word.c
	$(CC) -c src/text/word/word.c -o $@ $(CFLAGS)
obj/alpha.o: src/text/alpha/alpha.h src/text/alpha/alpha.c
	$(CC) -c src/text/alpha/alpha.c -o $@ $(CFLAGS)
obj/utf8char.o: src/text/utf8char/utf8char.h src/text/utf8char/utf8char.c
	$(CC) -c src/text/utf8char/utf8char.c -o $@ $(CFLAGS)
obj/tcalc.o: src/tcalc/tcalc.c
	$(CC) -c src/tcalc/tcalc.c -o $@ $(CFLAGS)
obj/talgs.o: src/tcalc/talgs/talgs.h src/tcalc/talgs/talgs.c
	$(CC) -c src/tcalc/talgs/talgs.c -o $@ $(CFLAGS)
obj/taux.o: src/tcalc/talgs/taux.h src/tcalc/talgs/taux.c
	$(CC) -c src/tcalc/talgs/taux.c -o $@ $(CFLAGS)
obj/prng.o: src/tcalc/talgs/prng/prng.h src/tcalc/talgs/prng/prng.c
	$(CC) -c src/tcalc/talgs/prng/prng.c -o $@ $(CFLAGS)

clean:
	rm -Rf obj
