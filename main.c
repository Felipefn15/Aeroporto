#include <stdio.h>
#include <stdlib.h>
#include "aero.h"
#include <time.h>
#include <locale.h>
void menu(){
    printf ("               ###########################################################\n ");
    printf ("               ##                                                       ##\n ");
    printf ("               ##          AUTHOR:FELIPE FRANÇA NOGUEIRA                ##\n ");
    printf ("               ##                   2017                                ##\n ");
    printf ("               ##                                                       ##\n ");
    printf ("               ###########################################################\n\n\n\n ");

}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    menu();
    aeroporto *aero;
    aero = cria();
    aviao *av;
    int i=0;
    int j=0;
    int chegaPou,chegaDec;
    int tempo=0;
    while(tempo<21)
    {
        system("cls");
        int c=1;
        printf("|--------|\n");
        printf("|Tempo %d |\n",tempo);
        printf("|--------|\n");
        chegaPou=rand()%4;
        chegaDec=rand()%4;
        if(chegaPou==1)
        {
            inPou(aero);
        }
        if(chegaPou==2)
        {
            inPou(aero);
            inPou(aero);
        }
        if(chegaPou==3)
        {
            inPou(aero);
            inPou(aero);
            inPou(aero);
        }
        if(chegaDec==1)
        {
            inDec(aero);
        }
        if(chegaDec==2)
        {
            inDec(aero);
            inDec(aero);
        }
        if(chegaDec==3)
        {
            inDec(aero);
            inDec(aero);
            inDec(aero);
        }
        printf("\nPouso:\n");
        for(i=0; i<2; i++)
        {
            printf("\nPista:%d\n",i+1);
            for(j=0; j<2; j++)
            {
                printf("\n  Pratileira pouso:%d\n\n",j);
                av=aero->pis[i].pou[j].ini;
                if(av==NULL)
                {
                    printf("        !!Vazia!!\n");
                }
                while(av!=NULL)
                {
                    printf("        -Id:%d\n        -Combustivel:%d\n        -Origem:%s\n",av->id,av->combustivel,av->local);
                    av=av->prox;
                }
            }
        }
        printf("\nDecolagem:\n");
        for(i=0; i<3; i++)
        {
            printf("\nPista:%d\n",i+1);
            av=aero->pis[i].dec->ini;
            while(av!=NULL)
            {
                printf("\n  Pratileira decolagem:\n");
                printf("        -Id:%d\n        -Destino:%s\n",av->id,av->local);
                av = av->prox;
            }
        }
        printf("\n\n");
        //Controla decolagens e pousos
        controlaAcoes(aero);
        //Passa uma unidade de tempo
        tempo++;
        //Desocupa pistas
        aero->pis[0].ocupada=0;
        aero->pis[1].ocupada=0;
        aero->pis[2].ocupada=0;
        //Retira uma unidade de combustivel dos aviões que estão na fila de pouso
        perdeCombustivel(aero);

        //Testa todos os aviões para ver se algum deles está sem combustivel e não conseguiu pousar
        while(c)
        {
            c = caiu(aero);
        }

        printf("\nIncidentes:\nQueda de Avioes: %d\nPouso de emergencia: %d\n",aero->aviaoCaiu,aero->faltaCombust);
        system("pause");
        system("cls");
    }
    printf("                    !END!\n                    Desenvolvedor:Felipe França Nogueira\n                    Data:01/07/2017\n");
    return 0;
}
