#ifndef WINDOWBOXSCROLL_H_INCLUDED
#define WINDOWBOXSCROLL_H_INCLUDED
#include <gtk/gtk.h>
typedef struct {
    gchar* image;
    gint width;
    gint height;
} layout;

typedef struct {
    GtkWidget* window;
    gchar *name;
    gchar* title;
    gchar* icon;
    gint height;
    gint width;
    gint position;
    gint posx;
    gint posy;
    gint resizable;
     gchar* bgColor;
     layout bgimage;

} Window;
typedef struct {
    GtkWidget* scrollWidget;
    GtkWidget* container;
    GtkWidget* childContainer;
    gint borderWidth;
    gint width;
    gint height;
} Scroll;

typedef struct {
    GtkWidget* box;
    gchar type;
    gchar* name;
    gint homogeneous;
    gint spacing;
    struct {
        gchar* color;
        gfloat degree;
    } bgcolor;
} Box;

typedef struct {
    GtkWidget* fixed;
    gchar* name;
    gint width;
    gint height;
} FixWidget;
  void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    GError *error = NULL;

    if (!gtk_css_provider_load_from_path(provider, "nada//style.css", &error)) {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        return;
    }
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}
// Fonction pour ajouter une image de fond à une fenêtre GTK
void add_bgimage(GtkWidget* window, GtkWidget** container, layout* bgimage) {
    GtkWidget* image;
    GdkPixbuf* pixbuf;
    GdkPixbuf* scaled_pixbuf;

    // Charge l'image depuis le chemin spécifié dans la structure bgimage
    pixbuf = gdk_pixbuf_new_from_file(bgimage->image, NULL);

    // Redimensionne l'image si la largeur ou la hauteur spécifiée est différente de zéro
    if (bgimage->width > 0 && bgimage->height > 0) {
        scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, bgimage->width, bgimage->height, GDK_INTERP_BILINEAR);
        image = gtk_image_new_from_pixbuf(scaled_pixbuf);
        g_object_unref(scaled_pixbuf);
    } else {
        image = gtk_image_new_from_pixbuf(pixbuf);
    }

    // Libère la mémoire utilisée par le GdkPixbuf
    g_object_unref(pixbuf);

    // Ajoute l'image à un conteneur et la rend visible
    gtk_container_add(GTK_CONTAINER(*container), image);
    gtk_widget_show(image);

    // Met à jour la taille du conteneur pour s'adapter à l'image
    gtk_widget_set_size_request(*container, bgimage->width, bgimage->height);

    // Attache l'événement "destroy" de la fenêtre à une fonction de rappel pour libérer la mémoire de l'image
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), image);
}

// Function to add background color to a widget
void addBackgroundColooor(GtkWidget* widget, const gchar* color, gdouble opacity) {
    GdkRGBA rgba;

    if (gdk_rgba_parse(&rgba, color)) {
        rgba.alpha = opacity;
        gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &rgba);
    } else {
        g_print("Error: Unable to parse color %s\n", color);
    }
}



Window* initializeWindow( gchar* name,gchar* title, gchar* icon, gint height, gint width, gint position, gint x, gint y, gint resizable, gchar* bgColor,gchar* bgimage,gint imagew,gint imageh) {
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        g_print("\nMemory allocation error");
        exit(-1);
    }

    window->title = NULL;
    window->icon = NULL;
    window->bgColor = NULL;  // Initialisez bgColor à NULL
    window->bgimage.image=NULL;
    window->name = NULL;
    if (name) {
        window->name = (gchar*)malloc(30 * sizeof(gchar));
        if (window->name)
            strcpy(window->name, name);
        else
            g_print("Memory allocation error for FixWidget name");
    }

    if (title) {
        window->title = (gchar*)malloc(30 * sizeof(gchar));
        if (window->title)
            strcpy(window->title, title);
        else
            g_print("Memory allocation error for title");
    }
    if (icon) {
        window->icon = (gchar*)malloc(100 * sizeof(gchar));
        if (window->icon)
            strcpy(window->icon, icon);
        else
            g_print("Memory allocation error for icon");
    }
    if (bgimage) {
        window->bgimage.image = (gchar*)malloc(100 * sizeof(gchar));

    }
    if (bgColor) {
        window->bgColor = (gchar*)malloc(15 * sizeof(gchar));
        if (window->bgColor)
            strcpy(window->bgColor, bgColor);
        else
            g_print("Memory allocation error for bgColor");
    }
    window->height = height;
    window->width = width;
    window->position = position;
    window->posx = x;
    window->posy = y;
    window->resizable = resizable;
    window->bgimage.width=imagew;
    window->bgimage.height=imageh;

    return window;
}


void createWindow(Window* wo) {
    wo->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     if (wo->name)
        gtk_widget_set_name(wo->window, wo->name);
    if (wo->title)
        gtk_window_set_title(GTK_WINDOW(wo->window), wo->title);

    if (wo->icon)
        gtk_window_set_icon_from_file(GTK_WINDOW(wo->window), wo->icon, NULL);
    if (wo->bgColor)  // Vérifiez si bgColor est défini
        addBackgroundColooor(wo->window, wo->bgColor, 1.0);  // Utilisez bgColor pour définir la couleur de fond
    if (wo->width > 0 && wo->height > 0)
        gtk_window_set_default_size(GTK_WINDOW(wo->window), wo->width, wo->height);
    if(wo->bgimage.image) {// Charger la feuille de style CSS

           load_css();
    }

    switch (wo->position) {
        case 1:
            gtk_window_set_position(GTK_WINDOW(wo->window), GTK_WIN_POS_NONE);
            break;
        case 2:
            gtk_window_set_position(GTK_WINDOW(wo->window), GTK_WIN_POS_CENTER);
            break;
        case 3:
            gtk_window_set_position(GTK_WINDOW(wo->window), GTK_WIN_POS_MOUSE);
            break;
        case 4:
            gtk_window_set_position(GTK_WINDOW(wo->window), GTK_WIN_POS_CENTER_ALWAYS);
            break;
        case 5:
            gtk_window_set_position(GTK_WINDOW(wo->window), GTK_WIN_POS_CENTER_ON_PARENT);
            break;
        default:
            gtk_window_move(GTK_WINDOW(wo->window), wo->posx, wo->posy);
            break;
    }
    if (wo->resizable)
        gtk_window_set_resizable(GTK_WINDOW(wo->window), TRUE);
    else
        gtk_window_set_resizable(GTK_WINDOW(wo->window), FALSE);

}


Scroll* initializeScroll(GtkWidget* container, GtkWidget* childContainer, gint borderWidth, gint width, gint height) {
    Scroll* scroll = (Scroll*)malloc(sizeof(Scroll));
    if (!scroll) {
        g_print("\nMemory allocation error");
        exit(-1);
    }

    scroll->container = NULL;
    scroll->childContainer = NULL;
    scroll->borderWidth = 0;
    scroll->height = scroll->width = 100;

    if (container)
        scroll->container = container;
    if (childContainer)
        scroll->childContainer = childContainer;
    if (borderWidth > 0)
        scroll->borderWidth = borderWidth;
    if (width > 100)
        scroll->width = width;
    if (height > 100)
        scroll->height = height;

    return scroll;
}

Scroll* createScroll(Scroll* scroll) {
    scroll->scrollWidget = gtk_scrolled_window_new(NULL, NULL);

    if (scroll->container) {
        if (GTK_IS_BOX(scroll->container))
            gtk_box_pack_start(GTK_BOX(scroll->container), scroll->scrollWidget, TRUE, TRUE, 0);
        else
            gtk_container_add(GTK_CONTAINER(scroll->container), scroll->scrollWidget);
    }

    gtk_container_set_border_width(GTK_CONTAINER(scroll->scrollWidget), scroll->borderWidth);

    if (scroll->childContainer) {
        gtk_container_add(GTK_CONTAINER(scroll->scrollWidget), scroll->childContainer);
    }

    gtk_widget_set_size_request(scroll->scrollWidget, scroll->width, scroll->height);

    return scroll;
}

Box* initializeBox(gchar* name, gchar type, gint homogeneous, gint spacing, gchar* bgcolor, gfloat opacity) {
    Box* B = (Box*)malloc(sizeof(Box));
    if (!B) {
        g_print("\nMemory allocation error for Box");
        exit(1);
    }

    B->name = NULL;
    B->bgcolor.color = NULL;

    if (name) {
        B->name = (gchar*)malloc(30 * sizeof(gchar));
        if (B->name)
            strcpy(B->name, name);
        else
            g_print("Memory allocation error for box name");
    }

    if (bgcolor) {
        B->bgcolor.color = (gchar*)malloc(15 * sizeof(gchar));
        if (B->bgcolor.color)
            strcpy(B->bgcolor.color, bgcolor);
        else
            g_print("Memory allocation error for box background color");
    }

    B->type = type;
    B->homogeneous = homogeneous;
    B->spacing = spacing;
    B->bgcolor.degree = opacity;

    return B;
}

Box* createBox(Box* B) {
    if (B->homogeneous)
        B->box = gtk_box_new(TRUE, B->spacing);
    else
        B->box = gtk_box_new(FALSE, B->spacing);

    if ((B->type == 'v') || (B->type == 'V'))
        gtk_orientable_set_orientation(GTK_ORIENTABLE(B->box), GTK_ORIENTATION_VERTICAL);
    else if ((B->type == 'h') || (B->type == 'H'))
        gtk_orientable_set_orientation(GTK_ORIENTABLE(B->box), GTK_ORIENTATION_HORIZONTAL);
    else {
        g_print("The type does not exist");
        exit(0);
    }

    if (B->bgcolor.color)
        addBackgroundColooor(B->box, B->bgcolor.color, B->bgcolor.degree);
    if (B->name)
        gtk_widget_set_name(B->box, B->name);

    return B;
}

void addToBox(GtkWidget* box, GtkWidget* child, gint type, gboolean expand, gboolean fill, gint padding) {
    if (type)
        gtk_box_pack_start(GTK_BOX(box), child, expand, fill, padding);
    else
        gtk_box_pack_end(GTK_BOX(box), child, expand, fill, padding);
}

FixWidget* initializeFixWidget(gchar* name, gint width, gint height) {
    FixWidget* FW = (FixWidget*)malloc(sizeof(FixWidget));
    if (!FW) {
        g_print("\nMemory allocation error for FixWidget");
        exit(1);
    }

    FW->name = NULL;
    if (name) {
        FW->name = (gchar*)malloc(30 * sizeof(gchar));
        if (FW->name)
            strcpy(FW->name, name);
        else
            g_print("Memory allocation error for FixWidget name");
    }

    FW->width = width;
    FW->height = height;
    return FW;
}

void createFixWidget(FixWidget* F) {
    F->fixed = gtk_fixed_new();
    gtk_widget_set_size_request(F->fixed, F->width, F->height);
    if (F->name)
        gtk_widget_set_name(F->fixed, F->name);
}

void addMoveToFixWidget(FixWidget* F, GtkWidget* child, gint posx, gint posy, gint type) {
    if (type)
        gtk_fixed_put(GTK_FIXED(F->fixed), child, posx, posy);
    else
        gtk_fixed_move(GTK_FIXED(F->fixed), child, posx, posy);
}




#endif // WINDOWBOXSCROLL_H_INCLUDED
