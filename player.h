

#ifndef TEST_GTK_PLAYER_H
#define TEST_GTK_PLAYER_H

// Structure to hold player data
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
} Player;

#endif //TEST_GTK_PLAYER_H
