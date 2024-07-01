#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h" // biblioteca com as funções criadas para o jogo da forca.

// VARIÁVEIS GLOBAIS
char palavraSecreta[TAMANHO_PALAVRA]; // array que armazena a palavra secreta
char chutes[26]; // array que armazena os chutes de letras que o usuário já deu
int chutesDados = 0; // número que servirá como índice de posição para o array "chutes" para que seja possível guardar o chute realizado em uma posição específica do array, preenchendo o array com os caracteres chutados

void abertura(){
    printf("*****************************\n");
    printf("*       Jogo da Forca       *\n");
    printf("*****************************\n\n");
}

void capturaChute(){
    char chute;
    scanf(" %c", &chute);

    // armazenando o chute (letra) feito, dentro do array "chutes" na posição que o número da tentativa corresponder, incrementando este número em todo final do loop
    chutes[chutesDados] = chute;
    chutesDados++;
    
}

int jaChutou(char letra){
    int achou = 0;

    // varrendo o array "chutes" o comparando com o array "palavraSecreta" para verificar se há algum caractér igual entre eles
    for(int j = 0; j < chutesDados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhandoForca(){

    int erros = chutesErrados();
    // desenho da forca em ASCII ART utilizando operador ternário para desenhar o corpo do enforcado de acordo com a quantidade de erros já cometidos na forca
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
        (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
        (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    // varrendo o array "palavraSecreta"
    for(int i = 0; i < strlen(palavraSecreta); i++){
        // verifica se o caractér inserido já foi chutado
        int achou = jaChutou(palavraSecreta[i]);
        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else{
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionaPalavra(){
    char quer;

    printf("Voce deseja adicionar uma nova palavra ao jogo? Digite S para SIM e N para NAO.\n");
    scanf(" %c", &quer);

    // se quer for igual a S, ou seja, se quiser adicionar uma nova palavra
    if(quer == 'S'){
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a palavra?\n");
        scanf("%s", &novaPalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+"); // abre o arquivo para leitura e escrita
        if(f == 0){
            printf("Desculpe, banco de dados não disponivel!\n\n");
            exit(1);
        }


        int quantidade;
        fscanf(f, "%d", &quantidade); // lê a quantidade de palavras que já existem
        quantidade++; // incrementa o número da quantidade de palavras que existem


        fseek(f, 0, SEEK_SET); // esse código posiciona o cursor de leitura na primeira linha do arquivo
        fprintf(f, "%d", quantidade); // escreve, em cima do que já existe, o novo n° da quantidade de palavras que existem

        fseek(f, 0, SEEK_END); // esse código posiciona o cursor de leitura na última linha do arquivo
        fprintf(f, "\n%s", novaPalavra); // dá um "enter" na linha que se encontra e escreve a nova palavra adicionada

        fclose(f); // fecha o arquivo
    }
}

void escolhePalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r"); // abre o arquivo para leitura
    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel!\n\n");
        exit(1);
    }

    int quantPalavras;
    fscanf(f, "%d", &quantPalavras); // lê a quantidade de palavras que existe no arquivo

    srand(time(0)); // gera um número pseudo-aleatório
    int randomico = rand() % quantPalavras; // gera um número randômico limitado à quantidade de palavras que existem no arquivo

    // loop que escolhe a palavra escolhida aleatoriamente com base no número randômico gerado
    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", &palavraSecreta);
    }

    fclose(f); // fecha o arquivo
}

// verifica se o usuário já acertou com base nas letras corretas chutadas
int acertou(){
    for(int i = 0; i < strlen(palavraSecreta); i++){

        // se a letra ainda não foi chutada, retorne zero (não acertou)
        if(!jaChutou(palavraSecreta[i])){
            return 0;
        }
    }

    return 1; //se todas as letras da palavra secreta já foram chutadas, retorne 1 (acertou)
}

int chutesErrados(){
    int erros = 0;

    // varre o array chutes
    for(int i = 0; i < chutesDados; i++){
        int existe = 0;
        
        // varre o array palavra secreta e compara com o array chutes para verificar se há alguma letra igual entre os dois
        for(int j = 0; j < strlen(palavraSecreta); j++){
            if(chutes[i] == palavraSecreta[j]){

                existe = 1;
                break;
            }
        }

        if(!existe) erros++; // condição formulada com lógica boolena
    }

    return erros;
}

// verifica se o usuário já foi enforcado com base na quantidade de erros chutados
int enforcou(){

    return chutesErrados() >= 5; // quando houverem 5 letras erradas ou mais, o jogo acaba (retorna para o terminal)
}

int main(){
    // escolhe a palavra secreta da forca
    escolhePalavra();

    // imprime o cabeçalho do jogo
    abertura();

    do{ 
        
        // desenha a forca
        desenhandoForca();

        // registra um novo chute no array "chutes"
        capturaChute();

    }while(!acertou() && !enforcou()); // condição formulada com lógica booleana. A "!" indica negação, ou seja, inversão. Em lógica booleana 0 é falso e 1 (ou valores maiores que 0) é verdadeiro.

    if(acertou()){
        printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else{
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavraSecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionaPalavra();
}
