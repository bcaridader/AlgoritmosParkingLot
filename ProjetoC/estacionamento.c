#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "estacionamento.h"
#include "parque.h"

//estacionar uma viatura
void estacionar(int n_pisos, int lugares_piso, ESTACIONAMENTO **parque, int piso, int lugar){
	int estacionado = 0;
	time_t t_entrada;
	time_t aux;
	while(!estacionado){
		if (piso >= n_pisos || lugar >= lugares_piso){
		
			printf("  | Lugar inexistente! Piso: [0 - %d], Lugar: [0 - %d]\n",n_pisos-1,lugares_piso-1);
			scanf("%d %d", &piso,&lugar);

		}else if(!parque[piso][lugar].ocupacao){

			printf("  | Qual e a matricula?\n");
			scanf("%s", parque[piso][lugar].matricula);
			while(!verifica_matricula(parque[piso][lugar].matricula)){
				printf("  | Qual e a matricula?\n");
				scanf("%s", parque[piso][lugar].matricula);
			}
			parque[piso][lugar].ocupacao = 1;
			printf("  | Carro estacionado\n");
			parque[piso][lugar].tempo_entrada = time(&t_entrada); //<- guarda em segundos
			printf("  | Piso: %d Lugar: %d\n", piso, lugar);
			printf("  | Tempo de entrada: ");
			convert((int) parque[piso][lugar].tempo_entrada);
			estacionado = 1;

		}else if(parque[piso][lugar].ocupacao){

			printf("  | Lugar ocupado!\n");
			scanf("%d %d", &piso,&lugar);
		}
	}
}

//pagamento
float pagamento(double diferenca){
	int hora = 3600;
	double custo_hora = 2.5;
	return (diferenca * custo_hora)/hora;
}

//remover carro
void retirar(int n_pisos, int lugares_piso, ESTACIONAMENTO **parque, char r_matricula[]){
	int i,j;
	time_t t_saida;
	int encontrado = 0;
	float pagar = 0;
	double diff_t;
	for(i=0;i<n_pisos;i++){
		for(j=0;j<lugares_piso;j++){
			if((strcmp(parque[i][j].matricula, r_matricula)) == 0 && !encontrado){
				parque[i][j].ocupacao = 0;
				//parque[i][j].matricula = '\0';
				memset(parque[i][j].matricula,0,strlen(parque[i][j].matricula));
				printf("%s\n",parque[i][j].matricula);
				printf("  | Carro encontrado e em movimento.\n");
				time(&t_saida);
				diff_t = difftime(t_saida, parque[i][j].tempo_entrada);
				pagar = pagamento(diff_t);
				encontrado = 1;
			}
		}	
	}
	if (!encontrado) printf("  | A matricula nao existe.\n");
	else{
		printf("  | A pagar: %0.2f\n", pagar);
	}
}

int verifica_matricula(char matricula[]){
	int size = strlen(matricula);
	int res = 0;
	if(size == 6){
		if(isalpha(matricula[0]) && isalpha(matricula[1]) && 
			isdigit(matricula[2]) && isdigit(matricula[3])&&
			isalpha(matricula[4]) && isalpha(matricula[5])){
			res = 1;
		}
	}else if(size == 8){
		if(isdigit(matricula[0]) && isdigit(matricula[1]) && matricula[2] == '-' &&
			isalpha(matricula[3]) && isalpha(matricula[4])&& matricula[5] == '-' && 
			isdigit(matricula[6]) && isdigit(matricula[7])){
			res = 1;
		}
	}else{
		printf("  | Matricula invalida.\n");
		res = 0;
	}
	return res;
}

int convert(int sec) {
	
	sec = sec % (24 * 3600);
    int h = sec / 3600;
 
    sec %= 3600;
    int m = sec / 60 ;
 
    sec %= 60;
    int s = sec;
	
	printf("%d:%d:%d\n",h,m,s);
	
	return 0;
}



