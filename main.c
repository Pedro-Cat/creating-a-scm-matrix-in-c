/******************************************************************/
/* Aluno: Pedro Henrique Catunda Rocha, Victor Hugo Araújo Abreu  */
/* Matrícula: 20221045050320, 20221045050397                      */
/* Avaliação 04: Trabalho Final                                   */
/* Compilador: (MinGW.org GCC-6.3.0-1) 6.3.0                      */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "scm.h"

#define QTDIMG 1312

int main(int argc, char *argv[]){

	// Verificação do formato
    if (argc!=4 || atoi(argv[2])%8 || atoi(argv[2])>256 || atoi(argv[2])<8){
        printf("Formato: \n\t %s <./diretorioImagens/> <quantizationLevel> <nomeTxt.txt>\n", argv[0]);
        printf("OBS: \n\t <quantizationLevel>: Multiplo de 8\n");
        exit(1);
    }

	// Ponteiro para as funções criadas
    void (*pRead)(struct pgm *, char *, char *) = &readPGMImage;
    void (*pQuant)(struct pgm *, short *) = &quantPGM;
    void (*pSCM)(struct pgm *, struct pgm *, int *) = &matrixSCM;
    void (*pSCMtoTxt)(int *, short *, FILE *, char *) = &SCMtoTxt;

    // Tempo total
    clock_t begin, end;
    double time_per_img, time_total=0;

    // INICIO
    short int *nivel = malloc(sizeof(short int));
	*nivel = (short int)atoi(argv[2]);

    DIR *d;
    struct dirent *dir;
    struct pgm img1, img2;

    d = opendir(argv[1]);

    if(d){
		
		// Cria e abre arquivo .txt
		FILE *f;
		if (!(f = fopen(argv[3],"a+"))){
			perror("Erro.");
			exit(2);
		}
		
		// Varre diretório
        while ((dir = readdir(d)) != NULL){

			// Inicio do timer
            begin = clock();
            
			// Verifica se é um arquivo válido
            while(strstr(dir->d_name, "_mean.pgm") != NULL || (*(dir->d_name)!='0' && *(dir->d_name)!='1')){
				if((dir = readdir(d)) == NULL) break;
            }
			if(dir == NULL) break;

			// Leitura e quantização da imagem não filtrada
            (*pRead)(&img1, argv[1], dir->d_name);
            (*pQuant)(&img1, nivel);

            // Processamento para obter o nome da imagem filtrada correspondente a anterior
            dir->d_name[(strlen(dir->d_name)-4)] = '\0';
            strcat(dir->d_name, "_mean.pgm");
			// Leitura e quantização da imagem filtrada
            (*pRead)(&img2, argv[1], dir->d_name);
            (*pQuant)(&img2, nivel);

			// Declaração de um ponteiro que será o vetor/matriz SCM
            int *m;
            if(!(m = calloc(*nivel * *nivel, sizeof(int)))){
                printf("Memória insuficiente!\n");
                exit(3);
            }
			
			// Criação do vetor/matriz SCM
            (*pSCM)(&img1, &img2, m);
			// Passagem do vetor SCM para o .txt gerado
            (*pSCMtoTxt)(m, nivel, f, dir->d_name);

            free(m);

			// Fim do timer
            end = clock();
            time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
            time_total += time_per_img;
            
        }

		free(nivel);
		fclose(f);
		closedir(d);
		
    }

    printf("Total:\n");
    printf("Tempo médio: %lf\n",time_total/QTDIMG);
    printf("Tempo Total: %lf\n",time_total);
    
    return 0;

}
