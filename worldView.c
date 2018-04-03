extern void draw_image(unsigned char *data);
extern void set_bkg_tiles(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *tiles);
extern void set_bkg_data(unsigned char first_tile, unsigned char nb_tiles, unsigned char *data);
extern void delay(unsigned int d);
extern void loadMap(unsigned char bank, char address[], char width, char height);
extern unsigned char waitpad(unsigned char mask);
extern unsigned char joypad();
extern unsigned char logoData[];
extern unsigned char arenaMap[];
extern unsigned char message[];
extern void checkEvents(unsigned int eventPointer, unsigned char bank);
extern void showMessage(unsigned char bank, unsigned int memoryLocation);
extern unsigned char overworldPosX, overworldPosY;
extern const char arenaEvents[];
extern char rand (void);
extern void initrand (unsigned int seed);
extern unsigned char cameraStatus;
extern void fadeIn(unsigned int d);
#include "defines.c"
#include "externNonbankedFunction.c"
#define CURRENT_MAP_X ((overworldPosX)>>3)
#define CURRENT_MAP_Y ((overworldPosY)>>3)

void showCollisionMap() {
    int i, j;
    long int currentMemory = MAP;
    for(i = 0; i < 32; i++) {
        for(j = 0; j < 32; j++) {
            MEM(currentMemory) = '0' + IS_COLLIDABLE(MEM(currentMemory));
            currentMemory++;
        }
    }
}

void showCharacter() {
    WAIT_FOR_NO_LCD;
    OAM_SET_SPRITE_POSITION_X(0, 80+8);
    OAM_SET_SPRITE_POSITION_X(1, 80+8);
    OAM_SET_SPRITE_POSITION_Y(0, 64+16);
    OAM_SET_SPRITE_POSITION_Y(1, 72+16);
    OAM_SET_SPRITE_TILE(0, TILE_OVERWORLD_CHARACTER);
    OAM_SET_SPRITE_TILE(1, TILE_OVERWORLD_CHARACTER_SECOND);
    if(cameraStatus & CAMERA_MOVING) {
        MEM(SCROLL_X) = overworldPosX-80;
        MEM(SCROLL_Y) = overworldPosY-72;
    }
    OAM_START_TRANSFER();
}

void worldViewLoop() {
    int pad, delta, iterator;
    unsigned char charmem;
    loadMap(5, arenaMap, 32, 32);
    showCharacter();
    fadeIn(200);
    checkEvents((unsigned int)arenaEvents, 5);
    while(1) {
        pad = joypad();
        delta = -1;
        if((pad & J_LEFT) && !IS_COLLIDABLE(MAP_AT(CURRENT_MAP_X-1, CURRENT_MAP_Y))) delta = 0;
        if((pad & J_RIGHT) && !IS_COLLIDABLE(MAP_AT(CURRENT_MAP_X+1, CURRENT_MAP_Y))) delta = 1;
        if((pad & J_UP) && !IS_COLLIDABLE(MAP_AT(CURRENT_MAP_X, CURRENT_MAP_Y-1))) delta = 2;
        if((pad & J_DOWN) && !IS_COLLIDABLE(MAP_AT(CURRENT_MAP_X, CURRENT_MAP_Y+1))) delta = 3;

        delay(20);
        if(delta != -1) {
            if(delta == 0) charmem = TILE_OVERWORLD_CHARACTER + 4;
            else if(delta == 1) charmem = TILE_OVERWORLD_CHARACTER + 12;
            else if(delta == 2) charmem = TILE_OVERWORLD_CHARACTER + 8;
            else charmem = TILE_OVERWORLD_CHARACTER;

            for(iterator = 0; iterator < 8; iterator++) {
                if(delta & 2)
                    overworldPosY -= 1 - ((delta & 1) << 1);
                else
                    overworldPosX -= 1 - ((delta & 1) << 1);
                if(cameraStatus & CAMERA_MOVING) {
                    MEM(SCROLL_X) = overworldPosX-80;
                    MEM(SCROLL_Y) = overworldPosY-72;
                } else {
                    OAM_SET_SPRITE_POSITION_X(0, overworldPosX+8-MEM(SCROLL_X));
                    OAM_SET_SPRITE_POSITION_X(1, overworldPosX+8-MEM(SCROLL_X));
                    OAM_SET_SPRITE_POSITION_Y(0, overworldPosY+8-MEM(SCROLL_Y));
                    OAM_SET_SPRITE_POSITION_Y(1, overworldPosY+16-MEM(SCROLL_Y));;
                }
                OAM_SET_SPRITE_TILE(0, charmem);
                OAM_SET_SPRITE_TILE(1, TILE_OVERWORLD_CHARACTER_SECOND_TRANSLATION(charmem));
                OAM_START_TRANSFER();
                if(iterator & 1)charmem++;
                delay(20);
            }
            checkEvents((unsigned int)arenaEvents, 5);
            if(cameraStatus & CAMERA_MOVING) {
                MEM(SCROLL_X) = overworldPosX-80;
                MEM(SCROLL_Y) = overworldPosY-72;
                OAM_SET_SPRITE_POSITION_X(0, 80+8);
                OAM_SET_SPRITE_POSITION_X(1, 80+8);
                OAM_SET_SPRITE_POSITION_Y(0, 64+16);
                OAM_SET_SPRITE_POSITION_Y(1, 72+16);
            }
            else {
                OAM_SET_SPRITE_POSITION_X(0, overworldPosX+8-MEM(SCROLL_X));
                OAM_SET_SPRITE_POSITION_X(1, overworldPosX+8-MEM(SCROLL_X));
                OAM_SET_SPRITE_POSITION_Y(0, overworldPosY+8-MEM(SCROLL_Y));
                OAM_SET_SPRITE_POSITION_Y(1, overworldPosY+16-MEM(SCROLL_Y));
            }

            OAM_START_TRANSFER();
        }



    }
}
