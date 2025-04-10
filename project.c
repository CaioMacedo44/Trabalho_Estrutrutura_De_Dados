#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structprojeto.h"
#include "funcoes.c"


int main(){
	FILE* arq;
	int tamanho = 0;
	Processo* array = (Processo*)malloc(sizeof(Processo) * 1);
	int i; 
	int acao;
	int quantPros = 0;
	int id_processo;
	int dias_tramitacao = 0;
	char num_id_classe[10];
	
	arq = fopen("processo_043_202409032338.csv", "r");
	
	if (arq == NULL){
		printf("Falha ao abrir!");
		return 1;
	}
	
	lerArquivo(arq, &array, &tamanho);
	
	do{
	print_menu();
	scanf("%d",&acao);
	switch(acao) {
		case 1:
			printf("Ordenando..");
			ordenarCrescenteId(array, tamanho);
			escreverArqCSV(array, tamanho, "ordenadoiD.csv");
			break;
			
		case 2:
			printf("Ordenando..");
			ordenarDecrescenteDataAjuizado(array, tamanho);
			escreverArqCSV(array, tamanho, "ordenadoData.csv");
			
			break;
		
		case 3:
			printf("Digite o id classe: ");
			scanf("%s" , num_id_classe );
			quantPros = contarIdClasse(array, num_id_classe, tamanho);
			printf("Quantidade de processo da classe: %s\nQuantidade: %d\n", num_id_classe, quantPros);
			break;
		case 4:
			IndentificarQuantAssuntos(array, tamanho);
			break;
		
		case 5:
			printf("Processos vinculados a mais de um assunto\n");
			ListarIdAssuntoMaisDeUm(array, tamanho);
			break;
		
		case 6:
			printf("\nDigite o numero do id do processo:");
			scanf("%d",&id_processo);
			dias_tramitacao = processoTramitacao( array , id_processo , &tamanho );
			if(dias_tramitacao != -1){
			printf("\nO processo esta ha %d dias em tramitacao na justica\n" , dias_tramitacao);
			break;
		}
			break;
		
		case(-1):
			printf("ENCERRANDO!\n");
			break;
		
		default:
			printf("ERRO\nOpcao invalida\n");
	}
	system("pause");
	system("cls");	
}while(acao != -1);	

	
	fclose(arq);
	return 0;
}
