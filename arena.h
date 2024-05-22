
#ifndef TEST_GTK_ARENA_H
#define TEST_GTK_ARENA_H
#include <gtk/gtk.h>
#include "player.h"

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

extern GtkImage *gladiator_image;
extern GdkPixbuf *sprite_sheet;
extern int current_frame;
extern int current_action;
extern int action_frames[];
extern int gladiator_x;
extern GtkWidget *life_image_player1;
extern GtkWidget *life_image_player2;
extern GtkWidget *time_image;
extern GtkWidget *table_time_image;


gboolean update_animation(gpointer data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
void run_game(Player *player);

#endif //TEST_GTK_ARENA_H
