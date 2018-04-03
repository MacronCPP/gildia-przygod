/*  Gildia Przygód
 *  A game on GB, written in C.
 *  Uses gbdk.
 *  Based on a RPG game made by Lukasz Pecia.
 *  Uses also pointerupdater.jar - a short application that let a map maker write addresses to char tables.
    GPL


 *  Recognized bugs:
 *  - GBDK loves to do something wrong with shifting - Shifts bigger than 4 may be generated wrongly.
 * Special thanks to:
 *  - Wielki Pierogo
 *  - ISSOtm
 *  - gekkio
*/

#include <gb/gb.h>
#include <rand.h>
#include "defines.c"

//Autoplay allows to test the game without any need for a user input.
//#define AUTOPLAY
#ifdef AUTOPLAY
unsigned char lastJoyPad = 1;
unsigned char joypad() {
    delay(300);
    lastJoyPad = !lastJoyPad;
    if(lastJoyPad)
        return 0;
    return J_A | J_DOWN;
}
void waitpadup() {delay(300);}
unsigned char waitpad(unsigned char val) { val = 0;}
#endif

extern unsigned char logoData[];
extern unsigned char tileset_arenaData[];
extern unsigned char characterIdleAnimation, timerFrame;
extern void intro();
extern void OAM_START_TRANSFER();
extern void mainMenu();
extern void worldViewLoop();
extern void fightViewLoop();
extern void moveSlowlyCameraBanked(unsigned char x, unsigned char y);

unsigned char currentBank = 1;
#define SWITCH_ROMS(x) MEM(0x2000) = x; currentBank = x;
//Some data or functions will be banked.
//Backuping currentBank and using SWITCH_ROMS will let you safely run functions between diffrent banks.


unsigned char overworldPosX = 80, overworldPosY = 56;
unsigned char cameraStatus = 1;
unsigned int eventsLocation;

unsigned char savedPaletteBackground, savedPaletteSprite0, savedPaletteSprite1;

#define RESTORE_PALETTE  BACKGROUND_PALETTE = savedPaletteBackground; SPRITE0_PALETTE = savedPaletteSprite0; SPRITE1_PALETTE = savedPaletteSprite1
#define SAVE_PALETTE  savedPaletteBackground = BACKGROUND_PALETTE; savedPaletteSprite0 = SPRITE0_PALETTE; savedPaletteSprite1 = SPRITE1_PALETTE

void zero(void* s, unsigned int sz) {
    unsigned int* p = (unsigned int*)s;
    sz >>= 1;
    while (sz--) {
        *p = 0;
        p++;
    }
}

void zeroVRAM(void* s, unsigned int sz) { // Due to the timing issues, it's much safer to use SET in this case
    unsigned int p = (unsigned int)s;     // Without using SET, some tiles wouldn't get cleared.
    while (sz--) {
        SET(p, 0);
        p++;
    }
}

#include "messageBufferOperations.c"

// Main characters names
const char Arkeitz[] = "ARKEITZ|";
const char Thidem[] = "THIDEM|";
const char Ryszard[] = "RYSZARD|";

void interruptIdle() // Run on timer interrupt, manages character idle animations during fights.
{
    unsigned char iterator, idles = characterIdleAnimation;
    timerFrame++;
    if(timerFrame & 7)
        return;
    if(timerFrame >= 24)
        timerFrame = 0;
    for(iterator = 0; iterator < 6; iterator++)
    {
        if(idles & 1)
        {
            /* There's need to reverse right ones
             * */
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 0), CHARACTER_IDLE_TILESET(iterator)+(timerFrame>>2)+(iterator > 2));
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 1), CHARACTER_IDLE_TILESET(iterator)+1+(timerFrame>>2)-(iterator > 2));
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 2), CHARACTER_IDLE_TILESET(iterator)+6+(timerFrame>>2)+(iterator > 2));
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 3), CHARACTER_IDLE_TILESET(iterator)+7+(timerFrame>>2)-(iterator > 2));
        }
        idles >>= 1;
    }
    OAM_START_TRANSFER();
}

unsigned char mainCharacterSkillMemory[3*4*SKILL_LENGTH]; //Type(1B) Stats(3B) NameAndDescription(2B) Bank(1B)

unsigned char enemySkillMemory[3*4*SKILL_LENGTH];

#define ENEMY_LOOT_TABLE_LENGTH 25

unsigned char mainCharacterMemory[15*3] =   //15
{
    1, 35, 6, 0x95U, 0x08U/*pointerArkeitz*/, 0xF2U, 0x52U/*pointerarkeitzData*/, 90, 70, 45, 40, 35, 0, 0, 0,/*dex 70 per 45*/
    1, 45, 6, 0x9EU, 0x08U/*pointerThidem*/, 0xF0U, 0x4CU/*pointerthidemData*/,  23, 95, 80, 15, 45, 0, 0, 0,
    1, 25, 6, 0xA6U, 0x08U/*pointerRyszard*/, 0xEEU, 0x46U/*pointerryszardData*/, 50, 42, 35, 84, 25, 0, 0, 0
};
unsigned char enemyLoot[2*12+1];
unsigned char enemyMemory[15*3];

#include "GUIOperations.c"

void copyMemory(unsigned char* source, unsigned char* destination, unsigned char length, unsigned char bank)
{
    unsigned char iterator, savedBank = currentBank;
    SWITCH_ROMS(bank);
    for(iterator = 0; iterator < length; iterator++)
    {
        *destination = *source;
        destination++;
        source++;
    }
    SWITCH_ROMS(savedBank);
}

unsigned char* currentMap,* currentTileset;
unsigned char currentMapBank, currentTilesetBank;

extern const unsigned char arkeitzSkills[];
extern const unsigned char thidemSkills[];
extern const unsigned char ryszardSkills[];

void loadMainCharacters() {
    copyMemory(arkeitzSkills, mainCharacterSkillMemory, CHARACTER_SKILLS_LENGTH, 6);
    copyMemory(thidemSkills, mainCharacterSkillMemory+CHARACTER_SKILLS_LENGTH, CHARACTER_SKILLS_LENGTH, 6);
    copyMemory(ryszardSkills, mainCharacterSkillMemory+CHARACTER_SKILLS_LENGTH*2, CHARACTER_SKILLS_LENGTH, 6);
}

void loadMap(unsigned char bank, unsigned char address[], unsigned char width, unsigned char height)
{
    unsigned char i, j, k;
    unsigned int currentMemory = MAP;
    unsigned char savedBank = currentBank;
    currentMap = address;
    currentMapBank = bank;
    SWITCH_ROMS(bank);
    width = width>>2;
    for(i = 0; i < height; ++i)
    {
        for(j = 0; j < width; ++j)
        {
            SET(currentMemory, GB_TILE(TILE_UNCOMPRESS_COMBINED(address)));
            currentMemory++;
            for(k = 0; k < 3; ++k)
            {
                SET(currentMemory, GB_TILE(TILE_UNCOMPRESS_PLAIN(address)));
                address++;
                currentMemory++;
            }
        }
        currentMemory = currentMemory + ((8-width)<<2);
    }
    SWITCH_ROMS(savedBank);
}

#include "bankWrappers.c"
#include "encounter.c"
#include "event.c"
#include "eqView.c"

int main()
{
    loadMainCharacters();
    SHOW_BKG;
    DISPLAY_ON;
    SWITCH_ROMS(2);
    intro();
    fadeOut(250);
    WAIT_FOR_NO_LCD;
    DISPLAY_OFF;
    HIDE_BKG;

    DISABLE_INTERRUPTS;
    SELECT_TILEPATTERN_TABLE_0;
    SELECT_BACKGROUND_TABLE_0;
    SELECT_WINDOW_TABLE_0;
    CLEAR_WHOLE_SCREEN;
    SHOW_BKG;
    DISPLAY_ON;
    SHOW_SPRITES;
    CLEAR_OAM_TRANSFER_TABLE;
    SWITCH_ROMS(5);
    currentTilesetBank = 5;
    currentTileset = tileset_arenaData;
    set_bkg_data(0, 255, tileset_arenaData);
    set_sprite_data(0, 255, tileset_arenaData);
    set_win_data(0, 128, tileset_arenaData);
    SWITCH_ROMS(3);
    worldViewLoop();
    return 0;
}
