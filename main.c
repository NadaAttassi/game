#include <gtk/gtk.h>
#include "arena.h"
#include "menuarena.h"
#include "gtk_utils.h"
#include "window.h"
#include "image.h"
#include "createChara.h"
//'a' key: Attacking
//'h' key: Hurting
//'d' key: Dying
//'w' key: Walking
//'r' key: Running
//'s' key: Standing



#define SPRITE_WIDTH (256)
#define SPRITE_HEIGHT (2560/10)
#define NUM_STANDING_FRAMES 6
#define NUM_WALKING_FRAMES 8
#define NUM_RUNNING_FRAMES 8
#define NUM_ATTACKING1_FRAMES 4
#define NUM_ATTACKING2_FRAMES 5
#define NUM_ATTACKING3_FRAMES 4
#define NUM_DEFENDING_FRAMES 2
#define NUM_JUMPING_FRAMES 8
#define NUM_HURTING_FRAMES 3
#define NUM_DYING_FRAMES 6
//PARTIE KHALID***************************************************************
GtkImage *gladiator_image;
GdkPixbuf *sprite_sheet;
int current_frame = 0;
int current_action = 0;
int action_frames[] = {NUM_STANDING_FRAMES, NUM_WALKING_FRAMES, NUM_RUNNING_FRAMES, NUM_ATTACKING1_FRAMES, NUM_ATTACKING2_FRAMES,NUM_ATTACKING3_FRAMES ,NUM_DEFENDING_FRAMES,NUM_JUMPING_FRAMES,NUM_HURTING_FRAMES,NUM_DYING_FRAMES};
int gladiator_x = 0; // Initial position of the gladiator
void on_images_start_button_clickedd(GtkWidget *widget, gpointer data);
GtkWidget *life_image_player1; // Image widget for player 1 life
GtkWidget *life_image_player2; // Image widget for player 2 life
GtkWidget *time_image;
GtkWidget *table_time_image;



GtkWidget *button_start;
GtkWidget *button_create;
GtkWidget *button_exit;
GtkWidget *button_help;



// Global variable to store the selected player
Player *selected_player = NULL;

//---------------------------------------------------

GtkWidget* create_button(const char *label, const char *css_name) {
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_widget_set_name(button, css_name);
    return button;
}

// Function to create labels
GtkWidget* create_label(const char *text, const char *font_desc_str, const char *color_str) {
    GtkWidget *label = gtk_label_new(text);
    PangoFontDescription *font_desc = pango_font_description_from_string(font_desc_str);
    gtk_widget_override_font(label, font_desc);
    GdkRGBA color;
    gdk_rgba_parse(&color, color_str);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color);
    return label;
}

// Function to set CSS styles
void set_css_styles() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    const char *css_data =
            " button {"
            "   border: 1px solid #7c7c7c;"
            "   border-radius: 15px;"
            "   font: Ranger Eastwood 36;"
            "   color: #543c1c;"
            "   background-color: #e4d3aa;"
            "   background-image: none;"
            "   min-width: 220px;"
            "   text-align: center;"
            "   padding: 10px 20px;"
            "}"
            " button:hover {"
            "   background-color: #fff7d7;"
            "   color: #ffffff;"
            "}"
            " button:hover:active {"
            "   background-color: #e8a154;"
            "   color: #ffffff;"
            "}"
            " button#custom-button-player1, button#custom-button-player2, button#custom-button-player3 {"
            "   border-color: #00ff00;"
            "   min-width: 150px;"
            "   padding: 5px 10px;"

            "}"
            " button#pause_button {"
            "   border: 5px solid #7c7c7c;"
            "   border-radius: 10%;"
            "   font: Ranger Eastwood 24;"
            "   color: #543c1c;"
            "   background-color: #e4d3aa;"
            "   background-image: none;"
            "   min-width: 55px;"
            "   min-height: 55px;"
            "   text-align: center;"
            "   padding: 2px 2px;"
            "}"
            ;

    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}
gchar* selected_arena="resourses\\Arena.png";
void on_images_start_button_click(GtkWidget *button, gpointer data) {
    selected_arena = (gchar *)data; // Update the selected_arena variable with the new path
    g_print("Selected arena path: %s\n", selected_arena);
}



//************************************************PARTIE IMANE***********************************************************
//ARENA THEME**************************
// Fonction principale
void create_images_window() {

    GdkScreen *screen = gdk_screen_get_default();
    gint screen_width = gdk_screen_get_width(screen);
    gint screen_height = gdk_screen_get_height(screen);

    // Utilisez une taille légèrement inférieure à celle de l'écran pour la fenêtre
    gint window_width = screen_width ;
    gint window_height = screen_height ;

    Fenetre *images_window = initialiser_win("Images Window", NULL, "Images_Window", NULL, window_width, window_height, 2, 0, 0, 1, TRUE);
    create_window(images_window);

    GtkWidget *fixed = gtk_fixed_new();
    add_child(images_window->window, fixed);

    // Add background image
    GtkWidget *background_image = gtk_image_new_from_file("bggg1.png");
    GdkPixbuf *bg_pixbuf = gdk_pixbuf_new_from_file("bggg1.png", NULL);
    GdkPixbuf *resized_t_pixbuf = gdk_pixbuf_scale_simple(bg_pixbuf, window_width, window_height, GDK_INTERP_BILINEAR);
    GtkWidget *t_image = gtk_image_new_from_pixbuf(resized_t_pixbuf);
    g_object_unref(bg_pixbuf); // Libère la mémoire du pixbuf original
    gtk_fixed_put(GTK_FIXED(fixed), background_image, 0, 0);

    // Load and resize table image
    GdkPixbuf *table_pixbuf = gdk_pixbuf_new_from_file("table4.png", NULL);
    GdkPixbuf *resized_table_pixbuf = gdk_pixbuf_scale_simple(table_pixbuf, 870, 600, GDK_INTERP_BILINEAR);
    GtkWidget *table_image = gtk_image_new_from_pixbuf(resized_table_pixbuf);
    g_object_unref(table_pixbuf); // Libère la mémoire du pixbuf original
    gtk_fixed_put(GTK_FIXED(fixed), table_image, window_width * 0.05, window_height * 0.05); // Ajustez la position si nécessaire

    // Ajoutez les quatre images au conteneur fixe
    add_image(fixed, 1, "arena7.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.2, window_height * 0.2);
    add_image(fixed, 1, "arena5.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.4, window_height * 0.2);
    add_image(fixed, 1, "arena6.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.2, window_height * 0.4);
    add_image(fixed, 1, "arena8.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.4, window_height * 0.4);

    // Ajoutez des boutons avec des noms pour le style CSS
    GtkWidget *button1 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button1, "custom-but");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_images_start_button_click), "arena7.png");
    gtk_fixed_put(GTK_FIXED(fixed), button1, window_width * 0.2, window_height * 0.3);

    GtkWidget *button2 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button2, "custom-but");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_images_start_button_click), "arena5.png");
    gtk_fixed_put(GTK_FIXED(fixed), button2, window_width * 0.4, window_height * 0.3);

    GtkWidget *button3 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button3, "custom-but");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_images_start_button_click), "arena9.png");
    gtk_fixed_put(GTK_FIXED(fixed), button3, window_width * 0.2, window_height * 0.5);

    GtkWidget *button4 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button4, "custom-but");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_images_start_button_click), "arena8.png");
    gtk_fixed_put(GTK_FIXED(fixed), button4, window_width * 0.4, window_height * 0.5);

    // Ajoutez le bouton "Start"
    GtkWidget *button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(on_images_start_button_clickedd), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button_start, 1000, 520);

    // Ajoutez le bouton "Exit"
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button_exit, 1000,600);

    show_window(images_window);
}



// Callback for the start button in the images window
void on_images_start_button_clickedd(GtkWidget *button_label, gpointer data) {
        // Add the logic you want to execute when the start button in the images window is clicked
         if(player) selected_player=player;
        if (selected_player) {
            g_print("Starting the game with %s\n", selected_player->name);
            run_game(selected_player); // Appelez run_game avec le joueur sélectionné
        } else {
            g_print("No player selected!\n");


        }
}
// Function to create a fixed container
GtkWidget *create_fixed() {
     return GTK_WIDGET(gtk_fixed_new());
}

// Function to update the background image
void update_background_image(GtkWidget *fixed, GtkWidget **background_image, const char *file_path) {
        if (*background_image) {
            gtk_widget_destroy(*background_image);
        }
        *background_image = gtk_image_new_from_file(file_path);
        gtk_fixed_put(GTK_FIXED(fixed), *background_image, 0, 0);
        gtk_widget_show(*background_image);
}
//FIN PARTIE IMANE


//PARTIE NADA****************
//********************************************CREATION DE PERSONNAGE*******************************************//
// Fonction de vérification des attributs du joueur avant de créer la fenêtre des images
void check_player_attributes(GtkWidget *button, gpointer data) {
        // Vérifiez si le joueur a été initialisé et que ses attributs sont > 0
        if (player == NULL || player->PV == 0 || player->Attack == 0 || player->Defense == 0 || player->speed == 0) {
            // Afficher une boîte de dialogue pour informer l'utilisateur
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Les attributs du joueur doivent etre superieurs a zero !");
                                                        // Définir la position de la boîte de dialogue au centre de l'écran
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return; // Arrêter l'exécution de la fonction si les attributs ne sont pas valides
        }

        // Si les attributs sont valides, appelez la fonction create_images_window
        create_images_window();
}

/*Fonction de creation d un personnage */
/*fenetre de creartion de personnage*/
//Creation de perso
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
            //gtk_window_set_modal(GTK_WINDOW(myNewWindow->window), TRUE);

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


            //    g_signal_connect(simpleButton->button, "clicked", G_CALLBACK(ok_button_clicked), callback_data);
                    load_css2();
            // Connectez d'abord le signal "clicked" du bouton à une fonction de vérification
            g_signal_connect(play_btn->button, "clicked", G_CALLBACK(check_player_attributes), NULL);


            // Show the new window
            gtk_widget_show_all(myNewWindow->window);

            gtk_widget_destroy(myWindow->window);

            // Start a new GTK main loop for the new window
            gtk_main();
}
int create_charachter() {


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

        imageObj* img=init_img("nada/golden.png",400,400);
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

//FIN PARTIE NADA**********************************************************************************************
//************************************************************************************************++




//PARTIE KHALID**************************************************************
// Function to play sound
void play_sound(const char *sound_file) {
    PlaySound(sound_file, NULL, SND_FILENAME | SND_ASYNC);
}



gboolean is_paused = FALSE;

// Global variable for the label widget
GtkWidget *time_label;



void toggle_pause(GtkWidget *widget, gpointer data) {
    is_paused = !is_paused;

    if (is_paused) {
        gtk_button_set_label(GTK_BUTTON(widget), "Play");
    } else {
        gtk_button_set_label(GTK_BUTTON(widget), "Pause");
    }
}


gboolean update_animation(gpointer data) {
    if (is_paused) {
        return TRUE;
    }
    // Calculate the coordinates of the current frame in the sprite sheet
    int x = (current_frame % action_frames[current_action]) * SPRITE_WIDTH;
    int y = current_action * SPRITE_HEIGHT;

    // Crop the sprite sheet to display only the current frame
    GdkPixbuf *frame = gdk_pixbuf_new_subpixbuf(sprite_sheet, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);

    // Update the image widget with the current frame
    gtk_image_set_from_pixbuf(gladiator_image, frame);
    gtk_fixed_move(GTK_FIXED(data), gladiator_image, gladiator_x, 450);

    // Increment the frame counter and loop back to the beginning if necessary
    current_frame++;
    if (current_frame >= action_frames[current_action]) {
        current_frame = 0;
    }



    // If the gladiator reaches the right edge of the arena, reset its position to the left
    if (!(gladiator_x >= 1900 - SPRITE_WIDTH)) {
        // Move the gladiator to the right
        if(current_action == 1){
            gladiator_x += 5;
        }
        else if( current_action == 2)
        {
            gladiator_x += 10;
        }
        else if( current_action == 7)
        {
            gladiator_x += 7;
        }
    }

    // Continue updating the animation
    return TRUE;
}

// Callback function to handle key press events
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_s:
            current_action = 0; // Standing
            break;
        case GDK_KEY_w:
            current_action = 1; // Walking
            break;
        case GDK_KEY_r:
            current_action = 2; // Running
            break;
        case GDK_KEY_a:
            current_action = 3; // Attacking 1
            break;
        case GDK_KEY_f:
            current_action = 4; // Attacking 2
            break;
        case GDK_KEY_g:
            current_action = 5; // Attacking 3
            break;
        case GDK_KEY_d:
            current_action = 6; // Defending
            break;
        case GDK_KEY_j:
            current_action = 7; // Jumping
            break;
        case GDK_KEY_h:
            current_action = 8; // Hurting
            break;
        case GDK_KEY_x:
            current_action = 9; // Dying
            break;
        default:
            return FALSE; // No action matched, do not reset the frame counter
    }
    // Reset the frame counter
    current_frame = 0;
    return TRUE;
}



// Function to update the time label
gboolean update_time_label(gpointer user_data) {
    if (is_paused) {
        return TRUE;
    }
    static int seconds = 0;

    // Calculate minutes and seconds
    int minutes = seconds / 60;
    int display_seconds = seconds % 60;

    // Create the time string
    char time_str[6];
    snprintf(time_str, sizeof(time_str), "%02d:%02d", minutes, display_seconds);

    // Update the label text
    gtk_label_set_text(GTK_LABEL(time_label), time_str);

    // Increment the seconds
    seconds++;

    // Return TRUE to keep the timeout running
    return TRUE;
}

void run_game(Player *player) {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Load the sprite sheet image
    sprite_sheet = gdk_pixbuf_new_from_file(player->spriteSheet, NULL);


    // Create the main window
    GdkPixbuf *arena_pixbuf = gdk_pixbuf_new_from_file(selected_arena, NULL);
    gint arena_width = gdk_pixbuf_get_width(arena_pixbuf);
    gint arena_height = gdk_pixbuf_get_height(arena_pixbuf);

    //GtkWidget *window = create_window("Sprite Animation",arena_width,arena_height);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Définir le titre de la fenêtre
    gtk_window_set_title(GTK_WINDOW(window), "Sprite Animation");

    // Définir la taille par défaut de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(window), arena_width, arena_height);

    // Connecter le signal "destroy" pour quitter l'application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect key press event to the window
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create a fixed container to hold the background image and gladiator image
    GtkWidget *fixed = create_fixed();

    // Update the background image
    GtkWidget *arena_image = NULL;
    update_background_image(fixed, &arena_image, selected_arena);

    // Create an image widget to display the sprite animation
    gladiator_image = GTK_IMAGE(gtk_image_new());
    gtk_widget_set_size_request(GTK_WIDGET(gladiator_image), SPRITE_WIDTH, SPRITE_HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(gladiator_image), gladiator_x+10, 0);

    // Create image widgets for player 1 and player 2 life
    life_image_player1 = gtk_image_new_from_file("resourses\\LifeBar.png");
    life_image_player2 = gtk_image_new_from_file("resourses\\LifeBar.png");


    time_image = gtk_image_new_from_file("resourses\\clock.png");
    table_time_image = gtk_image_new_from_file("resourses\\table.png");


    // Add the life images to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player1, 0, 0); // Adjust position as needed
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player2, arena_width - 375, 0);
    gtk_fixed_put(GTK_FIXED(fixed), table_time_image, arena_width / 2 - 160, 20);
    gtk_fixed_put(GTK_FIXED(fixed), time_image, arena_width / 2 - 200, 0);

    // Create a label for the text
    time_label = create_label("00:00", "Ranger Eastwood 24", "white");
    gtk_fixed_put(GTK_FIXED(fixed), time_label, arena_width / 2 - 90, 35);

    // Add the pause button
    GtkWidget *pause_button = create_button("Pause","pause_button");
    gtk_fixed_put(GTK_FIXED(fixed), pause_button, arena_width / 3 -10, 10);


    g_signal_connect(pause_button, "clicked", G_CALLBACK(toggle_pause), NULL);
    // Add the fixed container to the window
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Show the window
    gtk_widget_show_all(window);

    // Start the animation
    g_timeout_add(100, update_animation, fixed);

    // Start the time label update every second
    g_timeout_add_seconds(1, update_time_label, NULL);

    // Start playing the background music
//    play_sound("resourses\\prepare_yourself.wav");
//    Sleep(2000);
    play_sound("resourses\\GameMusic.wav");
    // Start the GTK main loop
    gtk_main();

}





// Callback for button click events
void on_select_button_clicked(GtkWidget *button, gpointer data) {
    Player *player = (Player *)data;
    selected_player = player;
    g_print("Selected player: %s\n", player->name);  // Print the selected player name for verification
}

void display_help_dialog() {
    GtkWidget *dialog;
    FILE *file;
    char help_text[1000000];  // Assuming the help text won't exceed 1000 characters

    // Open the help.txt file for reading
    file = fopen("help.txt", "r");
    if (file == NULL) {
        g_print("Error opening file!\n");
        return;
    }
    GtkWidget *scroll;
     char buffer[100];
    // Read the contents of the file into help_text
    help_text[0] = '\0';

    // Read the file line by line and append each line to help_text
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Concatenate the current line to help_text
        strcat(help_text, buffer);
    }

    // Close the file
    fclose(file);

    // Create a dialog with the help text as its content
    dialog = gtk_message_dialog_new(NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "%s",
                                     help_text);

    // Set the dialog title
    gtk_window_set_title(GTK_WINDOW(dialog), "Help");

    // Run the dialog
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Destroy the dialog
    gtk_widget_destroy(dialog);
}

void on_button_clicked(GtkWidget *button, gpointer data) {
    const char *button_label = gtk_button_get_label(GTK_BUTTON(button));
    if (g_strcmp0(button_label, "Start") == 0) {
        if (selected_player) {
            g_print("Starting the game with %s\n", selected_player->name);
            //run_game(selected_player);  // Call run_game with the selected player
            create_images_window(selected_player);
        } else {
            g_print("No player selected!\n");
        }
    } else if (g_strcmp0(button_label, "CREATE GLADIATOR") == 0) {
        g_print("Create Gladiator clicked\n");
          create_charachter();
        // Code to create a new gladiator
    } else if (g_strcmp0(button_label, "EXIT") == 0) {
        g_print("Exit clicked\n");
        gtk_main_quit();
    }  else if (g_strcmp0(button_label, "HELP") == 0) {
        // Code to display help dialog
        printf("ok a nada");
        display_help_dialog();
    }
}
void play_audio(const char *file_path) {
    // Open the audio file
    if (PlaySound(file_path, NULL, SND_FILENAME | SND_ASYNC) == 0) {
        // Error handling if the audio file fails to play
        printf("Error playing audio: %d\n", GetLastError());
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the character selection window
    //GtkWidget *window = create_window("Character Selection", 800, 600);
     GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Définir le titre de la fenêtre
    gtk_window_set_title(GTK_WINDOW(window), "Character Selection");

    // Définir la taille par défaut de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Connecter le signal "destroy" pour quitter l'application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Create a fixed container
    GtkWidget *fixed = create_fixed();
    GtkWidget *background_image = NULL;
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Set the initial background image
    update_background_image(fixed, &background_image, "bggg1.png");



    // Get the width and height of the background image
    GdkPixbuf *background_image_pixbuf = gdk_pixbuf_new_from_file("bggg1.png", NULL);
    gint background_image_width = gdk_pixbuf_get_width(background_image_pixbuf);
    gint background_image_height = gdk_pixbuf_get_height(background_image_pixbuf);

    // Create player data
    Player players[3] = {
            {1, "Samuri", "resourses\\vector1.png", "resourses\\Samurai_Spritelist.png",100, 50, 30, "Special 1"},
            {2, "Fire vizard", "resourses\\vector2.png", NULL,120, 40, 40, "Special 2"},
            {3, "Knight", "resourses\\vector3.png", NULL,80, 60, 20, "Special 3"}
    };

    // Create the player selection UI
    GtkWidget *list_cards = gtk_image_new_from_file("resourses\\list_card.png");
    gtk_fixed_put(GTK_FIXED(fixed), list_cards, 0, background_image_height / 10);


    GtkWidget *player1 = gtk_image_new_from_file(players[0].imageURL);
    GtkWidget *player2 = gtk_image_new_from_file(players[1].imageURL);
    GtkWidget *player3 = gtk_image_new_from_file(players[2].imageURL);

    gtk_fixed_put(GTK_FIXED(fixed), player1, 140, background_image_height / 3);
    gtk_fixed_put(GTK_FIXED(fixed), player2, background_image_width / 6 + 140, background_image_height / 3 );
    gtk_fixed_put(GTK_FIXED(fixed), player3, background_image_width / 3 + 140, background_image_height / 3 );



    GtkWidget *card_player1 = gtk_image_new_from_file("resourses\\Civilian_card.png");
    GtkWidget *card_player2 = gtk_image_new_from_file("resourses\\Civilian_card.png");
    GtkWidget *card_player3 = gtk_image_new_from_file("resourses\\Civilian_card.png");

    gtk_fixed_put(GTK_FIXED(fixed), card_player1, 100, background_image_height / 3 - 20);
    gtk_fixed_put(GTK_FIXED(fixed), card_player2, background_image_width / 6 + 100, background_image_height / 3 - 20);
    gtk_fixed_put(GTK_FIXED(fixed), card_player3, background_image_width / 3 + 100, background_image_height / 3 - 20);

    GtkWidget *player1_message = gtk_image_new_from_file("resourses\\message.png");
    GtkWidget *player2_message = gtk_image_new_from_file("resourses\\message.png");
    GtkWidget *player3_message = gtk_image_new_from_file("resourses\\message.png");

    gtk_fixed_put(GTK_FIXED(fixed), player1_message, 80, background_image_height / 4);
    gtk_fixed_put(GTK_FIXED(fixed), player2_message, background_image_width / 6 + 60, background_image_height / 4);
    gtk_fixed_put(GTK_FIXED(fixed), player3_message, background_image_width / 3 + 50, background_image_height / 4);


    GtkWidget *button_select_player1 = create_button("select", "custom-button-player1");
    GtkWidget *button_select_player2 = create_button("select", "custom-button-player2");
    GtkWidget *button_select_player3 = create_button("select", "custom-button-player3");

    gtk_fixed_put(GTK_FIXED(fixed), button_select_player1, 150, background_image_height - 280);
    gtk_fixed_put(GTK_FIXED(fixed), button_select_player2, background_image_width / 6 + 150, background_image_height - 280);
    gtk_fixed_put(GTK_FIXED(fixed), button_select_player3, background_image_width / 3 + 150, background_image_height - 280);

    g_signal_connect(button_select_player1, "clicked", G_CALLBACK(on_select_button_clicked), &players[0]);
    g_signal_connect(button_select_player2, "clicked", G_CALLBACK(on_select_button_clicked), &players[1]);
    g_signal_connect(button_select_player3, "clicked", G_CALLBACK(on_select_button_clicked), &players[2]);


    GtkWidget *message_player1 = create_label("Our destiny \n awaits us", "DRAGON HUNTER 12", "black");
    GtkWidget *message_player2 = create_label("Courage will \n guide us.", "DRAGON HUNTER 12", "black");
    GtkWidget *message_player3 = create_label("Faith leads \n the way.", "DRAGON HUNTER 12", "black");

    gtk_fixed_put(GTK_FIXED(fixed), message_player1, 100, background_image_height / 4 + 50);
    gtk_fixed_put(GTK_FIXED(fixed), message_player2, background_image_width / 6 + 90, background_image_height / 4 + 50);
    gtk_fixed_put(GTK_FIXED(fixed), message_player3, background_image_width / 3 + 80, background_image_height / 4 + 50);

    GtkWidget *label_player1 = create_label("Nom: Samuri\nPV: 100\nAttaque: 50\nDefense: 30\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");
    GtkWidget *label_player2 = create_label("Nom: Fire vizard\nPV: 120\nAttaque: 40\nDefense: 40\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");
    GtkWidget *label_player3 = create_label("Nom: Knight\nPV: 80\nAttaque: 60\nDefense: 20\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");

    gtk_fixed_put(GTK_FIXED(fixed), label_player1, 150, background_image_height / 3 + 270);
    gtk_fixed_put(GTK_FIXED(fixed), label_player2, background_image_width / 6 + 150, background_image_height / 3 + 270);
    gtk_fixed_put(GTK_FIXED(fixed), label_player3, background_image_width / 3 + 150, background_image_height / 3 + 270);

    button_start = create_button("Start", NULL);
    button_create = create_button("CREATE GLADIATOR", NULL);
    button_exit = create_button("EXIT", NULL);
    button_help = create_button("HELP", NULL);

    gtk_fixed_put(GTK_FIXED(fixed), button_start, background_image_width - 350, background_image_height - 350);
    gtk_fixed_put(GTK_FIXED(fixed), button_create, background_image_width - 350, background_image_height - 275);
    gtk_fixed_put(GTK_FIXED(fixed), button_exit, background_image_width - 350, background_image_height - 200);
    gtk_fixed_put(GTK_FIXED(fixed), button_help, background_image_width - 350, background_image_height - 100);


    g_signal_connect(button_start, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_create, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_exit, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_help, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkWidget *label = create_label("Select your Vector", "Ranger Eastwood 48", "black");
    gtk_fixed_put(GTK_FIXED(fixed), label, background_image_width / 7, background_image_height / 5);

    set_css_styles();
    gtk_widget_show_all(window);

    play_sound("resourses\\GameMusic.wav");
    gtk_main();

    return 0;
}

































//    // Create buttons for different actions
//    GtkWidget *button_standing = gtk_button_new_with_label("Standing");
//    GtkWidget *button_running = gtk_button_new_with_label("Running");
//    GtkWidget *button_attacking = gtk_button_new_with_label("Attacking");
//    GtkWidget *button_hurting = gtk_button_new_with_label("Hurting");
//    GtkWidget *button_dying = gtk_button_new_with_label("Dying");
//    GtkWidget *button_walking = gtk_button_new_with_label("Walking");
//
//    // Connect button signals to the button_clicked function
//    g_signal_connect(button_standing, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(5));
//    g_signal_connect(button_running, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(4));
//    g_signal_connect(button_attacking, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(0));
//    g_signal_connect(button_hurting, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(2));
//    g_signal_connect(button_dying, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(1));
//    g_signal_connect(button_walking, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(3));

// Create a horizontal box to hold the buttons
//    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

//    // Add the buttons to the button box
//    gtk_container_add(GTK_CONTAINER(button_box), button_standing);
//    gtk_container_add(GTK_CONTAINER(button_box), button_running);
//    gtk_container_add(GTK_CONTAINER(button_box), button_attacking);
//    gtk_container_add(GTK_CONTAINER(button_box), button_hurting);
//    gtk_container_add(GTK_CONTAINER(button_box), button_dying);
//    gtk_container_add(GTK_CONTAINER(button_box), button_walking);
// Add the main box to the window
