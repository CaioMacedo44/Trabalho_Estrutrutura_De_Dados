#ifndef STRUCTPROJETO_H
#define STRUCTPROJETO_H

typedef struct data{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	float second;
}Data;

typedef struct processo{
	int id;
	char number[25];
	Data data;
	char id_class[5][10];
	char id_subject[5][10];
	char year_election[5];
}Processo;

void limparString(char* string);

int encontrarFinalDasChaves(FILE* arq, char* string, int* i);

Data preencherData(char* string);

void retirarChavesEAspas(char* string, Processo* processo, int idClasseTrue);

void preencherStruct(Processo* array, char* string, int id, int campo);

void lerArquivo(FILE* arq, Processo** array, int* tamanho);

void ordenarCrescenteId(Processo *array, int tamanho);

void ordenarDecrescenteDataAjuizado(Processo *array, int tamanho);

void print_menu();

void printStruct(Processo processo);

int contarIdClasse(Processo* array, char* string, int tamanho);

void ListarIdAssuntoMaisDeUm(Processo* array, int tamanho);

bool contem(int* array, int elemento, int tamanho);

void IndentificarQuantAssuntos(Processo* array, int tamanho);

void formatarCorreto(Processo processo, bool classId, char* string);

void escreverArqCSV(Processo* array, int tamanho, char* nome);

int processoTramitacao( Processo *array , int id_processo , int *tamanho );

int processoTramitacao( Processo *array , int id_processo , int *tamanho );

void compararMes( char mes[4] , Data *month_struct );

void calculoTramitacao( Data *Processo_data , Data *Data_atual , int *temp_tramt);


#endif