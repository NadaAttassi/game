#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Ajout de la biblioth�que pour la fonction strcpy
#include <gtk/gtk.h>


// *** Label
typedef struct
{
    GtkWidget* label; // Pointeur sur le widget de label
    gchar *text; // Le texte à afficher
    gchar *name; // Le nom du label
    gint selectable; // 1 Si selectable, Sinon par défaut false
    gint wrap; // 1: TRUE, Sinon par défaut false
    gint height; // Hauteur de label
    gint width; // Longueur de label
    gint x; // Coordonnée x du label
    gint y; // Coordonnée y du label
} LabelObj;


LabelObj* init_label(gchar* text, gchar *nom, gint selec, gint wrap, gint width, gint height, gint x, gint y)
{
    LabelObj *LO = (LabelObj*)malloc(sizeof(LabelObj));

    // Test d'allocation
    if (!LO)
    {
        printf("\nErreur d'allocation!!!!!!\n");
        exit(0);
    }

    // Allocation réussie
    LO->text = NULL;
    LO->name = NULL;

    // Texte
    if (text)
    {
        LO->text = (gchar*)malloc((strlen(text) + 1) * sizeof(gchar));
        if (LO->text)
            strcpy(LO->text, text);
        else
            printf("\nErreur d'allocation\n");
    }

    // Nom
    if (nom)
    {
        LO->name = (gchar*)malloc((strlen(nom) + 1) * sizeof(gchar));
        if (LO->name)
            strcpy(LO->name, nom);
        else
            printf("\nErreur d'allocation\n");
    }

    LO->selectable = selec;
    LO->wrap = wrap;
    LO->height = height;
    LO->width = width;
    LO->x = x; // Coordonnée x
    LO->y = y; // Coordonnée y
    LO->label = NULL;

    return LO;
}


void create_label22(LabelObj *LO)
{
    // Label
    LO->label = gtk_label_new(LO->text);

    // Nom (si disponible)
    if (LO->name != NULL)
        gtk_widget_set_name(GTK_WIDGET(LO->label), LO->name);

    // Selectable
    if (LO->selectable == 1)
        gtk_label_set_selectable(GTK_LABEL(LO->label), TRUE);

    // Wrap
    if (LO->wrap == 1)
    {
        gtk_label_set_line_wrap(GTK_LABEL(LO->label), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(LO->label), PANGO_WRAP_WORD_CHAR);
    }
}
/*int main() {
    // Initialisation de GTK
    gtk_init(NULL, NULL);

    // Création de la fenètre
    windowz0bj myWindow;
    myWindow.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    myWindow.title = "Ma fenètre";
    myWindow.icon = NULL;
    myWindow.height = 300;
    myWindow.width = 400;
    myWindow.position = GTK_WIN_POS_CENTER;
    myWindow.posx = 0;
    myWindow.posy = 0;
    myWindow.resizable = TRUE;

    // Définition des caractéristiques de la fenètre
    gtk_window_set_title(GTK_WINDOW(myWindow.window), myWindow.title);
    gtk_window_set_default_size(GTK_WINDOW(myWindow.window), myWindow.width, myWindow.height);
    gtk_window_set_position(GTK_WINDOW(myWindow.window), myWindow.position);
    gtk_window_set_resizable(GTK_WINDOW(myWindow.window), myWindow.resizable);

    // Création du label
    LabelObj *myLabel = init_label("Hello, GTK!", "my_label", 1, 1, 200, 100);
    create_label(myLabel);

    // Ajout du label à la fenètre
    gtk_container_add(GTK_CONTAINER(myWindow.window), myLabel->label);

    // Affichage des éléments de la fenètre
    gtk_widget_show_all(myWindow.window);

    // Boucle principale GTK
    gtk_main();

    // Libération de la mémoire
    free(myLabel->text);
    free(myLabel->name);
    free(myLabel);

    return 0;
}*/
