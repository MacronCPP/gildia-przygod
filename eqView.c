unsigned char itemCount[3] = {3, 4, 3};
unsigned char items[90] = {0, 10,
                   4, 1,
                   7, 1,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   3, 1,
                   1, 1,
                   6, 1,
                   5, 2,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   2, 1,
                   5, 2,
                   6, 1};

unsigned int money;
const unsigned char itemBank = 5;
const unsigned char itemTableLocationPre[] = {0, 0x78U, 0x44U/*pointeritemTable*/};
unsigned int itemTableLocation = *((unsigned int*)(itemTableLocationPre+1));
unsigned char selectedItem[16];
unsigned char hasItem(unsigned char ID, unsigned char am) {
    unsigned char iterator1 = 0, iterator2 = 0;
    for(iterator1 = 0; iterator1 < 3; iterator1++)
        for(iterator2 = 0; iterator2 < itemCount[iterator1]; iterator2++){
            if(ITEM_OF_CHARACTER(iterator1, iterator2) == ID) {
                if(AMOUNT_OF_ITEM(iterator1, iterator2) >= am)
                    return 1;
                else am -= AMOUNT_OF_ITEM(iterator1, iterator2);
            }
        }
    return 0;
}

void throwAwayItem(unsigned char characterID, unsigned char n) {
    itemCount[characterID]--;
    for(; n < itemCount[characterID]-1; n++)
    {
        ITEM_OF_CHARACTER(characterID, n) = ITEM_OF_CHARACTER(characterID, n+1);
        AMOUNT_OF_ITEM(characterID, n) = AMOUNT_OF_ITEM(characterID, n+1);
    }
}

void deleteItem(unsigned char characterID, unsigned char ID, unsigned char am) {
    unsigned char iterator1 = 0;
    for(iterator1 = 0; iterator1 < itemCount[characterID]; iterator1++)
        if(ITEM_OF_CHARACTER(characterID, iterator1) == ID) {
            if(AMOUNT_OF_ITEM(characterID, iterator1) <= am) {
                throwAwayItem(characterID, iterator1);
            }
            else
                AMOUNT_OF_ITEM(characterID, iterator1) -= am;
            return;
         }
}

unsigned char armorValue(unsigned char value) {
    unsigned char iterator = 0, ret = 0, savedBank = currentBank;
    SWITCH_ROMS(itemBank);
    if(value < 3) {
        for(iterator = 0; iterator < itemCount[value]; iterator++)
            if(ITEM_TYPE(*ITEM_OF_ID(items[value * 30 + (iterator << 1)])) == ITEM_ARMOR)
                ret += ITEM_ARMOR_VALUE(ITEM_OF_ID(items[value * 30 + (iterator << 1)]));
    }
    else {
        if(ITEM_TYPE(*ITEM_OF_ID(enemyLoot[6+value<<1])) == ITEM_ARMOR)
            ret = ITEM_ARMOR_VALUE(ITEM_OF_ID(enemyLoot[6+value<<1]));
    }
    SWITCH_ROMS(savedBank);
    return ret;
}

unsigned char eqStatistic(unsigned char id, unsigned char statistic) {
    unsigned char iterator = 0, subIterator = 0, ret = 0, savedBank = currentBank;
    SWITCH_ROMS(itemBank);
    if(id < 3) {
        for(iterator = 0; iterator < itemCount[id]; iterator++)
            if(ITEM_TYPE(*ITEM_OF_ID(items[iterator << 1])) == ITEM_STAT_BOOST) {
                for(subIterator = 0; subIterator < 3; subIterator++) {
                    if(ITEM_BOOST_TYPE(ITEM_OF_ID(items[iterator << 1]), subIterator) == statistic) {
                        ret += ITEM_BOOST_AMOUNT(ITEM_OF_ID(items[iterator << 1]), subIterator);
                    }
                }
            }
    }
    SWITCH_ROMS(savedBank);
    return ret;
}


void showEQ(unsigned char selectedEq) {
    char buffer[2];
    unsigned char iterator = itemCount[selectedEq];
    while(iterator--) {
        buffer[0] = '0' + items[(selectedEq<<5)-(selectedEq<<2) + (iterator<<1) + 1]/10;
        buffer[1] = '0' + (items[(selectedEq<<5)-(selectedEq<<2) + (iterator<<1) + 1])%10;/*((itemTableLocation+(items[(selectedEq<<5)-(selectedEq<<2) + (iterator<<1)]<<4))+2)*/
        set_bkg_tiles(2, (iterator<<1) + 2, 14, 1, ITEM_OF_ID(selectedEq*30 + iterator)+2);
        set_bkg_tiles(17, (iterator<<1) + 2, 2, 1, buffer);
    }
}

extern const unsigned char chooseWeaponTitle[];
extern const unsigned char weaponRanged[];
extern const unsigned char weaponMelee[];
extern const unsigned char weaponDescription[];
extern const unsigned char bareHand[];
extern void chooseWeapon(unsigned char characterID);
extern void choosePotion(unsigned char characterID);

void chooseWeaponBanked(unsigned char characterID) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(itemBank);
    chooseWeapon(characterID);
    SWITCH_ROMS(savedBank);
}


void choosePotionBanked(unsigned char characterID) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(itemBank);
    choosePotion(characterID);
    SWITCH_ROMS(savedBank);
}


void eqViewLoop() {
    char changeBuffer[1];
    unsigned char savedBank = currentBank;
    unsigned char character = 0, selected = 0, lastPressedNegation = 0, last = 0, val;
    SWITCH_ROMS(itemBank);
    HIDE_WIN;
    CLEAR_WHOLE_SCREEN;
    showEQ(character);
    while(1) {
        last = selected;
        val = joypad();
        if(val & J_B & lastPressedNegation) break;
        if(val & J_A & lastPressedNegation);
        if(val & J_UP & lastPressedNegation) selected--;
        if(selected == 255u)
            selected = 0;
        if(val & J_DOWN & lastPressedNegation)
            selected++;
        if(selected >= itemCount[character])
            selected = itemCount[character]-1;

        if(last != selected) {
            changeBuffer[0] = 0;
            set_bkg_tiles(1, (last<<1) + 2, 1, 1, changeBuffer);
            changeBuffer[0] = '-';
            set_bkg_tiles(1, (selected<<1) + 2, 1, 1, changeBuffer);
            if(selected > 6 && (val & J_UP & lastPressedNegation)) {
               MEM(SCROLL_Y) = (selected - 6)<<4;
            } else if(selected < 0)
            MEM(SCROLL_Y) = 0;
            lastPressedNegation = ~val;
        }
    }
    SWITCH_ROMS(savedBank);
}
