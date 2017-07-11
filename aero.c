#include <stdio.h>
#include <stdlib.h>
#include "aero.h"
#include <time.h>
aeroporto* cria()
{
    int i = 0;
    aeroporto *aero=(aeroporto*)malloc(sizeof(aeroporto));
    aero->pis = (pis*) malloc(3*sizeof(pis));
    aero->faltaCombust=0;
    aero->aviaoCaiu=0;
//Inicia pista 1
    aero->pis[0].pou = (pousa*)malloc(2*sizeof(pousa));
    aero->pis[0].dec = (decola*) malloc (sizeof(decola));
    aero->pis[0].ocupada=0;
    aero->pis[0].dec->ini=NULL;
    aero->pis[0].dec->fim=NULL;
    aero->pis[0].dec->cont=0;

//Inicia pista 2
    aero->pis[1].pou = (pousa*)malloc(2*sizeof(pousa));
    aero->pis[1].dec = (decola*) malloc (sizeof(decola));
    aero->pis[1].ocupada=0;
    aero->pis[1].dec->ini=NULL;
    aero->pis[1].dec->fim=NULL;
    aero->pis[1].dec->cont=0;

//Inicia pista 3
    aero->pis[2].pou = (pousa*)malloc(sizeof(pousa));
    aero->pis[2].dec = (decola*)malloc(sizeof(decola));
    aero->pis[2].ocupada=0;
    aero->pis[2].pou->cont=0;
    aero->pis[2].dec->ini=NULL;
    aero->pis[2].dec->fim=NULL;
    aero->pis[2].dec->cont=0;

    for(; i<2; i++)
    {
        aero->pis[0].pou[i].ini=NULL;
        aero->pis[0].pou[i].cont=0;
        aero->pis[0].pou[i].fim=NULL;
        aero->pis[1].pou[i].ini=NULL;
        aero->pis[1].pou[i].cont=0;
        aero->pis[1].pou[i].fim=NULL;
    }
    return aero;
}

int randomizaId()
{
    int idp;

    do
    {
        idp/*impares*/ = rand() % 1000 + 1986;

    }
    while(idp%2==0);

    return idp;

}

void inPou(aeroporto *aero)
{
    int i;
    int j;
    aviao *av = (aviao*)malloc(sizeof(aviao));
    int combustivel/*unidade de tempo*/= 2+(rand() % 20);
    av->id = randomizaId();
    av->combustivel = combustivel;
    int k,t;
    k=1+(rand()%294);
    aero->destino=fopen("dest.txt","r");
    for(t=0;t<k;t++)
    {
        fscanf(aero->destino," %s\n",av->local);
    }
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            if(aero->pis[i].pou[j].ini==NULL)
            {
                aero->pis[i].pou[j].ini=av;
                aero->pis[i].pou[j].cont += 1;
                av->prox=aero->pis[i].pou[j].fim;
                aero->pis[i].pou[j].fim=av;
                return NULL;
            }
        }
    }
    if(aero->pis[0].pou[0].cont<=aero->pis[0].pou[1].cont)
    {

        if(aero->pis[0].pou[0].cont<=aero->pis[1].pou[0].cont)
        {

            if(aero->pis[1].pou[0].cont<=aero->pis[1].pou[1].cont)
            {
                av->prox=aero->pis[0].pou[0].fim->prox;
                aero->pis[0].pou[0].fim->prox=av;
                aero->pis[0].pou[0].fim=av;
                aero->pis[0].pou[0].cont++;
                return NULL;
            }
            else
            {
                av->prox=aero->pis[1].pou[1].fim->prox;
                aero->pis[1].pou[1].fim->prox=av;
                aero->pis[1].pou[1].fim=av;
                aero->pis[1].pou[1].cont++;
                return NULL;
            }
        }
        else
        {
            av->prox=aero->pis[1].pou[0].fim->prox;
            aero->pis[1].pou[0].fim->prox=av;
            aero->pis[1].pou[0].fim=av;
            aero->pis[1].pou[0].cont++;
            return NULL;
        }
    }
    else
    {
        av->prox=aero->pis[0].pou[1].fim->prox;
        aero->pis[0].pou[1].fim->prox=av;
        aero->pis[0].pou[1].fim=av;
        aero->pis[0].pou[1].cont++;
        return NULL;
    }
    fclose("dest.txt");
}

void perdeCombustivel(aeroporto *aero)
{
    aviao *av;
    int i;
    int j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            av = aero->pis[i].pou[j].ini;
            while(av!=NULL)
            {
                av->combustivel--;
                av = av->prox;
            }
        }
    }
    return NULL;
}

int aviaoPousa(aeroporto *aero)
{
    aviao *av;
    int id;
    int i;
    int j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            av = aero->pis[i].pou[j].ini;
            while(av!=NULL)
            {
                if(av->combustivel==0)
                {
                    aero->pis[i].pou[j].ini=aero->pis[i].pou[j].ini->prox;
                    if(aero->pis[2].ocupada==0)
                    {
                        printf("Pouso de emergencia na pista 3");
                        aero->pis[2].ocupada=1;
                    }
                    else if(aero->pis[0].ocupada==0)
                    {
                        printf("Pouso de emergencia na pista 1");
                        aero->pis[0].ocupada=1;
                    }
                    else if(aero->pis[1].ocupada==0)
                    {
                        printf("Pouso de emergencia na pista 2");
                        aero->pis[1].ocupada=1;
                    }
                    else
                        return NULL;
                    if(aero->pis[i].pou[j].ini == NULL)
                        aero->pis[i].pou[j].fim = NULL;
                    aero->pis[i].pou[j].cont--;
                    aero->faltaCombust++;
                    id = av->id;
                    free(av);
                    return id;
                }
                av = av->prox;
            }
        }
    }
    if(aero->pis[0].pou[0].cont>=aero->pis[0].pou[1].cont)
        j=0;
    else
        j=1;
    if(aero->pis[0].pou[j].ini!=NULL)
    {
        av = aero->pis[0].pou[j].ini;
        if(aero->pis[0].ocupada==0)
        {
            aero->pis[0].pou[j].ini=aero->pis[0].pou[j].ini->prox;
            if(aero->pis[0].pou[j].ini == NULL)
                aero->pis[0].pou[j].fim = NULL;
            aero->pis[0].ocupada=1;
            aero->pis[0].pou[j].cont--;
            id = av->id;
            free(av);
            return id;
        }
    }

    if(aero->pis[1].pou[0].cont>=aero->pis[1].pou[1].cont)
        j=0;
    else
        j=1;
    if(aero->pis[1].pou[j].ini!=NULL)
    {
        av = aero->pis[1].pou[j].ini;
        if(aero->pis[1].ocupada==0)
        {
            aero->pis[1].pou[j].ini=aero->pis[1].pou[j].ini->prox;
            if(aero->pis[1].pou[j].ini == NULL)
                aero->pis[1].pou[j].fim = NULL;
            aero->pis[1].ocupada=1;
            aero->pis[1].pou[j].cont--;
            id = av->id;
            free(av);
            return id;
        }
    }
}

void inDec(aeroporto *aero)
{
    int i;
    aviao *av = (aviao*) malloc( sizeof(aviao));
    av->id = randomizaId();
    int k,t;
    k=1+(rand()%294);
    aero->destino=fopen("dest.txt","r");
    for(t=0;t<k;t++)
    {
        fscanf(aero->destino," %s\n",av->local);
    }
    for(i=0; i<3; i++)
    {
        if(aero->pis[i].dec->ini==NULL)
        {
            av->prox = aero->pis[i].dec->fim;
            aero->pis[i].dec->ini = av;
            aero->pis[i].dec->fim = av;
            aero->pis[i].dec->cont++;
            return 0;
        }
    }
    if(aero->pis[0].dec->cont<=aero->pis[1].dec->cont)
    {
        if(aero->pis[0].dec->cont<=aero->pis[2].dec->cont)
        {
            av->prox=NULL;
            aero->pis[0].dec->fim->prox=av;
            aero->pis[0].dec->fim=av;
            aero->pis[0].dec->cont++;
            return 0;
        }
        else
        {
            av->prox=NULL;
            aero->pis[2].dec->fim->prox=av;
            aero->pis[2].dec->fim=av;
            aero->pis[2].dec->cont++;
            return 0;
        }
    }
    else
    {
        av->prox=NULL;
        aero->pis[1].dec->fim->prox=av;
        aero->pis[1].dec->fim=av;
        aero->pis[1].dec->cont++;
        return 0;
    }
    fclose("dest.txt");
}

int aviaoDecola(aeroporto *aero,int i)
{
    aviao *av;
    int id = 0;
    av = aero->pis[i].dec->ini;
    if(aero->pis[i].dec->ini!=NULL)
    {
        aero->pis[i].ocupada = 1;
        aero->pis[i].dec->cont--;
        aero->pis[i].dec->ini = aero->pis[i].dec->ini->prox;
        if(aero->pis[i].dec->ini==NULL)
        {
            aero->pis[i].dec->fim = NULL;
        }
        id = av->id;
        free(av);
    }
    return id;
}

int semCombustivel(aeroporto *aero)
{
    int i,j;
    aviao *av;
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            av = aero->pis[i].pou[j].ini;
            while(av != NULL)
            {
                if(av->combustivel == 0)
                {
                    return 1;
                }
                av = av->prox;
            }
        }
    }
    return 0;
}

int caiu(aeroporto *aero)
{
    aviao *av;
    int i;
    int id;
    int j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            av = aero->pis[i].pou[j].ini;
            if(aero->pis[i].pou[j].ini != NULL)
            {
                while(av->combustivel<0)
                {
                    aero->aviaoCaiu++;
                    aero->pis[i].pou[j].ini = aero->pis[i].pou[j].ini->prox;
                    id = av->id;
                    free(av);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void controlaAcoes(aeroporto *aero)
{
    int id;
    while(semCombustivel(aero)== 1)
    {
        id=aviaoPousa(aero);
        if(id>10)
        {
            printf("\nAviao id:%d Pousou\n",id);
        }
    }
    //Pista 1:
    if(aero->pis[0].ocupada!=1)
    {
        if(aero->pis[0].pou[0].cont>=aero->pis[0].pou[1].cont)
        {
            if(aero->pis[0].pou[0].cont>=aero->pis[0].dec->cont)
            {
                id = aviaoPousa(aero);
                if(id>10)
                {
                    printf("\nAviao id:%d Pousou na pista 1\n",id);
                }
            }
            else
            {
                id = aviaoDecola(aero,0);
                if(id>10)
                {
                    printf("\nAviao id:%d Decolou na pista 1\n",id);
                }
            }
        }
        else
        {
            id = aviaoPousa(aero);
            if(id>10)
            {
                printf("\nAviao id:%d Pousou na pista 1\n",id);
            }
        }
    }
    //Pista 2
    if(aero->pis[1].ocupada!=1)
    {
        if(aero->pis[1].pou[0].cont>=aero->pis[1].pou[1].cont)
        {
            if(aero->pis[1].pou[0].cont>=aero->pis[1].dec->cont)
            {
                id = aviaoPousa(aero);
                if(id>10)
                {
                    printf("\nAviao id:%d Pousou na pista 2\n",id);
                }
            }
            else
            {
                id = aviaoDecola(aero,1);
                if(id>10)
                {
                    printf("\nAviao id:%d Decolou na pista 2\n",id);
                }
            }
        }
        else
        {
            id = aviaoPousa(aero);
            if(id>10)
            {
                printf("\nAviao id:%d Pousou na pista 2\n",id);
            }
        }
    }
    if(aero->pis[2].ocupada!=1)
    {
        //Pista 3
        id=aviaoDecola(aero,2);
        if(id>10)
        {
            printf("\nAviao id:%d Decolou na pista 3\n",id);
        }
    }
}
