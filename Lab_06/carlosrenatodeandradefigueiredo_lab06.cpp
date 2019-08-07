/* Copyright by Carlos Renato de Andrade Figueiredo */
/* Turma 3                                          */
/* Lab 06: Criptografia em arquivo texto            */
/* Programa compilado com CodeBlocks 17.12          */
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<conio.h>

typedef struct caracter noh;

struct caracter
{
    char letra;
    int numero;
    int m;
    noh *prox;
};

int verificarPrimo(int primo)
{   //verifica se o numero eh primo
    int i;
    if(primo<=1 || primo>100)
        return 0;
    for(i=2;i*i<=primo;i++)
    {
        if(primo%i==0)
            return 0;
    }
    return 1;
}

void obterPrimos(int *p,int *q)
{   //obtem os dois primos baseados nos requisitos pedidos
    int valido =0;
    printf("\n\tDigite um numero primo menor que 100: ");
    while(valido ==0)
    {
        scanf("%d",p);
        fflush(stdin);
        valido = verificarPrimo(*p);
        if (!valido)
            printf("\n\tValor Invalido. Tente novamente.\n\t");
    }
    valido =0;
    while(valido ==0)
    {
        printf("\n\tDigite outro numero primo menor que 100.");
        printf("\n\tLembre-se! A multiplicacao dos dois primos ");
        printf("\n\tdeve ser maior que 23: ");
        scanf("%d",q);
        fflush(stdin);
        valido = verificarPrimo(*q);
        if(*q * *p <23 || (*p==*q && *p<=23))
            valido=0;
        if (!valido)
            printf("\n\tValor Invalido. Tente novamente.\n");
    }
    return;
}

int mdc(int num1,int num2)
{   //retorna o valor entre dois numeros
    int resto;
    do
    {
        resto = num1 % num2;
        num1 = num2;
        num2 = resto;
    } while (resto != 0);
    return num1;
}

void menorMDC(int tot, int *e,int *e2,int *e3)
{   //pega os tres primeiros valores possiveis da chave publica
    int i, maximo=0, valido=0;
    for (i=2; i<tot && valido<3;i++)
    {
        maximo=mdc(tot,i);
        if(maximo==1)
        {
            if(*e==0)
                *e=i;
            if(*e!=0&&*e2==0&&i!=*e)
                *e2=i;
            if (*e2!=0 &&*e3==0&&i!=*e2)
                *e3=i;
        valido++;
        }
    }
}

int potmod(int m,int e, int n)
{   //potencia modular. funcao recursiva para nao extrapolar o limite do unsigned int
    if(e==1)
        return 1;
    else if (e==2)
        return (m*m)%n;
    else
        return (potmod(m,e-1,n)*m)%n;
}

int gerarC(int n,int e,char letra,int *m)
{   //criptografa a letra
    unsigned long long int c;
    letra = toupper(letra);
    *m=letra-64;
    if(*m>10&& *m<23)
        *m-=1;
    if (*m==24)
        *m-=2;
    if (*m==26)
        *m-=3;
    c=potmod(*m,e,n);
    return c;
}

unsigned int gerarDValido(int letra1,int c, unsigned int d, int n)
{   //gera uma chave privada para a letra1 baseada num D ja existente
    while(d<4294967295)
    {
        if(letra1 == potmod(c,d,n))
        {
            return d;
        }
        else
            d++;
    }
    return 0;
}

int validarLetra2(int c, int d, int n,int e)
{   //valida a chave privada com todas as letras do alfabeto
    int cript;
    for(int i=2;i<=23;i++)
    {
        cript = potmod(i,e,n);
        if( i!=potmod(cript,d,n))
            return 0;
    }
    return 1;
}

unsigned int gerarPrivKey(int n, int e)
{   //gera a chave privada
    //usar a letra B(2) como referencia
    //sera achado o primeiro 'd' que sirva para ela, e depois sera testado em todas as outras letras por forca bruta
    //se nao funcionar com alguma letra, achara o segundo 'd' possivel e assim sucessivamente
    unsigned int d = 2;
    int c,valido=0;
    c= potmod(2,e,n);//letra 'B' criptografada
    while(d<4294967295 && !valido )
    {
        d = gerarDValido(2,c,d,n);
        valido = validarLetra2(c,d,n,e);
        if(!valido)
            d++;
    }
    return d;
}

int decript(int c, int d, int n)
{ //decripta a letra e leva ela para o valor maiusculo da tabela ASCII
    int m= potmod(c,d,n);
    if(m>0 && m<=10)
        return m+64;
    else if(m>10&& m<=21)
        return m+65;
    else if (m==22)
        return m+66;
    else if (m==23);
        return m+67;
}

int main()
{
    int p,q,e=0,e2=0,e3=0,n,m,d,d2,d3,tot;
    char letra;
    FILE *entrada,*saida;
    noh *inicio=NULL;
    noh *ponteiro=NULL;
    noh *fim=NULL;
    entrada = fopen("mensagem.txt","r");
    printf("\n\t\t\t LAB 06 - CRIPTOGRAFANDO");
    printf("\n\t\tDesenvolvido por: Carlos RENATO de Andrade Figueiredo\n\n");
    printf("\n\tDeve-se digitar dois numeros primos menores do que 100 com as seguintes condicoes:");
    printf("\n\t- A multiplicacao dos dois deve ser maior do que 23;e");
    printf("\n\t- Caso digite iguais, serao validos apenas valores acima de 23.\n");
    printf("\n\tObs: Nao esqueca de colocar o arquivo 'mensagem.txt' na mesma pasta desse programa.\n\n");
    obterPrimos(&p,&q);
    n=p*q;
    tot=(p-1)*(q-1);
    menorMDC(tot,&e,&e2,&e3);
    //ler o arquivo e gerar lista ligada com o char e o respesctivo numero criptografado
    while(fscanf(entrada,"%c",&letra)!=EOF)
    {
        letra =toupper(letra);
        if (letra>64 && letra <91 && letra!=75 && letra!=87 && letra!=89)
        {
            if(inicio == NULL)
            {
                inicio = (noh*)malloc(sizeof(noh));
                inicio->letra= letra;
                inicio->numero=gerarC(n,e,inicio->letra,&m);
                inicio->m=m;
                inicio->prox=NULL;
                fim = inicio;
            }
            else
            {
                ponteiro = (noh*)malloc(sizeof(noh));
                ponteiro->letra=letra;
                ponteiro->numero=gerarC(n,e,ponteiro->letra,&m);
                ponteiro->m=m;
                ponteiro->prox=NULL;
                fim->prox = ponteiro;
                fim=ponteiro;
            }
       }
    }

    //gerar a chave privada por forca bruta
    d = gerarPrivKey(n,e);
    d2 = gerarPrivKey(n,e2);
    d3 = gerarPrivKey(n,e3);
    printf("\n\t--------------------------------------------------");
    printf("\n\t|Chave Publica(e)| Chave Privada(d)| Tentativas  |");
    printf("\n\t| %9d      |  %10d     |  %10d |",e,d,d-1);
    printf("\n\t| %9d      |  %10d     |  %10d |",e2,d2,d2-1);
    printf("\n\t| %9d      |  %10d     |  %10d |",e3,d3,d3-1);
    printf("\n\t--------------------------------------------------");
    //printar na tela
    printf("\n\n\tVoce encriptou o seguinte texto:\n\n\t\t");
    ponteiro = inicio;
    while(ponteiro!=NULL)
    {
        int num = ponteiro->numero;
        int caract = decript(num,d,n);
        printf("%c",tolower(caract));
        ponteiro=ponteiro->prox;
    }
    printf("\n\n");
    // gerar o texto criptografado no arquivo txt
    ponteiro = inicio;
    saida = fopen("mensagemCriptografada.txt","w");
    while(ponteiro!=NULL)
    {
        fprintf(saida,"%d ",ponteiro->numero);
        ponteiro=ponteiro->prox;
    }
    fclose(entrada);
    fclose(saida);
    getch();
    return 0;
}





