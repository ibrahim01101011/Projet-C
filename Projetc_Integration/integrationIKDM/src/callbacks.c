#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ets.h"
#include "rdv.h"
#include <string.h>
#include "auth.h"
#include "user.h"

//VARIABLES GLOBALES :

int choixTreeETS=1;
int historiqueETS=0;
int sexe = 1;
int sexe_mod = 1;
user sup;

void
on_buttonLogin_clicked                 (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
//WINDOWS
  GtkWidget *Login;
  GtkWidget *windowEspaceAdmin;
  GtkWidget *windowEspaceDonneur;
  GtkWidget *Supprimer_window;
  GtkWidget *administrateur_window;


//INPUTS: ENTRY LOGIN , ENTRY PASSWORD
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *output;

char username[50];
char password[50];

//ASSIGNEMENT DES OBJETS GRAPHIQUES :

Login=lookup_widget(objet_graphique,"Login");
input1=lookup_widget(objet_graphique,"entryUsername");
input2=lookup_widget(objet_graphique,"entryPassword");
output=lookup_widget(objet_graphique,"labelMessageLogin");

//COPY :

strcpy(username,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(input2)));



//START CODE VERIFY AUTHENTIFICATION :

int verif = verifyAuth(username,password);
if (verif==1){

gtk_label_set_text(GTK_LABEL(output),"connection avec succès");

gtk_widget_destroy(Login);
windowEspaceAdmin = create_windowEspaceAdmin (); 
gtk_widget_show (windowEspaceAdmin);

}
else if (verif==2){

gtk_label_set_text(GTK_LABEL(output),"connection avec succès");

gtk_widget_destroy(Login);
windowEspaceDonneur = create_windowEspaceDonneur (); 
gtk_widget_show (windowEspaceDonneur);

}
else if (verif==3){

gtk_label_set_text(GTK_LABEL(output),"connection avec succès");

gtk_widget_destroy(Login);
administrateur_window = create_administrateur_window (); 
gtk_widget_show (administrateur_window);

}
else if (verif==0){
gtk_label_set_text(GTK_LABEL(output),"vérifiez vos coordonnées!!");
}
//END CODE VERIFY AUTHENTIFICATION :
}


void
on_buttonAfficherTriETS_clicked        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview;
GtkWidget *comboRegion;

char region[50];

treeview=lookup_widget(objet_graphique,"treeviewAcceuilETS");
comboRegion=lookup_widget(objet_graphique,"comboboxentryChoixRegionTreeETS");
//
strcpy(region,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboRegion)));
 if (choixTreeETS==2)
{
int reg= ETSParRegion("ets.txt", region);
afficher_ETS(treeview,"etsReg.txt");
}
else if (choixTreeETS==1)
{
ETSTrieCapacite("ets.txt");
afficher_ETS(treeview,"etsCap.txt");
}
else
{
afficher_ETS(treeview,"ets.txt");
}
}


void
on_radiobuttonCapaciteETS_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
choixTreeETS=1;
}


void
on_radiobuttonRegionETS_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
choixTreeETS=2;
}


void
on_buttonAjouterEts_clicked            (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *nom;
GtkWidget *region;
GtkWidget *adresse;
GtkWidget *ouverture;
GtkWidget *fermeture;
GtkWidget *capacite;
GtkWidget *telephone;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *annee;
GtkWidget *output_ID;

GtkWidget *treeviewHist;
GtkWidget *treeviewacc;
GtkWidget *treeviewsupp;

//GtkWidget *treeviewAcceuilETS;

int cap,ouv,ferm,horr ;
char nom_ets[50];
char adr[50];
char tel[50];
char reg[50];
char j[50];
char m[50];
char a[50];
char ouvert[50];
char fermet[50];
ets e ;

treeviewacc=lookup_widget(objet_graphique,"treeviewAcceuilETS");
treeviewsupp=lookup_widget(objet_graphique,"treeviewSupprimerETS");
treeviewHist=lookup_widget(objet_graphique,"treeviewHistoriqueETS");

output_ID=lookup_widget(objet_graphique,"labelIDETSgenerated");

nom=lookup_widget(objet_graphique,"entryNomETS");
region=lookup_widget(objet_graphique,"comboboxentryRegionETS");
adresse=lookup_widget(objet_graphique,"entryAdresseETS");
ouverture=lookup_widget(objet_graphique,"spinbuttonOuvertureETS");
fermeture=lookup_widget(objet_graphique,"spinbuttonFermetureETS");
capacite=lookup_widget(objet_graphique,"spinbuttonCapaciteETS");
telephone=lookup_widget(objet_graphique,"entryTelephoneETS");
jour=lookup_widget(objet_graphique,"comboboxentryJourETS");
mois=lookup_widget(objet_graphique,"comboboxentryMoisETS");
annee=lookup_widget(objet_graphique,"comboboxentryAnneeETS");
//necessite conversion :
ouv=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ouverture));
ferm=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(fermeture));
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxsprintf(horraire,"%dh-->%dh",ouv,ferm);
sprintf(ouvert,"%d",ouv);
sprintf(fermet,"%d",ferm);

//
strcpy(nom_ets,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(adr,gtk_entry_get_text(GTK_ENTRY(adresse)));
strcpy(tel,gtk_entry_get_text(GTK_ENTRY(telephone)));
//

strcpy(reg,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
strcpy(j,gtk_combo_box_get_active_text(GTK_COMBO_BOX(jour)));
strcpy(m,gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
strcpy(a,gtk_combo_box_get_active_text(GTK_COMBO_BOX(annee)));





//REMPLISSAGE DE L'ETS :
e.capacite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacite));
e.idets=generer_ID("ets.txt");
strcpy(e.jour,j);
strcpy(e.mois,m);
strcpy(e.annee,a);
strcpy(e.phone,tel);
strcpy(e.adress,adr);
strcpy(e.nom,nom_ets);
strcpy(e.ouv,ouvert);
strcpy(e.ferm,fermet);
strcpy(e.region,reg);
//AJOUT ETS :
int x= ajouterETS("ets.txt", e );
char GID[50];
sprintf(GID,"%d",e.idets);
//
gtk_label_set_text(GTK_LABEL(output_ID),GID);

//ACTUALISATION DES TREEVIEWS :

afficher_ETS(treeviewacc,"ets.txt");
afficher_ETS(treeviewsupp,"ets.txt");
afficher_ETS(treeviewHist,"etsHistorique.txt");
}


void
on_buttonChercherETS_clicked           (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *inputID;
GtkWidget *nom;
GtkWidget *region;
GtkWidget *adresse;
GtkWidget *ouverture;
GtkWidget *fermeture;
GtkWidget *capacite;
GtkWidget *telephone;
GtkWidget *date;
GtkWidget *outputID;
ets e;
char suppID[50];

char dateSTR[50];
char capaciteSTR[50];

int INTsuppID=0;

inputID=lookup_widget(objet_graphique,"entryRecherchETS");

outputID=lookup_widget(objet_graphique,"labelModifierPrevIDETS");

nom=lookup_widget(objet_graphique,"labelModifierPrevNOMETS");
region=lookup_widget(objet_graphique,"labelModifierPrevREGIONETS");
adresse=lookup_widget(objet_graphique,"labelModifierPrevADRESSETS");
ouverture=lookup_widget(objet_graphique,"labelModifierPrevOUVETS");
fermeture=lookup_widget(objet_graphique,"labelModifierPrevFERMETS");
capacite=lookup_widget(objet_graphique,"labelModifierPrevCAPETS");
telephone=lookup_widget(objet_graphique,"labelModifierPrevTELETS");
date=lookup_widget(objet_graphique,"labelModifierPrevDATEETS");



strcpy(suppID,gtk_entry_get_text(GTK_ENTRY(inputID)));




INTsuppID=atoi(suppID);

e =chercherETS("ets.txt",INTsuppID);
sprintf(dateSTR,"%s / %s / %s",e.jour,e.mois,e.annee);
sprintf(capaciteSTR,"%d",e.capacite);

gtk_label_set_text(GTK_LABEL(nom),e.nom);
gtk_label_set_text(GTK_LABEL(region),e.region);
gtk_label_set_text(GTK_LABEL(adresse),e.adress);
gtk_label_set_text(GTK_LABEL(ouverture),e.ouv);
gtk_label_set_text(GTK_LABEL(fermeture),e.ferm);
gtk_label_set_text(GTK_LABEL(capacite),capaciteSTR);
gtk_label_set_text(GTK_LABEL(telephone),e.phone);
gtk_label_set_text(GTK_LABEL(date),dateSTR);
gtk_label_set_text(GTK_LABEL(outputID),suppID);
}


void
on_buttonEnregistrerModificationETS_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *nom;
GtkWidget *region;
GtkWidget *adresse;
GtkWidget *ouverture;
GtkWidget *fermeture;
GtkWidget *capacite;
GtkWidget *telephone;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *annee;
GtkWidget *getID;

GtkWidget *treeviewHist;
GtkWidget *treeviewacc;
GtkWidget *treeviewsupp;
//GtkWidget *treeviewAcceuilETS;

int cap,ouv,ferm,horr ;
char nom_ets[50];
char adr[50];
char tel[50];
char ouvert[50];
char fermet[50];
char reg[50];
char j[50];
char m[50];
char a[50];
char ID[50];
ets e ;

treeviewacc=lookup_widget(objet_graphique,"treeviewAcceuilETS");
treeviewsupp=lookup_widget(objet_graphique,"treeviewSupprimerETS");
treeviewHist=lookup_widget(objet_graphique,"treeviewHistoriqueETS");
//entryRecherchETS

nom=lookup_widget(objet_graphique,"entryModifierNomETS");
region=lookup_widget(objet_graphique,"comboboxentryRegionModofierETS");
adresse=lookup_widget(objet_graphique,"entryModifierAdresseETS");
ouverture=lookup_widget(objet_graphique,"spinbuttonModifierOuvertureETS");
fermeture=lookup_widget(objet_graphique,"spinbuttonModifierFermetureETS");
capacite=lookup_widget(objet_graphique,"spinbuttonModifierCapaciteETS");
telephone=lookup_widget(objet_graphique,"entryModifierTelephoneETS");
jour=lookup_widget(objet_graphique,"comboboxentryJourModifierETS");
mois=lookup_widget(objet_graphique,"comboboxentryMoisModifierETS");
annee=lookup_widget(objet_graphique,"comboboxentryAnneModifierETS");

getID=lookup_widget(objet_graphique,"entryRecherchETS");

ouv=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ouverture));
ferm=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(fermeture));

//
strcpy(nom_ets,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(adr,gtk_entry_get_text(GTK_ENTRY(adresse)));
strcpy(tel,gtk_entry_get_text(GTK_ENTRY(telephone)));
//

strcpy(reg,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
strcpy(j,gtk_combo_box_get_active_text(GTK_COMBO_BOX(jour)));
strcpy(m,gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
strcpy(a,gtk_combo_box_get_active_text(GTK_COMBO_BOX(annee)));

cap=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacite));

strcpy(ID,gtk_entry_get_text(GTK_ENTRY(getID)));
int intID=atoi(ID);
e =chercherETS("ets.txt",intID);


if (strlen(nom_ets)>0)
{
strcpy(e.nom,nom_ets);
}

if (strlen(adr)!=0)
strcpy(e.adress,adr);
if (strlen(tel)!=0)
strcpy(e.phone,tel);

if (strlen(reg)!=0)
strcpy(e.region,reg);
if (cap!=0)
e.capacite=cap;
if (ouv>0){
sprintf(ouvert,"%d",ouv);
strcpy(e.ouv,ouvert);
}
if (ferm>0){
sprintf(fermet,"%d",ferm);
strcpy(e.ouv,fermet);
}
if (strlen(j)!=0)
strcpy(e.jour,j);
if (strlen(m)!=0)
strcpy(e.mois,m);
if (strlen(a)!=0)
strcpy(e.annee,a);

int x= modifierETS( "ets.txt", intID, e );
afficher_ETS(treeviewacc,"ets.txt");
afficher_ETS(treeviewsupp,"ets.txt");
afficher_ETS(treeviewHist,"etsHistorique.txt");
}


void
on_checkbuttonHistoriqueSuppETS_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
historiqueETS=1;
}


void
on_buttonSupprimerETS_clicked          (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *input_ID;
GtkWidget *outputMessage;
GtkWidget *treeviewHist;
GtkWidget *treeviewacc;
GtkWidget *treeviewsupp;
char suppID[50];
int INTsuppID;
ets e;

INTsuppID=0;
outputMessage=lookup_widget(objet_graphique,"messageidSupp");
treeviewacc=lookup_widget(objet_graphique,"treeviewAcceuilETS");
treeviewsupp=lookup_widget(objet_graphique,"treeviewSupprimerETS");
treeviewHist=lookup_widget(objet_graphique,"treeviewHistoriqueETS");
input_ID=lookup_widget(objet_graphique,"entryIdSupprimerETS");


strcpy(suppID,gtk_entry_get_text(GTK_ENTRY(input_ID)));

INTsuppID=atoi(suppID);
e =chercherETS("ets.txt",INTsuppID);
int supprimer=supprimerETS("ets.txt", INTsuppID);


if (supprimer==0)
{
gtk_label_set_text(GTK_LABEL(outputMessage),"L'ETS à supprimer n'existe pas !");
}
else if(supprimer>0)
{

gtk_label_set_text(GTK_LABEL(outputMessage),"L'ETS est supprimé avec succès");
}
afficher_ETS(treeviewacc,"ets.txt");
afficher_ETS(treeviewsupp,"ets.txt");

if (historiqueETS==1)
{
int ajouterHistorique= ajouterETS("etsHistorique.txt", e );
afficher_ETS(treeviewHist,"etsHistorique.txt");
}
}


void
on_buttonQuittarProgrammeETS_clicked   (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
gtk_main_quit();
}


void
on_button_confirmerDM_clicked          (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *nom;
//comboboxentryAjouterChoixEtsDM
GtkWidget *region;
//comboboxentryAjouterRegionDM
GtkWidget *type;
//comboboxentryAjouterTypeDonDM
GtkWidget *cin;
//entryAjouterCinDM
GtkWidget *code_rdvMess;
//labelAfficherAjoutRdvDM
GtkWidget *horraire;
//comboboxentryAjouterHorraireDM
GtkWidget *jour;
//spinbuttonAjouterJourDM
GtkWidget *mois;
//spinbuttonAjouterMoisDM
GtkWidget *annee;
//spinbuttonAjouterAnneDM



int code_rdv,INTcin,j,m,a,heur,minute ;


char nomRDV[50];
char regRDV[50];
char typeRDV[50];

char heurSTR[50];
char minuteSTR[50];

char cinSTR[50];
char regionSTR[50];
char nomEtsSTR[50];
char horraireSTR[50];
char typeSTR[50];

RendezVousDM rdv ;


//INPUTS

nom=lookup_widget(objet_graphique,"comboboxentryAjouterChoixEtsDM");
region=lookup_widget(objet_graphique,"comboboxentryAjouterRegionDM");
type=lookup_widget(objet_graphique,"comboboxentryAjouterTypeDonDM");
cin=lookup_widget(objet_graphique,"entryAjouterCinDM");
horraire=lookup_widget(objet_graphique,"comboboxentryAjouterHorraireDM");
jour=lookup_widget(objet_graphique,"spinbuttonAjouterJourDM");
mois=lookup_widget(objet_graphique,"spinbuttonAjouterMoisDM");
annee=lookup_widget(objet_graphique,"spinbuttonAjouterAnneDM");

//OUTPUTS
code_rdvMess=lookup_widget(objet_graphique,"labelAfficherAjoutRdvDM");

// GET VALUES :


j =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
m =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
a =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

strcpy(cinSTR,gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(regionSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));

strcpy(nomEtsSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nom)));
strcpy(horraireSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(horraire)));
strcpy(typeSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));

//decomposition d'horraire :

strncpy(heurSTR,horraireSTR,2);
strncpy(minuteSTR,horraireSTR+3,3);

//RDV STRUCT CONVERSION
code_rdv=generer_ID_RDV("rdv.txt");
INTcin=atoi(cinSTR);
// j
// m
// a
heur=atoi(heurSTR);
minute=atoi(minuteSTR);
//typeSTR
//nomEtsSTR
//regionSTR

//remlissage :
rdv.jour=j;
rdv.mois=m;
rdv.annee=a;
rdv.heure=heur;
rdv.minute=minute;
rdv.code_rdv=code_rdv;
rdv.cin=INTcin;
strcpy(rdv.region,regionSTR);
strcpy(rdv.nom_ets,nomEtsSTR);
strcpy(rdv.type,typeSTR);
/*    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int code_rdv;
    int cin ;
    char nom_ets[50];
    char region[50];
    char type[50];*/


int x= ajouterRendezVous("rdv.txt", rdv);

char GcodeRDV[50];
sprintf(GcodeRDV,"Voici le code de votre rendez-vous :%d",rdv.code_rdv);


gtk_label_set_text(GTK_LABEL(code_rdvMess),GcodeRDV);
}


void
on_buttonAjouterAfficherETSDM_clicked  (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *nom;

GtkWidget *region;




char regionSTR[50];



//INPUTS

nom=lookup_widget(objet_graphique,"comboboxentryAjouterChoixEtsDM");
region=lookup_widget(objet_graphique,"comboboxentryAjouterRegionDM");



strcpy(regionSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
//
//REMPLISSAGE DU COMBO_BOX DES ETS PAR REGION

ets e;
 int etsRegion = ETSParRegion( "ets.txt", regionSTR);
int nb=0;
FILE * f=fopen("etsReg.txt", "r");


    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
nb++;
gtk_combo_box_append_text (GTK_COMBO_BOX (nom), _(e.nom));


        }

    }
  fclose(f);

}


void
on_buttonAjouterAfficherhorraireDM_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *horraire;

GtkWidget *jour;
GtkWidget *mois;
GtkWidget *annee;

GtkWidget *nom;

char NomEtsCombo[50];
int j,m ,a;


//INPUTS

jour=lookup_widget(objet_graphique,"spinbuttonAjouterJourDM");
mois=lookup_widget(objet_graphique,"spinbuttonAjouterMoisDM");
annee=lookup_widget(objet_graphique,"spinbuttonAjouterAnneDM");


nom=lookup_widget(objet_graphique,"comboboxentryAjouterChoixEtsDM");
horraire=lookup_widget(objet_graphique,"comboboxentryAjouterHorraireDM");

j =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
m =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
a =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

strcpy(NomEtsCombo,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nom)));

//
//REMPLISSAGE DU COMBO_BOX DES ETS PAR REGION

ets e;
RendezVousDM rdv;
int capacite_rdv_par_jour=0;
int ouvertureETS;
int fermetureETS;
int capaciteETS;
int IDets;
char nom_ETS[50];

//int HoraireDispo(char fillename[],char *ets, int capacite, int jour, int mois, int annee, char horaire[]) {

FILE * f=fopen("ets.txt", "r");
FILE * f2=fopen("rdv.txt", "r");

    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
if (strcmp(e.nom,NomEtsCombo)==0)
{

capacite_rdv_par_jour=(e.ferm-e.ouv)*2;
ouvertureETS=atoi(e.ouv);
fermetureETS=atoi(e.ferm);
capaciteETS=e.capacite;
IDets=e.idets;
strcpy(nom_ETS,e.nom);
}

        }

    fclose(f);
}
//0000000000000000000000000000000

char tab[22][10]={"80","830","90","930","100","1030","110","1130","120","1230","130","1330","140","1430","150","1530","160","1630","170","1730","180"};
char tab2[22][10]={"08:00","08:30","09:00","09:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00"};
char rdvHeur[20];
char rdvMin[20];

    if(f2!=NULL)
{

        while(fscanf(f2, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type)!=EOF)
        {

if ( (rdv.jour==j )&& (rdv.mois== m )&& (rdv.annee==a)&& (capaciteETS>0)&& (strcmp(rdv.nom_ets,nom_ETS)==0) )
{

capaciteETS -- ;

sprintf(rdvHeur,"%d",rdv.heure);
sprintf(rdvMin,"%d",rdv.minute);
strcat(rdvHeur,rdvMin);

//printf("%s",rdvHeur);


if (capaciteETS==0){
//MessageCapaciteETS=1;
for(int i=0;i<21;i++)
{
if(strcmp(rdvHeur,tab[i])==0)
{
strcpy(tab[i],"xxxx");
}
}
}



//}

        }
//else return;



    }
    fclose(f2);
}



remove_all_items_from_combo_box(GTK_COMBO_BOX(horraire));

for(int k=((ouvertureETS*2)-16);k<((fermetureETS-18)+19);k++)
{

if(strcmp(tab[k],"xxxx")!=0)
{

gtk_combo_box_append_text (GTK_COMBO_BOX (horraire), _(tab2[k]));

}
}

//end

}


void
on_buttonModifierChercherRdvDM_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *Labelchercher ;
GtkWidget *entryChercher ;
char CodeRdvStr[200];
int CodeRDV;
RendezVousDM rdv;
Labelchercher=lookup_widget(objet_graphique,"labelModiffierRdvTrouveDM");
entryChercher=lookup_widget(objet_graphique,"entryModifSaisiCodeRdv");
strcpy(CodeRdvStr,gtk_entry_get_text(GTK_ENTRY(entryChercher)));
CodeRDV=atoi(CodeRdvStr);
rdv= chercherRendezVous("rdv.txt",CodeRDV);
sprintf(CodeRdvStr,"jour :%d\nmois: %d\nannée: %d\nminute: %d\nheure: %d\ncin: %d\nnom ETS: %s\nregion: %s\ntype: %s\n",rdv.jour,rdv.mois,rdv.annee,rdv.heure,rdv.minute,rdv.cin,rdv.nom_ets,rdv.region,rdv.type);
gtk_label_set_text(GTK_LABEL(Labelchercher),CodeRdvStr);

}


void
on_Modifier_supprimer_DM_clicked       (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *entryCodeRDV ;
GtkWidget *LabelValidationSupp ;
char CodeRdvStr[20];
int code_rdv ;
entryCodeRDV=lookup_widget(objet_graphique,"entryModifSaisiCodeRdv");
LabelValidationSupp=lookup_widget(objet_graphique,"labelModiffierRdvTrouveDM");
strcpy(CodeRdvStr,gtk_entry_get_text(GTK_ENTRY(entryCodeRDV)));

code_rdv=atoi(CodeRdvStr);


int supp= supprimerRendezVous("rdv.txt", code_rdv);
if (supp==0)
{
gtk_label_set_text(GTK_LABEL(LabelValidationSupp),"Le rendez-vous à supprimer n'existe pas !");
}
else if(supp>0)
{

gtk_label_set_text(GTK_LABEL(LabelValidationSupp),"Le rendez-vous est supprimé avec succès");
}
}


void
on_Modifier_confirmer_DM_clicked       (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *nom;
//comboboxentryModifierEtsDM
GtkWidget *region;
//comboboxentryModifierRegionDM
GtkWidget *type;
//comboboxentryModifierTypedonDM

//GtkWidget *cin;
//entryAjouterCinDM

/*  ENTRY !!!! */
GtkWidget *Getcode_rdvMess;
//entryModifSaisiCodeRdv 

GtkWidget *horraire;
//comboboxentryModifierHorraireDM
GtkWidget *jour;
//spinbuttonModifierJourDM
GtkWidget *mois;
//spinbuttonModifierMoisDM
GtkWidget *annee;
//spinbuttonModifierAnneDM



int code_rdv,INTcin,j,m,a,heur,minute ;


char nomRDV[50];
char regRDV[50];
char typeRDV[50];

char heurSTR[50];
char minuteSTR[50];

char cinSTR[50];
char regionSTR[50];
char nomEtsSTR[50];
char horraireSTR[50];
char typeSTR[50];
char codeRdvSTR[50];
RendezVousDM rdv ;

char jourSTR[20];
char moisSTR[20];
char anneeSTR[20];
//INPUTS

nom=lookup_widget(objet_graphique,"comboboxentryModifierEtsDM");
region=lookup_widget(objet_graphique,"comboboxentryModifierRegionDM");
type=lookup_widget(objet_graphique,"comboboxentryModifierTypedonDM");

horraire=lookup_widget(objet_graphique,"comboboxentryModifierHorraireDM");
jour=lookup_widget(objet_graphique,"spinbuttonModifierJourDM");
mois=lookup_widget(objet_graphique,"spinbuttonModifierMoisDM");
annee=lookup_widget(objet_graphique,"spinbuttonModifierAnneDM");

Getcode_rdvMess=lookup_widget(objet_graphique,"entryModifSaisiCodeRdv");

//code_rdvMess=lookup_widget(objet_graphique,"labelAfficherAjoutRdvDM");

// GET VALUES :

j =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
m =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
a =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

strcpy(codeRdvSTR,gtk_entry_get_text(GTK_ENTRY(Getcode_rdvMess)));
strcpy(regionSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
strcpy(nomEtsSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nom)));
strcpy(horraireSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(horraire)));
strcpy(typeSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));

//decomposition d'horraire :

strncpy(heurSTR,horraireSTR,2);
strncpy(minuteSTR,horraireSTR+3,3);

// j
// m
// a

heur=atoi(heurSTR);
minute=atoi(minuteSTR);
code_rdv=atoi(codeRdvSTR);
rdv = chercherRendezVous("rdv.txt",code_rdv);

//typeSTR
//nomEtsSTR
//regionSTR

if (strlen(nomEtsSTR)>0)
{
strcpy(rdv.nom_ets,nomEtsSTR);
}
if (strlen(typeSTR)>0)
{
strcpy(rdv.type,typeSTR);
}
if (strlen(regionSTR)>0)
{
strcpy(rdv.region,regionSTR);
}

if (strlen(horraireSTR)>0)
{
rdv.heure=heur;
rdv.minute=minute;
}

if (j>0){

rdv.jour=j;
}
if (m>0){

rdv.mois=m;
}
if (j>0){

rdv.annee=a;
}

int modif= modifierRendezVousDM("rdv.txt", code_rdv, rdv);

}


void
on_buttonModifierAfficherETSDM_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *nom;

GtkWidget *region;




char regionSTR[50];



//INPUTS

nom=lookup_widget(objet_graphique,"comboboxentryModifierEtsDM");
region=lookup_widget(objet_graphique,"comboboxentryModifierRegionDM");



strcpy(regionSTR,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
//
//REMPLISSAGE DU COMBO_BOX DES ETS PAR REGION

ets e;
 int etsRegion = ETSParRegion( "ets.txt", regionSTR);
int nb=0;
FILE * f=fopen("etsReg.txt", "r");


    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
nb++;
gtk_combo_box_append_text (GTK_COMBO_BOX (nom), _(e.nom));


        }

    }
  fclose(f);

}


void
on_buttonModifierAfficherhorraireDM_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *horraire;

GtkWidget *jour;
GtkWidget *mois;
GtkWidget *annee;

GtkWidget *nom;

char NomEtsCombo[50];
int j,m ,a;


//INPUTS

jour=lookup_widget(objet_graphique,"spinbuttonModifierJourDM");
mois=lookup_widget(objet_graphique,"spinbuttonModifierMoisDM");
annee=lookup_widget(objet_graphique,"spinbuttonModifierAnneDM");


nom=lookup_widget(objet_graphique,"comboboxentryModifierEtsDM");
horraire=lookup_widget(objet_graphique,"comboboxentryModifierHorraireDM");

j =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
m =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
a =gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

strcpy(NomEtsCombo,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nom)));

//
//REMPLISSAGE DU COMBO_BOX DES ETS PAR REGION

ets e;
RendezVousDM rdv;
int capacite_rdv_par_jour=0;
int ouvertureETS;
int fermetureETS;
int capaciteETS;
int IDets;
char nom_ETS[50];

//int HoraireDispo(char fillename[],char *ets, int capacite, int jour, int mois, int annee, char horaire[]) {

FILE * f=fopen("ets.txt", "r");
FILE * f2=fopen("rdv.txt", "r");

    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %d %s %s %s %s %s %s %s %d\n",e.adress,e.nom,&e.idets,e.phone,e.ouv,e.ferm,e.region,e.jour,e.mois,e.annee,&e.capacite)!=EOF)
        {
if (strcmp(e.nom,NomEtsCombo)==0)
{

capacite_rdv_par_jour=(e.ferm-e.ouv)*2;
ouvertureETS=atoi(e.ouv);
fermetureETS=atoi(e.ferm);
capaciteETS=e.capacite;
IDets=e.idets;
strcpy(nom_ETS,e.nom);
}

        }

    fclose(f);
}


char tab[22][10]={"80","830","90","930","100","1030","110","1130","120","1230","130","1330","140","1430","150","1530","160","1630","170","1730","180"};
char tab2[22][10]={"08:00","08:30","09:00","09:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00"};
char rdvHeur[20];
char rdvMin[20];

    if(f2!=NULL)
{

        while(fscanf(f2, "%d %d %d %d %d %d %d %s %s %s\n",  &rdv.jour,&rdv.mois,&rdv.annee,&rdv.heure,&rdv.minute,
            &rdv.code_rdv,&rdv.cin,rdv.nom_ets,rdv.region,rdv.type)!=EOF)
        {

if ( (rdv.jour==j )&& (rdv.mois== m )&& (rdv.annee==a)&& (capaciteETS>0)&& (strcmp(rdv.nom_ets,nom_ETS)==0) )
{

capaciteETS -- ;

sprintf(rdvHeur,"%d",rdv.heure);
sprintf(rdvMin,"%d",rdv.minute);
strcat(rdvHeur,rdvMin);

//printf("%s",rdvHeur);


if (capaciteETS==0){
//MessageCapaciteETS=1;
for(int i=0;i<21;i++)
{
if(strcmp(rdvHeur,tab[i])==0)
{
strcpy(tab[i],"xxxx");
}
}
}





        }




    }
    fclose(f2);
}



remove_all_items_from_combo_box(GTK_COMBO_BOX(horraire));

for(int k=((ouvertureETS*2)-16);k<((fermetureETS-18)+19);k++)
{

if(strcmp(tab[k],"xxxx")!=0)
{

gtk_combo_box_append_text (GTK_COMBO_BOX (horraire), _(tab2[k]));

}
}


}


void
on_buttonAfficherRDVDM_clicked         (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview1;



treeview1=lookup_widget(objet_graphique,"treeviewAfficherDRVSDM");


 afficher_RendezVous(treeview1,"rdv.txt");
}


void
on_buttonAfficherHistoriqueDM_clicked  (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *treeview1;
GtkWidget *entryCIN;

char cin[20];
treeview1=lookup_widget(objet_graphique,"treeview4");
entryCIN=lookup_widget(objet_graphique,"entryHistoriqueCinDM");

strcpy(cin,gtk_entry_get_text(GTK_ENTRY(entryCIN)));
historiqueDM("rdv.txt", cin);
 afficher_RendezVous(treeview1,"historiqueRDV.txt");
}


void
on_button_Supprimer_oui_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
supprimer_user(sup);
	
	GtkWidget *close_window = lookup_widget(objet_graphique, "Supprimer_window");
	gtk_widget_destroy (close_window);

}


void
on_button_Supprimer_Annuler_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *close_window = lookup_widget(objet_graphique, "Supprimer_window");
	gtk_widget_destroy (close_window);
}


void
on_button_aj_annuler_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *administrateur_window;
	administrateur_window = lookup_widget(objet_graphique,"administrateur_window");
	gtk_widget_destroy(administrateur_window);

	
	administrateur_window = create_administrateur_window ();
	gtk_widget_show (administrateur_window);
}


void
on_radiobutton_aj_homme_WT_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
	sexe=1;
}


void
on_radiobutton_aj_femme_WT_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
	sexe=2;
}


void
on_button_aj_ajouter_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

	user U;
	int JN,MN,AN;
	int JR,MR,AR;

	GtkWidget *nom;
	GtkWidget *prenom;
	GtkWidget *role;
	GtkWidget *cin;
	GtkWidget *tele;
	GtkWidget *id;
	GtkWidget *mdp;


    nom = lookup_widget(objet_graphique, "entry_aj_nom_WT");
	strcpy(U.nom,gtk_entry_get_text(GTK_ENTRY(nom)));

	prenom=lookup_widget(objet_graphique, "entry_aj_prenom_WT");
	strcpy(U.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));

	role=lookup_widget(objet_graphique, "comboboxentry_aj_role_WT");
	strcpy(U.role,gtk_combo_box_get_active_text(GTK_COMBO_BOX (role)));

	cin=lookup_widget(objet_graphique, "entry_aj_cin_WT");
	strcpy(U.cin,gtk_entry_get_text(GTK_ENTRY(cin)));

	tele=lookup_widget(objet_graphique, "entry_aj_tele_WT");
	strcpy(U.tele,gtk_entry_get_text(GTK_ENTRY(tele)));

	id=lookup_widget(objet_graphique, "entry_aj_id_WT");
	strcpy(U.id,gtk_entry_get_text(GTK_ENTRY(id)));
	

	mdp=lookup_widget(objet_graphique, "entry_aj_mdp_WT");
	strcpy(U.mdp,gtk_entry_get_text(GTK_ENTRY(mdp)));

	//sexe

	if(sexe==1)
	{strcpy(U.sexe,"Homme");}
	else if(sexe==2){strcpy(U.sexe,"Femme");}


	//date de naissance

	GtkWidget *JourN;
	GtkWidget *MoisN;
	GtkWidget *AnneeN;
	JourN=lookup_widget (objet_graphique, "spinbutton_aj_jour_naissance_WT");
	MoisN=lookup_widget (objet_graphique, "spinbutton_aj_mois_naissance_WT");
	AnneeN=lookup_widget(objet_graphique, "spinbutton_aj_annee_naissance_WT");

	JN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (JourN));
	MN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (MoisN));
	AN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (AnneeN));
	sprintf(U.DN.jour,"%d",JN);
	sprintf(U.DN.mois,"%d",MN);
	sprintf(U.DN.annee,"%d",AN);

	//date de recrutement

	GtkWidget *JourR;
	GtkWidget *MoisR;
	GtkWidget *AnneeR;
	JourR=lookup_widget (objet_graphique, "spinbutton_aj_jour_recrut_WT");
	MoisR=lookup_widget (objet_graphique, "spinbutton_aj_mois_recrut_WT");
	AnneeR=lookup_widget(objet_graphique, "spinbutton_aj_annee_recrut_WT");

	JR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (JourR));
	MR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (MoisR));
	AR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (AnneeR));
	sprintf(U.DR.jour,"%d",JR);
	sprintf(U.DR.mois,"%d",MR);
	sprintf(U.DR.annee,"%d",AR);

	ajouter_user(U);
}


void
on_button_mod_annuler_WT_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *administrateur_window;
	administrateur_window = lookup_widget(objet_graphique,"administrateur_window");
	gtk_widget_destroy(administrateur_window);

	
	administrateur_window = create_administrateur_window ();
	gtk_widget_show (administrateur_window);	

}


void
on_radiobutton_mod_homme_WT_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
	sexe_mod = 1;
}


void
on_radiobutton_mod_femme_WT_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
	sexe_mod = 2;
}


void
on_button_mod_modif_WT_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

	user U;	
	user nouv;
	int JN,MN,AN;
	int JR,MR,AR;

	GtkWidget *nom;
	GtkWidget *prenom;
	GtkWidget *role;
	GtkWidget *cin;
	GtkWidget *tele;
	GtkWidget *id;
	GtkWidget *mdp;

    nom = lookup_widget(objet_graphique, "entry_mod_nom_WT");
	strncpy(nouv.nom,gtk_entry_get_text(GTK_ENTRY(nom)), 30);

	prenom=lookup_widget(objet_graphique, "entry_mod_prenom_WT");
	strncpy(nouv.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)), 30);

	role=lookup_widget(objet_graphique, "comboboxentry_mod_role_WT");
	strncpy(nouv.role,gtk_combo_box_get_active_text(GTK_COMBO_BOX (role)), 20);

	cin=lookup_widget(objet_graphique, "entry_mod_cin_WT");
	strncpy(nouv.cin,gtk_entry_get_text(GTK_ENTRY(cin)), 20);

	tele=lookup_widget(objet_graphique, "entry_mod_tele_WT");
	strncpy(nouv.tele, gtk_entry_get_text(GTK_ENTRY(tele)), 20);

	id=lookup_widget(objet_graphique, "entry_mod_id_WT");
	strncpy(nouv.id,gtk_entry_get_text(GTK_ENTRY(id)), 20);

	mdp=lookup_widget(objet_graphique, "entry_mod_mdp_WT");
	strncpy(nouv.mdp,gtk_entry_get_text(GTK_ENTRY(mdp)), 20);

	//sexe

	if (sexe_mod == 1) {
		strcpy(nouv.sexe,"Homme");
	}
	else if (sexe_mod == 2) {
		strcpy(nouv.sexe,"Femme");
	}


	//date de naissance

	GtkWidget *JourN;
	GtkWidget *MoisN;
	GtkWidget *AnneeN;
	JourN=lookup_widget (objet_graphique, "spinbutton_mod_jour_naissance_WT");
	MoisN=lookup_widget (objet_graphique, "spinbutton_mod_mois_naissance_WT");
	AnneeN=lookup_widget(objet_graphique, "spinbutton_mod_annee_naissance_WT");

	JN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (JourN));
	MN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (MoisN));
	AN=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (AnneeN));
	sprintf(nouv.DN.jour,"%d",JN);
	sprintf(nouv.DN.mois,"%d",MN);
	sprintf(nouv.DN.annee,"%d",AN);

	//date de recrutement

	GtkWidget *JourR;
	GtkWidget *MoisR;
	GtkWidget *AnneeR;
	JourR=lookup_widget (objet_graphique, "spinbutton_mod_jour_recrut_WT");
	MoisR=lookup_widget (objet_graphique, "spinbutton_mod_mois_recrut_WT");
	AnneeR=lookup_widget(objet_graphique, "spinbutton_mod_annee_recrut_WT");

	JR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (JourR));
	MR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (MoisR));
	AR=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (AnneeR));
	sprintf(nouv.DR.jour,"%d",JR);
	sprintf(nouv.DR.mois,"%d",MR);
	sprintf(nouv.DR.annee,"%d",AR);

	modifier_user(nouv);
}


void
on_treeview_liste_row_WT_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button_actualiser_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview_liste;
	treeview_liste=lookup_widget(objet_graphique,"treeview_liste_WT");

	afficher_user(treeview_liste);

	float pHomme, pFemme;
	char pourcentage_homme[10];
	char pourcentage_femme[10];

	pourcentage_user(&pHomme, &pFemme);

	sprintf(pourcentage_homme,"%.3f",pHomme);
	gtk_label_set_text(GTK_LABEL(lookup_widget(objet_graphique, "label_homme")), pourcentage_homme);

	sprintf(pourcentage_femme,"%.3f",pFemme);
	gtk_label_set_text(GTK_LABEL(lookup_widget(objet_graphique, "label_femme")), pourcentage_femme);

}


void
on_button_rechercher_WT_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
char role[20];
	GtkWidget *role_list = lookup_widget(objet_graphique, "comboboxentry_liste_role_WT");
	strncpy(role,gtk_combo_box_get_active_text(GTK_COMBO_BOX (role_list)),20);

	GtkWidget *treeview_liste = lookup_widget(objet_graphique,"treeview_liste_WT");
	chercher_user(treeview_liste, role);
}


void
on_button_Supprimer_WT_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *idsup;

   	idsup = lookup_widget(objet_graphique, "entry_sup_id_WT");
	strncpy(sup.id,gtk_entry_get_text(GTK_ENTRY(idsup)), 20);

	GtkWidget *Supprimer_window = create_Supprimer_window();
	gtk_widget_show(Supprimer_window);

}
void
on_treeview_liste_WT_row_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

	GtkTreeIter iter;
	gchar* nom;
	gchar* prenom;
	gchar* role ;
	gchar* cin;
	gchar* tele;
	gchar* sexe;
	gchar* dn_j;
	gchar* dn_m;
	gchar* dn_a;
	gchar* dr_j;
	gchar* dr_m;
	gchar* dr_a;
	gchar* id;
	gchar* mdp;
	user U;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		//obtention des valeurs de la ligne selectionnée
		gtk_tree_model_get (GTK_LIST_STORE(model), &iter, 0, &nom, 1, &prenom, 2, &role, 3, &cin, 4, &tele, 5, &sexe, 6, &dn_j, 7, &dn_m, 8, &dn_a, 9, &dr_j, 10, &dr_m, 11, &dr_a, 12, &id, 13,&mdp, -1);
		// Copie des valeurs dans la variable pdu type personne pour le passer à la fonction de suppression
		strcpy(U.nom, nom);
		strcpy(U.prenom, prenom);
		strcpy(U.role, role);
		strcpy(U.cin, cin);
		strcpy(U.tele, tele);
		strcpy(U.sexe, sexe);
		strcpy(U.DN.jour, dn_j);
		strcpy(U.DN.mois, dn_m);
		strcpy(U.DN.annee, dn_a);
		strcpy(U.DR.jour, dr_j);
		strcpy(U.DR.mois, dr_m);
		strcpy(U.DR.annee, dr_a);
		strcpy(U.id, id);
		strcpy(U.mdp,mdp);
	}


		// mise à jour de l'affichage de la treeview
		afficher_user(treeview);

} 


void
on_buttonDeconnectionETS_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *Login;
  GtkWidget *windowEspaceAdmin;
windowEspaceAdmin=lookup_widget(objet_graphique,"windowEspaceAdmin");
gtk_widget_destroy(windowEspaceAdmin);
Login = create_Login (); 
gtk_widget_show (Login);
}

