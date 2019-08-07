/* Copyright by Carlos Renato de Andrade Figueiredo */
/* Turma 3                                          */
/* Lab 05: Copa do Mundo 2018                       */
/* Programa compilado com CodeBlocks 17.12          */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string>
#include<windows.h>
#include<conio.h>

typedef char cadeia[26];

typedef struct primeiros primeiros;
struct primeiros
{
    int numPrimeiro,numSegundo;
    cadeia primeiro,segundo;
};

typedef struct selecao selecao;
struct selecao
{
    cadeia nome;
    int pontos,vitorias,empates,golspro,golscontra,saldogols,maxgolspro,maxgolcontra;
};

typedef struct grupo grupo;
struct grupo
{//armazena as selecoes e resultados da primeira fase
    char nome;
    selecao VetorSelecoes[5];
    int Resultados[6][2];
    primeiros vencedoresGrupo;
};

typedef struct res2fase res2fase;
struct res2fase
{//armazena as selecoes e resultados da segunda fase
    int selecoes2Fase[36][2];
    /* coluna 0: grupo - coluna 1: selecao */
    /*  0-15   selecoes oitavas de final   */
    /*  16-23  selecoes quartas de final   */
    /*  24-27  selecoes semifinais         */
    /*  28-31  selecoes final              */
    /*  32-35  classificao                 */
    int placar2fase[16][2];
    /*  0-7     oitavas     */
    /*  8-11    quartas     */
    /*  12-13   semifinais  */
    /*  14-15   finais      */
};

void LerSelecoes(grupo *VetorGrupos,FILE *FileIn, FILE *Estatisticas)
{//funcao para ler os dados os arquivos de texto
    int i,j,lenght;
    char nomegrupo;
    for(i=1,nomegrupo = 'A';i<=8;nomegrupo++,i++)
    {
        VetorGrupos[i].nome = nomegrupo;
        for(j = 1; j<= 4;j++)
        {
            fgets(VetorGrupos[i].VetorSelecoes[j].nome,31,FileIn);
            lenght = strlen(VetorGrupos[i].VetorSelecoes[j].nome);
            VetorGrupos[i].VetorSelecoes[j].nome[lenght-1]='\0';
            VetorGrupos[i].VetorSelecoes[j].pontos = 0;
            VetorGrupos[i].VetorSelecoes[j].vitorias = 0;
            VetorGrupos[i].VetorSelecoes[j].empates = 0;
            VetorGrupos[i].VetorSelecoes[j].golspro = 0;
            VetorGrupos[i].VetorSelecoes[j].golscontra = 0;
            VetorGrupos[i].VetorSelecoes[j].saldogols = 0;
            VetorGrupos[i].vencedoresGrupo.numPrimeiro =0;
            VetorGrupos[i].vencedoresGrupo.numSegundo =0;
            fscanf(Estatisticas,"%d",&VetorGrupos[i].VetorSelecoes[j].maxgolspro);
            fscanf(Estatisticas,"%d",&VetorGrupos[i].VetorSelecoes[j].maxgolcontra);
        }
    }
}

void atualizaPontos(grupo *VetorGrupos,int grupo,int selecao)
{//atualiza pontos e saldo de gols de uma selecao de um grupo
    VetorGrupos[grupo].VetorSelecoes[selecao].pontos =
        VetorGrupos[grupo].VetorSelecoes[selecao].vitorias * 3 +
        VetorGrupos[grupo].VetorSelecoes[selecao].empates;
    VetorGrupos[grupo].VetorSelecoes[selecao].saldogols =
        VetorGrupos[grupo].VetorSelecoes[selecao].golspro -
        VetorGrupos[grupo].VetorSelecoes[selecao].golscontra;
}

int maior(grupo *VetorGrupos,int grupo,int comparado, int comparar)
{//usando os criterios determinados pelo professor, a funcao retorna a selecao que esta na frente na tabela entre as duas
   if(VetorGrupos[grupo].VetorSelecoes[comparado].pontos<VetorGrupos[grupo].VetorSelecoes[comparar].pontos)
        return comparar;
    else if(VetorGrupos[grupo].VetorSelecoes[comparado].pontos==VetorGrupos[grupo].VetorSelecoes[comparar].pontos && comparado!=comparar)
    {
        if(VetorGrupos[grupo].VetorSelecoes[comparado].vitorias<VetorGrupos[grupo].VetorSelecoes[comparar].vitorias)
            return comparar;
        else if(VetorGrupos[grupo].VetorSelecoes[comparado].vitorias==VetorGrupos[grupo].VetorSelecoes[comparar].vitorias)
        {
            if(VetorGrupos[grupo].VetorSelecoes[comparado].saldogols<VetorGrupos[grupo].VetorSelecoes[comparar].saldogols)
                return comparar;
            else if(VetorGrupos[grupo].VetorSelecoes[comparado].saldogols==VetorGrupos[grupo].VetorSelecoes[comparar].saldogols)
            {
                if(VetorGrupos[grupo].VetorSelecoes[comparado].golspro<VetorGrupos[grupo].VetorSelecoes[comparar].golspro)
                    return comparar;
                else if (strcmp(VetorGrupos[grupo].VetorSelecoes[comparado].nome,VetorGrupos[grupo].VetorSelecoes[comparar].nome)==1)
                    return comparar;
            }
        }
    }
    return comparado;
}

int golsMax(grupo *VetorGrupos,int grupo1,int grupo2, int sel1, int sel2)
{//verifica a quantidade maxima de gols que uma selecao pode tomar/fazer num jogo especifico
    if (VetorGrupos[grupo1].VetorSelecoes[sel1].maxgolspro>=VetorGrupos[grupo2].VetorSelecoes[sel2].maxgolcontra)
        return VetorGrupos[grupo2].VetorSelecoes[sel2].maxgolcontra;
    else
        return VetorGrupos[grupo1].VetorSelecoes[sel1].maxgolspro;
}

void resultado(grupo *VetorGrupos,int i, int sel1, int sel2, int c)
{//gera o resultado de um jogo da primeira fase
    int valor;
    srand(time(NULL));
    valor = golsMax(VetorGrupos,i,i,sel1,sel2);
    if(valor)
        VetorGrupos[i].Resultados[c][0] = rand()%(valor+1);
    else
        VetorGrupos[i].Resultados[c][0] = 0;
    valor = golsMax(VetorGrupos,i,i,sel2,sel1);
    if(valor)
        VetorGrupos[i].Resultados[c][1] = rand()%(valor+1);
    else
        VetorGrupos[i].Resultados[c][1] = 0;
    VetorGrupos[i].VetorSelecoes[sel1].golspro+=VetorGrupos[i].Resultados[c][0];
    VetorGrupos[i].VetorSelecoes[sel1].golscontra+=VetorGrupos[i].Resultados[c][1];
    VetorGrupos[i].VetorSelecoes[sel2].golspro+=VetorGrupos[i].Resultados[c][1];
    VetorGrupos[i].VetorSelecoes[sel2].golscontra+=VetorGrupos[i].Resultados[c][0];
    if( VetorGrupos[i].Resultados[c][0]>VetorGrupos[i].Resultados[c][1])
        VetorGrupos[i].VetorSelecoes[sel1].vitorias++;
    else if(VetorGrupos[i].Resultados[c][0]==VetorGrupos[i].Resultados[c][1])
    {
        VetorGrupos[i].VetorSelecoes[sel1].empates++;
        VetorGrupos[i].VetorSelecoes[sel2].empates++;
    }
    else
        VetorGrupos[i].VetorSelecoes[sel2].vitorias++;
    atualizaPontos(VetorGrupos,i,sel1);
    atualizaPontos(VetorGrupos,i,sel2);
}

void atualizaPrimeiro(grupo *VetorGrupos,int grupoi)
{//verifica quem sao os dois primeiros colocados do grupo
    int prim,seg,aux;
    prim=maior(VetorGrupos,grupoi,1,2);
    for(int i = 2;i<=3;i++)
    {
        aux = maior(VetorGrupos,grupoi,i,i+1);
        prim = maior(VetorGrupos,grupoi,prim,aux);
    }
    if(prim!=4)
        seg=4;
    else
        seg=3;
    for(int i = 1;i<=3;i++)
    {
        aux = maior(VetorGrupos,grupoi,i,i+1);
        if(prim == aux){
            if(aux == i)
                seg = maior(VetorGrupos,grupoi,seg,i+1);
            else
                seg = maior(VetorGrupos,grupoi,seg,i);
        }
        else
            seg = maior(VetorGrupos,grupoi,seg,aux);
    }
    VetorGrupos[grupoi].vencedoresGrupo.numPrimeiro=prim;
    VetorGrupos[grupoi].vencedoresGrupo.numSegundo=seg;
    strcpy(VetorGrupos[grupoi].vencedoresGrupo.primeiro,VetorGrupos[grupoi].VetorSelecoes[prim].nome);
    strcpy(VetorGrupos[grupoi].vencedoresGrupo.segundo,VetorGrupos[grupoi].VetorSelecoes[seg].nome);
    VetorGrupos[grupoi].VetorSelecoes[prim].maxgolspro++;
    VetorGrupos[grupoi].VetorSelecoes[prim].maxgolcontra--;
}

void addSelecoesOitavas(grupo *VetorGrupos, res2fase *segFase)
{//adiciona selecoes que vao para as oitavas de final na estrutura segFase. foi necessario forca bruta, ja que nao ha logica na definicao dos jogos
    segFase->selecoes2Fase[0][0]=3;
    segFase->selecoes2Fase[0][1]=VetorGrupos[3].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[1][0]=4;
    segFase->selecoes2Fase[1][1]=VetorGrupos[4].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[2][0]=1;
    segFase->selecoes2Fase[2][1]=VetorGrupos[1].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[3][0]=2;
    segFase->selecoes2Fase[3][1]=VetorGrupos[2].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[4][0]=5;
    segFase->selecoes2Fase[4][1]=VetorGrupos[5].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[5][0]=6;
    segFase->selecoes2Fase[5][1]=VetorGrupos[6].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[6][0]=7;
    segFase->selecoes2Fase[6][1]=VetorGrupos[7].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[7][0]=8;
    segFase->selecoes2Fase[7][1]=VetorGrupos[8].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[8][0]=2;
    segFase->selecoes2Fase[8][1]=VetorGrupos[2].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[9][0]=1;
    segFase->selecoes2Fase[9][1]=VetorGrupos[1].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[10][0]=4;
    segFase->selecoes2Fase[10][1]=VetorGrupos[4].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[11][0]=3;
    segFase->selecoes2Fase[11][1]=VetorGrupos[3].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[12][0]=6;
    segFase->selecoes2Fase[12][1]=VetorGrupos[6].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[13][0]=5;
    segFase->selecoes2Fase[13][1]=VetorGrupos[5].vencedoresGrupo.numSegundo;
    segFase->selecoes2Fase[14][0]=8;
    segFase->selecoes2Fase[14][1]=VetorGrupos[8].vencedoresGrupo.numPrimeiro;
    segFase->selecoes2Fase[15][0]=7;
    segFase->selecoes2Fase[15][1]=VetorGrupos[7].vencedoresGrupo.numSegundo;
}

void PrimeiraFase(grupo *VetorGrupos, res2fase *segFase)
{//gera os dados de cada grupo da primeira fase
    for(int i=1;i<=8;i++)
    {
        resultado(VetorGrupos,i,1,2,0);
        resultado(VetorGrupos,i,3,4,1);
        resultado(VetorGrupos,i,1,3,2);
        resultado(VetorGrupos,i,2,4,3);
        resultado(VetorGrupos,i,1,4,4);
        resultado(VetorGrupos,i,2,3,5);
        atualizaPrimeiro(VetorGrupos,i);
    }
    addSelecoesOitavas(VetorGrupos,segFase);
}

void resultado2Fase(grupo *VetorGrupos, res2fase *segFase, int ini, int qtdJogos,int jogofinal)
{//gera o resultado de um jogo na segunda fase e adiciona as selecoes que irao para a proxima fase. a partir da semifinal, todas as selecoes sao classificadas
    for(int i=ini;i <ini+2*qtdJogos;i+=2)
    {
        int valor1,valor2,valido=0;
        int grupo1 = segFase->selecoes2Fase[i][0];
        int selecao1 = segFase->selecoes2Fase[i][1];
        int grupo2 = segFase->selecoes2Fase[i+1][0];
        int selecao2 = segFase->selecoes2Fase[i+1][1];
        valor1 = golsMax(VetorGrupos,grupo1,grupo2,selecao1,selecao2);
        valor2 = golsMax(VetorGrupos,grupo2,grupo1,selecao2,selecao1);
        srand(time(NULL));
        while(!valido)
        {
            if(valor1)
                segFase->placar2fase[i/2][0] = rand()%(valor1+1);
            else
                segFase->placar2fase[i/2][0] = 0;
            if(valor2)
                segFase->placar2fase[i/2][1] = rand()%(valor2+1);
            else
                segFase->placar2fase[i/2][1] = 0;
            if(segFase->placar2fase[i/2][0]!=segFase->placar2fase[i/2][1])
                valido =1;
        }
        if(segFase->placar2fase[i/2][0]>segFase->placar2fase[i/2][1])
        {
            segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2][0]=grupo1;
            segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2][1]=selecao1;
            if(jogofinal)
            {
                segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2+2][0]=grupo2;
                segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2+2][1]=selecao2;
            }
        }
        else
        {
            segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2][0]=grupo2;
            segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2][1]=selecao2;
            if(jogofinal)
            {
                segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2+2][0]=grupo1;
                segFase->selecoes2Fase[(i-ini)/2+ini+qtdJogos*2+2][1]=selecao1;
            }
        }
    }
}

void mostrarJogos2(grupo *VetorGrupos, res2fase *segFase,int ini,int iniPlacar, int qtd)
{//apresenta na tela os resultados de uma fase
    int *selecao;
    selecao = &segFase->selecoes2Fase[ini][0];
    for(int i=0;i<qtd;i++)
        printf("\n\t%-14s %d x %d %14s",
               VetorGrupos[*(selecao+i*4)].VetorSelecoes[*(selecao+i*4+1)].nome,
               segFase->placar2fase[iniPlacar+i][0],
               segFase->placar2fase[iniPlacar+i][1],
               VetorGrupos[*(selecao+i*4+2)].VetorSelecoes[*(selecao+i*4+3)].nome);
    printf("\n\n\tAperte em qualquer tecla para continuar: ");
    getch();
}

void MostrarCampeoes(grupo *VetorGrupos,res2fase *segFase)
{//apresenta na tela os tres primeiros lugares da copa
    int *p;
    p = &segFase->selecoes2Fase[32][0];
    system("cls");
    printf("\n\t    RESULTADO FINAL\n");
    printf("\n\tPRIMEIRO LUGAR: %s\n",VetorGrupos[*p].VetorSelecoes[*(p+1)].nome);
    printf("\n\tSEGUNDO LUGAR:  %s\n",VetorGrupos[*(p+4)].VetorSelecoes[*(p+5)].nome);
    printf("\n\tTERCEIRO LUGAR: %s\n",VetorGrupos[*(p+2)].VetorSelecoes[*(p+3)].nome);
}

void SegundaFase(grupo *VetorGrupos, res2fase *segFase)
{//gera o resultado da segunda fase e apresenta na tela
    resultado2Fase(VetorGrupos,segFase,0,8,0);//oitavas
    resultado2Fase(VetorGrupos,segFase,16,4,0);//quartas
    resultado2Fase(VetorGrupos,segFase,24,2,1);//semifinais
    resultado2Fase(VetorGrupos,segFase,28,2,1);//finais
    system("cls");
    printf("\n\t     RESULTADO OITAVAS DE FINAL\n");
    mostrarJogos2(VetorGrupos,segFase,0,0,8);
    printf("\n\n\t     RESULTADO QUARTAS DE FINAL\n");
    mostrarJogos2(VetorGrupos,segFase,16,8,4);
    printf("\n\n\t\tRESULTADO SEMIFINAL\n");
    mostrarJogos2(VetorGrupos,segFase,24,12,2);
    printf("\n\n\t     RESULTADO DISPUTA 3 LUGAR\n");
    mostrarJogos2(VetorGrupos,segFase,30,15,1);
    printf("\n\n\t\t  RESULTADO FINAL\n");
    mostrarJogos2(VetorGrupos,segFase,28,14,1);
    MostrarCampeoes(VetorGrupos,segFase);
}

void EscreverResultados(grupo *VetorGrupos, FILE *FileOut,int jogo,int grupo1,int sel1,int sel2)
{//salva num txt os jogos e seus resultados da primeira fase de um grupo
    fprintf(FileOut,"\n\t%-14s",VetorGrupos[grupo1].VetorSelecoes[sel1].nome);
    fprintf(FileOut,"%2dx%-2d",
                    VetorGrupos[grupo1].Resultados[jogo][0],
                    VetorGrupos[grupo1].Resultados[jogo][1]);
    fprintf(FileOut,"%14s",VetorGrupos[grupo1].VetorSelecoes[sel2].nome);
}

void EscreverGrupos(grupo *VetorGrupos, FILE *FileOut)
{//salva num txt a tabela com os resultados da primeira fase
    int i,j;
    fprintf(FileOut,"\n\t\t\tCOPA DO MUNDO DE 2018");
    fprintf(FileOut,"\n--------------------------------------------------------------------------");
    for(i =1;i<=8;i++)
    {
        fprintf(FileOut,"\n\n\t\t\t\tGRUPO %c \nResultado Jogos ",VetorGrupos[i].nome);
        EscreverResultados(VetorGrupos,FileOut,0,i,1,2);
        EscreverResultados(VetorGrupos,FileOut,1,i,3,4);
        EscreverResultados(VetorGrupos,FileOut,2,i,1,3);
        EscreverResultados(VetorGrupos,FileOut,3,i,2,4);
        EscreverResultados(VetorGrupos,FileOut,4,i,1,4);
        EscreverResultados(VetorGrupos,FileOut,5,i,2,3);
        fprintf(FileOut,"\n\n%-20s|%8s|%8s|%8s|%8s|%8s|%8s",
                "Selecao","Pontos","Vitorias","Empates","GolsPro","GolsCon","SaldGols");
        fprintf(FileOut,
                "\n--------------------|--------|--------|--------|--------|--------|--------");
        for(j=1;j<=4;j++)
            fprintf(FileOut,"\n%-20s|%8d|%8d|%8d|%8d|%8d|%8d",
                    VetorGrupos[i].VetorSelecoes[j].nome,
                    VetorGrupos[i].VetorSelecoes[j].pontos,
                    VetorGrupos[i].VetorSelecoes[j].vitorias,
                    VetorGrupos[i].VetorSelecoes[j].empates,
                    VetorGrupos[i].VetorSelecoes[j].golspro,
                    VetorGrupos[i].VetorSelecoes[j].golscontra,
                    VetorGrupos[i].VetorSelecoes[j].saldogols);
        fprintf(FileOut,"\n\n\tPrimeiro colocado:  %s \n\tSegundo colocado:   %s ",
                VetorGrupos[i].vencedoresGrupo.primeiro,
                VetorGrupos[i].vencedoresGrupo.segundo);
        fprintf(FileOut,"\n\n--------------------------------------------------------------------------");

    }
}

int main()
{
    char c ='s';
    while(c == 's')
    {
        //Variaveis e Ponteiros
        grupo VetorGrupos[9];
        res2fase segFase;
        FILE *FileIn,*FileOut,*Estatisticas;
        //Processamento das ingformacoes sobre a Copa
        printf("\n\t\tSIMULADOR COPA DO MUNDO 2018\n");
        do
        {//leitura do nome das selecoes
            printf("\n\tClique em qualquer tecla para realizar a leitura dos nomes das selecoes: ");
            getch();
            FileIn = fopen("ListaSelecoes.txt","r");
            if(FileIn!=NULL)
            {
                printf("\n\tLeitura realizada com sucesso!");
                printf("\n\tArquivo ListaSelecoes.txt: Contem o nome das 32 selecoes da Copa");
                getch();
            }
            else
            {
                printf("\n\tArquivo nao encontrado, coloque ele na mesma pasta do seu executavel!");
                getch();
            }
        }while(FileIn==NULL);
        do
        {//leitura das estatisticas das selecoes
            printf("\n\n\tClique em qualquer tecla para realizar a leitura das estatisticas das selecoes: ");
            getch();
            Estatisticas = fopen("EstatisticaSelecoes.txt","r");
            if(Estatisticas!=NULL)
            {
                printf("\n\tLeitura realizada com sucesso!");
                printf("\n\tArquivo EstatisticaSelecoes.txt: Estatistica das Selecoes da Copa");
                getch();
            }
            else
            {
                printf("\n\tArquivo nao encontrado, coloque ele na mesma pasta do seu executavel!");
                getch();
            }
        }while(Estatisticas==NULL);
        LerSelecoes(VetorGrupos,FileIn,Estatisticas);
        FileOut = fopen("RelatorioCopa2018.txt","w");
        system("cls");
        printf("\n\t\tSIMULADOR COPA DO MUNDO 2018\n");
        PrimeiraFase(VetorGrupos,&segFase);
        EscreverGrupos(VetorGrupos,FileOut);
        fclose(FileIn);
        fclose(Estatisticas);
        fclose(FileOut);
        printf("\n\tPRIMEIRA FASE: Clique em qualquer tecla para apresentar o relatorio da primeira fase: ");
        getch();
        system("RelatorioCopa2018.txt");
        printf("\n\n\tFeche o arquivo txt aberto e clique em qualquer tecla para apresentar a proxima fase: ");
        getch();
        SegundaFase(VetorGrupos,&segFase);
        printf("\n\n\tDeseja realizar nova simulacao? Digite 's' para sim ou qualquer tecla para sair: ");
        c = getche();
        c = tolower(c);
        system("cls");
    }
    return 0;
}


