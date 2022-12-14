#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

void readPGMImage(struct pgm *, char *, char *);
void quantPGM(struct pgm *, short *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);