#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED
#include <gtk/gtk.h>


typedef struct
{
    char jour[5];
    char mois[5];
    char annee[5];
} date;

typedef struct
{
    char nom[30];
    char prenom[30];
    char role[20];
    char cin[20];
    char tele[20];
    char sexe[20];
    date DN;
    date DR;
    char id[20];
    char mdp[20];

} user;
	
	void ajouter_user(user U);
	void modifier_user(user nouv);
	void supprimer_user(user sup);
	user chercher_user(GtkWidget *liste, char *rolep);
	void afficher_user(GtkWidget *liste);
	void pourcentage_user(float *nbH, float *nbF);
    
extern char *filename;

#endif // CRUD_H_INCLUDED

