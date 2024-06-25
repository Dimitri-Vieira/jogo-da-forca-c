#include <stdio.h>
#include <string.h>

// VARIÁVEIS GLOBAIS
char palavraSecreta[20]; // array que armazena a palavra secreta
char chutes[26]; // array que armazena os chutes de letras que o usuário já deu
int numTentativas = 0; // número que servirá como índice de posição para o array "chutes" para que seja possível guardar o chute realizado em uma posição específica do array, preenchendo o array com os caracteres chutados

void abertura(){
    printf("*****************************\n");
    printf("*       Jogo da Forca       *\n");
    printf("*****************************\n\n");
}

void capturaChute(){
    char chute;
    scanf(" %c", &chute);

    // armazenando o chute (letra) feito, dentro do array "chutes" na posição que o número da tentativa corresponder, incrementando este número em todo final do loop
    chutes[numTentativas] = chute;
    numTentativas++;
    
}

int jaChutou(char palavraSecreta){
    int achou = 0;

    // varrendo o array "chutes" o comparando com o array "palavraSecreta" para verificar se há algum caractér igual entre eles
    for(int j = 0; j < numTentativas; j++){
        if(chutes[j] == palavraSecreta){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhandoForca(){
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

void escolhePalavra(){
    // escreve uma string inteira dentro do array (é acrescentado o caracter \0 ao final da string)
    sprintf(palavraSecreta, "MELANCIA");
}

int main(){
    int acertou = 0;
    int enforcou = 0;

    
    // escolhe a palavra secreta da forca
    escolhePalavra();

    // imprime o cabeçalho do jogo
    abertura();

    do{ 
        
        // desenha a forca
        desenhandoForca();

        // registra um novo chute no array "chutes"
        capturaChute();

    }while(!acertou && !enforcou); // condição formulada com lógica booleana. A "!" indica negação, ou seja, inversão

}
