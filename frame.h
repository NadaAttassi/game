#include <gtk/gtk.h>
#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include "label.h"

// Structure pour repr�senter un cadre (frame) avec des �l�ments associ�s
typedef struct
{
    GtkWidget *widget;          // Le widget GTK repr�sentant le cadre
    GtkWidget *parent;          // Le parent du cadre
    gint xligne;                // Position horizontale de l'�tiquette dans le cadre
    gint yligne;                // Position verticale de l'�tiquette dans le cadre
    texte *text;                // Structure de texte associ�e au cadre
    GtkWidget *conteneur;       // Le conteneur associ� au cadre (peut �tre un label ou autre)
    GtkShadowType type;         // Type d'ombre du cadre
} frame;

// Fonction pour initialiser une structure de cadre avec des param�tres sp�cifi�s
frame *initialiser_frame(GtkWidget *pere, gint x, gint y, texte *t, GtkWidget *fils, GtkShadowType type)
{
    // Allouer dynamiquement la m�moire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs sp�cifi�es
    fr->widget = gtk_frame_new(NULL);
    fr->text = t;
    fr->parent = pere;
    fr->type = type;
    fr->xligne = x;
    fr->yligne = y;
    fr->conteneur = fils;

    // Retourner la structure de cadre initialis�e
    return fr;
}

// Fonction pour cr�er un cadre en utilisant les param�tres sp�cifi�s dans la structure
void creer_frame(frame *fr)
{
    // Cr�er une cha�ne de caract�res format�e pour l'�tiquette avec des propri�t�s de texte sp�cifi�es
    gchar *lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->text);

    // Cr�er un widget de label GTK et d�finir son contenu avec la cha�ne format�e
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

    // D�finir le label comme �tiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);

    // Assigner le label au conteneur du cadre
    fr->conteneur = label;

    // Si des positions sp�cifi�es, les appliquer � l'�tiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre sp�cifi�, l'appliquer au cadre
    if (fr->type)
        gtk_frame_set_shadow_type(GTK_FRAME(fr->widget), fr->type);
}

frame * add_frame(GtkWidget *pere,gfloat xligne,gfloat yligne,texte *tx,GtkWidget *fils,GtkShadowType type,gint x,gint y)
{
    frame *fr=initialiser_frame(pere,xligne,yligne,tx,fils,type);
    creer_frame(fr);
    gtk_fixed_put(GTK_FIXED(pere),fr->widget,x,y);
    return fr;
}



#endif // FRAME_H_INCLUDED
