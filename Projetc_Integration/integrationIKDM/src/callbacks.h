#include <gtk/gtk.h>


void
on_buttonLogin_clicked                 (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonAfficherTriETS_clicked        (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_radiobuttonCapaciteETS_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonRegionETS_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonAjouterEts_clicked            (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonChercherETS_clicked           (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonEnregistrerModificationETS_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_checkbuttonHistoriqueSuppETS_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonSupprimerETS_clicked          (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonQuittarProgrammeETS_clicked   (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_button_confirmerDM_clicked          (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonAjouterAfficherETSDM_clicked  (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonAjouterAfficherhorraireDM_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonModifierChercherRdvDM_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_Modifier_supprimer_DM_clicked       (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_Modifier_confirmer_DM_clicked       (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonModifierAfficherETSDM_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonModifierAfficherhorraireDM_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonAfficherRDVDM_clicked         (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_buttonAfficherHistoriqueDM_clicked  (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_button_Supprimer_oui_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_Supprimer_Annuler_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_aj_annuler_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_radiobutton_aj_homme_WT_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_aj_femme_WT_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_aj_ajouter_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_mod_annuler_WT_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_radiobutton_mod_homme_WT_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_mod_femme_WT_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_mod_modif_WT_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_treeview_liste_row_WT_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_actualiser_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_rechercher_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_Supprimer_WT_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_treeview_liste_WT_row_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_buttonDeconnectionETS_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);
