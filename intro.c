#include <rand.h>
extern void set_bkg_tiles(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *tiles);
extern void set_bkg_data(unsigned char first_tile, unsigned char nb_tiles, unsigned char *data);
extern void delay(unsigned int d);
extern void fadeIn(unsigned int d);
extern void fadeOut(unsigned int d);
extern void draw_image_own(unsigned char *data);
extern unsigned char waitpad(unsigned char mask);
extern unsigned char joypad();
extern unsigned char logoData[];
extern char rand (void);
extern void initrand (unsigned int seed);
#include "defines.c"

void mainMenu() {
    unsigned char lastPressedNegation = 0;
    int selectedOption = 4, val = 0;
    while(1) {
        if(selectedOption == 0 || selectedOption == 4)
            set_bkg_tiles(2, 7, 11, 1, "- PLAY GAME");
        else
            set_bkg_tiles(2, 7, 11, 1, "  PLAY GAME");

        if(selectedOption == 1)
            set_bkg_tiles(2, 9, 9, 1,  "- OPTIONS");
        else
            set_bkg_tiles(2, 9, 9, 1,  "  OPTIONS");

        if(selectedOption == 2)
            set_bkg_tiles(2, 11, 9, 1, "- CREDITS");
        else
            set_bkg_tiles(2, 11, 9, 1, "  CREDITS");

        if(selectedOption == 4) {
            fadeIn(125);
            selectedOption = 0;
        }

        val = joypad();
        if((val & J_DOWN & lastPressedNegation)) {
            selectedOption++;
        }
        if(selectedOption > 2) selectedOption = 2;

        if(val & J_UP & lastPressedNegation) {
            selectedOption--;
        }
        if(selectedOption < 0) selectedOption = 0;

        if(val & J_START) {
            return;
        }
        lastPressedNegation = ~val;
    }
}



void intro()
{
    draw_image_own(logoData);
    waitpad(J_START);
}
