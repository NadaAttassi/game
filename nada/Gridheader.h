#ifndef Grille_H_INCLUDED
#define Grille_H_INCLUDED

typedef struct {
    gchar* image; // Chemin d'accès de l'image
    guint width; // Largeur de l'image
    guint height; // Hauteur de l'image
    gdouble opacity; // Opacité de l'image
} Layout;

typedef struct c{
        gchar* couleur;
        gfloat degre;
} CL;
 typedef struct
 {
   GtkWidget *Grille; /// le conteneur Grille
   gchar* name; ///name du Grille
   guint width; ///longueur
   guint height; ///hauteur
   guint bordure; /// taille de bordure
   //CL bgCLor; ///background
   Layout imageBg; ///background image
 }Grille;

//Initialiser Grille
Grille* init_Grille(gchar* name, gint width, gint height, gint bordure,
        gfloat opc, gchar* imageBg, gint imgw, gint imgh)
{

    Grille* GO = NULL;
    ///Allocation memoire
    GO = (Grille*)malloc(sizeof(Grille)); ///test d'allocation
    if(!GO)
    {
         printf("\nErreur d'allocation !!!\n");
         exit(1);
    }


    GO->name=NULL;
    //GO->bgCLor.couleur = NULL;
    GO->imageBg.image = NULL; ///Si le name exist
    if(name)
    {
            GO->name = (gchar*)malloc(30*sizeof(gchar)); ///affectation si l'allocation a réussie
            if(GO->name) strcpy(GO->name, name);
             else printf("erreur de memoire");
    }

    ///Si le name de couleur du background exist
    /*if(bgCL)
    {
        GO->bgCLor.couleur = (gchar*)malloc(15* sizeof(gchar)); ///affectation si l'allocation a réussie
        if(GO->bgCLor.couleur)
        strcpy(GO->bgCLor.couleur,bgCL);
        else printf("erreur de memoire");
    }*/

    ///Si le chemin de l'image du background exist
     if(imageBg)
    {
        GO->imageBg.image = (gchar*)malloc(30*sizeof(gchar)); ///affectation si l'allocation a réussie
        if(GO->imageBg.image) strcpy(GO->imageBg.image, imageBg);
        else printf("erreur de memoire");

    }
    ///Affectation des valeurs
    GO->width=width;
    GO->height=height;
    GO->bordure=bordure;
    //GO->bgCLor.degre=opc;
    GO->imageBg.width=imgw;
    GO->imageBg.height=imgh;
    return (Grille*)GO;
}
// Fonction pour ajouter une image de fond
void add_imageBg(GtkWidget *grid, const char *filename) {
    // Création d'un widget pour l'image
    GtkWidget *imageWidget = gtk_image_new_from_file(filename);

    // Ajout de l'image au conteneur (grid)
    gtk_container_add(GTK_CONTAINER(grid), imageWidget);

    // Modification des propriétés de l'image pour la placer en arrière-plan
    gtk_widget_set_hexpand(imageWidget, TRUE);
    gtk_widget_set_vexpand(imageWidget, TRUE);
    gtk_widget_set_halign(imageWidget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(imageWidget, GTK_ALIGN_FILL);

    // Rafraîchissement de l'affichage
    gtk_widget_show_all(grid);
}
//Creer Grille
void create_Grille(Grille*G)
{

    //creation du Grille
    G->Grille=gtk_grid_new();
    //changement de la taille du Grille
    gtk_widget_set_size_request(G->Grille, G->width, G->height);
    //la bordure de Grille

    gtk_container_set_border_width(GTK_CONTAINER (G->Grille), G->bordure); //application du couleur du background s'il exist
    //if(G->bgCLor.couleur)

    //add_bgcolor(G->Grille, G->bgCLor.couleur, G->bgCLor.degre);
     //application d'image du background s'elle exist
    /*if (G->imageBg.image != NULL)
    add_imageBg(G->Grille, G->imageBg.image);
*/
    if(G->name) gtk_widget_set_name(G->Grille, G->name);
}

//Ajouter le child au Grille
void ajout_au_Grille(GtkWidget* widget_parent, GtkWidget* child,gint X, gint Y)
{
        // Ajouter l'élément au conteneur Grid à la position spécifiée
    gtk_grid_attach(GTK_GRID(widget_parent), child, X, Y, 1, 1);
}
#endif // Grille_H_INCLUDED
