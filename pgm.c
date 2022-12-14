/******************************************************************/
/* Aluno: Pedro Henrique Catunda Rocha, Victor Hugo Araújo Abreu  */
/* Matrícula: 20221045050320, 20221045050397                      */
/* Avaliação 04: Trabalho Final                                   */
/* Compilador: (MinGW.org GCC-6.3.0-1) 6.3.0                      */
/******************************************************************/

#include "pgm.h"

void quantPGM(struct pgm *pio, short *n){
    int q = 256 / *n;
	pio->mv = pio->mv / q;
	for (int k=0; k < (pio->r * pio->c); k++){
		*(pio->pData+k) = *(pio->pData+k) / q;
	}
}

void readPGMImage(struct pgm *pio, char *dir, char *filename){
	
	FILE *fp;
	char ch, *new_name = NULL;

	if(!(new_name = malloc((strlen(dir) + strlen(filename)) * sizeof(char)))){
		printf("Memoria insuficiente!\n");
		exit(1);
	}

	sprintf(new_name, "%s%s", dir, filename);
	if(!(fp = fopen(new_name,"r"))){
		perror("Erro.");
		exit(1);
	}
	free(new_name);

	if((ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-2, SEEK_CUR);

	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->mv);
	fseek(fp,1, SEEK_CUR);

	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Não está implementado");
			exit(4);
	}
	
	fclose(fp);
}