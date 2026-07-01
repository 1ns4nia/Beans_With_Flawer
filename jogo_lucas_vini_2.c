#include <stdio.h>
#include <windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#define MONSTRO 3
int amp = 1;
int ampmonstro = 2;
int contfase = 1;
int contm = 0;
int contmonstruso = 0;
int tam = 7;
int perigo = 0;
int fase = 0;
int dinheiro = 0;
struct status{
    int vida, dfs, atq, posx, posy, chave;
}heroi, monstro, monstro2, monstro3, boss;
struct status heroi = {10, 2, 3, 0, 0, 0};
struct status monstro = {6, 1, 2};
struct status boss = {8, 1, 3};

char **mapa;

int posx, posy;

int menu() {
    char op;
   // int au;
    //au = (80 - tam - 2)/2;
printf(
    "                              .:--=--:::--==-=--:                               \n"
    "                           ::-==--------==--==--==:                            \n"
    "                         ::--==--========--===-==--:                           \n"
    "                        :--========================--:                          \n"
    "                       :--=======================--=:                                \n"
    "                      :-=       ===--==-         --:                                     \n"
    "                    :-==-    0    --==--      0    -=:                          \n"
    "                    :==--============--============--==:                         \n"
    "                   .-=================================-:                        \n"
    "                   :-============--====================-:                       \n"
    "                 :.--============---==-==--==-=======--:                       \n"
    "                :.--==   |  |   |   |   |  |   |   | | --=:                         \n"
    "                 :--===    |   |   |   |  |   |   |   |==--:                         \n"
    "                  :-============-==-==--===============-:                        \n"
    "                  ..:-================================-::-:                       \n"
    "                :......--===--.....::--=-=--::....---=:                          \n"
    "                .:......::-----:.....:-----:......--=:                            \n"
    "                 .:........:---:::...::---:...::::--:.                            \n"
    "                ::--:.........:--::..:----:..:-----:-=--   ::                         \n"
    "            :::-=====-::........:::-.:----:.:-:::..-======-::::                            \n"
    "         ::---====--:::::::::::::..:-.:---.::....::::-::                         \n"
    "            .:-----:.........::----------::------::--:                            \n"
    );
    printf("Escolha o que deseja fazer:\n\n1- Entra no jogo\n\n2- Sair do jogo\n\n");
    op=getch();
    switch(op){
    case '1':
        printf("entrando no jogo");
        system("cls");
        return 1;
            break;
    case '2':
        printf("saindo do jogo...");
        Sleep(500);
        system("cls");
        return 0;
            break;
    default:
        system("cls");
        printf("opcao invalida");
        Sleep(1000);
        system("cls");
        menu();
    }





}
void liberarMapa() {
    if (mapa != NULL) {
        for (int l = 0; l < tam; l++) {
            free(mapa[l]);
        }
        free(mapa);
        mapa = NULL;
    }
}
void inicializarMapa() {
    int l, c;
    mapa = (char **)malloc(tam * sizeof(char *));
    for (l = 0; l < tam; l++) {
        mapa[l] = (char *)malloc(tam * sizeof(char));
    }
    for (l = 0; l < tam; l++) {
        for (c = 0; c < tam; c++) {
            mapa[l][c] = '.';
        }
    }
    mapa[heroi.posx][heroi.posy] = 'E';
    heroi.posx = 0;
    heroi.posy = 0;
    mapa[0][0] = 'T';
    mapa[tam-1][tam-1] = 'E';
}
void gotoxy(int x, int y){
    COORD c;
    c.X = x-1;
    c.Y = y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }

    void moldura(int linhaInicial, int linhaFinal, int colunaInicial, int colunaFinal, int tipo){ //aqui ele define o nome das variaveis que vao receber o valor delimitado na show map, 1,23,1,80,0
    int l,c;
    int borda[2][6]={{205,186,201,187,200,188}, //tipos de borda, os numeros sao caracteres Ascii
                    {196,'|',218,191,192,217}};
    for(c = colunaInicial+1; c <= colunaFinal-1; c++){//printa a as bordas de cima e baixo de esquerda pra direita, usa-se coluna +1 coluna -1 pra poder deixar espaço pras bordas
        gotoxy(c,linhaInicial); printf("%c", borda[tipo][0]);
        gotoxy(c,linhaFinal); printf("%c", borda[tipo][0]);
 }
    for(l=linhaInicial+1;l<=linhaFinal-1;l++){//printa as bordas da esquerda e direita de cima pra baixo deixando espaço pras quinas
        gotoxy(colunaInicial,l); printf("%c", borda[tipo][1]);
        gotoxy(colunaFinal,l); printf("%c", borda[tipo][1]);
    }
    gotoxy(colunaInicial,linhaInicial); printf("%c", borda[tipo][2]);
    gotoxy(colunaFinal,linhaInicial); printf("%c", borda[tipo][3]);
    gotoxy(colunaInicial,linhaFinal); printf("%c", borda[tipo][4]);
    gotoxy(colunaFinal,linhaFinal); printf("%c", borda[tipo][5]);
}
void Showmap(){
    int l, c, au;
    au = (80 - tam - 2) / 2; // Centraliza horizontalmente com base no tamanho atual

    // Desenha a borda externa da tela (fixa)
    moldura(1, 23, 1, 80, 0);

    // CORREÇÃO: A altura da moldura (linha final) agora é dinâmica baseada em 'tam'
    // Começa na linha 9 e vai até a linha (9 + tam + 1)
    moldura(9, 9 + tam + 1, au, au + tam + 1, 1);

    for(l = 0; l < tam; l++){
        for(c = 0; c < tam; c++){
            // Posiciona cada caractere do mapa perfeitamente dentro da nova moldura
            gotoxy(au + 1 + c, 10 + l);

            if(mapa[l][c] == 'M')
                printf(".");
            else if(mapa[l][c] == 'B')
                printf(".");
            else
                printf("%c", mapa[l][c]);
        }
    }
}

int contamonstro(){
    int x, y, checkx, checky, contmonstro = 0;
    for(x=-2;x<=2;x++){
        for(y=-2;y<=2;y++){
            checkx = heroi.posx + x;
            checky = heroi.posy + y;
            if(checkx>=0 && checkx<tam && checky>=0 && checky<tam){
                if(mapa[checkx][checky] == 'M'){
                    contmonstro++;
                }
            }
        }
    }
    return contmonstro;
}

void Spawn(int qntd){ //int qntd é pego do int main, no caso 10, entao serao no maximo 10 monstros
    int x,y,cont,a=0;
    for(cont=1;cont<=qntd;cont++,a++){ // a e pra ver quantas vezes rolou no total, cont e pra comparar com a qntd, ele vai ate o cont superar o qntd
    x = rand()%tam; //sorteia um numero para o x de 0 a 6, ja que tam = 7
    y = rand()%tam;
    if(mapa[x][y]== '.') //se o mapa for vazio ele spawna o monstro no lugar sorteado
    mapa[x][y]= 'M';
    else
        cont--; //para quando o monstro cair num lugar que nao for vazio, o cont nao colocar menos monstros do que o desejado
    }
 }
void bossg(){
    int x,y,cont,a=0;
    for(cont=0;cont<=1;cont++,a++) {
    x = rand()%tam;
    y = rand()%tam;
    if(mapa[x][y] == '.')
        mapa[x][y] = 'B';
    else
        cont--;
    }
}
void frutas(int qntdf){
    int x,y,cont,a=0;
    for(cont=1;cont<=qntdf;cont++,a++) {
    x = rand()%tam;
    y = rand()%tam;
    if(mapa[x][y] == '.')
        mapa[x][y] = 'F';
    else
        cont--;
    }
}
    /*gotoxy(85,5);
    printf("a=%d",a);//contador de vezes em que o codigo rodou até colocar os M
}*/
void bossbattle(){
    int dano, danomonstro, dado, danosoma = 0, danomonstrosoma = 0, cont=0;
    dado = rand()%2;
    if(dado==0){
        do{
        dano = (heroi.atq * (rand()%2 + 1)) - boss.dfs;
        boss.vida = boss.vida - dano;
        danosoma = danosoma + dano;
        gotoxy(25,25);
        printf("voce deu %d de dano", dano);
        Beep(600, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(boss.vida <= 0){
            gotoxy(25,25);
            printf("voce ganhou!!!, dando %d de dano em %d rodadas", danosoma, cont);
            heroi.chave = 1;
            Beep(700, 300);
            Beep(600, 300);
            dinheiro = dinheiro + 100;
            Sleep(1000);
            printf("\033[25;25H\033[K");
            gotoxy(25,25);
            printf("a vida do heroi e %d", heroi.vida);
            break;
        }
        danomonstro = (boss.atq * (rand()%2 + 1)) - heroi.dfs;
        danomonstrosoma = danomonstrosoma + danomonstro;
        heroi.vida = heroi.vida - danomonstro;
        gotoxy(25,25);
        printf("você tomou %d de dano", danomonstro);
        Beep(200, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(heroi.vida <= 0){
            gotoxy(25,25);
            printf("voce perdeu!!!, tomou %d de dano em %d rodadas", danomonstrosoma, cont);
            Beep(200, 800);
            Sleep(1000);
            printf("\033[25;25H\033[K");
            exit(0);
        }
        }while(boss.vida>0 && heroi.vida>0);
    mapa[heroi.posx][heroi.posy] = '.';
    }
    else if(dado>0){
        do{
        danomonstro = (monstro.atq * (rand()%2 + 1)) - heroi.dfs;
        danomonstrosoma = danomonstrosoma + danomonstro;
        heroi.vida = heroi.vida - danomonstro;
        gotoxy(25,25);
        printf("voce tomou %d de dano", danomonstro);
        Beep(200, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(heroi.vida<=0){
            gotoxy(25,25);
            printf("voce perdeu, tomando %d de dano, em %d rodadas", danomonstrosoma, cont);
            Beep(200, 800);
            Sleep(1000);
            printf("\033[25;25H\033[K");
            exit(0);
        }
        dano = (heroi.atq * (rand()%2 + 1)) - monstro.dfs;
        danosoma = danosoma + dano;
        monstro.vida = monstro.vida - dano;
        gotoxy(25,25);
        printf("voce deu %d de dano", dano);
        Beep(600, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(monstro.vida <= 0){
            gotoxy(25,25);
            printf("voce ganhou, dando %d de dano, em %d rodadas", danosoma, cont);
            heroi.chave = 1;
            Beep(700, 300);
            Sleep(800);
            dinheiro = dinheiro + 50;
            printf("\033[25;25H\033[K");
            gotoxy(25,25);
            printf("a vida do heroi e %d", heroi.vida);
            printf("\033[25;25H\033[K");
            break;
        }
    }while(monstro.vida>0 && heroi.vida>0);
}

}
void ataque(){
    int dano, danomonstro, dado, danosoma = 0, danomonstrosoma = 0, cont=0;
    monstro.vida = 6;
    dado = rand()%2;
    if(dado==0){
        do{
        dano = (heroi.atq * (rand()%2 + 1)) - monstro.dfs;
        monstro.vida = monstro.vida - dano;
        danosoma = danosoma + dano;
        gotoxy(25,25);
        printf("voce deu %d de dano", dano);
        Beep(600, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(monstro.vida <= 0){
            gotoxy(25,25);
            printf("voce ganhou!!!, dando %d de dano em %d rodadas", danosoma, cont);
            Beep(700, 300);
            Beep(600, 300);
            dinheiro = dinheiro + 50;
            Sleep(1000);
            printf("\033[25;25H\033[K");
            gotoxy(25,25);
            printf("a vida do heroi e %d", heroi.vida);
            break;
        }
        danomonstro = (monstro.atq * (rand()%2 + 1)) - heroi.dfs;
        danomonstrosoma = danomonstrosoma + danomonstro;
        heroi.vida = heroi.vida - danomonstro;
        gotoxy(25,25);
        printf("você tomou %d de dano", danomonstro);
        Beep(200, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(heroi.vida <= 0){
            gotoxy(25,25);
            printf("voce perdeu!!!, tomou %d de dano em %d rodadas", danomonstrosoma, cont);
            Beep(200, 800);
            Sleep(1000);
            printf("\033[25;25H\033[K");
            exit(0);
        }
        }while(monstro.vida>0 && heroi.vida>0);
    mapa[heroi.posx][heroi.posy] = '.';
    }
    else if(dado>0){
        do{
        danomonstro = (monstro.atq * (rand()%2 + 1)) - heroi.dfs;
        danomonstrosoma = danomonstrosoma + danomonstro;
        heroi.vida = heroi.vida - danomonstro;
        gotoxy(25,25);
        printf("voce tomou %d de dano", danomonstro);
        Beep(200, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(heroi.vida<=0){
            gotoxy(25,25);
            printf("voce perdeu, tomando %d de dano, em %d rodadas", danomonstrosoma, cont);
            Beep(200, 800);
            Sleep(1000);
            printf("\033[25;25H\033[K");
            exit(0);
        }
        dano = (heroi.atq * (rand()%2 + 1)) - monstro.dfs;
        danosoma = danosoma + dano;
        monstro.vida = monstro.vida - dano;
        gotoxy(25,25);
        printf("voce deu %d de dano", dano);
        Beep(600, 300);
        Sleep(1000);
        printf("\033[25;25H\033[K");
        cont++;
        if(monstro.vida <= 0){
            gotoxy(25,25);
            printf("voce ganhou, dando %d de dano, em %d rodadas", danosoma, cont);
            Beep(700, 300);
            Sleep(800);
            dinheiro = dinheiro + 50;
            printf("\033[25;25H\033[K");
            gotoxy(25,25);
            printf("a vida do heroi e %d", heroi.vida);
            printf("\033[25;25H\033[K");
            break;
        }
    }while(monstro.vida>0 && heroi.vida>0);
}
}
int fuga(){
    int fator = (rand() % 20);
    int x=25;
    int y=25;
    if(fator<10){
        gotoxy(y,x);
        printf("Golpe de Sorte deu errado, voce tomou dano!!!");
        sleep(1000);
        heroi.vida = heroi.vida - 5;
        Beep(200, 300);
        Sleep(1500);
        printf("\033[25;25H\033[K");
        ataque();
    }else if(fator>=10){
        gotoxy(y,x);
        printf("Golpe de Sorte deu certo!!!");
        Sleep(1000);
        dinheiro = dinheiro + 75;
        printf("\033[25;25H\033[K");
    }
}
void itemmenu(){

}
void brigaboss(){
    int op;
    int x=25;
    int y=25;
    int erro;
    if(mapa[heroi.posx][heroi.posy]){
    gotoxy(y,x);
    printf("Luta com o Boss!!");
    Sleep(300);
    printf("                     ");
    printf("\n1 - Lutar!!!");
    printf("\n2 - menu de itens");
    printf("\nescolha oque fazer:  ");erro = scanf("%d", &op);
    switch(op){
    case 1:
        Sleep(1000);
        printf("\033[25;25H\033[K");
        printf("\033[26;26H\033[K");
        printf("\033[27;27H\033[K");
        printf("\033[28;28H\033[K");
        bossbattle();
        break;
    case 2:
        Sleep(1000);
        printf("\033[25;25H\033[K");
        itemmenu();
        break;
    default:
        break;
    }
}
}
void briga(){
    char op;
    int x=25;
    int y=25;
    int erro;
    if(mapa[heroi.posx][heroi.posy]){
    gotoxy(y,x);
    printf("Briga!!");
    Sleep(300);
    printf("                     ");
    printf("\n1 - Lutar!!!                                                ");
    printf("\n2 - Golpe De Sorte!!!                                        ");
    //printf("\n3 - menu de itens");
    printf("\nescolha oque fazer:                                           ");

    op=getch();
    switch(op){
    case '1':
        Sleep(1000);
        printf("\033[25;25H\033[K");
        printf("\033[26;26H\033[K");
        printf("\033[27;27H\033[K");
        printf("\033[28;28H\033[K");
        ataque();
        Sleep(2000);
        system("cls");
        break;
    case '2':
        Sleep(1000);
        printf("\033[25;25H\033[K");
        fuga();
        Sleep(2000);
        system("cls");
        break;
   /* case '3':
        itemmenu();
        break;*/
    default:
        printf("invalido");
        Sleep(1000);
        briga();
        system("cls");
        break;
    }
}
}
void movi(char letra){ //movimenta pra baixo
    static int movimentos = 0;
    movimentos++;
    gotoxy(10, 28);
    printf("movimentos %3d: ", movimentos);
    if (letra == 's'|| letra == 80){
        Beep(200, 100);
            if(heroi.posx + 1 >= tam){
                return;
            }else if(mapa[heroi.posx+1][heroi.posy] == 'M'){
                briga();
            }else if(mapa[heroi.posx+1][heroi.posy] == 'F'){
                heroi.vida = heroi.vida + 3;
                gotoxy(25,25);
                dinheiro = dinheiro + 10;
                printf("você tava com %d de vida, agora é %d", heroi.vida - 3, heroi.vida);
                Beep(220, 125); // Lá (A3)
                Beep(233, 125); // Lá# (A#3)
                Beep(247, 125); // Si (B3)
                Beep(261, 125); // Dó (C4)

                Beep(277, 125); // Dó# (C#4)
                Beep(294, 125); // Ré (D4)
                Beep(311, 125); // Ré# (D#4)
                Beep(330, 125); // Mí (E4)

                Sleep(800);
                printf("\033[25;25H\033[K");

            }else if(mapa[heroi.posx+1][heroi.posy] == 'B'){
                bossbattle();
            }
        mapa[heroi.posx][heroi.posy] ='.';
        mapa[heroi.posx+1][heroi.posy] ='T';
        heroi.posx++;
    }
    if (letra == 'd'|| letra == 77){
        Beep(200, 100);
            if(heroi.posy + 1 >= tam){
                return;
            }else if(mapa[heroi.posx][heroi.posy+1] == 'M'){
                briga();
            }else if(mapa[heroi.posx][heroi.posy+1] == 'F'){
                heroi.vida = heroi.vida + 3;
                dinheiro = dinheiro + 10;
                gotoxy(25,25);
                printf("você tava com %d de vida, agora é %d", heroi.vida - 3, heroi.vida);
                Beep(220, 125); // Lá (A3)
                Beep(233, 125); // Lá# (A#3)
                Beep(247, 125); // Si (B3)
                Beep(261, 125); // Dó (C4)

                Beep(277, 125); // Dó# (C#4)
                Beep(294, 125); // Ré (D4)
                Beep(311, 125); // Ré# (D#4)
                Beep(330, 125); // Mí (E4)
                Sleep(800);
                printf("\033[25;25H\033[K");
            }else if(mapa[heroi.posx][heroi.posy+1] == 'B'){
                bossbattle();
            }
        mapa[heroi.posx][heroi.posy] ='.';
        mapa[heroi.posx][heroi.posy+1] ='T';
        heroi.posy++;
    }
    if (letra == 'a'|| letra == 75){
        Beep(200, 100);
            if(heroi.posy - 1 < 0){
                return;
            }else if(mapa[heroi.posx][heroi.posy-1] == 'M'){
                briga();
            }else if(mapa[heroi.posx][heroi.posy-1] == 'F'){
                heroi.vida = heroi.vida + 3;
                gotoxy(25,25);
                dinheiro = dinheiro + 10;
                printf("voce estava com %d de vida, agora esta com %d", heroi.vida - 3, heroi.vida);
                Beep(220, 125); // Lá (A3)
                Beep(233, 125); // Lá# (A#3)
                Beep(247, 125); // Si (B3)
                Beep(261, 125); // Dó (C4)

                Beep(277, 125); // Dó# (C#4)
                Beep(294, 125); // Ré (D4)
                Beep(311, 125); // Ré# (D#4)
                Beep(330, 125); // Mí (E4)
                Sleep(800);
                printf("\033[25;25H\033[K");
            }else if(mapa[heroi.posx][heroi.posy-1] == 'B'){
                bossbattle();
            }
        mapa[heroi.posx][heroi.posy] ='.';
        mapa[heroi.posx][heroi.posy-1] ='T';
        heroi.posy--;
    }
    if (letra == 'w'|| letra == 72){
        Beep(200, 100);
            if(heroi.posx - 1 < 0){
                return;
            }else if(mapa[heroi.posx-1][heroi.posy] == 'M'){
                briga();
            }else if(mapa[heroi.posx-1][heroi.posy] == 'F'){
                heroi.vida = heroi.vida + 3;
                dinheiro = dinheiro + 10;
                gotoxy(25,25);
                printf("voce estava com %d de vida, agora esta com %d", heroi.vida - 3, heroi.vida);
                Beep(220, 125); // Lá (A3)
                Beep(233, 125); // Lá# (A#3)
                Beep(247, 125); // Si (B3)
                Beep(261, 125); // Dó (C4)

                Beep(277, 125); // Dó# (C#4)
                Beep(294, 125); // Ré (D4)
                Beep(311, 125); // Ré# (D#4)
                Beep(330, 125); // Mí (E4)
                Sleep(800);
                printf("\033[25;25H\033[K");
            }else if(mapa[heroi.posx-1][heroi.posy] == 'B'){
                bossbattle();
            }
        mapa[heroi.posx][heroi.posy] ='.';
        mapa[heroi.posx-1][heroi.posy] ='T';
        heroi.posx--;
    }
}

void loja(){
    char op, ys;
    do{
      system("cls");
        printf("=================================================================\n");
        printf(" Bem Vindo a Loja, Aqui voce pode melhorar seu personagem!      \n");
        printf("=================================================================\n");
        printf(" Seu Dinheiro Atual: R$ %d\n\n", dinheiro);
        printf(" 1 - Melhorar Dano   (R$ 100) -> Atual: %d\n", heroi.atq);
        printf(" 2 - Melhorar Vida   (R$  70) -> Atual: %d\n", heroi.vida);
        printf(" 3 - Melhorar Defesa (R$ 140) -> Atual: %d\n", heroi.dfs);
        printf(" 9 - Proxima fase!!\n");
        printf("-----------------------------------------------------------------\n");
        printf(" Escolha uma opcao (pressione a tecla): ");
        op= getch();



        switch(op){
        case '1':
            if(dinheiro - 100 < 0){
                printf("\nvoce necessita de matar mais monstros!!!\n");
                Sleep(800);
                system("cls");
            }else{
                dinheiro = dinheiro - 100;
                heroi.atq = heroi.atq + 1;
                printf("\nagora voce ta com %d de dano", heroi.atq);
                Sleep(2000);
                system("cls");
            }
            break;
    //        printf("\ngostaria de comprar mais?\n");
    //        printf("1 - SIM\n");
    //        printf("2 - NAO\n");
    //        scanf("%d", &ys);
    //        Sleep(500);
    //        system("cls");
    //        if(ys == 1){
    //            loja();
    //        }else{
    //            system("cls");
    //            inicializarMapa();
    //        }
    //            break;
        case '2':
            if(dinheiro - 70 < 0){
            printf("\nvoce precisa de mais dinheiro para a compra!!!\n");
            Sleep(800);
            system("cls");
            }
            else{
            dinheiro = dinheiro - 70;
                heroi.vida = heroi.vida + 1;
                printf("\nagora voce ta com %d de vida", heroi.vida);
                Sleep(2000);
                system("cls");
            }
    /*            printf("\ngostaria de comprar mais?\n");
                printf("1 - SIM\n");
                printf("2 - NAO\n");
                scanf("%d", &ys);
            if(ys == 1){
                    system("cls");
                loja();
            }else{
                system("cls");
                inicializarMapa();
            }
     */           break;
        case '3':
            if(dinheiro - 140 < 0){
                printf("\nvoce necessita de matar mais monstros\n!!!");
                Sleep(800);
                system("cls");
            }else{
                dinheiro = dinheiro - 140;
                heroi.dfs = heroi.dfs + 1;
                printf("\nvoce ta com %d de defesa\n", heroi.dfs);
                Sleep(2000);
                system("cls");
            }
    /*        printf("gostaria de comprar mais?\n");
            printf("1 - SIM\n");
            printf("2 - NAO\n");
            scanf("%d", &ys);
            if(ys == 1){
                Sleep(600);
                system("cls");
                loja();
            }else{
                Sleep(500);
                system("cls");
                inicializarMapa();
            }
    */            break;
        case '9':
            Sleep(500);
                system("cls");
                inicializarMapa();
                op=27;
                break;
        default:
             printf("invalido");
             Sleep(1000);
            system("cls");
        }

    }while(op != 27);
}


int saida(){
        system("cls");
        system("cls");
        gotoxy(25, 35);
        printf("parabens voce encontrou a saida, passando pra fase %d", contfase);
        system("cls");
        contfase++;
        Sleep(1500);
        printf("\033[25;25H\033[K");
        tam = tam + 1;
        amp = amp + 1;
        heroi.posx = heroi.posy = 0;
        ampmonstro = ampmonstro + 2;
        heroi.vida = 10;
        heroi.vida = heroi.vida + amp;
        heroi.atq = heroi.atq + amp;
        monstro.vida = 6;
        monstro.vida = monstro.vida + ampmonstro;
        monstro.atq = monstro.atq + ampmonstro;
        heroi.chave = 0;
        if(contfase == 4){
            printf("parabens voce exterminou a praga do labirinto");
            exit(1);
        }else{
        loja();
        system("cls");
        inicializarMapa();
        Spawn(4*amp);
        frutas(2*amp);
        bossg();
        }
}
int main(){
    system("");
    if(menu() == 0){
        return 0;
    }else{
        liberarMapa();
        heroi.posx = heroi.posy = 0;
        inicializarMapa();
    }
    char letra;
    srand(time(NULL));
    heroi.posx = heroi.posy = 0; //definição dupla para o jogador começar em 0,0
    char nomeJogo[]="Beans with Flour";
    gotoxy((80-strlen(nomeJogo))/2,5); //usa strlen pra pegar o numero de caracteres e por isso delimitar o centro
    printf("%s", nomeJogo);
    Spawn(5); //qntd, quantidade de monstros
    frutas(2);
    bossg();
    gotoxy(25,25);
    printf("a vida do heroi e %d", heroi.vida);
 do{
 Showmap();
  gotoxy(10, 26);
printf("FASE ATUAL: %d / 3 | Dinheiro: R$ %d  ",fase+1, dinheiro);
 gotoxy(10, 27);
printf("Sua Vida: %d  | Ataque: %d | Defesa: %d", heroi.vida, heroi.atq, heroi.dfs);
 letra = getch(); //pega a letra, se for s ele vai pra baixo
 movi(letra);
 perigo = contamonstro();
 gotoxy(1,29);
 printf("\033[K");
 gotoxy(10,29);
 if(perigo > 0){
    printf("Tem %d monstros por perto", perigo);
 }else{
    printf("seguro");
 }
 if(heroi.posx == tam - 1 && heroi.posy == tam - 1){
    if(heroi.chave == 0){
        gotoxy(25,25);
        printf("voce precisa matar o boss");
        Sleep(400);
        printf("\033[25;25H\033[K");
        mapa[heroi.posx][heroi.posy] = 'E';
        mapa[heroi.posx][heroi.posy-1] = 'T';
        heroi.posy--;
    }else{
    gotoxy(25, 25);
    printf("Terminou a fase %d", contfase);
    Beep(300, 500);
    Beep(450, 500);
    Beep(700, 700);
    Sleep(1000);
    printf("\033[25;25H\033[K");
    system("cls");
    saida();
 }
 }
 if(mapa[heroi.posx][heroi.posy] == 'M'){
    briga();
 }
 }while(letra!=27); //ate o usuario apertar esc
 getch();
}

