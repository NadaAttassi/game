#include <gtk/gtk.h>
#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED


typedef struct
{
    gchar text[200];
    guint alignement;/* L'alignement du texte
    1: GTK_JUSTIFY_LEFT pour aligner le texte � gauche (par d�faut);
    2: GTK_JUSTIFY_RIGHT pour aligner le texte � droite ;
    3: GTK_JUSTIFY_CENTER pour centrer le texte ;
    4:GTK_JUSTIFY_FILL pour justifier�le�texte*/
    gint w; // Largeur
    gint h; // Hauteur
    gchar police[30];//Pour definir la police utils�e*/
    gint taille_text;/* Pour definir la taille du texte*/
    gchar style[15];//Pour definir le style du texte*/
    gchar epaisseur[15]; /*Pour definir l'epaisseur du texte : small , large , Xlaarge... */
    gchar couleur_text[15];//Pour definir la couleur du texte*/
    gchar couleur_fond[15];//Pour definir la couleur du fond*/
    gchar underline[15];/* Pour le soulignement du texte*/
    gboolean line_through; //Pour barrer le texte/

}texte;

// Fonction pour initialiser une structure texte
texte *initialiser_texte(gint w, gint h, gchar lb[200], guint alg, gchar police[30], gint size, gchar styl[15], gchar epaisseur[15], gchar couleur[15], gchar background[15], gchar underline[15])
{
    // Allouer dynamiquement de la m�moire pour une nouvelle structure texte
    texte *tex = (texte *)g_malloc(sizeof(texte));

    // Copier le texte pass� en param�tre dans la structure texte
    strcpy(tex->text, lb);

    // Si alg est non nul, utiliser sa valeur, sinon, utiliser 1 (GTK_JUSTIFY_LEFT) par d�faut
    tex->alignement = (alg != 0) ? alg : 1;

    // Si une police est sp�cifi�e, l'utiliser, sinon, utiliser "Sans" par d�faut
    if (police)
        strcpy(tex->police, police);
    else
        strcpy(tex->police, "Sans");

    // Si une taille de texte est sp�cifi�e, l'utiliser, sinon, utiliser 10 par d�faut
    if (size)
        tex->taille_text = size;
    else
        tex->taille_text = 10;

    // Si un style est sp�cifi�, l'utiliser, sinon, utiliser "normal" par d�faut
    if (styl)
        strcpy(tex->style, styl);
    else
        strcpy(tex->style, "normal");

    // Si une couleur de texte est sp�cifi�e, l'utiliser, sinon, utiliser "#000000" (noir) par d�faut
    if (couleur)
        strcpy(tex->couleur_text, couleur);
    else
        strcpy(tex->couleur_text, "#000000");

    // Si un soulignement est sp�cifi�, l'utiliser, sinon, utiliser "none" par d�faut
    if (underline)
        strcpy(tex->underline, underline);
    else
        strcpy(tex->underline, "none");

    // Initialiser la structure style � partir des valeurs de largeur (w) et hauteur (h)
    tex->w = w;
    tex->h = h;

    // Renvoyer un pointeur vers la structure texte nouvellement cr��e
    return tex;
}

// Fonction pour appliquer un style � un �l�ment GTK en fonction d'un type donn�
GtkWidget *style_texte(GtkWidget *element, texte *text, gint type)
{
    gchar *sUtf8; // Cha�ne de caract�res pour le formatage du texte en UTF-8

    // Utiliser un commutateur (switch) pour g�rer diff�rents types d'�l�ments GTK
    switch (type)
    {
        case 1: // Cas o� l'�l�ment est un label (GTK_LABEL)
            element = gtk_label_new(NULL);

            // Formater le texte avec les propri�t�s sp�cifi�es dans la structure texte
            sUtf8 = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ",
                                    text->taille_text, text->style, text->couleur_text, text->police, text->underline, text->text);

            // Appliquer le texte format� au label
            gtk_label_set_markup(GTK_LABEL(element), sUtf8);

            // Lib�rer la m�moire allou�e pour la cha�ne sUtf8
            g_free(sUtf8);
            break;

            // Ajouter d'autres cas pour d'autres types d'�l�ments GTK si n�cessaire

    }

    // Renvoyer l'�l�ment GTK avec le style appliqu�
    return element;
}



/**********************************************************************************************************/

// Structure pour repr�senter une �tiquette avec un texte stylis�
typedef struct Label_et
{
    GtkWidget *widget;    /// Pointeur vers le widget du label
    GtkWidget *pere;      /// Pointeur vers le parent du label
    texte *text;          /// Texte du label
    gboolean selectable;  /// Indique si le texte peut �tre s�lectionn�
    gboolean wrap;        /// Indique si le texte peut �tre coup� en lignes
} Etiquette;

// Fonction pour initialiser une �tiquette (label) avec un texte stylis�
Etiquette *initialiser_label(GtkWidget *parent, texte *stext, gboolean select, gboolean coupe)
{
    // Allouer dynamiquement de la m�moire pour une nouvelle �tiquette
    Etiquette *label = (Etiquette *)g_malloc(sizeof(Etiquette));

    // Initialiser les champs de la structure Etiquette
    label->widget = gtk_label_new(NULL); // Cr�er un nouveau widget label
    label->pere = parent; // Stocker le widget parent
    label->text = stext; // Stocker le texte � afficher
    label->widget = style_texte(label->widget, label->text, 1); // Appliquer le style au label
    label->selectable = select; // Indiquer si le texte peut �tre s�lectionn�
    gtk_label_set_selectable(GTK_LABEL(label->widget), label->selectable);
    label->wrap=coupe;
    gtk_label_set_line_wrap(GTK_LABEL(label->widget), label->wrap);

    // Renvoyer un pointeur vers la structure Etiquette nouvellement cr��e
    return label;
}

void add_label(GtkWidget *pere,texte *text,gboolean selectable,gboolean wrap,gint x,gint y)
{
    Etiquette *label=initialiser_label(pere,text,selectable,wrap);
    gtk_fixed_put(GTK_FIXED(pere),label->widget,x,y);
    if(label->text->h && label->text->w)
        gtk_widget_set_size_request(label->widget,label->text->w,label->text->h);

}



#endif // LABEL_H_INCLUDED
