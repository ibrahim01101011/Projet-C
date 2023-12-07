#include <stdio.h>
#include <string.h>
#include "user.h"
#include <stdlib.h>
#include <gtk/gtk.h>


char *filename= "user.txt";

enum
{
	ENOM,
	EPRENOM,
	EROLE,
	ECIN,
	ETELE,
	ESEXE,
	EDATEN,
	EDATER,
	EID,
	EMDP,
	COLUMNS
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ajouter_user(user U){

    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp);


        fclose(f);
        return ;
    }
    else
        return ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void modifier_user(user nouv) {
    user U;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp) != EOF){
				
			
            if (strcmp(U.id, nouv.id) == 0 || strcmp(U.cin, nouv.cin)==0)
            {
				printf("DEBUG:: modified line\n");
                fprintf(f2, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", nouv.nom, nouv.prenom, nouv.role, nouv.cin, nouv.tele, nouv.sexe,
                nouv.DN.jour, nouv.DN.mois, nouv.DN.annee, nouv.DR.jour,nouv.DR.mois, nouv.DR.annee, nouv.id, nouv.mdp);
            
            }
            else
                fprintf(f2, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
user chercher_user(GtkWidget *liste, char *rolep){
	user U;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	// GtkListStore *list_store;

	char nom[30];
    char prenom[30];
    char role[20];
    char cin[20];
    char tele[20];
    char sexe[20];
    char jourN[5];
    char moisN[5];
    char anneeN[5];
	char jourR[5];
    char moisR[5];
    char anneeR[5];
    char id[20];
    char mdp[20];
	// list_store=NULL;

	FILE *f;

	GtkListStore *store = gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("role", renderer, "text",EROLE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text",ECIN, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("tele", renderer, "text",ETELE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("date naissance", renderer, "text",EDATEN , NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("date recrutement", renderer, "text",EDATER , NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	f = fopen(filename,"r");
	if(f == NULL)
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier\n");
		return;
	}
	else
	{
		// f = fopen(filename, "a+");
		while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp) != EOF)
		{
			if (strncmp(U.role, rolep, 20) == 0) {
				char date_naissance[20] = {0}, date_recrut[20] = {0};
				strcat(date_naissance, U.DN.jour); strcat(date_naissance, "/"); strcat(date_naissance, U.DN.mois); strcat(date_naissance, "/"); strcat(date_naissance, U.DN.annee);
				strcat(date_recrut, U.DR.jour); strcat(date_recrut, "/"); strcat(date_recrut, U.DR.mois); strcat(date_recrut, "/"); strcat(date_recrut, U.DR.annee);
	
				gtk_list_store_append(store, &iter);
				gtk_list_store_set(store, &iter, ENOM, U.nom, EPRENOM, U.prenom, EROLE, U.role, ECIN, U.cin, ETELE, U.tele, ESEXE, U.sexe, EDATEN, date_naissance, EDATER, date_recrut, EID, U.id, EMDP, U.mdp, -1);
			}
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_user(GtkWidget *liste)

{
	user U;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char nom[30];
    char prenom[30];
    char role[20];
    char cin[20];
    char tele[20];
    char sexe[20];
    char jourN[5];
    char moisN[5];
    char anneeN[5];
	char jourR[5];
    char moisR[5];
    char anneeR[5];
    char id[20];
    char mdp[20];
	store=NULL;

	FILE *f;

	store = gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("role", renderer, "text",EROLE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text",ECIN, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("tele", renderer, "text",ETELE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("date naissance", renderer, "text",EDATEN , NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("date recrutement", renderer, "text",EDATER , NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	f = fopen(filename,"r");
	if(f == NULL)
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier\n");
		return;
	}
	else
	{
		// f = fopen(filename, "a+");
		while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp) != EOF)
		{
			char date_naissance[20] = {0}, date_recrut[20] = {0};
			strcat(date_naissance, U.DN.jour); strcat(date_naissance, "/"); strcat(date_naissance, U.DN.mois); strcat(date_naissance, "/"); strcat(date_naissance, U.DN.annee);
			strcat(date_recrut, U.DR.jour); strcat(date_recrut, "/"); strcat(date_recrut, U.DR.mois); strcat(date_recrut, "/"); strcat(date_recrut, U.DR.annee);
			printf("DEBUG:: date naissance = %s, date recrut = %s\n", date_naissance, date_recrut);

			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ENOM, U.nom, EPRENOM, U.prenom, EROLE, U.role, ECIN, U.cin, ETELE, U.tele, ESEXE, U.sexe, EDATEN, date_naissance, EDATER, date_recrut, EID, U.id, EMDP, U.mdp, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void supprimer_user(user sup)
{
   
   	user U; 

    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("user2.txt", "w");

	if (f == NULL || f2 == NULL)
		return;
	else
	{
		while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp) != EOF)
		{
            		printf("DEBUG :: U.id : %s,sup.id : %s",U.id, sup.id);		
			if (strcmp(U.id, sup.id) != 0 ){

                fprintf(f2, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour,U.DR.mois, U.DR.annee, U.id, U.mdp);
			}      		 
		}
   	 }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("user2.txt", filename);
    return;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pourcentage_user(float *nbH, float *nbF) 
{

    user U;
    int TH = 0, TF = 0, TU = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", U.nom, U.prenom, U.role, U.cin, U.tele, U.sexe,
                 U.DN.jour, U.DN.mois, U.DN.annee, U.DR.jour, U.DR.mois, U.DR.annee, U.id, U.mdp) != EOF) {
        
        if (strcmp(U.sexe, "Homme") == 0) {
            TH++;
        } else if (strcmp(U.sexe, "Femme") == 0) {
            TF++;
        }
        TU++;
    }

    fclose(f);
    *nbH = (float)TH / TU * 100;
    *nbF = (float)TF / TU * 100;

}
