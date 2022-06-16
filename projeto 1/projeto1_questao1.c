#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SIZE 12

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    assert (n <= RAND_MAX);

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew
    assert (end > 0);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

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
	int total_passos = 0;
	
	for(int i = 0; i < runs; i++){
		
		//inicialização da run.
		passos = 0;
		pos = 0;
		inicializar(vertices);
		vertices[pos]++;
		
		//processo de uma run.
		while(!verificar(vertices)){
			if(randint(2) == 1){
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
		total_passos += passos;
	}
	
	//retorno da quantidade média de passos para atingir o objetivo de uma run.
	return ((float)total_passos/runs);
}

int main(int argc, char* argv[]){
	
	//variáveis globais.
	float media;
	int runs = 0;
	int vertices[SIZE];
	srand(time(NULL));
	
	//inicialização do vetor de vértices. O conteúdo de cada índice representa a quantidade de acessos que já ocorreram ao respectivo vértice.
	inicializar(vertices);

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
