
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"rdv.h"
#include"ets.h"
#include"auth.h"

enum{
JOUR,
MOIS,
ANNEE,
MINUTE,
HEURE,
CODERDV,
CIN,
ETS,
REGION,
TYPE,
COLUMNS
};

int ajouterRendezVous(char *filename, RendezVousDM rdv){
   
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
      fprintf(f, "%d %d %d %d %d %d %d %s %s %s\n",
            rdv.jour,rdv.mois,rdv.annee,rdv.heure,rdv.minute,
            rdv.code_rdv,rdv.cin,rdv.nom_ets,rdv.region,rdv.type);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}


 

int modifierRendezVousDM(char *filename, int code_rdv, RendezVousDM nouveauRdv) {

char region[20];
char type_dons[50];
strcat(region,"tunis");
strcat(type_dons,"totale");


    int tr = 0;
    RendezVousDM rdv;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF) {
            if (rdv.code_rdv == code_rdv) {
                fprintf(f2, "%d %d %d %d %d %d %d %s %s %s\n", nouveauRdv.jour,
                        nouveauRdv.mois, nouveauRdv.annee, nouveauRdv.heure,
                        nouveauRdv.minute, nouveauRdv.code_rdv, nouveauRdv.cin,
                        nouveauRdv.nom_ets,nouveauRdv.region,nouveauRdv.type);
                tr = 1;
            } 
	else {
                fprintf(f2, "%d %d %d %d %d %d %d %s %s %s\n",  rdv.jour,rdv.mois,rdv.annee,rdv.heure,rdv.minute,
            rdv.code_rdv,rdv.cin,rdv.nom_ets,rdv.region,rdv.type);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);

    return tr;
}


RendezVousDM chercherRendezVous(char *filename, int code_rdv) {

   RendezVousDM rdv;

char region[20];
char type_dons[50];
strcat(region,"tunis");
strcat(type_dons,"totale");

    int tr = 0;
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (tr == 0 && fscanf(f, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF) {
            if (rdv.code_rdv == code_rdv) {
                tr = 1;
            }
        }
        fclose(f);
    }

    if (tr == 0) {
        rdv.code_rdv = -1;
    }

    return rdv;
}






int supprimerRendezVous(char *filename, int code_rdv) {

char region[20];
char type_dons[50];
strcat(region,"tunis");
strcat(type_dons,"totale");


    int tr = 0;
    RendezVousDM rdv;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF) {
            if (rdv.code_rdv == code_rdv) {
                tr = 1;
            } else {
                fprintf(f2, "%d %d %d %d %d %d %d %s %s %s\n",  rdv.jour,rdv.mois,rdv.annee,rdv.heure,rdv.minute,
            rdv.code_rdv,rdv.cin,rdv.nom_ets,rdv.region,rdv.type);
            }
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }

    return tr;
}

void historiqueDM(char *filename, char *cin ) 
{

    int cinINT;
   

    RendezVousDM rdv;
    int tr = 0;
    FILE *f = fopen(filename, "r");
                FILE *f2 = fopen("historiqueRDV.txt", "a");

    if ((f != NULL)&&(f2 != NULL)) {
        while (fscanf(f, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF)
            {
             cinINT=atoi(cin);

            if (rdv.cin == cinINT) {
                tr = 1;
            fprintf(f2, "%d %d %d %d %d %d %d %s %s %s\n",  rdv.jour,rdv.mois,rdv.annee,rdv.heure,rdv.minute,
            rdv.code_rdv,rdv.cin,rdv.nom_ets,rdv.region,rdv.type);


        }

    }
            fclose(f2);

        fclose(f);

    }
}

void afficher_RendezVous(GtkWidget *liste,char*file){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
//
    char jSTR[50];
    char mSTR[50];
    char aSTR[50];
    char heureSTR[50];
    char minuteSTR[50];
    char cinSTR[50];
    char coderdvSTR[50];
//
    char jour[50];
    char mois[50];
    char annee[50];
    char heure[50];
    char minute[50];
    char cin[50];
    char coderdv[50];
    char nom_ets[50];
    char region[50];
    char type[50];


RendezVousDM rdv;

store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL){
renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" jour",renderer,"text",JOUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" mois",renderer,"text",MOIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" annee",renderer,"text",ANNEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" minute",renderer,"text",MINUTE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" heure",renderer,"text",HEURE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" code_rdv",renderer,"text",CODERDV,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" cin",renderer,"text",CIN,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" nom_ets",renderer,"text",ETS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" region",renderer,"text",REGION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes(" type",renderer,"text",TYPE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

f = fopen(file,"r");
if(f==NULL)
{
return;
}
else
{
f=fopen(file,"a+");
  while(fscanf(f,"%d %d %d %d %d %d %d %s %s %s\n",&rdv.jour,&rdv.mois,&rdv.annee,&rdv.minute,&rdv.heure,&rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type)!=EOF)
{

sprintf(jSTR,"%d",rdv.jour);
sprintf(mSTR,"%d",rdv.mois);
sprintf(aSTR,"%d",rdv.annee);
sprintf(minuteSTR,"%d",rdv.minute);
sprintf(heureSTR,"%d",rdv.heure);
sprintf(coderdvSTR,"%d",rdv.code_rdv);
sprintf(cinSTR,"%d",rdv.cin);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,JOUR,jSTR,MOIS,mSTR,ANNEE,aSTR,MINUTE,minuteSTR,HEURE,heureSTR,CODERDV,coderdvSTR,CIN,cinSTR,ETS,rdv.nom_ets,REGION,rdv.region,TYPE,rdv.type,-1);
}
fclose(f);





gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
gtk_object_unref(store);
}

}

int generer_ID_RDV(char *filename) {
RendezVousDM rdv;
    int id = 0;
    int repeat = 1;
    int i = 0;
    int maxIterations = 1000; // Limit the number of iterations

    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (repeat == 1 && i < maxIterations) {
            i++;
            repeat = 0;
		fseek(f,0,SEEK_SET);
            while (fscanf(f,"%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF) {
                if (rdv.code_rdv == i) {
                    repeat = 1;
                }
            }
        }

        fclose(f);
        id = i;
    }

    return id;
}

int HoraireDispo(char fillename[],char *ets, int capacite, int jour, int mois, int annee, char horaire[]) {
    RendezVousDM rdv;

    int nombreRDVs = 0;
char heurSTR[20];
char minuteSTR[50];
int heurRDV;
int minuteRDV;

strncpy(heurSTR,horaire,2);
strncpy(minuteSTR,horaire+3,3);
 heurRDV=atoi(heurSTR);
minuteRDV=atoi(minuteSTR);

    FILE *f = fopen(fillename, "r");

    if(f != NULL) {
        while(fscanf(f, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type) != EOF) {

 if((strcmp(rdv.nom_ets, ets)==0) && (rdv.jour==jour) && (rdv.mois==mois) && (rdv.annee==annee) && (rdv.heure==heurRDV) && (rdv.minute==minuteRDV) ) {
                nombreRDVs++;
            }
        }
        fclose(f);
    }


    if (nombreRDVs < capacite) {

    return capacite- nombreRDVs;
    }
else return 0;

}
void remove_all_items_from_combo_box(GtkComboBox *combo_box) {
    GtkListStore *store = GTK_LIST_STORE(gtk_combo_box_get_model(combo_box));

    // Clear the store (remove all items)
    gtk_list_store_clear(store);
}
