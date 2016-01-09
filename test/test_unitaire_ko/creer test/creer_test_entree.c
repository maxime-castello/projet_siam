#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define N 6
#define F 12

int main ()
{
    int i=0;
    for(i=N;i<F;i++)
    {
	char filename[1024];
	sprintf(filename,"test_unitaire_ko_0%d_sortie.txt",i);
	printf("%s\n",filename);
	FILE *fid=NULL; //struct contenant un descripteur de fichier
	fid=fopen(filename,"w"); //ouverture du fichier “filename” en mode ecriture
	if(fid==NULL)
	{
	printf("Erreur ouverture du fichier %s\n",filename); exit(1);
	}
	fprintf(fid,"joueur 0 (elephant)\n[4] *** | *** | *** | *** | *** | \n[3] *** | *** | *** | *** | *** | \n[2] r-v | RRR | RRR | RRR | *** | \n[1] e-^ | *** | *** | *** | *** | \n[0] *** | *** | *** | *** | *** |\n[0]   [1]   [2]   [3]   [4]  \n");
	int c=fclose(fid);
	if(c!=0)
	{printf("Erreur fermeture fichier %s\n",filename);exit(1);}
    }
    return 0;
}
