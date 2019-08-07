#include <stdio.h>
#include <stdlib.h>

int main(){
    //variaveis
    int a,b,c,cont;     //a=multiplicando b=multiplicador c=resultado cont=contador
    c=0;                //atribui valor pro c para poder fazer a primeira soma
    cont=1;             //atribui valor 1 ao contador referente ao primeiro ciclo

    //TITULO
    printf("\n\n\tCALCULADORA DE LEIBNITZ  1671\n\n");

    //scanear variaveis
    printf(" Entre com o Multiplicando  : ");
    scanf("%d",&a); //scaneando o multiplicando
    printf(" Entre com o Multiplicador  : ");
    scanf("%d",&b); //scaneando o multiplicador

    //espacamento + titulo do calculo
    printf("\n\n --------------------------------\n");
    printf(" RESULTADO EM CICLOS SUCESSIVOS\n\n");

    //inicio dos calculos e ciclos
    while(cont<=b){                          //enquanto cont <= b,
        c+=a;                                //some "a" ao resultado c,
        printf("\tCiclo %d = +%d\n",cont,a); //imprima o numero do ciclo e o valor que será somado,
        printf("\t\tParcela = %d\n\n",c);    //imprima o resultado parcial
        cont++;                              //some 1 ao contador
    }

    //rodape de encerramento e resultado
    printf(" --------------------------------\n");
    printf(" Resultado Produto  (%d x %d) = %d\n\n\n",a,b,c);

    system("PAUSE");
    return 0;
}
