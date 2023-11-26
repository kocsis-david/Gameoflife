#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"

int **beker(int *m,int *s){
    int magas,szeles;
    printf("kerem a magassagot, szelesseget:");
    scanf("%d %d",&magas,&szeles);

    int **eletter=(int **) malloc(magas * sizeof(int*));
    if(eletter==NULL)return NULL;
    for(int i=0;magas>i;i++)eletter[i]=(int *) malloc(szeles*sizeof(int));

    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            eletter[i][j]=0;
        }

    }

    printf("keres a magassag szelesseg koordinatakat:\n");
    int x,y;
    scanf("%d %d",  &y,&x);
    while(szeles>=x&&magas>=y&&y>0&&x>0){
        eletter[y-1][x-1]=1;
        scanf("%d %d",&y,&x);
    }


    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            printf("%d ",eletter[i][j]);
        }
        printf("\n");
    }
    *m=magas;
    *s=szeles;
    return eletter;
}
int **beolvas(int *m,int *s){
    FILE *be;
    be= fopen("mentes.txt","r");
    int magas,szeles;
    fscanf(be,"%d %d",&magas,&szeles);
    int **eletter=(int **) malloc(magas * sizeof(int*));
    for(int i=0;magas>i;i++)eletter[i]=(int *) malloc(szeles*sizeof(int));
    if(eletter==NULL)return NULL;
    for (int i = 0; i < magas; ++i)
        for (int j = 0; j < szeles; ++j)eletter[i][j]=0;
    int y,x;
    while(fscanf(be,"%d %d",&y,&x)!=EOF&&magas>y&&szeles>x)
        eletter[y][x]=1;

    fclose(be);
    for(int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            printf("%d ",eletter[i][j]);
        }
        printf("\n");
    }
    *m=magas;
    *s=szeles;
    return eletter;
}

int szomszedok(int **tmb, int x,int y,int magas, int szeles){
    int szomszed=0;
    magas--;
    szeles--;
    if(x>0)if(tmb[y][x-1])szomszed++;
    if(y>0)if(tmb[y-1][x])szomszed++;
    if(y>0&&x>0)if(tmb[y-1][x-1])szomszed++;
    if(magas>y)if(tmb[y+1][x])szomszed++;
    if(szeles>x)if(tmb[y][x+1])szomszed++;
    if(szeles>x&&magas>y)if(tmb[y+1][x+1])szomszed++;
    if(magas>y&&x>0)if(tmb[y+1][x-1])szomszed++;
    if(szeles>x&&y>0)if(tmb[y-1][x+1])szomszed++;
    return szomszed;
}

void leptet(int ***eletter,int magas, int szeles){
    int ** temp = *eletter;
    int **uj=(int **) malloc(magas * sizeof(int*));
    for(int i=0;magas>i;i++)uj[i]=(int *) malloc(szeles*sizeof(int));
    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            int szomszed= szomszedok(temp,j,i,magas,szeles);
            if(szomszed==3)uj[i][j]= 1;
            else if(temp[i][j]&&szomszed==2)uj[i][j]=1;
            else uj[i][j]=0;
        }
    }
    for(int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            printf("%d ",uj[i][j]);
        }
        printf("\n");
    }

    *eletter=uj;
}
void mentes(int *tmb[],int magas,int szeles){

    FILE *ki;
    ki= fopen("mentes.txt","w");
    fprintf(ki,"%d %d\n",magas,szeles);
    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            if(tmb[i][j])fprintf(ki,"%d %d\n",i,j);
        }
    }
    fclose(ki);
}
void freel(int **eletter,int magas){
    for (int i = 0; i < magas; ++i) {
        free(eletter[i]);
    }
    free(eletter);
}
void kezd(int ***eletter, int *magas,int *szeles){
    printf("Adja meg hogy kezbol vagy mentesbol szeretne kezdeni:\n 1:Sajat ertekek\n2:Menestbol\n");
    int kezd=0;

    scanf("%d",&kezd);
    switch (kezd) {
        case 1:*eletter=beker(magas,szeles);
            break;
        case 2:*eletter=beolvas(magas,szeles);
            break;
        default:*eletter=beker(magas,szeles);
            break;
    }
}
void futas(int **eletter,int magas, int szeles){
    printf("Lehetosegek:\n1:Leptet \n2: Mentes\n3: Ujrakezd\n4: Kilep\n");
    int valasz;
    scanf("%d",&valasz);
    switch (valasz) {
        case 1:
            leptet(&eletter,magas,szeles);
            futas(eletter,magas,szeles);
            break;
        case 2:
            mentes(eletter,magas,szeles);
            futas(eletter,magas,szeles);
            break;
        case 3:
            kezd(&eletter,&magas,&szeles);
            futas(eletter,magas,szeles);
            break;
        case 4:
            printf("Ha szeretne menteni elotte nyomja meg az m gombot es egy entert!");
            char ment;
            scanf("%c",&ment);
            if(ment=='m')mentes(eletter,magas,szeles);
            freel(eletter,magas);
            return;
    }

}
int main(){
    int **eletter=NULL;
    int magas,szeles;
    kezd(&eletter,&magas,&szeles);
    printf("%d %d\n",magas,szeles);

    futas(eletter,magas,szeles);






}
