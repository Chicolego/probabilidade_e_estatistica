#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define LINHAS 3
#define COLUNAS 3

//posição em linha e coluna de cada armadilha.
#define LTRAP1 0
#define LTRAP2 2
#define CTRAP1 0
#define CTRAP2 2

float trap1 = 0.0;
float trap2 = 0.0;
float central = 0.0;

//função dedicada a zerar o valor de todas as casas do tabuleiro para que seja possível realizar outra simulação.
void inicializar(int tabuleiro[LINHAS][COLUNAS]){
	for(int i = 0; i < LINHAS; i++){
		for(int k = 0; k < COLUNAS; k++){
			tabuleiro[i][k] = 0;
		}
	}
}

//função dedicada a realizar todas as simulações.
float simular(int runs, int tabuleiro[LINHAS][COLUNAS], int pos_linha, int pos_coluna){
	int saltos = 0;
	int pos_laux, pos_caux, random;
	
	for(int i = 0; i < runs; i++){
		
		//inicialização da run.
		pos_laux = pos_linha;
		pos_caux = pos_coluna;
		inicializar(tabuleiro);
		tabuleiro[pos_laux][pos_caux]++;
		
		//processo de uma run.
		while(tabuleiro[pos_laux][pos_caux] != tabuleiro[LTRAP1][CTRAP1] && tabuleiro[pos_laux][pos_caux] != tabuleiro[LTRAP2][CTRAP2] ){
			random = rand()%4;
			switch(random){
				// cima
				case 0:
					if(pos_laux+1 != LINHAS){
						pos_laux++;
						tabuleiro[pos_laux][pos_caux]++;
						saltos++;								
					}
				break;
				
				//baixo
				case 1:
					if(pos_caux+1 != COLUNAS){
						pos_caux++;	
						tabuleiro[pos_laux][pos_caux]++;
						saltos++;		
					}
				break;
				
				//esquerda
				case 2:
					if(pos_laux != 0){
						pos_laux--;
						tabuleiro[pos_laux][pos_caux]++;
						saltos++;								
					}
				break;
				
				//direita
				case 3:
					if(pos_caux != 0){
						pos_caux--;
						tabuleiro[pos_laux][pos_caux]++;
						saltos++;						
					}

				break;	
			}
		}
		
		//checagem de qual armadilha a mosca caiu.
		if(pos_laux == LTRAP1 && pos_caux == CTRAP1){
			trap1++;
		}
		else{trap2++;}
		
		//computa visitas na casa central.
		central += tabuleiro[(LINHAS-1)/2][(COLUNAS-1)/2];
	}
	
	//retorno da quantidade média de saltos para a mosca ser capturada em uma run.
	return ((float)saltos/runs);
}

int main(int argc, char* argv[]){
	
	float media;
	int runs, pos_linha, pos_coluna;
	int tabuleiro[LINHAS][COLUNAS];
	srand(time(NULL));

	//leitura e avaliação dos parâmetros de entrada.
	if(argc<4) {
		printf("Digite: %s <Quantidade de Execuções> <Linha Inicial> <Coluna Inicial>\n", argv[0]);
		return 1;
	}
	
	//passa a quantidade de execuções e a posição inicial e chama a função para fazer todas as simulações pedidas.
	runs = atoi(argv[1]);
	pos_linha = atoi(argv[2]);
	pos_coluna = atoi(argv[3]);
	media = simular(runs, tabuleiro, pos_linha, pos_coluna);
	
	printf("Execuções: %d\nPosição Inicial: [%d][%d]\nMédia de Saltos: %.2f \nArmadilha 1: %.2f por cento \nArmadilha 2: %.2f por cento \nVisitas ao Centro: %.2f", runs, pos_linha, pos_coluna, media, (trap1/runs)*100, (trap2/runs)*100, (central/runs));
	
	return 0;
}
