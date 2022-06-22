#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SIZE 12

//booleano que verifica se todos os vértices já foram visitados.
int verificar(int vertices[]){
	for(int i = 0; i < SIZE; i++){
		if(vertices[i] == 0){
			//printf("Vértice %d não foi acessado!\n", i);
			return 0;
		}
	}
	return 1;
}

//função dedicada a zerar o valor de todos os vértices para que seja possível realizar outra simulação.
void inicializar(int vertices[]){
	for(int i = 0; i < SIZE; i++){
		vertices[i] = 0;
	}
}

//função dedicada a realizar todas as simulações.
float gerar(int runs, int vertices[]){
	int passos = 0;
	int pos = 0;
	
	for(int i = 0; i < runs; i++){
		
		//inicialização da run.
		pos = 0;
		inicializar(vertices);
		vertices[pos]++;
		
		//processo de uma run.
		while(!verificar(vertices)){
			if((rand()%2) == 1){
				pos = (((pos+1)%SIZE)+SIZE)%SIZE;
				vertices[pos]++;			
			}
			else{
				pos = (((pos-1)%SIZE)+SIZE)%SIZE;
				vertices[pos]++;
			}
			passos++;
			//printf("Passo nº%d dado. \n", passos);
		}
	}
	
	//retorno da quantidade média de passos para atingir o objetivo de uma run.
	return ((float)passos/runs);
}

int main(int argc, char* argv[]){
	
	//variáveis globais.
	float media;
	int runs = 0;
	int vertices[SIZE];
	srand(time(NULL));

	//leitura e avaliação dos parâmetros de entrada.
	if(argc<2) {
		printf("Digite: %s <quantidade de execuções>\n", argv[0]);
		return 1;
	}
	
	//passa a quantidade de execuções e chama a função para fazer todas as simulações pedidas.
	runs = atoi(argv[1]);
	media = gerar(runs, vertices);
	
	printf("Após %d execuções, constatamos que o valor médio de passos para passar por todos os vértices é %.2f\n", runs, media);
	
	return 0;
}
