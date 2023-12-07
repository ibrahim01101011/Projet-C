#ifndef ets_H_INCLUDED
#define et_H_INCLUDED
#include <gtk/gtk.h>
typedef struct
{
   char adress[50];
   char nom[50];
   int idets;
   char phone[50];
   char ouv[50];
   char ferm[50];
   char region[50];
   char jour[50];
   char mois[50];
   char annee[50];
   int capacite;

} ets;

int ajouterETS(char *, ets );

int modifierETS( char *, int, ets );
int supprimerETS(char * filename, int id);
ets chercherETS(char * filename, int id);
int ETSParRegion(char nomFichier[], char reg[]);
void ETSTrieCapacite(char nomFichier[]);
void afficher_ETS(GtkWidget *liste,char *);
int generer_ID(char *filename);
//void afficher_ETS(GtkTreeView *liste);
#endif // POINT_H_INCLUDED
