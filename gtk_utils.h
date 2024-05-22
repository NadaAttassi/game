#ifndef GTK_UTILS_H
#define GTK_UTILS_H

#include <gtk/gtk.h>
#include <windows.h>
#include <mmsystem.h>

//#include "window.h"
// Function declarations
 //GtkWidget* create_window(const char *title, int width, int height);

GtkWidget* create_button(const char *label, const char *css_name);
GtkWidget* create_label(const char *text, const char *font_desc_str, const char *color_str);
void set_css_styles();
GtkWidget *create_fixed();
void update_background_image(GtkWidget *fixed, GtkWidget **background_image, const char *file_path);
void play_sound(const char *sound_file);

#endif // GTK_UTILS_H
