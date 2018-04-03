#include "defines.c"
#include <types.h>
extern void delay (unsigned int d);
extern void OAM_START_TRANSFER();
extern unsigned char savedPaletteBackground, savedPaletteSprite0, savedPaletteSprite1;
void fadeInBanked(unsigned int delayValue) {
    unsigned char* palettes[] = {BACKGROUND_PALETTE_LOCATION, SPRITE0_PALETTE_LOCATION, SPRITE1_PALETTE_LOCATION};
    unsigned char* savedPalettes[] = {&savedPaletteBackground, &savedPaletteSprite0, &savedPaletteSprite1};
    unsigned char change, iterator;
    while(BACKGROUND_PALETTE != savedPaletteBackground || SPRITE0_PALETTE != savedPaletteSprite0 || SPRITE1_PALETTE != savedPaletteSprite1) {
        for(iterator = 0; iterator < 3; iterator++) {
            change = 0;
            if(((*(palettes[iterator])) & 3) != ((*(savedPalettes[iterator])) & 3))
                change = 1;

            if(((*(palettes[iterator])) & 12) != ((*(savedPalettes[iterator])) & 12))
                change |= 4;

            if(((*(palettes[iterator])) & 48) != ((*(savedPalettes[iterator])) & 48))
                change |= 16;

            if(((*(palettes[iterator])) & 192) != ((*(savedPalettes[iterator])) & 192))
                change |= 64;
            if(change == 0) {
                BACKGROUND_PALETTE = ~BACKGROUND_PALETTE;
                delay(500);
            }
            WAIT_FOR_NO_LCD;
            *(palettes[iterator]) += change;
        }
        delay(delayValue);
    }
}


void fadeOutBanked(unsigned int delayValue) {
    unsigned char* palettes[] = {BACKGROUND_PALETTE_LOCATION, SPRITE0_PALETTE_LOCATION, SPRITE1_PALETTE_LOCATION};
    unsigned char change, iterator;
    while(BACKGROUND_PALETTE != LIGHTEST_PALETTE || SPRITE0_PALETTE != LIGHTEST_PALETTE || SPRITE1_PALETTE != LIGHTEST_PALETTE) {
        for(iterator = 0; iterator < 3; iterator++) {
            change = 0;
            if((*(palettes[iterator])) & 3)
                change = 1;

            if((*(palettes[iterator])) & 12)
                change |= 4;

            if((*(palettes[iterator])) & 48)
                change |= 16;

            if((*(palettes[iterator])) & 192)
                change |= 64;

            WAIT_FOR_NO_LCD;
            *(palettes[iterator]) -= change;
        }
        delay(delayValue);
    }

}

void moveSlowlyCameraBanked(unsigned char x,  unsigned char y) {
    int xT = x, yT = y;
    int fX = MEM(SCROLL_X), fY = MEM(SCROLL_Y);
    unsigned char charX = OAM_GET_SPRITE_POSITION_X(0), charY = OAM_GET_SPRITE_POSITION_Y(0);
    char stepX, stepY;
    int iterator;
    if(fX > 176)//256-80
        fX -= 256;
    if(fY > 168)//256-72
        fY -= 256;
    xT -= 80;
    yT -= 72;
    for(iterator = 0; iterator < 100; iterator++) {
        stepX = (char)(fX + (xT-fX)*iterator/100);
        stepY = (char)(fY + (yT-fY)*iterator/100);
        MEM(SCROLL_X) = stepX;
        MEM(SCROLL_Y) = stepY;
        OAM_SET_SPRITE_POSITION_X(0, charX+((char)(fX-stepX)));
        OAM_SET_SPRITE_POSITION_Y(0, charY+((char)(fY-stepY)));
        OAM_SET_SPRITE_POSITION_X(1, charX+((char)(fX-stepX)));
        OAM_SET_SPRITE_POSITION_Y(1, charY+8+((char)(fY-stepY)));
        OAM_START_TRANSFER();
        delay(16);
    }
    MEM(SCROLL_X) = xT;
    MEM(SCROLL_Y) = yT;
    OAM_SET_SPRITE_POSITION_X(0, charX+((char)(fX-xT)));
    OAM_SET_SPRITE_POSITION_Y(0, charY+((char)(fY-yT)));
    OAM_SET_SPRITE_POSITION_X(1, charX+((char)(fX-xT)));
    OAM_SET_SPRITE_POSITION_Y(1, charY+8+((char)(fY-yT)));
    OAM_START_TRANSFER();

}
