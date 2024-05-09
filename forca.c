#include <stdio.h>
#include <string.h>

int main(){
    char palavraSecreta[20];

    // escreve uma string inteira dentro do array (é acrescentado o caracter \0 ao final da string)
    sprintf(palavraSecreta, "MELANCIA");

    int acertou = 0;
    int enforcou = 0;

    char chutes[26]; // array que armazena os chutes de letras que o usuário já deu
    int numTentativas = 0; // número que servirá como índice de posição para o array "chutes" para que seja possível guardar o chute realizado em uma posição específica do array, preenchendo o array com os caracteres chutados

    do{ 
        
        // varrendo o array "palavraSecreta"
        for(int i = 0; i < strlen(palavraSecreta); i++){

            int achou = 0;

            // varrendo o array "chutes" o comparando com o array "palavraSecreta" para verificar se há algum caractér igual entre eles
            for(int j = 0; j < numTentativas; j++){
                if(chutes[j] == palavraSecreta[i]){
                    achou = 1;
                    break;
                }
            }

            if(achou){
                printf("%c ", palavraSecreta[i]);

            } else{
                printf("_ ");
            }
        }
        printf("\n");
        char chute;
        scanf(" %c", &chute);

        // armazenando o chute (letra) feito, dentro do array "chutes" na posição que o número da tentativa corresponder, incrementando este número em todo final do loop
        chutes[numTentativas] = chute;
        numTentativas++;

    }while(!acertou && !enforcou); // condição formulada com lógica booleana. A "!" indica negação, ou seja, inversão

}