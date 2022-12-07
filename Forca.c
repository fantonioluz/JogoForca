#include<stdio.h>
#include<string.h>
#include"Forca.h"
#include<time.h>
#include<stdlib.h>

char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

void abertura(){
    printf("*********************\n");
    printf("*   Jogo da forca   *\n");
    printf("*********************\n\n");
}

int ganhou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

void chuta(){
    char chute;
    scanf(" %c", &chute);
    chutes[chutesdados]= chute;
    chutesdados++;
}

int jachutou(char letra){
    int achou = 0;
            
    for(int j = 0; j<chutesdados; j++){
        if (chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

void desenhaforca(){

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {
    
        int achou = jachutou(palavrasecreta[i]);
        if(achou){
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    
    }
    printf("\n");
}

void escolhepalavra(){
    FILE* f;

    f = fopen("palavras.txt","r");
    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1);
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras);

    srand(time(0));
    int randomico = rand() % qtdpalavras;

    for(int i = 0; i<= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

   fclose(f);
}

void adcionapalvra(){
    char quer;
    printf("Voce deseja adcionar um nova palavra no jogo? (S/N)");
    scanf(" $c", &quer);
    if(quer == 'S'){
        char novapalavra[20];

        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");

        if(f == 0){
            printf("Desculpe, banco de dados nao disponivel\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);
        fseek(f, 0, SEEK_END);

        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

int enforcou(){
    int erros = 0;
    for (int i = 0; i < chutesdados; i++){
        int existe = 0;
        for (int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros >=5;
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int main() {
    
    
    escolhepalavra();
    abertura();
    do{
        desenhaforca();
        chuta(); 

    } while(!acertou() && !enforcou());
    
    
    if(ganhou()) {
        printf("\nParabéns, você ganhou!\n\n");

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

    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

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
    
    
    adcionapalvra();
    
}