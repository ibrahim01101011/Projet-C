#include "ets.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
/*
CODE INTERFACE.C :

afficher_ETS(treeviewAcceuilETS,"ets.txt");
afficher_ETS(treeviewSupprimerETS,"ets.txt");
afficher_ETS(treeviewHistoriqueETS,"etsHistorique.txt");

*/
enum{
ADRESS,
NOM,
IDETS,
PHONE,
OUVERTURE,
FERMETURE,
REGION,
JOUR,
MOIS,
ANNEE,
CAPACITE,
COLUMNS
};


int ajouterETS(char * filename, ets e )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,e.capacite);
        fclose(f);
        return 1;
    }
    else return 0;
}

int modifierETS( char * filename, int id, ets nouv )
{
    int tr=0;
    ets e;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
            if(e.idets== id)
            {
                fprintf(f2,"%s %s %d %s %s %s %s %s %s %s %d\n",nouv.adress,nouv.nom,nouv.idets,nouv.phone,nouv.ouv,nouv.ferm,nouv.region,nouv.jour,nouv.mois,nouv.annee,nouv.capacite);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,e.capacite);

        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;

}

int supprimerETS(char * filename, int id)
{
    int tr=0;
    ets e;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
            if(e.idets== id)
                tr=1;
            else
                fprintf(f2,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,e.capacite);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

ets chercherETS(char * filename, int id)
{
    ets e;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(tr==0&& fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
            if(e.idets== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        e.idets=-1;
    return e;

}


int ETSParRegion(char  nomFichier[], char reg[])

{

int nb=0;
ets e;
 FILE * f=fopen(nomFichier, "r");
 FILE * f2=fopen("etsReg.txt", "w");
 if(f!=NULL && f2!=NULL)
    {
     while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {

            if(strcmp(e.region,reg)==0)
            {

                nb ++;
                fprintf(f2,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,e.capacite);
                }
        }
    }
    else{
    printf("erreur d'ouverture du fichier");

    }
   
fclose(f2);
fclose(f);
return nb;
}

void ETSTrieCapacite(char nomFichier[]){

int nb =0;


ets *tabETS= malloc(nb * sizeof(ets) );
ets e ;
FILE * f=fopen(nomFichier, "r");
 FILE * f2=fopen("etsCap.txt", "w");
if (tabETS == NULL){
printf("Echec malloc");

}else{

 
 if(f!=NULL && f2!=NULL)
    {
     while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {      
        nb++;

  tabETS = realloc(tabETS, nb * sizeof(ets));
        tabETS[nb-1]=e;

 printf("%s %s %d %s %s %s %s %s %s %s %d\n",tabETS[nb-1].adress,tabETS[nb-1].nom,tabETS[nb-1].idets,tabETS[nb-1].phone,tabETS[nb-1].ouv,tabETS[nb-1].ferm,tabETS[nb-1].region,tabETS[nb-1].jour,tabETS[nb-1].mois,tabETS[nb-1].annee,tabETS[nb-1].capacite);
 
      
        }
 printf("nb= %d",nb);
 //trie des ets par capacite
int permut ;
do
{
ets aux;
 permut = 0; // initilement pas de permutation
for( int i = 0 ; i < nb-1 ; i++ )
{
if (  tabETS[i].capacite > tabETS[i+1].capacite )
{ // permutation
aux = tabETS[i];
tabETS[i] = tabETS[i+1];
tabETS[i+1] = aux ;
permut = 1; // on a fait une permutation
}
}
}
while (permut == 1);
 //fin tri
 //
 //
 //remplissage du ficher f2 : etsCap.txt
 for(int j=0;j<nb;j++){
 
  fprintf(f2,"%s %s %d %s %s %s %s %s %s %s %d\n",tabETS[j].adress,tabETS[j].nom,tabETS[j].idets,tabETS[j].phone,tabETS[j].ouv,tabETS[j].ferm,tabETS[j].region,tabETS[j].jour,tabETS[j].mois,tabETS[j].annee,tabETS[j].capacite);
 }
}

}
fclose(f2);
fclose(f);
}




void afficher_ETS(GtkWidget *liste,char*file){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
//
char adress[50];
char nom[50]; 
char idets[50];
char phone[50];
char ouverture[50];
char fermeture[50];
char region[50];
char jour[50];
char mois[50];
char annee[50];
char capacite[50];

char id[50];
char cap[50];

ets e;

store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL){


renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" NOM",renderer,"text",NOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" ID",renderer,"text",IDETS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" REGION",renderer,"text",REGION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" ADRESSE",renderer,"text",ADRESS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" TEL",renderer,"text",PHONE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" OUVERTURE",renderer,"text",OUVERTURE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" FERMETURE",renderer,"text",FERMETURE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" CAPACITE",renderer,"text",CAPACITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" J",renderer,"text",JOUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" M",renderer,"text",MOIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" A",renderer,"text",ANNEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


}
store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

f = fopen(file,"r");
if(f==NULL)
{
return;
}
else
{
f=fopen(file,"a+");
  while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
{
sprintf(id,"%d",e.idets);
sprintf(cap,"%d",e.capacite);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ADRESS,e.adress,NOM,e.nom,IDETS,id,PHONE,e.phone,OUVERTURE,e.ouv,FERMETURE,e.ferm,REGION,e.region,JOUR,e.jour,MOIS,e.mois,ANNEE,e.annee,CAPACITE,cap,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
gtk_object_unref(store);
}

}



int generer_ID(char *filename) {
    ets e;
    int id = 1;
    int repeat = 1;
    int i = 0;
    int maxIterations = 1000; // Limit the number of iterations

    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (repeat == 1 && i < maxIterations) {
            i++;
            repeat = 0;
		fseek(f,0,SEEK_SET);
            while (fscanf(f, "%s %s %d %s %s %s %s %s %s %s %d\n", e.adress, e.nom, &e.idets, e.phone, e.ouv, e.ferm, e.region, e.jour, e.mois, e.annee, &e.capacite) != EOF) {
                if (e.idets == i) {
                    repeat = 1;
                }
            }
        }

        fclose(f);
        id = i;
    }

    return id;
}





