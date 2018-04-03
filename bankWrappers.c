extern void fadeInBanked(unsigned int d);
extern void fadeOutBanked(unsigned int d);
extern void moveSlowlyCameraBanked(unsigned char x, unsigned char y);


void loadBankedTileset(unsigned char bank, unsigned char first_tile, unsigned char nb_tiles, unsigned char * data) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(bank);
    set_sprite_data(first_tile, nb_tiles, data);
    SWITCH_ROMS(savedBank);
}

void fadeIn(unsigned int delayValue) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(6);
    fadeInBanked(delayValue);
    SWITCH_ROMS(savedBank);
}

void fadeOut(unsigned int delayValue) {
    unsigned char savedBank = currentBank;
    SAVE_PALETTE;
    SWITCH_ROMS(6);
    fadeOutBanked(delayValue);
    SWITCH_ROMS(savedBank);
}

void moveSlowlyCamera(unsigned char x, unsigned char y) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(6);
    moveSlowlyCameraBanked(x, y);
    SWITCH_ROMS(savedBank);
}

extern void playAnimation(unsigned char flag, unsigned char attacked);

void playAnimationBanked(unsigned char flag, unsigned char attacked) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(FIGHT_STRING_BANK);
    playAnimation(flag, attacked);
    SWITCH_ROMS(savedBank);
}

typedef void (BankedFunction)(unsigned char);

void runAdditionalBankedFunction(BankedFunction* function, unsigned char id) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(FIGHT_STRING_BANK);
    (*function)(id);
    SWITCH_ROMS(savedBank);
}

