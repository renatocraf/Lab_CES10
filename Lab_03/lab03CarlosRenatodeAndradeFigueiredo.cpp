/* Copyright by CARLOS RENATO DE ANDRADE FIGUEIREDO   */
/* Turma 3                                            */
/* Lab 03: Sudoku Inteligente                         */
/* Programa compilado com CodeBlocks 17.12            */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<conio.h>
#define MAX 5             //ajustavel entre 2 e 9
#define NUMPREENCHIDO 6   //Numeros gerados no inicio do jogo
typedef int vetor[MAX];
typedef vetor matriz[MAX];

//variaveis globais
matriz tabuleiro={0};
int numLinCol, numLin, numCol, numJogo,jogadas, pontuacao,tentativa,derrota,vitoria,recorde;

//funcoes de formatacao
void mostrarTopo(){
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t\t\t SUDOKU INTELIGENTE");
    printf("\n\n\t\t\tMinha Pontuacao: %d\t\tRecorde Atual: %d",pontuacao,recorde);
    printf("\n\t\t\tTentativas restantes: %d",tentativa);
    return;
}

void mostrarTabuleiro(){
    //mostra o tabuleiro com bordas. Eh ajustavel para jogos 2x2 ate 9x9
    printf("\n\n\t\t\t\t\t-");
    for(int i = 0;i<MAX;i++)
        printf("----");
    for(int i =0; i<MAX; i++){
        printf("\n\t\t\t\t\t| ");
        for(int j=0; j<MAX;j++)
            //o valor 'MAX+1' significa que a posicao nao possui valores possiveis para se colocar
            if (tabuleiro[i][j]== MAX+1)
            printf("X | ");
            else
            printf("%d | ",tabuleiro[i][j]);
        printf("\n\t\t\t\t\t");
        for(int i = 0;i<MAX;i++)
            printf("----");
        printf("-");
    }
     printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    return;
}

void mostrarPontuacao(){
    //Tendo em vista o tabuleiro ter bordas, a formatacao da borda fica errada caso o numero de cada posicao tenha dois digitos ou mais.
    //Para evitar colocar "if's" desnecessarios, preferiu-se fazer uma nova funcao para mostrar a pontuacao
    printf("\n\n\t\t\t\t-");
    for(int i = 0;i<MAX;i++)
        printf("------");
    for(int i =0; i<MAX; i++){
        printf("\n\t\t\t\t| ");
        for(int j=0; j<MAX;j++)
            printf("%3d | ",pontuacao);
        printf("\n\t\t\t\t");
        for(int i = 0;i<MAX;i++)
            printf("------");
        printf("-");
    }
     printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    return;
}

void mostrarPerdeu(){
    //funcao que mostra um 'Perdeu!' e em seguida mostra o tabuleiro zerado
    //apos essa tela, o jogador volta para o menu inicial onde eh possivel iniciar um novo jogo
    system("cls");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\n\t\t\t\t ______ _________________ _____ _   _   _ ");
    printf("\n\t\t\t\t | ___ |  ___| ___ |  _  |  ___| | | | | |");
    printf("\n\t\t\t\t | |_/ | |__ | |_/ | | | | |__ | | | | | |");
    printf("\n\t\t\t\t |  __/|  __||    /| | | |  __|| | | | | |");
    printf("\n\t\t\t\t | |   | |___| |\\ \\| |/ /| |___| |_| | |_|");
    printf("\n\t\t\t\t \\_|   \\____/\\_| \\_|___/ \\____/ \\___/  (_)");
    mostrarTabuleiro();
    getch();
    fflush(stdin);
    return;
}

void mostrarGanhou(){
    //mostra apenas o 'Ganhou!'
    system("cls");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\n\n\n\t\t\t     _____  ___  _   _ _   _ _____ _   _   _ ");
    printf("\n\t\t\t    |  __ \\/ _ \\| \\ | | | | |  _  | | | | | |");
    printf("\n\t\t\t    | |  \\/ /_\\ |  \\| | |_| | | | | | | | | |");
    printf("\n\t\t\t    | | __|  _  | . ` |  _  | | | | | | | | |");
    printf("\n\t\t\t    | |_\\ | | | | |\\  | | | \\ \\_/ | |_| | |_|");
    printf("\n\t\t\t     \\____\\_| |_\\_| \\_\\_| |_/\\___/ \\___/  (_)");
    printf("\n\n\n\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    getch();
    fflush(stdin);
    return;
}

void mostrarPalavraSudoku(){
    //funcao para mostrar o Titulo no menu inicial
    printf("\n\t\t   _____ _   _______ _____ _   ___   _ ");
    printf("\n\t\t  /  ___| | | |  _  |  _  | | / | | | |");
    printf("\n\t\t  \\ `--.| | | | | | | | | | |/ /| | | |");
    printf("\n\t\t   `--. | | | | | | | | | |    \\| | | |");
    printf("\n\t\t  /\\__/ | |_| | |/ /\\ \\_/ | |\\  | |_| |");
    printf("\n\t\t  \\____/ \\___/|___/  \\___/\\_| \\_/\\___/ ");
    return;
}

void mostrarInstrucoes(){
    //funcao adicional que explica ao usuario as regras do jogo e como jogar
    system("cls");
    mostrarPalavraSudoku();
    printf("\n\n\tO jogo consiste em um tabuleiro %dx%d. O objetivo eh a colocao de numeros de 1 a %d nos",MAX,MAX,MAX);
    printf("\n\tespacos que estao numerados com o 0 de tal maneira que cada linha e coluna nao possa ter");
    printf("\n\tnumeros repetidos. O jogo pedira duas informacoes: ");
    printf("\n\n\t * A primeira eh a posicao de colocacao dos numeros. Para isso, deve-se digitar um numero");
    printf("\n\tde dois digitos, onde o algarismo das dezenas corresponde a linha e o algarismo das unidades ");
    printf("\n\tcorresponde a coluna. Por exemplo: o numero 14 sera a primeira linha e quarta coluna.");
    printf("\n\t * A segunda eh o numero que corresponde aquela posicao. Deve-se digitar um numero entre");
    printf("\n\t1 e %d, de modo que ele nao seja repetido em linhas e colunas. Caso voce perceba que aquela",MAX);
    printf("\n\tposicao nao possui numeros possiveis, basta escrever um numero negativo, e aquela posicao");
    printf("\n\tsera desconsiderada ao longo do jogo.");
    printf("\n\n\tVoce possui apenas 5 tentativas, e para cada erro, 5 pontos serao perdidos. Cuidado! Ao final");
    printf("\n\tdas 5 tentativas, voce perdera 10 pontos por cada espaco que nao foi preenchido.");
    printf("\n\tCaso esteja em duvida, voce pode pedir auxilio. Ao pedir auxilio, voce perde 2 pontos.");
    printf("\n\n\tDesenvolvido por: Carlos Renato de Andrade Figueiredo. ");
    printf("\n\n\tBom jogo! Aperte qualquer tecla para voltar: ");
    getch();
    fflush(stdin);
    return;
}

void preencherTodoTabuleiro(int valor){
    //funcao para preencher todo o tabuleiro com um unico valor. Agiliza ao zerar o tabuleiro.
    for (int i =0; i<MAX; i++)
        for(int j=0; j<MAX;j++)
            tabuleiro[i][j]=valor;
}

void verificarRecorde(){
    //Se bater recorde, o usuario recebe uma mensagem.
    system("cls");
    if(pontuacao>recorde){
        recorde=pontuacao;
        mostrarTopo();
        mostrarPontuacao();
        printf("\n\n\t\t\t  Parabens, voce bateu o recorde do jogo!!\n");
    }
    else{
        mostrarTopo();
        mostrarPontuacao();
    }
    printf("\n\n\t\tPressione qualquer tecla para voltar para a tela inicial.\n");
    getch();
    fflush(stdin);
}

int verificarDerrota(){
    //Funcao que verifica se o numero de tentativas ja foi extrapolado
    //Se sim, o usuario perdeu: mostra a tela perdeu com o tabuleiro com 'X' e apos uma tela com a pontuacao do usuario.
    //Apos, retorna ao menu inicial com a possibilidade de o jogador iniciar uma nova partida
    if(tentativa==0){
        preencherTodoTabuleiro(MAX+1);
        mostrarPerdeu();
        pontuacao-=jogadas*10;
        if(pontuacao<0)
            pontuacao=0;
        verificarRecorde();
        return 1;
    }
    return 0;
}

int verificarVitoria(){
    //Verifica se ainda ha jogadas disponeis. Se houver, retorna 0.
    //Se nao houver, significa que o jogo acabou e o usuario ganhou.
    if(jogadas)
        return 0;
    mostrarGanhou();
    verificarRecorde();
    return 1;
}

int validarLinCol(int lin, int col,int num){
    //valida se o num pode estar na matriz[lin][col]
    //se puder, retorna 1, senao, retorna 0
    for(int i = 0;i<MAX;i++)
        if(tabuleiro[lin][i]== num || tabuleiro[i][col]==num)
            return 0;
    return 1;
}

int checarValImp(int lin,int col){
    //funcao que vai verificar checar a posicao [lin][col] na tabela por forca bruta se existe valores impossiveis
    // se for impossivel, retorna 1, se houver algum valor possivel, retorna 0
    int valido;
    for(int i=1;i<=MAX;i++){
        valido = validarLinCol(numLin,numCol,i);
        if(valido)
            return 0;
    }
    return 1;
}

void gerarUmErro(){
    //essa funcao entra em acao quando o erro eh conhecido, diminui uma tentativa, diminui 5 pontos da pontuacao
    //e fala o numero de tentativas restantes
    tentativa--;
    pontuacao-=5;
    system("cls");
    mostrarTopo();
    mostrarTabuleiro();
    printf("\n\n\t\t\tValor incorreto. Voce ainda possui %d tentativa(s).",tentativa);
    return;
}

void verificarErro(int lin, int col, int num){
    //se houver erros de numJogo preenchido, a funcao gera um erro(chama outra funcao) e retorna o valor invalido(0)
    //se nao houver erros, a funcao retorna valido(1)
    int valido=0;
    if(num>0 && num<=MAX)
        valido = validarLinCol(lin,col,num);
    else if(numJogo<0){
        valido = checarValImp(numLin,numCol);
        num = MAX+1;
    }
    if(!valido)
        gerarUmErro();
    else{
        tabuleiro[lin][col]=num;
        jogadas--;
        system("cls");
        mostrarTopo();
        mostrarTabuleiro();
        }
    return;
}

void auxiliar(){
    //quando o usuario aceita o auxilio esta funcao percorre o tabuleiro a partir da linha 0, coluna 0 procurando
    //um espaco disponivel(0). quando acha, ele testa os numeros de um ate MAX para ver qual eh permitido naquele espaco
    //se nenhum desses valores for permitido, ele atribui o valor MAX+1, que eh o 'espaco impossivel' do jogo
    pontuacao-=2;
    for(int i=0;i<MAX;i++){
        for(int j=0; j<MAX;j++){
            if(!tabuleiro[i][j]){
                printf("\n\t\tA linha %d coluna %d sera preenchida",i+1,j+1);
                for(int k=1;k<=MAX;k++){
                        int valido;
                        valido = validarLinCol(i,j,k);
                        if(valido){
                            tabuleiro[i][j]=k;
                            jogadas--;
                            printf(" com um %d.",k);
                            getch();
                            fflush(stdin);
                            return;
                        }
                }
                tabuleiro[i][j]=MAX+1;
                jogadas--;
                printf(" com um 'X'.");
                getch();
                fflush(stdin);
                return;
            }
        }
    }
    return;
}

void oferecerAuxilio(){
    //essa funcao pergunta se o usuario deseja um auxilio ao custo de 2 pontos.
    //se ele aceitar a funcao auxiliar() eh chamada.
    //foi necessario incluir a funcao verificarVitoria() porque essa jogada pode acontecer no ultimo numero disponivel no tabuleiro
    if(!vitoria && tentativa>0){
        char ajuda = 'x';
        printf("\n\n\t\tDeseja receber um auxilio? Isso lhe custara apenas 2 pontos.(s/n) ");
        while(ajuda != 's' && ajuda != 'n' ){
            fflush(stdin);
            ajuda = getche();
            ajuda = tolower(ajuda);
            switch(ajuda){
            case 's':
                auxiliar();
                system("cls");
                mostrarTopo();
                mostrarTabuleiro();
                break;
            case 'n':
                break;
            default:
                printf("\n\n\t\tCaractere invalido. Digite novamente. ");
            }
        }
    }
    return;
}

void pegarPosicao(){
    //Funcao que pede a posicao ao usuario e verifica se os valores estao validos.
    //O usuario erra enquanto nao preencher uma posicao corretamente.
    int valido = 0;
    while(!vitoria && !valido && tentativa>0){
        numLinCol = -1;
        numLin = -1;
        numCol=-1;
        printf("\n\n\t\t\tDigite a localizacao(Para instrucoes, digite 99): ");
        scanf("%d",&numLinCol);
        fflush(stdin);
        //Para achar a coluna pega-se o resultado da divisao do numLinCol por 10
        //Para achar a linha pega-se o resto da divisao do numLinCol por 10
        if ((numLinCol/10)>0 && (numLinCol/10)<=MAX && (numLinCol%10)>0 && (numLinCol%10)<=MAX){
            numLin = numLinCol/10-1;
            numCol = numLinCol%10-1;
            if(!tabuleiro[numLin][numCol])
                valido++;
            else
                //se o usuario escolher uma posicao ja ocupada, gera um erro.
                gerarUmErro();
        }
        else if (numLinCol == 99){
            //serve para dar instrucoes de como preencher
            printf("\n\t\tDeve-se digitar um numero de dois digitos, onde o algarismo das dezenas");
            printf("\n\t\tcorresponde a linha e o algarismo das unidades corresponde a coluna. Por");
            printf("\n\t\texemplo: o numero 14 sera a primeira linha e quarta coluna.");
            printf("\n\n\t\tAperte qualquer tecla para voltar: ");
            getch();
            fflush(stdin);
        }
        else
            //se o usuario digitar um valor fora do escopo, gera um erro.
            gerarUmErro();
    }
    return;
}

void pegarNumJogo(){
    //Funcao que solicita e pega o numero que o usuario quer jogar.
    //Se ele errar, o programa oferece ajuda.
    numJogo=6;
    if(!vitoria && tentativa>0){
        //se o numero digitado for valido(1) e o numero de tentativas for extrapolado(<0), o programa para de pedir um numero
        printf("\n\t\t\tDigite um numero entre 1-%d que sera armazenado",MAX);
        printf("\n\t\t\tna posicao escolhida(linha %d, coluna %d): ",numLin+1,numCol+1);
        scanf("%d",&numJogo);
        fflush(stdin);
        verificarErro(numLin,numCol,numJogo);
    }
    if(!jogadas)
            vitoria=1;
    return;
}

void gerarTabuleiroInicial(){
    //funcao que vai gerar numeros aleatorios em posicoes aleatorias e colocar no tabuleiro antes do inicio do jogo
    srand(time(NULL));
    int lin,col,num,scan,valido;
    for(int i = 0;i<NUMPREENCHIDO;i++){
        //com o NUMPREENCHIDO eh possivel escolher com qnts numero o tabuleiro vai comecar (facilita o debug)
        valido = 0;
        while(!valido){
            scan = 0;
            lin = rand()%MAX;
            col = rand()%MAX;
            num = rand()%MAX+1;
            scan = validarLinCol(lin,col,num);
            //se a posicao do tabuleiro nao estiver ocupada(!tabuleiro) e o escaneamento da linha e da coluna forem validos(1) retorna 1
            if(!tabuleiro[lin][col] && scan){
                valido = 1;
                tabuleiro[lin][col]=num;
                }
        }
    }
    return;
}

void iniciarNovoJogo(){
    //zerando variaveis
    vitoria = 0;
    derrota = 0;
    tentativa = 5;
    pontuacao = 100;
    jogadas=MAX*MAX-NUMPREENCHIDO;
    preencherTodoTabuleiro(0);
    gerarTabuleiroInicial();
    //inicio do jogo propriamente dito
    while(!vitoria && !derrota){
        system("cls");
        mostrarTopo();
        mostrarTabuleiro();
        pegarPosicao();
        pegarNumJogo();
        oferecerAuxilio();
        //a cada rodada ele verifica se o jogador venceu ou perdeu
        derrota = verificarDerrota();
        vitoria = verificarVitoria();
    }
    return;
};

void iniciarMenu(){
    int opcao = 0;
    while(opcao!=3){
        opcao = 0;
        system("cls");
        mostrarPalavraSudoku();
        printf("\n\n\t\tBEM VINDO AO SUDOKU \"UM POUCO\" INTELIGENTE");
        printf("\n\n\t\t\t    Recorde Atual: %d",recorde);
        printf("\n\n\t\t\tEscolha uma opcao abaixo:");
        printf("\n\n\t\t1. Novo jogo;");
        printf("\n\t\t2. Instrucoes;");
        printf("\n\t\t3. Sair");
        printf("\n\n\t\tOpcao escolhida: ");
        scanf("%d",&opcao);
        fflush(stdin);
        switch(opcao){
        case 1:
            iniciarNovoJogo();
            break;
        case 2:
            mostrarInstrucoes();
            break;
        case 3:
            break;
        default:
            printf("\n\n\tOpcao invalida. Aperte qualquer tecla para retornar.");
            getch();
            fflush(stdin);
        }
    }
    return;
}

int main(){
    recorde = 0;
    iniciarMenu();
    return 0;
}

