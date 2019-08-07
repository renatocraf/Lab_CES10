#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct voo voo;
struct voo{
    int numero;
    char origem[25];
    int estadoUrgencia=FALSE;
    voo *prox;
};

//Protótipos das funções:
int lerComando (FILE *arqA, FILE *arqB, voo **C);

int main ()
{
    //Variáveis:
    FILE *arqEntrada, *arqSaida;
    int cont=0;
    char aux[71];
    voo *inicioLista=NULL;
    //Início:
    arqEntrada=fopen("C:\\Lab11\\entrada11.txt", "r");
    arqSaida=fopen("C:\\Lab11\\ArturAssisAlves11.txt", "w");
    for (int i=0; i<8; i++)
        fgets(aux, 70, arqEntrada);
    fprintf(arqSaida,"Torre de Controle\nAeronautica\nAUTORIZACAO DE POUSO\n=========================================\nFLIGHT  FROM\n\n");
while (lerComando(arqEntrada, arqSaida, &inicioLista));
return 0;
}

//Funções:
int lerComando (FILE *arqA, FILE *arqB, voo **C)
{
    char aux[70];
    int auxNum;
    voo *P, *auxP;

    fscanf(arqA, "%s ", aux);
    if (strcmp(aux,"pede_pouso")==0) //Aviao pede para pousar.
    {
        P=(voo*)malloc(sizeof(voo));
        P->prox=NULL;
        fscanf(arqA, "%d ",&P->numero);
        fgets(P->origem,71,arqA);
        //Eliminar \n
        for (int i=0; i<71; i++)
        {
            if (P->origem[i]=='\n')
                P->origem[i]='\0';
        }
        if (*C==NULL)
            *C=P;
        else
        {
            auxP=*C;
            while (auxP->prox!=NULL)
                auxP=auxP->prox;
            auxP->prox=P;
        }
    }
    if (strcmp(aux,"URGENCIA")==0)  //Aviao declara URGÊNCIA.
    {
        fscanf(arqA, "%d ", &auxNum);
        fgets(aux, 70, arqA);
        if (auxNum==(*C)->numero)
            (*C)->estadoUrgencia=TRUE;
        else
        {
            P=*C;
            while (auxNum!=(P->prox->numero))
                P=P->prox;
            if (P->estadoUrgencia==TRUE)
                P->prox->estadoUrgencia=TRUE;
            else
            {
                P->prox->estadoUrgencia=TRUE;
                auxP=P->prox;
                P->prox=auxP->prox;
                if ((*C)->estadoUrgencia==TRUE)
                {
                    P=*C;
                    while (P->prox->estadoUrgencia==TRUE)
                    P=P->prox;
                    auxP->prox=P->prox;
                    P->prox=auxP;

                }
                else
                {
                    auxP->prox=*C;
                    *C=auxP;
                }
            }
        }
    }
    if (strcmp(aux,"pista_liberada")==0)  //Terra declara pista liberada.
    {
        fgets(aux, 70, arqA);
        if(*C==NULL)
            fprintf(arqB,"0000    Nenhum aviao pousando\n");
        else
        {
            fprintf(arqB,"%0.4d    %s\n",(*C)->numero,(*C)->origem);
            auxP=*C;
            *C=(*C)->prox;
            free(auxP);
        }
    }
    if (strcmp(aux,"FIM")==0) //FIM do arquivo entrada11.txt
    {
        if (*C==NULL)
            fprintf(arqB,"\nSituacao da fila\n\nVAZIA\n");
        else
        {
           fprintf(arqB,"\nSituacao da fila\n\n");
           P=*C;
           while (P!=NULL)
           {
               fprintf(arqB,"%0.4d    %s\n",P->numero,P->origem);
               P=P->prox;
           }
        }
        return 0;
    }

    return 1;
}
