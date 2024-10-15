#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

// DATA
struct data{
	int dia;
	int mes;
	int ano;
};
typedef struct data DATA;

//HORA
struct horario{
	int hora;
	int minuto;
};
typedef struct horario HORARIO;

//FILA
struct fila{
	char nome[50];
	int telefone;
	int preferencial;
	struct fila *ant, *prox;
};
typedef struct fila FILA;

//VOO
struct voo{
	char codigo_voo[20];
	char codigo_aeroporto[20];
	DATA data;
	HORARIO horario;
	struct voo *inicio;
	struct voo *fim;
	struct voo *ant, *prox;
	FILA *fila;
	int quantidade_passageiros;
};
typedef struct voo VOO;

VOO *voo = NULL;

void adicionar_voo(){
	VOO *novo_voo;
	
	novo_voo = (VOO*) malloc(sizeof(VOO));
	
	printf("Digite o código do voo: ");
	scanf("%s", novo_voo->codigo_voo);
	printf("Digite o código do aeroporto: ");
	scanf("%s", novo_voo->codigo_aeroporto);
	printf("Digite a data do voo no formato (dd mm aaaa): ");
	scanf("%d %d %d", &novo_voo->data.dia, &novo_voo->data.mes, &novo_voo->data.ano);
	printf("Digite o horário do voo no formato (hh mm): ");
	scanf("%d %d", &novo_voo->horario.hora, &novo_voo->horario.minuto);
	
	novo_voo->ant = NULL;
	novo_voo->prox = NULL;
	
	// PRIMEIRO REGISTRO
	if(voo == NULL){
		voo = novo_voo;
		return;
	}
	
	VOO *aux = voo;
	
	// INSERÇÃO NO INÍCIO
	if (strcasecmp(novo_voo->codigo_voo, aux->codigo_voo) < 0) {
		novo_voo->prox = voo;
		voo->ant = novo_voo;
		voo = novo_voo;
		return;
	}

	while (aux->prox != NULL && strcasecmp(aux->prox->codigo_voo, novo_voo->codigo_voo) < 0) {
		aux = aux->prox;
	}

	// INSERÇÃO NO FINAL
	if (aux->prox == NULL) {
		aux->prox = novo_voo;
		novo_voo->ant = aux;
	} else {
		// INSERÇÃO NO MEIO
		novo_voo->prox = aux->prox;
		novo_voo->ant = aux;
		aux->prox->ant = novo_voo;
		aux->prox = novo_voo;
	}
}

void remover_voo(){
	VOO *aux = voo;
	char codigo_voo[20];
	
	printf("Digite o código do voo: ");
	scanf("%s", &codigo_voo);
	
	while(aux != NULL && strcasecmp(aux->codigo_voo, codigo_voo) != 0){
		aux = aux->prox;
	}
	
	if(aux->ant == NULL){
		voo = NULL;
		printf("\nO código %s foi removido da lista\n", codigo_voo);
	}
	else if(aux != NULL){
		aux->ant->prox = aux->prox;
		printf("\nO código %s foi removido da lista\n", codigo_voo);
	} else {
		printf("\nO código do voo informado está incorreto ou não está presente na lista.\n");
	}
}

void consultar_voos(){
	VOO *aux = voo;
	int cont = 1;	
		
	while(aux != NULL){
		printf("---------------------------------------------------\n");
		printf("%d.", cont);
		printf("COD.AEROPORTO: %s", aux->codigo_aeroporto);
		printf(" COD.VOO: %s", aux->codigo_voo);
		printf(" DATA: %02d/%02d/%d", aux->data.dia, aux->data.mes, aux->data.ano);
		printf(" HORA: %02d:%02d\n", aux->horario.hora, aux->horario.minuto);
		printf("---------------------------------------------------\n");
		aux = aux->prox;	
		cont++;
	}
	printf("\n");
}

void adicionar_passageiro(){
    VOO *aux_voo = voo;
    FILA *novo_passageiro;
    char codigo_voo[20];
    
    printf("Digite o código do voo: ");
    scanf("%s", codigo_voo);
    
    while(aux_voo != NULL && strcasecmp(aux_voo->codigo_voo, codigo_voo) != 0){
        aux_voo = aux_voo->prox;
    }
    
    if(aux_voo != NULL){
        novo_passageiro = (FILA*) malloc(sizeof(FILA));

        printf("Digite o nome do passageiro:");
        scanf("%s", novo_passageiro->nome);
        printf("Digite o telefone do passageiro:");
        scanf("%d", &novo_passageiro->telefone);
        novo_passageiro->preferencial = 0;
        
        novo_passageiro->ant = NULL;
        novo_passageiro->prox = NULL;
        
        FILA *aux_fila = aux_voo->fila;
        
        // PRIMEIRO REGISTRO
        if(aux_fila == NULL){
            aux_voo->fila = novo_passageiro;
            return;
        }

        while (aux_fila->prox != NULL) {
            aux_fila = aux_fila->prox;
        }
        
        // INSERÇÃO NO FINAL
        if (aux_fila->prox == NULL) {
            aux_fila->prox = novo_passageiro;
            novo_passageiro->ant = aux_fila;
        }
        
        aux_voo->quantidade_passageiros++;
    } else {
        printf("\nO código do voo informado está incorreto ou não está presente na lista.\n");
    }
}

void remover_passageiro(){
    VOO *aux_voo = voo;
    char codigo_voo[20];
    
    printf("Digite o código do voo: ");
    scanf("%s", codigo_voo);
    
    while(aux_voo != NULL && strcasecmp(aux_voo->codigo_voo, codigo_voo) != 0){
        aux_voo = aux_voo->prox;
    }
    
    if(aux_voo != NULL){
        FILA *aux_fila = aux_voo->fila;
        char nome_passageiro[50];
        
        printf("Digite o nome do passageiro: ");
        scanf("%s", nome_passageiro);
        
        while(aux_fila != NULL && strcasecmp(aux_fila->nome, nome_passageiro) != 0){
            aux_fila = aux_fila->prox;
        }

        if(aux_fila != NULL){
            
			if(aux_fila->ant == NULL){
                aux_voo->fila = aux_fila->prox;
                if(aux_voo->fila != NULL){
                    aux_voo->fila->ant = NULL;
                }
            } else {
                aux_fila->ant->prox = aux_fila->prox;
                if(aux_fila->prox != NULL){
                    aux_fila->prox->ant = aux_fila->ant;
                }
            }
            
            printf("\nO passageiro %s foi removido da lista\n", nome_passageiro);
            aux_voo->quantidade_passageiros--;
            free(aux_fila);
        } else {
            printf("\nO passageiro informado está incorreto ou não está presente na lista.\n");
        }
    } else {
        printf("\nO código do voo informado está incorreto ou não está presente na lista.\n");
    }
}

void consultar_fila_espera(){
	VOO *aux_voo = voo;
	char codigo_voo[20];
	
	printf("Digite o código do voo: ");
	scanf("%s", &codigo_voo);
	
	while(aux_voo != NULL && strcasecmp(aux_voo->codigo_voo, codigo_voo) != 0){
		aux_voo = aux_voo->prox;
	}
	
	if(aux_voo != NULL){
	
		FILA *aux_fila = aux_voo->fila;
		int cont = 1;	
			
		while(aux_fila != NULL){
			printf("---------------------------------------------------\n");
			printf("%d.", cont);
			printf("NOME: %s", aux_fila->nome);
			printf(" TELEFONE: %d", aux_fila->telefone);
			printf("\n---------------------------------------------------\n");
			aux_fila = aux_fila->prox;	
			cont++;
		}
	} else {
		printf("\nO código do voo informado está incorreto ou não está presente na lista.\n");
	}
	printf("\n");
}
void consultar_maior_fila_espera(){
	VOO *aux = voo;
    VOO *voo_maior_fila = NULL;
    int maior_fila = 0;
    
    while(aux != NULL){
        if(aux->quantidade_passageiros > maior_fila){
            maior_fila = aux->quantidade_passageiros;
            voo_maior_fila = aux;
        }
        aux = aux->prox;
    }
    
    if(voo_maior_fila != NULL){
        printf("---------------------------------------------------\n");
        printf("Voo com maior fila de espera:\n");
        printf("COD.AEROPORTO: %s", voo_maior_fila->codigo_aeroporto);
        printf(" COD.VOO: %s", voo_maior_fila->codigo_voo);
        printf(" DATA: %02d/%02d/%d", voo_maior_fila->data.dia, voo_maior_fila->data.mes, voo_maior_fila->data.ano);
        printf(" HORA: %02d:%02d\n", voo_maior_fila->horario.hora, voo_maior_fila->horario.minuto);
        printf(" Passageiros na fila: %d\n", voo_maior_fila->quantidade_passageiros);
        printf("---------------------------------------------------\n");
    } else {
        printf("\nNenhum voo encontrado.\n");
    }
}
void consultar_voos_sem_fila_espera(){
	VOO *aux = voo;
    int encontrado = 0;
    
    while(aux != NULL){
        if(aux->fila == NULL){
            printf("---------------------------------------------------\n");
            printf("COD.AEROPORTO: %s", aux->codigo_aeroporto);
            printf(" COD.VOO: %s", aux->codigo_voo);
            printf(" DATA: %02d/%02d/%d", aux->data.dia, aux->data.mes, aux->data.ano);
            printf(" HORA: %02d:%02d\n", aux->horario.hora, aux->horario.minuto);
            printf("---------------------------------------------------\n");
            encontrado = 1;
        }
        aux = aux->prox;
    }
    
    if (!encontrado) {
        printf("\nNenhum voo sem fila de espera encontrado.\n");
    }
}
void consultar_voo_especifico(){
	VOO *aux = voo;
    char codigo_voo[20];
    
    printf("Digite o código do voo: ");
    scanf("%s", codigo_voo);
    
    while(aux != NULL && strcasecmp(aux->codigo_voo, codigo_voo) != 0){
        aux = aux->prox;
    }
    
    if(aux != NULL){
        printf("---------------------------------------------------\n");
        printf("COD.AEROPORTO: %s", aux->codigo_aeroporto);
        printf(" COD.VOO: %s", aux->codigo_voo);
        printf(" DATA: %02d/%02d/%d", aux->data.dia, aux->data.mes, aux->data.ano);
        printf(" HORA: %02d:%02d\n", aux->horario.hora, aux->horario.minuto);
        printf("---------------------------------------------------\n");
    } else {
        printf("\nO voo com código %s não foi encontrado.\n", codigo_voo);
    }	
}

void adicionar_passageiro_preferencial(){
	VOO *aux_voo = voo;
    FILA *novo_passageiro;
    char codigo_voo[20];
    
    printf("Digite o código do voo: ");
    scanf("%s", codigo_voo);
    
    while(aux_voo != NULL && strcasecmp(aux_voo->codigo_voo, codigo_voo) != 0){
        aux_voo = aux_voo->prox;
    }
    
    if(aux_voo != NULL){
        novo_passageiro = (FILA*) malloc(sizeof(FILA));

        printf("Digite o nome do passageiro:");
        scanf("%s", novo_passageiro->nome);
        printf("Digite o telefone do passageiro:");
        scanf("%d", &novo_passageiro->telefone);
        
		novo_passageiro->preferencial = 1;
        novo_passageiro->ant = NULL;
        novo_passageiro->prox = NULL;
        
        FILA *aux_fila = aux_voo->fila;
        
        // PRIMEIRO REGISTRO
        if(aux_fila == NULL){
            aux_voo->fila = novo_passageiro;
            return;
        }
        
        // INSERÇÃO NO INÍCIO
        if (aux_fila->preferencial == 0) {
            novo_passageiro->prox = aux_fila;
            aux_fila->ant = novo_passageiro;
            aux_voo->fila = novo_passageiro;
            return;
        }

        while (aux_fila->prox != NULL && aux_fila->prox->preferencial == 1) {
            aux_fila = aux_fila->prox;
        }
        
        // INSERÇÃO NO FINAL
        if (aux_fila->prox == NULL) {
            aux_fila->prox = novo_passageiro;
            novo_passageiro->ant = aux_fila;
        } else {
        	// INSERÇÃO NO MEIO
            novo_passageiro->prox = aux_fila->prox;
            novo_passageiro->ant = aux_fila;
            aux_fila->prox->ant = novo_passageiro;
            aux_fila->prox = novo_passageiro;
        }
        
        aux_voo->quantidade_passageiros++;
    } else {
        printf("\nO código do voo informado está incorreto ou não está presente na lista.\n");
    }
}

void consultar_voo_horario(){
	VOO *aux = voo;
    HORARIO horario_consulta;
    
    printf("Digite o horario do voo no formato (hh mm): ");
    scanf("%d %d", &horario_consulta.hora, &horario_consulta.minuto);
    
    int encontrado = 0;
    while(aux != NULL){
        if(aux->horario.hora == horario_consulta.hora && aux->horario.minuto == horario_consulta.minuto){
            printf("---------------------------------------------------\n");
            printf("COD.AEROPORTO: %s", aux->codigo_aeroporto);
            printf(" COD.VOO: %s", aux->codigo_voo);
            printf(" DATA: %02d/%02d/%d", aux->data.dia, aux->data.mes, aux->data.ano);
            printf(" HORA: %02d:%02d\n", aux->horario.hora, aux->horario.minuto);
            printf("---------------------------------------------------\n");
            encontrado = 1;
        }
        aux = aux->prox;
    }
    
    if (!encontrado) {
        printf("\nNenhum voo encontrado para o horário informado.\n");
    }
}

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void menu(){
	int op;
	
	printf("\n* * * * * *  FILAS DE ESPERA PARA VOOS  * * * * * *\n");
	printf("*                                                 *\n");
	printf("*       1. ADICIONAR VOO                          *\n");
	printf("*       2. REMOVER VOO                            *\n");
	printf("*       3. CONSULTAR VOOS                         *\n");
	printf("*       4. ADICIONAR PASSAGEIRO                   *\n");
	printf("*       5. REMOVER PASSAGEIRO                     *\n");
	printf("*       6. CONSULTAR FILA DE ESPERA               *\n");
	printf("*       7. CONSULTAR MAIOR FILA DE ESPERA         *\n");
	printf("*       8. CONSULTAR VOOS SEM FILA DE ESPERA      *\n");
	printf("*       9. CONSULTAR UM VOO ESPECÍFICO            *\n");
	printf("*      10. ADICIONAR PASSAGEIRO PREFERENCIAL      *\n");
	printf("*      11. CONSULTAR VOOS POR HORÁRIO             *\n");
	printf("*      12. FINALIZAR A EXECUÇÃO DO PROGRAMA       *\n");
	printf("*                                                 *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("SELECIONE UMA DAS OPERAÇÕES DO QUADRO: ");
	
	if(scanf("%d", &op) != 1) {
        printf("\nENTRADA INVÁLIDA. POR FAVOR, INSIRA UM NÚMERO.\n");
        limpar_buffer(); 
        menu();
        return;
    }
	
	switch (op) {
  		case 1:
  			printf("\n* * * * * * * * * ADICIONAR VOO * * * * * * * * * *\n\n");
  			adicionar_voo();
    		break;
	  	case 2:
	  		printf("\n* * * * * * * * * REMOVER VOO * * * * * * * * * * *\n\n");
	  		remover_voo();
	    	break;
	   	case 3:
	   		printf("\n* * * * * * * * * CONSULTAR VOOS * * * * * * * * * *\n\n");
	   		consultar_voos();
    		break;
	  	case 4:
	  		printf("\n* * * * * * *  ADICIONAR PASSAGEIRO * * * * * * * *\n\n");
	  		adicionar_passageiro();
	    	break;
	    case 5:
	    	printf("\n* * * * * * *  * REMOVER PASSAGEIRO * * * * * * * *\n\n");
	    	remover_passageiro();
    		break;
	  	case 6:
	  		printf("\n* * * * * *  CONSULTAR FILA DE ESPERA * * * * * * *\n\n");
	  		consultar_fila_espera();
	    	break;
	   	case 7:
	   		printf("\n* * * *  CONSULTAR MAIOR FILA DE ESPERA * * * * * *\n\n");
	   		consultar_maior_fila_espera();
    		break;
	  	case 8:
	  		printf("\n* * * * CONSULTAR VOOS SEM FILA DE ESPERA * * * * *\n\n");
	  		consultar_voos_sem_fila_espera();
	    	break;
	   	case 9:
	   		printf("\n* * * * * *  CONSULTAR UM VOO ESPECÍFICO * * * * * *\n\n");
	   		consultar_voo_especifico();
    		break;
	  	case 10:
	  		printf("\n* * * *  ADICIONAR PASSAGEIRO PREFERENCIAL * * * * *\n\n");
	  		adicionar_passageiro_preferencial();
	    	break;
	    case 11:
	    	printf("\n* * * *  *  * CONSULTAR VOOS POR HORÁRIO * * * * * *\n\n");
	  		consultar_voo_horario();
	    	break;
	    case 12:
	    	system("cls");
	    	printf("\nPROGRAMA FINALIZADO.\n");
	    	break;
	  	default:
	    	printf("\nA OPERAÇÃO SOLICITADA NÃO ESTÁ DISPONÍVEL NO QUADRO, TENTE NOVAMENTE.\n\n");
	    	sleep(3);
	}
	
	if(op != 12){
		menu();	
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	menu();
	return 0;
}





















