/* Copyright by CARLOS RENATO DE ANDRADE DE FIGUEIREDO */
/* Turma 3                                             */
/* Lab 02: TV ASCII                                    */
/* Programa compilado com CodeBlocks 17.12             */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

//Funcoes de validacao
int validarNum(int num){
    //Funcao para validar o numero digitado pela pessoa.
    //Caso o numero esteja entre 0 e 255, retorna True(1)
    //Senao, ele retorna False(0)
    if(num>=0 && num<=255)
        return 1;
    else{
        printf("\t\tNumero invalido, tente novamente.\n\t\t");
        return 0;
    }
}

int validarChar(int c){
    //Funcao para validar um char.
    //Caso seja igual aos caracteres citados, retorna true(1). Senao, retorna false(0).
    if(c=='s' || c=='n')
        return 1;
    else{
        printf("\tOpcao Invalida. Digite 's' para sim ou 'n' para nao.\n\t");
        return 0;
    }
}

//Funcoes operacao de bits
int shiftDireita(int num){
    //Funcao para jogar os bits de um numero para direita e retornar o novo numero
    //Utilizado na tela esquerda
    if (num&1){
        num = num >> 1;
        num+=128;
    }
    else
        num = num >> 1;
    return num;
}

int shift3Direita(int num){
    //Funcao para dar um shift para direita 3 vezes seguidas e retornar o valor
    //Utilizado na tela esquerda
    int i=0;
    while(i<3){
        num = shiftDireita(num);
        i++;
    }
    return num;
}

//Funcoes apresentacao
void mostrarNum(int num,int base){
    //Funcao para mostrar 8 bits de um numero(num)
    //Se o numero base(base) for uma letra entre a-z e A-Z o numero(num) eh apresentado com caracteres ASCII
    //Senao, ele eh apresentado pelo no formato binario (0's e 1's)
    int i=0;
    if((base>=65 && base<=90)||(base>=97 && base <= 122)){
            while(i<8){
                if (num&128)
                    printf("%c",base);
                else
                    printf(".");
                num = num <<1;
                i++;
            }
    }
    else{
        while(i<8){
                if (num&128)
                    printf("1");
                else
                    printf("0");
                num = num <<1;
                i++;
            }
    }

    return;
}

void printarTvTopo(){
        //printa a parte de cima da tv, com a antena
        printf("\t\t\t\t        \\\\           //\n");
        printf("\t\t\t\t         \\\\         //\n");
        printf("\t\t\t\t          \\\\       //\n");
        printf("\t\t\t\t           \\\\     //\n");
        printf("\t\t\t\t            \\\\   //\n");
        printf("\t\t\t\t             \\\\ //\n");
        printf("\t\t\t\t           /~~~~~~~\\\n");
        printf("\t\t\t\t##################################\n");
        printf("\t\t\t\t# _____________________ #        #\n");
        printf("\t\t\t\t# |                   | #        #\n");
    return;
}

void printarBotao(int cont){
    //Printa os botoes nas linhas 1 e 4. Nas linhas 2 e 5 printa vol e can
    switch (cont){
        case 1:
            printf(" | # (-)(+) #");
            break;
        case 2:
            printf(" | #  vol   #");
            break;
        case 4:
            printf(" | # (<)(>) #");
            break;
        case 5:
            printf(" | #  can   #");
            break;
        default:
            printf(" | #        #");
            break;
    }
    return;
}

void printarTvBot(){
        //print da parte de baixo da televisao
        printf("\t\t\t\t# |___________________| #  (O)   #\n");
        printf("\t\t\t\t#                       # on/off #\n");
        printf("\t\t\t\t##################################\n");
}

//Funcoes para resultados
int somar3(int n1,int n2){
    //verifica se cada um dos numeros eh multiplo de 3.
    //apos retorna a soma.
    int soma=0;
    if(n1%3==0)
        soma+=n1;
    if(n2%3==0)
        soma+=n2;
    return soma;
}

int ehPrimo(int n){
    //verifica se eh primo. se sim, retorna 1, se nao retorna 0
    int i;
    i=2;
    while(i<=n/2){
        if (n%i==0){
            return 0;
        }
        i++;
    }
    return 1;

}

int ehQP(int n){
    //verifica se eh um quadrado perfeito. se sim, retorna 1, senao retorna 0.
    int i=1;
    while(i*i<=n){
        if(i*i==n)
            return 1;
        i++;
    }
    return 0;
}

int ehImp(int n){
    //verifica se eh impar, caso seja, retorna 1, senao, retorna 0.
    if(n%2==0)
        return 0;
    else
        return 1;
}


int main(){
    int base,n,i,h,valido,soma,qtdPrimos,qtdQP,soma3,qtdImp,qtdPar;
    char c = 's';

    //Tela de Boas vindas
    printf("\n\t\t\t\t\t BEM VINDO A TV ASCII!!");
    printf("\n\t\tA TV ASCII eh uma televisao na qual o usuario digita um numero entre 0 e 255 e a");
    printf("\n\ttelevisao mostrara algumas linhas de numeros em binario. Ao fim sao apresentadas algumas");
    printf("\n\tinformacoes sobre os numeros apresentados.");
    printf("\n\t\tSe o numero digitado corresponder a uma letra na tabela ASCII, os valores dos \"1's\"");
    printf("\n\t serao substituidos pela respectiva letra, e os valores \"0's\" serao substituidos por ponto \".\". ");

    while(c == 's'){
        //Solicitacao do numero (caso o usuario utilize float, sera considerado a parte inteira)
        printf("\n\t\tDigite um numero inteiro entre 0 e 255, inclusive: ");

        //Zerando as variáveis
        //Atribuindo valor nao valido para a base(utilizado para evitar problemas de validacao quando o problema for executado mais de uma vez)
        base = -1;
        i = 0;
        soma=0;
        qtdPrimos=0;
        qtdQP=0;
        soma3=0;
        qtdImp=0;
        qtdPar=0;

        //zerando a variavel 'valido' para fazer a validacao do numero recebido
        valido = 0;

        //validacao do numero recebido. Enquanto nao receber um numero entre 0 e 255, o programa nao continua
        do{
            scanf("%d",&base);
            fflush(stdin);
            valido = validarNum(base);
        }while(valido!=1);

        //Variavel da tela direita
        n=base;
        //Variavel da tela esquerda
        h = shift3Direita(n);

        //print de formatacao da tv
        printf("\n");
        printarTvTopo();

        //while que printa as linhas da televisao
        while(i<8){
            //print das linhas
            printf("\t\t\t\t# | ");
            mostrarNum(n,base);
            printf("|");
            mostrarNum(h,base);
            printarBotao(i);

            //print para debug (verificacao dos numeros que estao sendo printados em cada linha)
            //printf(" | n=%3d h=%3d",n,h);

            printf("\n");

            //operacoes realizadas para futura apresentacao dos resultados
            soma+=n+h;
            soma3+=somar3(n,h);
            qtdPrimos+=ehPrimo(n)+ehPrimo(h);
            qtdQP+=ehQP(n) + ehQP(h);
            qtdImp+=ehImp(n) + ehImp(h);
            qtdPar=16-qtdImp;

            //preparacao para o proximo ciclo do while
            n = shiftDireita(n);
            h = shift3Direita(h);
            i++;
        }

        //print de formatacao da tv
        printarTvBot();
        printf("\n");

        //apresentacao dos resultados obtidos
        printf("\n\tDesenvolvido por: Carlos Renato de Andrade Figueiredo - Turma 03");
        printf("\n\tSOMA DOS NUMEROS OBTIDOS: %d",soma);
        printf("\n\tQUANTIDADE DE PRIMOS: %d",qtdPrimos);
        printf("\n\tQUANTIDADE DE QUADRADOS PERFEITOS: %d",qtdQP);
        printf("\n\tSOMA DOS MULTIPLOS DE 3: %d",soma3);
        printf("\n\tQUANTIDADE DE IMPARES: %d",qtdImp);
        printf("\n\tQUANTIDADE DE PARES: %d\n",qtdPar);

        printf("\n\tDeseja verificar mais um numero?(s/n)");

        //zerando a variavel 'valido' para validacao do char recebido
        valido = 0;

        //realizando validacao do caractere recebido. Pode ser 's' ou 'n', maisculo ou minusculo
        do{
            c = getchar();
            fflush(stdin);
            c = tolower(c);
            valido = validarChar(c);
        }while(valido!=1);
    }
    return 0;
}
