#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aviao {
	
    int numero_voo;
    char modelo[50];
    char companhia_aerea[50];
    struct Aviao* proximo;
    
} tipoAviao;

typedef struct Aeroporto {
	
    tipoAviao* fila_de_espera;
} tipoPorto;

void listar_numero_de_avioes(tipoPorto* aeroporto) {
	
    int count = 0;
    tipoAviao* aviao;
    
    for (aeroporto->fila_de_espera; aviao != NULL; aviao = aviao->proximo) {
    	
        count++;
    }
    printf("Numero de avioes aguardando na fila de decolagem: %d\n", count);
}

void autorizar_decolagem(tipoPorto* aeroporto) {
	
    if (aeroporto->fila_de_espera == NULL) {
    	
        printf("Nenhum aviao aguardando na fila de decolagem.\n");
    } else {
    	
        tipoAviao* aviao = aeroporto->fila_de_espera;
        aeroporto->fila_de_espera = aviao->proximo;
        printf("Decolagem autorizada para o aviao com numero de voo %d!\n", aviao->numero_voo);
        free(aviao);
    }
}

void adicionar_aviao(tipoPorto* aeroporto, int numero_voo, const char* modelo, const char* companhia_aerea) {
	
    tipoAviao* aviao = malloc(sizeof(tipoAviao));
    
    aviao->numero_voo = numero_voo;
    
    strncpy(aviao->modelo, modelo, sizeof(aviao->modelo));
    strncpy(aviao->companhia_aerea, companhia_aerea, sizeof(aviao->companhia_aerea));
    
    aviao->proximo = NULL;

    tipoAviao** ult = &aeroporto->fila_de_espera;
    
    while (*ult != NULL) {
    	
        ult = &(*ult)->proximo;
    }
    
    *ult = aviao;

    printf("Aviao com numero de voo %d adicionado a fila de espera.\n", numero_voo);
}

void listar_avioes_na_fila(tipoPorto* aeroporto) {
	
    printf("Avioes na fila de espera:\n");
    
    tipoAviao* aviao;
    
    for ( aeroporto->fila_de_espera; aviao != NULL; aviao = aviao->proximo) {
    	
        printf("Número de Voo: %d, Modelo: %s, Companhia Aerea: %s\n", aviao->numero_voo, aviao->modelo, aviao->companhia_aerea);
    }
}

void listar_caracteristicas_primeiro_aviao(tipoPorto* aeroporto) {
	
    tipoAviao* aviao = aeroporto->fila_de_espera;
    
    if (aviao == NULL) {
    	
        printf("Nenhum aviao na fila de espera.\n");
    } else {
    	
        printf("Caracteristicas do primeiro aviao na fila de espera:\n");
        printf("Numero de Voo: %d, Modelo: %s, Companhia Aerea: %s\n", aviao->numero_voo, aviao->modelo, aviao->companhia_aerea);
    }
}

int main() {
	
    tipoPorto aeroporto = { .fila_de_espera = NULL };

    while (1) {
    	
    	int escolha;
    	
        printf("\nOpcoes:\n1 - Listar numero de avioes\n2 - Autorizar decolagem\n3 - Adicionar aviao\n4 - Listar avioes na fila\n5 - Listar caracteristicas do primeiro aviao\n6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        int numero_voo;
        char modelo[50];
        char companhia_aerea[50];

        switch (escolha) {
        	
            case 1: 
				listar_numero_de_avioes(&aeroporto); 
				break;
				
            case 2: 
				autorizar_decolagem(&aeroporto); 
				break;
				
            case 3: 
                printf("Numero de voo: "); scanf("%d", &numero_voo);
                printf("Modelo: "); scanf("%s", modelo);
                printf("Companhia aerea: "); scanf("%s", companhia_aerea);
                adicionar_aviao(&aeroporto, numero_voo, modelo, companhia_aerea);
                break;
                
            case 4: 
				listar_avioes_na_fila(&aeroporto); 
				break;
				
            case 5: 
				listar_caracteristicas_primeiro_aviao(&aeroporto); 
				break;
				
            case 6: 
				printf("Encerrando o programa.\n"); 
				return 0;
				
            default: 
				printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}

