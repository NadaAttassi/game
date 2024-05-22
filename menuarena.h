#ifndef MENUARENA_H_INCLUDED
#define MENUARENA_H_INCLUDED


#include <gtk/gtk.h>
#include "window.h"
#include "image.h"

// Forward declarations

GtkWidget *button_start;

GtkWidget *button_exit;
void on_start_button_clicked(GtkWidget *widget, gpointer data);
void create_main_window();
void create_images_window();
void show_large_image(const char *filename);
void on_images_start_button_clicked(GtkWidget *widget, gpointer data);
void add_child(GtkWidget *container, GtkWidget *child) {
    gtk_container_add(GTK_CONTAINER(container), child);
}
// Fonction pour afficher une fenêtre GTK
void show_window(Fenetre *window) {
    gtk_widget_show_all(window->window);
}

/*int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Créez le fournisseur de CSS
    /*GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    // Chargez le fichier CSS depuis le chemin spécifié
    gtk_css_provider_load_from_path(provider, "stylesbutton.css", NULL);

    // Associez le fournisseur de CSS à l'écran par défaut
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    create_images_window();

    gtk_main();
    return 0;
}*/

// Reste de votre code ici...


// Create the main window with the start button
void create_main_window() {
    Fenetre *main_window = initialiser_win("Main Window", NULL, "Main_Window", NULL, 200, 300, 2, 0, 0, 1, TRUE);
    create_window(main_window);

    GtkWidget *button = gtk_button_new_with_label("Start");
    g_signal_connect(button, "clicked", G_CALLBACK(on_start_button_clicked), NULL);

    add_child(main_window->window, button);
    show_window(main_window);
}

// Callback for the start button click
void on_start_button_clicked(GtkWidget *widget, gpointer data) {
    create_images_window();
}
/*void button_clicked(GtkWidget *button, gpointer data) {
    const char *button_label = gtk_button_get_label(GTK_BUTTON(button));
    if (g_strcmp0(button_label, "Start") == 0) {
        if (selected_player) {
            g_print("Starting the game with %s\n", selected_player->name);
            run_game(selected_player);  // Call run_game with the selected player
            //create_images_window();
        } else {
            g_print("No player selected!\n");
        }
    }
        // Code to create a new gladiator
     else if (g_strcmp0(button_label, "EXIT") == 0) {
        g_print("Exit clicked\n");
        gtk_main_quit();
    }
}*/
// Create the window with the four images
/*void create_images_window() {
    Fenetre *images_window = initialiser_win("Images Window", NULL, "Images_Window", NULL, 700, 800, 2, 0, 0, 1, TRUE);
    create_window(images_window);

    GtkWidget *fixed = gtk_fixed_new();
    add_child(images_window->window, fixed);

    // Add background image
    GtkWidget *background_image = gtk_image_new_from_file("C:\\Users\\AdMin\\Downloads\\bggg1.png");
    gtk_fixed_put(GTK_FIXED(fixed), background_image, 0, 0);
    GtkWidget *table_image = gtk_image_new_from_file("C:\\Users\\AdMin\\Downloads\\table4.png");
    gtk_fixed_put(GTK_FIXED(fixed), table_image, 100, 100); // Adjust position as needed


    // Add four images to the fixed container
    add_image(fixed, 1, "C:\\wamp64\\www\\arena7.png", GTK_ICON_SIZE_BUTTON, 300, 300, 300, 230);
    add_image(fixed, 1, "C:\\wamp64\\www\\arena5.png", GTK_ICON_SIZE_BUTTON, 300, 300, 800, 230);
    add_image(fixed, 1, "C:\\wamp64\\www\\arena9.png", GTK_ICON_SIZE_BUTTON, 300, 300, 300, 550);
    add_image(fixed, 1, "C:\\wamp64\\www\\arena8.png", GTK_ICON_SIZE_BUTTON, 300, 300, 800, 550);

    // Add buttons with names for CSS styling
    GtkWidget *button1 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button1, "custom-button"); // Set name for CSS
    g_signal_connect(button1, "clicked", G_CALLBACK(on_images_start_button_clicked), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 650, 340);

    GtkWidget *button2 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button2, "custom-button"); // Set name for CSS
    g_signal_connect(button2, "clicked", G_CALLBACK(on_images_start_button_clicked), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 1150, 340);


    GtkWidget *button3 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button3, "custom-button"); // Set name for CSS
    g_signal_connect(button3, "clicked", G_CALLBACK(on_images_start_button_clicked), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button3, 650, 650);


    GtkWidget *button4 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button4, "custom-button"); // Set name for CSS
    g_signal_connect(button4, "clicked", G_CALLBACK(on_images_start_button_clicked), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button4, 1150, 650);



    // Add "Start" button
    // Add "Start" button
GtkWidget *button_start = gtk_button_new_with_label("Start");
g_signal_connect(button_start, "clicked", G_CALLBACK(on_images_start_button_clicked), NULL);
gtk_fixed_put(GTK_FIXED(fixed), button_start, 1500, 700);


    // Add "Exit" button
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button_exit, 1500, 800);
    show_window(images_window);
}*/

// Callback for image click
void on_image_clicked(GtkWidget *widget, gpointer data) {
    const char *filename = (const char *)data;
    show_large_image(filename);
}

// Show the clicked image in a large window
void show_large_image(const char *filename) {
    Fenetre *large_image_window = initialiser_win("Large Image", NULL, "Large_Image", NULL, 600, 800, 2, 0, 0, 1, TRUE);
    create_window(large_image_window);

    GtkWidget *image = gtk_image_new_from_file(filename);
    add_child(large_image_window->window, image);

    show_window(large_image_window);
}

// Callback for the start button in the images window
void on_images_start_button_clicked(GtkWidget *widget, gpointer data) {
    // Add the logic you want to execute when the start button in the images window is clicked
    g_print("Start button in images window clicked\n");
}

#endif // MENUARENA_H_INCLUDED
