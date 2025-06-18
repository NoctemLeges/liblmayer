CC = gcc
CFLAGS = -Wall -lm
SRC = ../src/word.c ../src/parseconf.c ../src/render.c ../src/strexp.c

bush1: Bushes/Bush1/bush1.c
	$(CC) $(SRC) $< -o Bushes/Bush1/$@ $(CFLAGS)

bush2: Bushes/Bush2/bush2.c
	$(CC) $(SRC) $< -o Bushes/Bush2/$@ $(CFLAGS)

triangle1: Triangles/Triangle1/triangle1.c
	$(CC) $(SRC) $< -o Triangles/Triangle1/$@ $(CFLAGS)

triangle2: Triangles/Triangle2/triangle2.c
	$(CC) $(SRC) $< -o Triangles/Triangle2/$@ $(CFLAGS)

MA1: MultiAlphabet/MA1/MA1.c
	$(CC) $(SRC) $< -o MultiAlphabet/MA1/$@ $(CFLAGS)

MA2: MultiAlphabet/MA2/MA2.c
	$(CC) $(SRC) $< -o MultiAlphabet/MA2/$@ $(CFLAGS)

all: bush1 bush2 triangle1 triangle2 MA1 MA2