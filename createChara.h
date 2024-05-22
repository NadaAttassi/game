#ifndef CREATECHARA_H_INCLUDED
#define CREATECHARA_H_INCLUDED

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "nada/windowboxscroll.h"
#include "nada/Gridheader.h"
#include "nada/label.h"
#include "nada/ButtonSimpleheader.h"
#include "nada/EntryHeader.h"
#include "nada/imageHeader.h"


#define TOTAL_POINTS 100
#define NUM_PlayerISTICS 4
  // Create player data

Box *photo_area ;// Déclaration de la variable globale
GtkWidget *current_photo_widget = NULL;
GtkWidget *main_box = NULL;

typedef struct {
    GtkWidget *sliders[NUM_PlayerISTICS];
    GtkWidget *remaining_points_label;
    int remaining_points;
} PlayerOptions;

// Structure to hold player data
/*
typedef struct {
    int id;
    const char *name;
    const char *imageURL;
    const char *spriteSheet;
    int PV;
    int Attack;
    int Defense;
    int speed;
    const char *specialCapacity;
} Player;*/
Player* player=NULL;
typedef struct {
    GtkWidget *entry;
    Window *window;
} CallbackData;

typedef struct {
    const gchar *name;
    int value;
} Playeristic;

typedef struct {
    gchar* grp;
    gchar* name;
} infos;

GList *button_groups = NULL;

typedef struct {
    const gchar *ancienNom;
    gchar *nouveauNom;
} Noms;

Noms *noms = NULL;

void apply_label_style(GtkWidget *label) {
    PangoAttrList* attrList = pango_attr_list_new();
    PangoAttribute* attr;

    attr = pango_attr_family_new("arial");
    pango_attr_list_insert(attrList, attr);

    attr = pango_attr_size_new(16 * PANGO_SCALE);
    pango_attr_list_insert(attrList, attr);

    GdkRGBA color;
    gdk_rgba_parse(&color, "#ffd55c");
    attr = pango_attr_foreground_new(color.red * 65535, color.green * 65535, color.blue * 65535);
    pango_attr_list_insert(attrList, attr);

    gtk_label_set_attributes(GTK_LABEL(label), attrList);
    pango_attr_list_unref(attrList);
}
void modifier(GtkButton *button, gpointer data) {
    GtkWidget *label = GTK_WIDGET(data);
    const gchar *ancienNom = gtk_label_get_text(GTK_LABEL(label));

    GtkWidget *dialog = gtk_dialog_new_with_buttons("Modifier le nom",
                                                     GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                     GTK_DIALOG_MODAL,
                                                     "OK",
                                                     GTK_RESPONSE_OK,
                                                     "Annuler",
                                                     GTK_RESPONSE_CANCEL,
                                                     NULL);

    // Appliquer un ID au dialog pour le styliser
    gtk_widget_set_name(dialog, "dialog");

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), ancienNom);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // Appliquer un ID au entry pour le styliser
    gtk_widget_set_name(entry, "dialog-entry");

    // Montrer tous les widgets
    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK) {
        const gchar *nouveauNom = gtk_entry_get_text(GTK_ENTRY(entry));
        gtk_label_set_text(GTK_LABEL(label), nouveauNom);
        player->name = strdup(nouveauNom);
    }

    gtk_widget_destroy(dialog);
}


void update_remaining_points_label(PlayerOptions *options) {
    gchar label_text[64];
    g_snprintf(label_text, sizeof(label_text), "Remaining Points: %d", options->remaining_points);
    gtk_label_set_text(GTK_LABEL(options->remaining_points_label), label_text);
}

void on_slider_value_changed(GtkRange *range, gpointer user_data) {
    PlayerOptions *options = (PlayerOptions *)user_data;
    int total_allocated = 0;
    printf("\nEntered on_slider_value_changed");

    // Calculate the total allocated points
    for (int i = 0; i < NUM_PlayerISTICS; ++i) {
        total_allocated += (int)gtk_range_get_value(GTK_RANGE(options->sliders[i]));
    }
    printf("\nTotal allocated points: %d", total_allocated);

    // Update remaining points
    options->remaining_points = TOTAL_POINTS - total_allocated;
    printf("\nRemaining points: %d", options->remaining_points);
    update_remaining_points_label(options);

    // Adjust sliders based on remaining points
    int adjustment = options->remaining_points < 0 ? -options->remaining_points : 0;
    if (adjustment != 0) {
        printf("\nAdjusting sliders by: %d", adjustment);
    }

    for (int i = 0; i < NUM_PlayerISTICS; ++i) {
        double value = gtk_range_get_value(GTK_RANGE(options->sliders[i])) - adjustment;
        gtk_range_set_value(GTK_RANGE(options->sliders[i]), value);
    }
    printf("\nSliders adjusted");

      // Ensure player is allocated before updating
    if (player == NULL) {
        fprintf(stderr, "\nError: player is NULL. Allocating memory now.");
        player = (Player*)malloc(sizeof(Player));
        if (player == NULL) {
            fprintf(stderr, "\nFailed to allocate memory for player");
            exit(1);
        }
        // Optionally initialize player fields to default values
        player->PV = 0;
        player->Attack = 0;
        player->Defense = 0;
        player->speed = 0;
    }

    // Mettre à jour les caractéristiques du joueur à partir des curseurs
    player->PV = (int)gtk_range_get_value(GTK_RANGE(options->sliders[2]));
    player->Attack = (int)gtk_range_get_value(GTK_RANGE(options->sliders[1]));
    player->Defense = (int)gtk_range_get_value(GTK_RANGE(options->sliders[0]));
    player->speed = (int)gtk_range_get_value(GTK_RANGE(options->sliders[3]));
    printf("\nPlayer stats updated: name:%s PV=%d, Attack=%d, Defense=%d, Speed=%d",
           player->name,player->PV, player->Attack, player->Defense, player->speed);

    // example_function(); // Uncomment if needed
}
// Exemple d'utilisation des valeurs de la structure Player
void example_function() {
    // Utilisez les valeurs du joueur comme vous le souhaitez
    printf("PV du joueur : %d\n", player->name);
    printf("PV du joueur : %d\n", player->PV);
    printf("Attaque du joueur : %d\n", player->Attack);
    printf("Défense du joueur : %d\n", player->Defense);
    printf("Vitesse du joueur : %d\n", player->speed);
}
GtkWidget* create_slider(PlayerOptions *options) {
    GtkWidget *slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, TOTAL_POINTS, 1);
    g_signal_connect(slider, "value-changed", G_CALLBACK(on_slider_value_changed), options);
    return slider;
}

void load_css2() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    GError *error = NULL;

    if (!gtk_css_provider_load_from_path(provider, "nada/style.css", &error)) {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        return;
    }
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

// Fonction pour charger la grande photo du personnage sélectionné
void load_Player_photo(const gchar *photo_path) {
    // Charger la nouvelle photo dans le widget existant
    gtk_image_set_from_file(GTK_IMAGE(current_photo_widget), photo_path);
}
void Player_thumbnail_clicked(GtkWidget *widget, gpointer data) {
    Player *player_selected = (Player *)data;
     player->imageURL=player_selected->imageURL;
     player->spriteSheet=player_selected->spriteSheet;
    //player->name=player_selected->name;
    // Utilisez les données du joueur comme vous le souhaitez
    printf("ID: %d\n", player->id);
    printf("Nom: %s\n", player->name);
    printf("Chemin d'image: %s\n", player->imageURL);
      // Utilisez les valeurs du joueur comme vous le souhaitez
    printf("PV du joueur : %d\n", player->PV);
    printf("Attaque du joueur : %d\n", player->Attack);
    printf("Défense du joueur : %d\n", player->Defense);
    printf("Vitesse du joueur : %d\n", player->speed);

    load_Player_photo(player->imageURL);

    // Pas besoin de libérer la mémoire allouée pour les données du joueur
    // g_free((gpointer)data);
}

GtkWidget* create_Player_thumbnails(Player players[], int num_Players) {
    // Créer un conteneur pour les miniatures
    GtkWidget *thumbnails_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Ajouter des boutons de miniature pour chaque personnage
    for (int i = 0; i < num_Players; i++) {
        // Créer un bouton avec une étiquette pour le nom du personnage
        GtkWidget *button = gtk_button_new();
        GtkWidget *label = gtk_label_new(players[i].name);
        gtk_container_add(GTK_CONTAINER(button), label);

        // Connecter le signal "clicked" du bouton à la fonction de rappel Player_thumbnail_clicked
        g_signal_connect(button, "clicked", G_CALLBACK(Player_thumbnail_clicked), &players[i]);

        // Ajouter une marge en bas de chaque miniature
        gtk_widget_set_margin_bottom(button, 5);

        // Ajouter le bouton à la liste des miniatures
        gtk_box_pack_start(GTK_BOX(thumbnails_container), button, FALSE, FALSE, 0);
    }

    return thumbnails_container;
}


// Fonction pour créer ou mettre à jour le widget de la photo du personnage
GtkWidget *create_or_update_photo_widget(const gchar *photo_path) {
    // Vérifiez si le widget de photo existe déjà
    if (current_photo_widget != NULL) {
        // Si le widget existe, mettez à jour son chemin d'image
        gtk_image_set_from_file(GTK_IMAGE(current_photo_widget), photo_path);
    } else {
        // Si le widget n'existe pas, créez-le et chargez l'image
        current_photo_widget = gtk_image_new_from_file(photo_path);
    }
    // Retournez le widget de photo
    return current_photo_widget;
}
/*
void ok_button_clicked_create(GtkWidget *widget, gpointer data) {
    CallbackData *callback_data = (CallbackData *)data;
    GtkWidget *entry = callback_data->entry;
    Window *myWindow = callback_data->window;

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("Texte de l'entrée : %s\n", text);



// Ensure player is allocated
    if (player == NULL) {
        player = (Player *)malloc(sizeof(Player));
        if (player == NULL) {
            fprintf(stderr, "\nFailed to allocate memory for player");
            exit(1);
        }
        player->name = NULL;
        player->PV = 0;
        player->Attack = 0;
        player->Defense = 0;
        player->speed = 0;
    }

    // Free the existing name if necessary
    if (player->name != NULL) {
        free(player->name);
    }

    // Duplicate the entry text
    player->name = strdup(text);
    if (player->name == NULL) {
        fprintf(stderr, "\nFailed to allocate memory for player name");
        exit(1);
    }
    printf("db le nom :%s", player->name);

    GdkScreen *screen = gdk_screen_get_default();
    gint screen_width = gdk_screen_get_width(screen);
    gint screen_height = gdk_screen_get_height(screen);

    gchar* title = "Nouvelle fenêtre";
    gchar* icon = NULL;
    gint width = screen_width;
    gint height = screen_height;
    gint position = 1;
    gint x = 0;
    gint y = 0;
    gint resizable = 1;

    Window* myNewWindow = initializeWindow("f2", title, icon, height, width, position, x, y, resizable, NULL, "nada/temple.jpg", screen_width, screen_height);
    createWindow(myNewWindow);
    gtk_window_set_position(GTK_WINDOW(myNewWindow->window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(myNewWindow->window), TRUE);

    Grille* myGrid = init_Grille("maGrille", width, height, 5, 0, NULL, 0, 0);
    create_Grille(myGrid);
    gtk_container_add(GTK_CONTAINER(myNewWindow->window), myGrid->Grille);

    LabelObj* titre = init_label("CREATE YOUR Player", "lbl", 0, 1, 0, 0, 0, 0);
    create_label22(titre);
    ajout_au_Grille(myGrid->Grille, titre->label, 0, 0);

    Box *left_box = initializeBox("left-box", 'v', 1, 0, "#FAFAD2", 0.7);
    createBox(left_box);
    gtk_widget_set_size_request(left_box->box, 200, 600);
    ajout_au_Grille(myGrid->Grille, left_box->box, 0, 1);

    LabelObj* myLabel = init_label(text, "nom", FALSE, FALSE, 100, 20, 0, 12);
    create_label22(myLabel);

    GtkWidget *edit_name_button = gtk_button_new_with_label("Modifier le nom");
    noms = g_malloc(sizeof(Noms));
    noms->ancienNom = g_strdup(text);
    g_signal_connect(edit_name_button, "clicked", G_CALLBACK(modifier), myLabel->label);

    LabelObj* label_Defense = init_label("Defense", "lelabel", FALSE, FALSE, 100, 20, 0, 12);
    create_label22(label_Defense);
    LabelObj* label_Attack = init_label("Attaque", "lelabel", FALSE, FALSE, 100, 20, 0, 12);
    create_label22(label_Attack);
    LabelObj* label_PV = init_label("Vitalite", "lelabel", FALSE, FALSE, 100, 20, 0, 12);
    create_label22(label_PV);
    LabelObj* label_speed = init_label("Vitesse", "lelabel", FALSE, FALSE, 100, 20, 0, 12);
    create_label22(label_speed);

    PlayerOptions options;
    options.remaining_points = TOTAL_POINTS;
    options.remaining_points_label = gtk_label_new("Remaining Points: 100");
    gtk_widget_set_name(GTK_WIDGET(options.remaining_points_label), "remaining-points-label");

    addToBox(left_box->box, options.remaining_points_label, 0, 1, 1, 1);
    options.sliders[0] = create_slider(&options);
    options.sliders[1] = create_slider(&options);
    options.sliders[2] = create_slider(&options);
    options.sliders[3] = create_slider(&options);

    addToBox(left_box->box, options.sliders[0], 0, FALSE, FALSE, FALSE);
    addToBox(left_box->box, label_Defense->label, 0, FALSE, FALSE, FALSE);
    addToBox(left_box->box, options.sliders[1], 0, 1, 1, 1);
    addToBox(left_box->box, label_Attack->label, 0, FALSE, FALSE, FALSE);
    addToBox(left_box->box, options.sliders[2], 0, 1, 1, 1);
    addToBox(left_box->box, label_PV->label, 0, FALSE, FALSE, FALSE);
    addToBox(left_box->box, options.sliders[3], 0, 1, 1, 1);
    addToBox(left_box->box, label_speed->label, 0, FALSE, FALSE, FALSE);



    GtkWidget *edit_name_button1 = gtk_button_new_with_label("Edit Name Character");
    g_signal_connect(edit_name_button1, "clicked", G_CALLBACK(modifier), myLabel->label);

    addToBox(left_box->box, edit_name_button1, 0, FALSE, FALSE, 0);
    addToBox(left_box->box, myLabel->label, 0, 1, 1, 1);


         // Create the photo area and add it to the grid
        photo_area= initializeBox("photo-area", 'v', 1, 0, "", 0.7);

        createBox(photo_area);
        gtk_widget_set_size_request(photo_area->box, 400, 600);
        const gchar *photo_path = "nada/knight.png"; // Replace with the path to your default photo
        current_photo_widget = create_or_update_photo_widget(photo_path);
         addToBox(photo_area->box, current_photo_widget, 0, 1, 1, 1);
        //ajout_au_Grille(myGrid->Grille, photo_area->box, 2, 1);


         Player players[] = {
        {1, "knight", "nada/knight.png", NULL, 0, 0, 0, 0, NULL},
        {2, "Lightning mage", "nada/mage.png", NULL, 0, 0, 0, 0, NULL},
        {3, "samurai", "nada/samurai.png", NULL, 0, 0, 0, 0, NULL},
        {4, "commander", "nada/commander.png", NULL, 0, 0, 0, 0, NULL},
        {5, "magician", "nada/magician.png", NULL, 0, 0, 0, 0, NULL},
        {6, "knight2", "nada/knight2.png", NULL, 0, 0, 0, 0, NULL}
    };
               // Create the Player thumbnails and add them to the grid
        GtkWidget *thumbnails_container = create_Player_thumbnails(players, 6);
        gtk_widget_set_name(thumbnails_container, "thumbnails-container");

        // Attach thumbnails_container to the grid
       // gtk_grid_attach(GTK_GRID(container), thumbnails_container, 1, 0, 1, 1); // position (1,0), spanning 1 cell

       // ajout_au_Grille(myGrid->Grille, thumbnails_container, 5, 1);

        // Création d'un bouton simple
       ButtonSimple* play_btn = init_button_simple("start", "Play",NULL, 10,10, "arial", "black","", FALSE, TRUE, 1000, 190);
       creer_button_Simple(play_btn);
      // ajout_au_Grille(myGrid->Grille,simpleButton->button,simpleButton->x,simpleButton->y);

       // Création du conteneur grid
    GtkWidget *container = gtk_grid_new();
     gtk_widget_set_name(container, "container");
    // Ajout de photo_area au conteneur grid
    gtk_grid_attach(GTK_GRID(container), photo_area->box, 0, 0, 1, 1); // position (0,0), spanning 1 cell

    // Ajout des vignettes des joueurs au conteneur grid
    gtk_grid_attach(GTK_GRID(container), thumbnails_container, 1, 0, 1, 1); // position (1,0), spanning 1 cell

    // Ajout du bouton au conteneur grid
    gtk_grid_attach(GTK_GRID(container), play_btn->button, 1, 1, 1, 1); // position (1,1), spanning 1 cell

    // Ajout du conteneur grid à la grille
    ajout_au_Grille(myGrid->Grille, container, 2, 1);

// Assurez-vous de libérer la mémoire si nécessaire


//    g_signal_connect(simpleButton->button, "clicked", G_CALLBACK(ok_button_clicked_create), callback_data);
        load_css2();
    g_signal_connect(button_start, "clicked", G_CALLBACK(create_images_window), NULL);

    // Ajoutez le bouton "Exit"
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    // Ajout du conteneur grid à la grille
    ajout_au_Grille(myGrid->Grille, button_exit, 2, 2);
    // Show the new window
    gtk_widget_show_all(myNewWindow->window);

    gtk_widget_destroy(myWindow->window);

    // Start a new GTK main loop for the new window
    gtk_main();
}




void ok_button_clicked_create_delete(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_destroy(window);
}
int create() {


          // Création de la fenêtre principale
        gchar* title = "Nom du personnage";
        gchar* icon = NULL;
        gint height = 200;
        gint width = 400;
        gint position = 1; // Position centrale
        gint x = 0;
        gint y = 0;
        gint resizable = 0; // Redimensionnable

        // Initialisation de la fenêtre principale
        Window* myWindow = initializeWindow("f1",title, icon, height, width, position, x, y, resizable, NULL, "image.jpeg", 100, 100);
        createWindow(myWindow);
        // Positionner la fenêtre au centre de l'écran
        gtk_window_set_position(GTK_WINDOW(myWindow->window), GTK_WIN_POS_CENTER);

        // Laisser les icônes désactivées
        gtk_window_set_icon(GTK_WINDOW(myWindow->window), NULL);
        // Rendre la fenêtre modale
        gtk_window_set_modal(GTK_WINDOW(myWindow->window), TRUE);

        Grille* myGrid = init_Grille("maGrille", 400, 200, 5, 0, NULL, 100, 100);
                create_Grille(myGrid);
  gtk_container_add(GTK_CONTAINER(myWindow->window), myGrid->Grille);
 // Création du conteneur de défilement
       // Scroll* sc = initializeScroll(myWindow->window, myGrid->Grille, 30, 0, 0); // Le premier argument est NULL car le conteneur parent sera défini plus tard
        //createScroll(sc);

        // Création et initialisation du label
   // Création et initialisation du label
        LabelObj* myLabel = init_label("Veuillez choisir le nom du personnage", "mon_label", FALSE, FALSE, 100, 20, 0, 10);
        create_label22(myLabel);

        // Appliquer le style au label
        apply_label_style(myLabel->label);

    ajout_au_Grille(myGrid->Grille,myLabel->label,myLabel->x,myLabel->y);
    //image

    imageObj* img=init_img("golden.png",400,400);
    create_image(img);
   ajout_au_Grille(myGrid->Grille,img->image,0,0);
    //ENTRY

     EntryObj* entry= init_entry ("Nom du personnage...",NULL, 1,0,10,40,0,14);
     create_entry(entry);
     ajout_au_Grille(myGrid->Grille,entry->entry ,entry->x,entry->y);
        // Chemin vers l'icône
  // const gchar *icon_path = "icon.png";
    CallbackData *callback_data = g_new(CallbackData, 1);
    callback_data->entry = entry->entry;
    callback_data->window = myWindow;


    // Création d'un bouton simple
   ButtonSimple* simpleButton = init_button_simple("mon_bouton", "OK",NULL, 10,10, "arial", "","white", FALSE, TRUE, 0, 190);
   creer_button_Simple(simpleButton);
  // ajout_au_Grille(myGrid->Grille,simpleButton->button,simpleButton->x,simpleButton->y);

   ajout_au_Grille(myGrid->Grille, simpleButton->button,simpleButton->x,simpleButton->y);

    g_signal_connect(simpleButton->button, "clicked", G_CALLBACK(ok_button_clicked_create), callback_data);

       //*******************************
    // Connexion de l'événement de fermeture de la fenêtre principale
    g_signal_connect(myWindow->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage de la fenêtre principale et démarrage de la boucle GTK
    gtk_widget_show_all(myWindow->window);
  //
// gtk_widget_show(myDialog->dialog);

    gtk_main();
 // Libération de la mémoire allouée
    if (myWindow) {
        g_free(myWindow->title);
        g_free(myWindow->icon);
        free(myWindow);
    }

    if (simpleButton) {
        g_free(simpleButton->name);
        g_free(simpleButton->label);
        free(simpleButton);
    }

         // Libération de la mémoire allouée pour le label
    if (myLabel) {
        if (myLabel->text)
            g_free(myLabel->text);
        if (myLabel->name)
            g_free(myLabel->name);
        free(myLabel);
    }
    if (myGrid) {
        g_free(myGrid->name);
        //if (myGrid->bgCLor.couleur)
           // g_free(myGrid->bgCLor.couleur);
        if (myGrid->imageBg.image)
            g_free(myGrid->imageBg.image);
        free(myGrid);
    }

 return 0;
}
*/

#endif // CREATECHARA_H_INCLUDED
