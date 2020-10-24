/*
    Curso.....: Ciência da Computação           .
    Disciplina: Fundamentos de Programação      .
    Discentes.:
        * Alysson Lucas Braga Pinheiro..........| MÂª: 494691
        * Bruno de Andrande Pereira.............| MÂª: 493419
        * Felipe Soares do Nascimento...........| MÂª: 497182 
        * Paulo Henrique Diniz de Lima Alencar..| MÂª: 494837
        * Yan Rodrigues da Silva................| MÂª: 495532
    Tema......: Joga da Forca                 
    Assuntos..: 
        * Estrurtura sequencial....01
        * Estrura Condicional......02
        * Estrutuea de repetição...03
        * Vetores..................04
        * String...................05
        * Matrizes.................06
        * Funções..................07
        * Ponteiros................08
        * Alocação Dinâmica........09
        * Arquivos.................10
        * Comando de desvios.......11
        * Structs..................12
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POKEMON_PATH "./utils/pokemons.txt"
#define FRUTAS_PATH  "./utils/frutas.txt"
#define JOGOS_PATH   "./utils/jogos.txt"
#define FILMES_PATH  "./utils/filmes.txt"
#define ANIMES_PATH  "./utils/animes.txt"

// Estrutura do tipo Jogador com campos nickname e num.
typedef struct {
    char nickname[40];
    int  num;
} Jogador;

//Procedimento: Inicio de execução
void inicio(Jogador player) {
    puts("\n****************************************");
    puts("*     BEM VINDO AO JOGO DA FORCA!!     *");
    printf("      %s\n*", player.nickname);
    puts("***************************************");
}

// Procedimento: Exibição do menu de temas.
void menu() {
    puts("\n*************************");
    puts("*  Opcoes de temas:     *");
    puts("*  [1] - Pokemons       *");
    puts("*  [2] - Frutas         *");
    puts("*  [3] - Filmes         *");
    puts("*  [4] - Jogos          *");
    puts("*  [5] - Animes         *");
    puts("*  [0] - Exit           *");
    puts("*************************");
}

// Procedimento: Mostra o bonequinho de acordo com os erros do usuário.
void desenhar_personagem(int erros) {

    if (erros == 0)  {
        puts("._______     ");
        puts("|      !     ");
        puts("|            ");
        puts("|            ");
        puts("|            ");
        puts("|            ");
        puts("|____________");
        puts("0 erros!     ");
    } 
    else if (erros == 1)  {
        puts("._______     ");
        puts("|      !     ");
        puts("|      O     ");
        puts("|            ");
        puts("|            ");
        puts("|            ");
        puts("|____________");
        puts("1 erro!      ");
    }
    else if (erros == 2) {
        puts("._______     ");
        puts("|      !     ");
        puts("|      O     ");
        puts("|      |     ");
        puts("|            ");
        puts("|            ");
        puts("|____________");
        puts("2 erros!     ");
    }
    else if (erros == 3) {
        puts("._______     ");
        puts("|      !     ");
        puts("|      O     ");
        puts("|      |\\   ");
        puts("|            ");
        puts("|            ");
        puts("|____________");
        puts("3 erros!     ");
    }
    else if (erros == 4) {
        puts("._______     ");
        puts("|      !     ");
        puts("|      O     ");
        puts("|     /|\\   ");
        puts("|            ");
        puts("|            ");
        puts("|____________");
        puts("4 erros!     ");
    }
    else if (erros == 5) {
        puts("._______     ");
        puts("|      !     ");
        puts("|      O     ");
        puts("|     /|\\   ");
        puts("|       \\   ");
        puts("|            ");
        puts("|____________");
        puts("5 erros!     ");
    }
    else if (erros == 6) {
        puts("._______     ");
        puts("|      !     ");
        puts("|     0\\    ");
        puts("|     /|\\   ");
        puts("|     / \\   ");
        puts("|            ");
        puts("|____________");
        puts("6 erros!     ");
    }
    puts("");
}
// Função: responsável pelo sorteio de uma número [0-14] que vai representar posição da palavra sorteada.
int sortear() {
    srand(time(NULL));
    int numero = rand() % 15; 
    return numero;
}
// Procedimento: responsável por ler o arquivo referente ao tema escolhido
void importar_strings(FILE* arquivo, char* tema[], char path[], int* numero_sorteado) {
    char message[100];
    int count = 0, length = 0, i; 

    arquivo = fopen(path, "r");

    while(!feof(arquivo)) {
    	fscanf(arquivo,"%s",message);
        length = strlen(message);
        tema[count] = (char *) malloc((length + 1) * sizeof(char)); 
        strcpy(tema[count], message);
        count++;
    }

    *numero_sorteado = sortear();

    fclose(arquivo);
}
// Função: verifica se o usuário degitou caractere já digitado anteriormente.
char entrada_e_verificacao(char letra_repetida[], int* n) {
    // Dicionário de dados:
    char letra;
    int existe;
    int i;

    do {
        existe = 0;
        fflush(stdin);
        printf("\nEntre com uma letra: ");
        scanf("%c",&letra);
        								
        if (!(letra > 96 && letra < 123)) letra = letra + 32;
        letra_repetida[*n] = letra; 
        
        for(i = 0; i < *n; i++){
            if(letra_repetida[i] == letra) {
                existe = 1;
                printf("Letra repetida, tente novamente!\n");
            }
        }
        
    }while(existe == 1);
    (*n)++;

    return letra;
}

// Procedimento: permite o usuário realizar uma jogada.
void jogada (char* tema[], int* numero_sorteado, Jogador player) {
    // Dicionário de dados:
    int  tamanho, existe, contador_underline;
    int  status_erro = 0, contador_erros = 0, n = 0;
    int  i, j;
    char *aux, letra_repetida[15];
    char letra;
    
    printf("\nTema: %s\n\n",tema[15]);

    tamanho = strlen(tema[*numero_sorteado]); 
    aux = (char*) malloc ((tamanho+1) * sizeof(char));
    for(i = 0; i < tamanho; i++) {
        aux[i] = '_';
        printf("%c ", aux[i]);
    }
    
    contador_underline = tamanho;
    while (1) {
        
        status_erro = 0;
        
        letra = entrada_e_verificacao(letra_repetida, &n);
        
        for(j = 0; j < tamanho; j++) {
            if(tema[*numero_sorteado][j] == letra) {
                aux[j] = letra;
                status_erro = 1;
                contador_underline--;
            }
        }
        
        if(status_erro == 0) {
            contador_erros++;
            printf("\nTema: %s\n",tema[15]);
            desenhar_personagem(contador_erros);
        } 
        else {
            printf("\nTema: %s\n",tema[15]);
            desenhar_personagem(contador_erros);
        }
        
        for(j = 0; j < tamanho; j++) {
            printf("%c ",aux[j]);
        }
        
        if(contador_underline == 0) {
            printf("\nA palavra era: %s",tema[*numero_sorteado]);
            printf("\n%s, voce venceu!!\n",player.nickname);
            break;
        }
        else if(contador_erros == 6) {
            printf("\nA palavra era: %s",tema[*numero_sorteado]);
            printf("\n%s, voce errou!\n",player.nickname);
            break;
        }
    }
    free(aux);
}
// Procedimento: responsável por desalocar memória.
void desalocando_memoria(char* tema[]) {
	int i;
    for(i = 0; i < 16; i++) {
        free(tema[i]);
    }
}
// Função: principal
int main(void) {   

    // Dicionário de dados:
    FILE* pokemons_aq, *frutas_aq, *filmes_aq, *jogos_aq, *animes_aq;   
    char* pokemons[16], *frutas[16], *filmes[16], *jogos[16], *animes[16];
    int   numero_sorteado = 0, escolha;
    Jogador player;

    // Entrada de dados:
    printf("\nDigite o seu nome: ");
    fflush(stdin);
    scanf("%[^\n]s", player.nickname);

    inicio(player);
    while(1) {
        menu();
        printf("Entre com tema: ");
        scanf("%d",&escolha);
        
        // Processamento: realizando a chamada das funções
        switch (escolha){   
            
            case 1:{
                importar_strings(pokemons_aq, pokemons, POKEMON_PATH, &numero_sorteado);
                jogada(pokemons, &numero_sorteado, player);
                
                desalocando_memoria(pokemons);
            } break;
            
            case 2:{
                importar_strings(frutas_aq, frutas, FRUTAS_PATH, &numero_sorteado);
                jogada(frutas, &numero_sorteado, player);

                desalocando_memoria(frutas); 
            } break;
            
            case 3: {
                importar_strings(filmes_aq, filmes, FILMES_PATH, &numero_sorteado);
                jogada(filmes, &numero_sorteado, player);

                desalocando_memoria(filmes); 
            } break;
            
            case 4: {
                importar_strings(jogos_aq, jogos, JOGOS_PATH, &numero_sorteado);
                jogada(jogos, &numero_sorteado, player);

                desalocando_memoria(jogos); 
            } break;

            case 5: {
                importar_strings(animes_aq, animes, ANIMES_PATH, &numero_sorteado);
                jogada(animes, &numero_sorteado, player);
            
                desalocando_memoria(animes);
            } break;
        }
        if (escolha == 0) {
            puts("Sad :(");
            break;
        }
    }
    return 0;
}
