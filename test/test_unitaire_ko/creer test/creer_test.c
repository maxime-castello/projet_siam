

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
	sprintf(filename,"test_unitaire_ko_0%d.txt",i);
	printf("%s\n",filename);
	FILE *fid=NULL; //struct contenant un descripteur de fichier
	fid=fopen(filename,"w"); //ouverture du fichier “filename” en mode ecriture
	if(fid==NULL)
	{
	printf("Erreur ouverture du fichier %s\n",filename); exit(1);
	}
	fprintf(fid,"#test_unitaire_ko_0%d\n#\n# test l'interdiction ...\nlit ../test/test_unitaire_ko/test_unitaire_ko_0%d_entree.txt\nfin\n#Comportement attendu:\n# ..., aucune piece ne doit #bouger, le mouvement est invalide.\n",i, i);
	int c=fclose(fid);
	if(c!=0)
	{printf("Erreur fermeture fichier %s\n",filename);exit(1);}
    }
    return 0;
}
