#ifndef RDV_H_INCLUDED
#define RDV_H_INCLUDED

#include <gtk/gtk.h>
//

//
typedef struct {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int code_rdv;
    int cin ;
    char nom_ets[50];
    char region[50];
    char type[50];
} RendezVousDM;

int HoraireDispo(char fillename[],char *ets, int capacite, int jour, int mois, int annee, char horaire[]) ;
int modifierRendezVousDM(char *filename, int code_rdv, RendezVousDM nouveauRdv);
int ajouterRendezVous(char *filename, RendezVousDM rdv);
void historiqueDM(char *filename, char *cin ) ;
int supprimerRendezVous(char *filename, int code_rdv);
RendezVousDM chercherRendezVous(char *filename, int code_rdv);
//afficher tree view 
void afficher_RendezVous(GtkWidget *liste,char*file);
void remove_all_items_from_combo_box(GtkComboBox *combo_box);
int generer_ID_RDV(char *filename) ;





#endif // RDV_H_INCLUDED

