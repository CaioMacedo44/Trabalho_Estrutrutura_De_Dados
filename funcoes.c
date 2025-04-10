#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "structprojeto.h"



void limparString(char* string){
	int i;
	for(i = 0 ; i < 49; i++){
		string[i] = '\0';
		if (string[i + 1] == '\0'){
			break;
		}
	}
}

int encontrarFinalDasChaves(FILE* arq, char* string, int* i){
	char ch;
	string[(*i)] = ',';
	while((ch = fgetc(arq)) != EOF){
		(*i)++;
		if (ch == '"'){
			string[(*i)] = ch;
			(*i)++;
			ch = fgetc(arq);
			string[(*i)] = '\0';
			break;
		} else {
			string[(*i)] = ch;
		}
	}
}

Data preencherData(char* string){
	Data data;
	sscanf(string, "%4d-%2d-%2d %2d:%2d:%5f", 
	       &data.year, &data.month, &data.day,
	       &data.hour, &data.minute, &data.second);
	return data;
}

void retirarChavesEAspas(char* string, Processo* processo, int idClasseTrue){
	int i = 0;
	int j = 0;
	int k = 0;
	char subString[10];
	char* newString;
	while(string[i] != '\0'){
		if(string[i] == ',' || string[i] == '}'){
			subString[j] = '\0';
			
			if(subString[0] == '{') {
				newString = subString + 1;
			} else if(subString[0] == '"') {
				newString = subString + 2;	
			} else {
				newString = subString;	
			}
			if(idClasseTrue == 1){
				strcpy((*processo).id_class[k], newString);
			} else {
				strcpy((*processo).id_subject[k], newString);
			}	
			
			limparString(subString);
			j = 0;
			k += 1;
			i++;
		} else {
			subString[j] = string[i];
			i++;
			j++;
		}
	}
	subString[0] = '\0';
	while(k < 5){
		if(idClasseTrue == 1){
			strcpy((*processo).id_class[k], subString);
		} else {
			strcpy((*processo).id_subject[k], subString);
		}
		k += 1;	
	}
}

void preencherStruct(Processo* array, char* string, int id, int campo){
	switch(campo){
		case 1:
			array[id].id = atoi(string);
			break;
		case 2:
			strcpy(array[id].number, string);
			break;
		case 3:
			array[id].data = preencherData(string);
			break;
		case 4:
			retirarChavesEAspas(string, &array[id], 1);
			break;
		case 5:
			retirarChavesEAspas(string, &array[id], 0);
			break;
		case 6:
			strcpy(array[id].year_election, string);
			break;
		default:
			printf("Erro nos campos!");
			exit(1);
	}
}

void lerArquivo(FILE* arq, Processo** array, int* tamanho){
	char ch;
	char string[50];
	int i = 0;
	int campo = 1;
	int id = 0;
	
	while ((ch = fgetc(arq)) != EOF) {
		if (ch == '\n') {
			break;
		}
	}
	while((ch = fgetc(arq)) != EOF) {
		if (ch == ',' || ch == '\n' ) {	
			if(string[0] == '"' && string[1] == '{'){ // caso seja multi valorado, dai eu fiz isso
				encontrarFinalDasChaves(arq, string, &i);
			}
			i++;
			string[i] = '\0';
			
			//if(campo == 6) // printa o campo escolhido, se quiser testar coloca valor entre 1 a 6
			//	printf("%s\n", string);
			
			preencherStruct(*array, string, id, campo);	
			
			campo += 1;
			if (campo > 6){ // Isso aqui eh os campos, para quando chegar no ultimo ele voltar para o primeiro
				campo = 1;
				id += 1;
				(*tamanho) = id + 1;
				
				*array = realloc(*array, sizeof(Processo) * (id + 1));
				if (*array == NULL) {
					printf("Erro ao realocar memoria!");
					exit(1);
				}
				
			}
			
			limparString(string);
			i = 0;
			
		} else {
			string[i] = ch;
			i++;
		}
	}
}

void ordenarCrescenteId(Processo *array, int tamanho){
	int i, j;
	Processo temp;
	for(i = 0; i < tamanho - 1 ; i++){
		for(j = i + 1 ; j < tamanho ; j++){
			if(array[i].id > array[j].id){
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

void ordenarDecrescenteDataAjuizado(Processo *array, int tamanho){
    int i, j;
    Processo temp;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = i + 1; j < tamanho; j++) {
            if (array[i].data.year < array[j].data.year) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else if (array[i].data.year == array[j].data.year) {
                if (array[i].data.month < array[j].data.month) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
                else if (array[i].data.month == array[j].data.month) {
                    if (array[i].data.day < array[j].data.day) {
                        temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                    else if (array[i].data.day == array[j].data.day) {
                        if (array[i].data.hour < array[j].data.hour) {
                            temp = array[i];
                            array[i] = array[j];
                            array[j] = temp;
                        }
                        else if (array[i].data.hour == array[j].data.hour) {
                            if (array[i].data.minute < array[j].data.minute) {
                                temp = array[i];
                                array[i] = array[j];
                                array[j] = temp;
                            }
                            else if (array[i].data.minute == array[j].data.minute) {
                                if (array[i].data.second < array[j].data.second) {
                                    temp = array[i];
                                    array[i] = array[j];
                                    array[j] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void print_menu(){
	printf("Escolha o que desejar:\n");
	printf("--------------------------------------------------------------------------------------\n");
	
	printf("\t  1- Ordenar em ordem crescente do ID\n\n");	
	printf("\t  2- Ordenar em decrescente por data de ajuizamento\n\n");
	printf("\t  3- Quantia de processo relacionada ao ID classe\n\n");
	printf("\t  4- Quantidade de IDs assunto\n\n");
	printf("\t  5- Quantidade de processos com mais de um ID assunto\n\n");
	printf("\t  6- Tempo de tramitacao do processo\n\n");
	printf("\t -1- Encerra o programa\n\n");

	printf("--------------------------------------------------------------------------------------\n");
}

void printStruct(Processo processo){
	printf("ID: %d\n", processo.id);
	printf("Numero: %s\n", processo.number);
	printf("DATA\n");
	printf("Ano: %d\n", processo.data.year);
	printf("Mes: %d\n", processo.data.month);
	printf("Dia: %d\n", processo.data.day);
	printf("Hora: %d\n", processo.data.hour);
	printf("Min: %d\n", processo.data.minute);
	printf("Seg: %.3f\n", processo.data.second);
	printf("Id_Classe:\n"); 
	printf("%s \n", processo.id_class[0]);
	if(processo.id_class[1][0] != '\0'){
		printf("%s\n", processo.id_class[1]);	
	}
	if(processo.id_class[2][0] != '\0'){
		printf("%s\n", processo.id_class[2]);	
	}
	if(processo.id_class[3][0] != '\0'){
		printf("%s\n", processo.id_class[3]);	
	}
	
	printf("Id_Assunto:\n");
	printf("%s\n", processo.id_subject[0]);
	if(processo.id_subject[1][0] != '\0'){
		printf("%s\n", processo.id_subject[1]);	
	} 
	if(processo.id_subject[2][0] != '\0'){
		printf("%s\n", processo.id_subject[2]);	
	}
	if(processo.id_subject[3][0] != '\0'){
		printf("%s\n", processo.id_subject[3]);	
	}  
	
	
	printf("Ano de eleicao: %s\n", processo.year_election);
	printf("\n\n");
}

int contarIdClasse(Processo* array, char* string, int tamanho){
	int i;
	int quant = 0;
	for(i = 0 ; i < tamanho ; i++){	
		if(strcmp(string, array[i].id_class[0]) == 0){
			quant += 1;	
		}
		if(strcmp(string, array[i].id_class[1]) == 0){
			quant += 1;
		}
		if(strcmp(string, array[i].id_class[2]) == 0){
			quant += 1;
		}
	}
	return quant;
}

void ListarIdAssuntoMaisDeUm(Processo* array, int tamanho){
	int i;
	for(i = 0 ; i < tamanho ; i++){	
		if (array[i].id_subject[1][0] != '\0'){
			printStruct(array[i]);
		}
	}
}

bool contem(int* array, int elemento, int tamanho){
	int i;
	for(i = 0; i < tamanho ; i++){
		if (array[i] == elemento){
			return true;
		}
	}
	return false;
}

void IndentificarQuantAssuntos(Processo* array, int tamanho){
	int i = 0;
	int j = 0;
	int tamanhoIntArray = 0;
	int elemento = 0;
	int* intArray = malloc(sizeof(int) * 100);
	for( ; i < tamanho ; i++){
		while (array[i].id_subject[j][0] != '\0'){
			elemento = atoi(array[i].id_subject[j]);
			if(!contem(intArray, elemento, tamanhoIntArray + 1)){
				intArray[tamanhoIntArray] = elemento;
				tamanhoIntArray += 1;
				intArray = realloc(intArray, (tamanhoIntArray + 1) * sizeof(int));
			} 
			j++;
		}
		j = 0;
	}
	printf("Todos os assuntos no banco de dados sao:\n\n");
	for(i = 0; i < tamanhoIntArray ; i++){
		printf("\t%d\n", intArray[i]);
	}	
}

void formatarCorreto(Processo processo, bool classId, char* string){
	char stringReturn[50];
	stringReturn[0] = '\0';
	int j = 0;
	if(classId){
		if(processo.id_class[1][0] != '\0') {
			strcat(stringReturn, "\"{");
			strcat(stringReturn, processo.id_class[j]);
			
			j++;
			while(processo.id_class[j][0] != '\0'){
				strcat(stringReturn, ",");
				strcat(stringReturn, processo.id_class[j]);
				j += 1;
			}
			strcat(stringReturn, "}\"");
		} else {
			strcat(stringReturn, "{");
			strcat(stringReturn, processo.id_class[j]);
			strcat(stringReturn, "}");
		}
		strcpy(string, stringReturn);	
	} else {
		if(processo.id_subject[1][0] != '\0') {
			strcat(stringReturn, "\"{");
			strcat(stringReturn, processo.id_subject[j]);
			
			j++;
			while(processo.id_subject[j][0] != '\0'){
				strcat(stringReturn, ",");
				strcat(stringReturn, processo.id_subject[j]);
				j += 1;
			}
			strcat(stringReturn, "}\"");
		} else {
			strcat(stringReturn, "{");
			strcat(stringReturn, processo.id_subject[j]);
			strcat(stringReturn, "}");
		}
		strcpy(string, stringReturn);
	}
}

void escreverArqCSV(Processo* array, int tamanho, char* nome){
	FILE* arq;
	arq = fopen(nome, "w");
	int i;
	char string[200];
	char idClassString[50];
	char idSubjectString[50];
	
	fprintf(arq, "id;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");
	for(i = 0 ; i < tamanho ; i++){
		
		formatarCorreto(array[i], true, idClassString);
		formatarCorreto(array[i], false, idSubjectString);
		if(array[i].id != 0){
		sprintf(string, "%d,%s,%04d-%02d-%02d %02d:%02d:%.3f,%s,%s,%s\n",
		    array[i].id,
		    array[i].number,
		    array[i].data.year,
		    array[i].data.month,
		    array[i].data.day,
		    array[i].data.hour,
		    array[i].data.minute,
		    array[i].data.second,
		    idClassString,
		    idSubjectString,
		    array[i].year_election
		);

		limparString(idClassString);
		fprintf(arq, "%s", string);
	}
	}
	fclose(arq);
}

int processoTramitacao( Processo *array , int id_processo , int *tamanho ){
	int i;
	char data_atual[25];
	char dia[4];
	char mes[4];
	int temp_tramt = 0 ;
	time_t tempo_atual = time(NULL);
	Data num_data_atual;

	sprintf(data_atual , ctime(&tempo_atual));

	for( i = 0 ; i < sizeof(data_atual) ; i++){
		if(data_atual[i] == ' '){
			data_atual[i] = ',';
		}
	}
	sscanf( data_atual , "%[^,],%[^,],%d,%d:%d:%d,%d", dia , mes, &num_data_atual.day , &num_data_atual.hour , &num_data_atual.minute , &num_data_atual.second , &num_data_atual.year  );

	compararMes( mes , &num_data_atual );

	for( i = 0; i < (*tamanho) ; i++)
		if ((array[i].id - id_processo) == 0)break;
	
	if(array[i].id - id_processo != 0)return -1;
	
	calculoTramitacao( &array[i].data , &num_data_atual , &temp_tramt );

	 return temp_tramt;
	
}

void compararMes( char mes[4] , Data *month_struct ){

	if( strcmp( mes , "Jan" ) == 0){
		month_struct->month = 1;
	}
	else if( strcmp( mes , "Feb" ) == 0){
		month_struct->month = 2;
	}
	else if( strcmp( mes , "Mar" ) == 0){
		month_struct->month = 3;
	}
	else if( strcmp( mes , "Apr" ) == 0){
		month_struct->month = 4;
	}
	else if( strcmp( mes , "May" ) == 0){
		month_struct->month = 5;
	}
	else if( strcmp( mes , "Jun" ) == 0){
		month_struct->month = 6;
	}
	else if( strcmp( mes , "Jul" ) == 0){
		month_struct->month = 7;
	}
	else if( strcmp( mes , "Aug" ) == 0){
		month_struct->month = 8;
	}
	else if( strcmp( mes , "Sep" ) == 0){
		month_struct->month = 9;
	}
	else if( strcmp( mes , "Oct" ) == 0){
		month_struct->month = 10;
	}
	else if( strcmp( mes , "Nov" ) == 0){
		month_struct->month = 11;
	}
	else if( strcmp( mes , "Dec" ) == 0){
		month_struct->month = 12;
	}

}

void calculoTramitacao( Data *Processo_data , Data *Data_atual , int *temp_tramt ){
	*temp_tramt +=  ( Data_atual->year >= Processo_data->year )? 365 * (Data_atual->year - Processo_data ->year ) :  ( Processo_data-> year - Data_atual->year ) ;
	
	*temp_tramt += ( Data_atual->month >= Processo_data->month )? 30 * ( Data_atual->month - Processo_data->month ) : (30 * ( Data_atual->month + (12 - Processo_data->month ) )) - 365;
	
	*temp_tramt += ( Data_atual->day >= Processo_data->day )? (Data_atual->day - Processo_data->day) : ( (Data_atual->day - Processo_data->day) );
	
}
