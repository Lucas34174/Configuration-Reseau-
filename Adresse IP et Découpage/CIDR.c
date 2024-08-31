#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_deci(int  decima[4][8]);
void traitement();
void sub_network(int coupage,int mask,int adress1[4]);
void list(int reseau[4][8],int mask[4][8],int broadcast[4][8],int coupage,int max);

int main()
{       
    traitement();
    return (0);
}       

void traitement()
{       
    int adress[4],adress1[4],mask,reseau[4][8],broadcast[4][8],i,j,host=0,masque[4][8],coupage;
    retry:
    printf("\nEntrer l'adresse IP (X.X.X.X/netmask):");
    if(scanf("%d.%d.%d.%d/%d",&adress[0],&adress[1],&adress[2],&adress[3],&mask)!=5) 
        printf("..Non Valid\n");
    if(coupage<0) 
        coupage=0;
    for(j=0;j<4;j++)
    {   
        if(adress[j]<0||adress[j]>255||mask<=0||mask>=32||adress[0]>255)
        {
            printf("..Non Valid!!");
            goto retry;
        }
        for(i=0;i<=7;i++)  
        {   
            masque[j][i]=1;
            if(host>=mask)
                masque[j][i]=0;
            host++;
            reseau[j][7-i]=adress[j]%2;
            broadcast[j][7-i]=adress[j]%2;
            if(i==0)
                adress1[j]=adress[j];
            adress[j]/=2;
        };
    }   
    for(i=0;i<4;i++)
    {   
        for(j=0;j<8;j++)
        {
            reseau[i][j]=reseau[i][j] & masque[i][j];
            broadcast[i][j]=broadcast[i][j] || 1-masque[i][j];
        }
    }
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
    printf("Adresse IP\t\t:   %03d.%03d.%03d.%03d\n",adress[0],adress[1],adress[2],adress[3]);   
    printf("Masque sous reseau\t:   ");
    print_deci(masque);
    printf("Adresse Réseau\t\t:   ");
    print_deci(reseau);
    printf("Adresse Broadcast\t:   ");
    print_deci(broadcast);
    printf("IP utilisable\t\t:   %d\n\n",(int)pow(2,(int)(32-mask))-2);
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
    printf("Entrer le nombre découpage:");
    ge:
    scanf("%d",&coupage);
    if(coupage>32-mask||coupage<0)
    {
        printf("Coupage invalid,Recommence:");
        goto ge;
    }
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
    sub_network(coupage,mask,adress1);
    list(reseau,masque,broadcast,coupage,mask);
}                  

void list(int reseau[4][8],int mask[4][8],int broadcast[4][8],int coupage,int cidr)
{       
    int networt[4],end[4],wild[4],add[4];
    int i,j,m=0,mi=0,k=0;
    printf("Nouveau masque\t:   /%d",coupage+cidr);
    for(i=0;i<4;i++)
    {       
        networt[i]=0;
        end[i]=0;
        for(j=0;j<8;j++)
        {
            networt[i]+=reseau[i][j]*pow(2,7-j);
            end[i]+=broadcast[i][j]*pow(2,7-j);
        }   
        wild[i]=end[i]-networt[i];  
        if(m==1&&mi==0)
            add[i]=pow(2,8);
        else
            add[i]=1;
        if((cidr+coupage)>8*i && (cidr+coupage)<=8*(i+1))
        {   
            mi=1;
            add[i]=pow(2,cidr+coupage-8*i);
        }   
        if(cidr>8*i && cidr<=8*(i+1))
        {   
            m=1;
            add[i]=pow(2,8*(i+1)-(cidr));
            if((cidr+coupage)>8*i && (cidr+coupage)<=8*(i+1))
                add[i]=pow(2,coupage);
        }   
    }     
    printf("\n\n+---------------------------------------------+\n");
    printf(    "| N° | Adresse Reseau    | Adresse Broacast   |\n");
    printf("+---------------------------------------------+\n");
    for(i=0;i<add[0];i++)
    {               
        for(j=0;j<add[1];j++)
        {           
            for(m=0;m<add[2];m++)
            {       
                for(mi=0;mi<add[3];mi++)
                {   
                    k++;
                    printf("|%03d | %03d.%03d.%03d.%03d  ==>  %03d.%03d.%03d.%03d  | \n",k,\
                    networt[0]+i*(wild[0]+1)/add[0],networt[1]+j*(wild[1]+1)/add[1],networt[2]+m*(wild[2]+1)/add[2],networt[3]+mi*(wild[3]+1)/add[3]\
                    ,end[0]-(add[0]-1-i)*(wild[0]+1)/add[0],end[1]-((add[1]-1-j)*(wild[1]+1)/add[1]),end[2]-(add[2]-1-m)*(wild[2]+1)/add[2],end[3]-(add[3]-1-mi)*(wild[3]+1)/add[3]\
                    );                    
                }
            }
        }
    }
    printf("+---------------------------------------------+\n");
}       

void sub_network(int coupage,int mask,int adress1[4])
{       
    printf("Sous reseau\t:   %d  \n",(int)pow(2,coupage));
    printf("IP utilisable\t:   %d * %d  =  %d\n",(int)((int)pow(2,32-mask)-(int)pow(2,coupage)*2)/(int)pow(2,coupage),(int)pow(2,coupage),(int)pow(2,coupage)*(int)((int)pow(2,32-mask)-(int)pow(2,coupage)*2)/(int)pow(2,coupage));
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