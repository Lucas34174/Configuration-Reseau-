#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_deci(int  decima[4][8]);
void traitement();

int main()
{   
    traitement();
    return (0);
}   

void traitement()
{   
    int adress[4],mask[4],reseau[4][8],broadcast[4][8],i,j,host=0;
    retry:
    printf("Entrer le IP:");
    if(scanf("%d.%d.%d.%d",&adress[0],&adress[1],&adress[2],&adress[3])!=4) 
        printf("Non Valid\n");
    printf("Entrer le masque Reseau:");
    if(scanf("%d.%d.%d.%d",&mask[0],&mask[1],&mask[2],&mask[3])!=4)
        printf("Non Valid\n");
    for(i=0;i<4;i++)
    {
        if(adress[i]<0||adress[i]>255||mask[i]<0||mask[i]>255)
        {
            printf("Non Valid");
            goto retry;
        }
    }
    printf("\n");
    for(j=0;j<4;j++)
    {   
        i=0;
        while(i<=7)  
        {   
            reseau[j][7-i]=adress[j]%2 & mask[j]%2;
            broadcast[j][7-i]=adress[j]%2 || 1-(mask[j]%2);    
            if( mask[j]%2 ==0)
                host++;
            i++;
            adress[j]/=2;
            mask[j]/=2;
        };
    }   
    printf("Adresse Réseau:\t");
    print_deci(reseau);
    printf("Broadcast:\t");
    print_deci(broadcast);
    printf("Nombre de machine(%d): %d\n\n",host,(int)pow(2,host)-2);
}                  
void print_deci(int decima[4][8])
{
    int deci=0;
    for(int i=0;i<4;i++)
    {       
        deci=0;
        for(int j=0;j<8;j++)
            deci+=decima[i][j]*pow(2,7-j);
        printf("%d.",deci);
    }
    printf("\n");
}