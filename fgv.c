#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int **beker(void){
    int magas,szeles;
    printf("kerem a magassagot, szelesseget:");
    scanf("%d %d",&magas,&szeles);
    printf("\n%d %d\n", magas, szeles);
    int **mat=(int **) malloc(magas * sizeof(int*));
    for(int i=0;magas>i;i++)mat[i]=(int *) malloc(szeles*sizeof(int));
    if(mat==NULL)return NULL;
    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            mat[i][j]=0;
        }

    }

    printf("keres a magassag szelesseg koordinatakat:\n");
    int x,y;
    scanf("%d %d",  &y,&x);
    while(szeles>=x&&magas>=y&&y>0&&x>0){
        mat[y-1][x-1]=1;
        scanf("%d %d",&y,&x);
    }


    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
return mat;
}
int **beolvas(void){
    FILE *be;
    be= fopen("mentes.txt","r");
    int magas,szeles;
    fscanf(be,"%d %d",&magas,&szeles);
    int **mat=(int **) malloc(magas * sizeof(int*));
    for(int i=0;magas>i;i++)mat[i]=(int *) malloc(szeles*sizeof(int));
    if(mat==NULL)return NULL;
    for (int i = 0; i < magas; ++i)
        for (int j = 0; j < szeles; ++j)mat[i][j]=0;
    int y,x;
    while(fscanf(be,"%d %d",&y,&x)!=EOF)
        mat[y][x]==1;

    fclose(be);
    return mat;
}
int szomszedok(int ***tmb, int x,int y){
    int szomszed=0;
    int hossz=sizeof(tmb[y]);
    int magas=sizeof(tmb);
    if(x>0)if(tmb[y][x-1]==1)szomszed++;
    if(y>0)if(tmb[y-1][x]==1)szomszed++;
    if(y>0&&x>0)if(tmb[y-1][x-1]==1)szomszed++;
    if(magas>y)if(tmb[y+1][x]==1)szomszed++;
    if(hossz>x)if(tmb[y][x+1]==1)szomszed++;
    if(hossz>x&&magas>y)if(tmb[y+1][x+1])szomszed++;
    if(magas>y&&x>0)if(tmb[y+1][x-1]==1)szomszed++;
    if(hossz>x&&y>0)if(tmb[y-1][x+1]==1)szomszed++;
    return szomszed;
}

void leptet(int ***tmb){
    int magas=sizeof(tmb);
    int szeles=sizeof(tmb[0]);
    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < szeles; ++j) {
            int szomszed= szomszedok(tmb,j,i);
            if(szomszed==3)tmb[i][j]=1;
            else if(tmb[i][j]==1&&szomszed==2)tmb[i][j]=1;
            else tmb[i][j]=0;
        }
    }
}
void mentes(int ***tmb){
    int hossz=sizeof(tmb[0]);
    int magas=sizeof(tmb);
    FILE *ki;
    ki= fopen("mentes.txt","w");
    fprintf(ki,"%d %d\n",magas,hossz);
    for (int i = 0; i < magas; ++i) {
        for (int j = 0; j < hossz; ++j) {
            if(tmb[i][j]==1)fprintf(ki,"%d %d\n",i,j);
        }
    }
    fclose(ki);
}


