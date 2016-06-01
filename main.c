/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jessica
 *
 * Created on 1 de Junho de 2016, 18:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double aleatorio() {
	double u;
	u = rand() % RAND_MAX;
	u = u / RAND_MAX;
	u = 1.0 - u;
	return (u);
}

double minimo(double a, double b){
	if(a < b)
		return a;
	else
		return b;
}

int main() {
	//parametro Exponencial, intervaloChegadas
	double lChegada, lSaida;
	
	//tempo de chegada da proxima requisicao
	double tChegada;
	//tempo total de simulacao
	double tSimulacao = 10000;
	//tempo atual de execucao
	double tDecorrido = 0.0;
	//fila do sistema, lembrando que
	//a cabeca da fila eh quem esta
	//em atendimento.
	double fila = 0.0;
	
	//tempo que o servidor gasta atendendo
	double tSaida = 0.0;

	printf("Informe o tempo medio entre chegadas: ");
	scanf("%lF", &lChegada);
	printf("\n");
	
	printf("Informe o tempo medio de atendimento: ");
	scanf("%lF", &lSaida);
	printf("\n");
	
	lChegada = 1.0/lChegada;
	
	lSaida = 1.0/lSaida;
	
	/**************************
	 *  Iniciando semente     *
	 **************************/
	int sementeAleat;
	sementeAleat = time(NULL); //retorna um inteiro com base na hora do sistema
	srand(sementeAleat); //inicia o rand
	
	/************************
	 *	     Execucao       *
	 ************************/
	//gerar o tempo de chegada da primeira requisicao
	tChegada = (-1.0 / lChegada) * log(aleatorio());
	
	do{
		if(tSaida > 0.0)
			tDecorrido = minimo(tChegada, tSaida);
		else
			tDecorrido = tChegada;

		//tratando chegada de requisicoes
		if(tDecorrido == tChegada){
			printf("Chegou: %lF\n", tDecorrido);
			if(!fila){
				tSaida = tDecorrido + (-1.0 / lSaida) * log(aleatorio());
			}
			fila++;
			//gerando a chegada da proxima requisicao
			tChegada = tDecorrido + ((-1.0 / lChegada) * log(aleatorio()));
		}else{//tratando saida de requisicoes
			printf("Saiu: %lF\n", tDecorrido);
			fila --;
			if(fila){
				tSaida = tDecorrido + (-1.0 / lSaida) * log(aleatorio());
			}else{
				tSaida = 0.0;
			}
		}
	}while(tDecorrido < tSimulacao);
	printf("Fim: %lF\n", tDecorrido);

	exit(0);
}

