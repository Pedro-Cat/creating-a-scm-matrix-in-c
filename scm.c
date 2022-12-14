/******************************************************************/
/* Aluno: Pedro Henrique Catunda Rocha, Victor Hugo Araújo Abreu  */
/* Matrícula: 20221045050320, 20221045050397                      */
/* Avaliação 04: Trabalho Final                                   */
/* Compilador: (MinGW.org GCC-6.3.0-1) 6.3.0                      */
/******************************************************************/

#include "scm.h"

void matrixSCM(struct pgm *pio1, struct pgm *pio2, int *m){
    for(int i = 0; i < (pio1->r * pio1->c); i++){
        *(m + (*(pio2->pData+i) * (pio1->mv+1)) + *(pio1->pData+i)) += 1;
    }
}

void SCMtoTxt(int *m, short *tam, FILE *fp, char *img_name){

    for(int i = 0; i < *tam * *tam; i++){
        fprintf(fp, "%d,", *(m+i));
    }
    fprintf(fp, "%c\n", *img_name);

}