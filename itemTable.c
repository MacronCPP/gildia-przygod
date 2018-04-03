#include "defines.c"
#include "externNonbankedFunction.c"
const unsigned char itemTable[] = {
        244, 5, 'T', 'A', 'B', 'A', 'K', 'A', 0, 0, 0, 0, 0, 0, 0, 0,
        161, 89, 'C', 'L', 'A', 'W', 'S', 0, 0, 0, 0, 0, 0, 0, 0, 0,
        97, 96, 'M', 'O', 'R', 'N', 'I', 'N', 'G', ' ', 'S', 'T', 'A', 'R', 0, 0,
        129, 153, 'B', 'O', 'W', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        97, 160, 'L', 'O', 'N', 'G', ' ', 'S', 'W', 'O', 'R', 'D', 0, 0, 0, 0,
        229, 10, 'H', 'E', 'A', 'L', 'T', 'H', ' ', 'P', 'O', 'T', 'I', 'O', 'N', 0,
        65, 5, 'C', 'A', 'P', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        65, 20, 'L', 'E', 'A', 'T', 'H', 'E', 'R', ' ', 'A', 'R', 'M', 'O', 'R', 0,
        97, 95, 'H', 'A', 'L', 'B', 'E', 'R', 'D', 0, 0, 0, 0, 0, 0, 0,
        97, 82, 'D', 'A', 'G', 'G', 'E', 'R', 0, 0, 0, 0, 0, 0, 0, 0,
        97, 76, 'R', 'O', 'D', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
extern unsigned char items[];
extern unsigned char itemCount[];
extern unsigned char enemyLoot[];
extern unsigned int money;
extern unsigned int itemTableLocation;
extern unsigned char selectedItem[];
const unsigned char chooseWeaponTitle[] = "CHOOSE WEAPON"; // length 13
const unsigned char choosePotionTitle[] = "CHOOSE POTION";
const unsigned char weaponRanged[] = "RANGED|";
const unsigned char weaponMelee[] = "MELEE|";
const unsigned char weaponDescription[] = "(%D%+% %)|";
const unsigned char potionDescription[] = "(X%, +% HP)|";
const unsigned char bareHand[] = {
    161u, 81, 'B', 'A', 'R', 'E', ' ', 'H', 'A', 'N', 'D', 'S', 0, 0, 0, 0
};

const unsigned char noneItem[] = {
    225u, 0, 'N', 'O', ' ', 'I', 'T', 'E', 'M', 'S', ' ', 'I', 'N', ' ', 'E', 'Q'
};


void chooseWeapon(unsigned char characterID) {
    unsigned char selected = 0, listSize = 0, iterator = 0, lastPressedNegation = 0, last;
    unsigned char* current;
    char buffer[1];
    if(characterID > 2) {
        if(enemyLoot[((characterID - 3)<<1) + 1] != 0) {
            copyMemory(ITEM_OF_ID(enemyLoot[((characterID - 3)<<1)]), selectedItem, 16, ITEM_BANK);
        } else
            copyMemory(bareHand, selectedItem, 16, ITEM_BANK);
        return;
    }
    buffer[0] = FRAME_TOP;
    CLEAR_WHOLE_WINDOW;
    set_win_tiles(0, 0, 1, 1, buffer);
    set_win_tiles(1, 0, 13, 1, chooseWeaponTitle);
    for(iterator = 14; iterator < 20; iterator++)
        set_win_tiles(iterator, 0, 1, 1, buffer);

    for(iterator = 0; iterator < itemCount[characterID] + 1 && listSize < 3; iterator++) {
        if(iterator == itemCount[characterID]) {
            if(listSize == 0)
                current = bareHand;
            else break;
        }
        else current = ITEM_OF_ID(ITEM_OF_CHARACTER(characterID, iterator));
        if(ITEM_IS_WEAPON(*current)) {
            set_win_tiles(2, (listSize<<1) + 1, 14, 1, current+2);
            copyToBuffer(0, weaponDescription);
            replaceInBufferInt(ITEM_AMOUNT_OF_DICES(current));
            replaceInBufferInt(ITEM_DICE_VALUES(current));
            replaceInBufferInt(ITEM_ADD_VALUE(current));
            if(ITEM_TYPE(*current) == ITEM_WEAPON_RANGED)
                replaceInBuffer(0, weaponRanged);
            else
                replaceInBuffer(0, weaponMelee);
            current = messageBuffer;
            selected = 0;
            while(*current != '|') {
                selected++;
                current++;
            }
            set_win_tiles(4, (listSize<<1) + 2, selected, 1, messageBuffer);
            listSize++;
        }
    }
    rollWindowIn(136-(listSize<<4));
    selected = 0;
    buffer[0] = '-';
    set_win_tiles(1, 1, 1, 1, buffer);
    while(1) {
        last = selected;
        iterator = joypad();
        if(iterator & J_A & lastPressedNegation) break;;
        if(iterator & J_UP & lastPressedNegation) selected--;
        if(selected == 255u)
            selected = 0;
        if(iterator & J_DOWN & lastPressedNegation)
            selected++;
        if(selected >= listSize)
            selected = listSize-1;

        if(last != selected) {
            buffer[0] = 0;
            set_win_tiles(1, (last<<1) + 1, 1, 1, buffer);
            buffer[0] = '-';
            set_win_tiles(1, (selected<<1) + 1, 1, 1, buffer);
        }
        lastPressedNegation = ~iterator;
    }
    for(iterator = 0; iterator < itemCount[characterID] + 1 && selected != 255; iterator++) {
        if(iterator == itemCount[characterID])
                current = bareHand;
        else current = ITEM_OF_ID(ITEM_OF_CHARACTER(characterID, iterator));
        if(ITEM_IS_WEAPON(*current)) {
           selected--;
        }
    }
    copyMemory(current, selectedItem, 16, ITEM_BANK);
    rollWindowBack(104);
}

void choosePotion(unsigned char characterID) {
    unsigned char selected = 0, listSize = 0, iterator = 0, lastPressedNegation = 0, last;
    unsigned char* current;
    char buffer[1];
    buffer[0] = FRAME_TOP;
    CLEAR_WHOLE_WINDOW;
    set_win_tiles(0, 0, 1, 1, buffer);
    set_win_tiles(1, 0, 13, 1, choosePotionTitle);
    for(iterator = 14; iterator < 20; iterator++)
        set_win_tiles(iterator, 0, 1, 1, buffer);

    for(iterator = 0; iterator < itemCount[characterID] + 1 && listSize < 3; iterator++) {
        if(iterator == itemCount[characterID]) {
            if(listSize == 0)
                current = noneItem;
            else break;
        }
        else current = ITEM_OF_ID(ITEM_OF_CHARACTER(characterID, iterator));
        if(ITEM_IS_POTION(*current)) {
            set_win_tiles(2, (listSize<<1) + 1, 14, 1, current+2);
            if(iterator != itemCount[characterID]) {
                copyToBuffer(0, potionDescription);
                replaceInBufferInt(AMOUNT_OF_ITEM(characterID, iterator));
                replaceInBufferInt(ITEM_HP_VALUE(current));
                current = messageBuffer;
                selected = 0;
                while(*current != '|') {
                    selected++;
                    current++;
                }
                set_win_tiles(4, (listSize<<1) + 2, selected, 1, messageBuffer);
                listSize++;
            }
        }
    }
    rollWindowIn(136-(listSize<<4));
    selected = 0;
    buffer[0] = '-';
    set_win_tiles(1, 1, 1, 1, buffer);
    while(1) {
        last = selected;
        iterator = joypad();
        if(iterator & J_A & lastPressedNegation) break;;
        if(iterator & J_UP & lastPressedNegation) selected--;
        if(selected == 255u)
            selected = 0;
        if(iterator & J_DOWN & lastPressedNegation)
            selected++;
        if(selected >= listSize)
            selected = listSize-1;

        if(last != selected) {
            buffer[0] = 0;
            set_win_tiles(1, (last<<1) + 1, 1, 1, buffer);
            buffer[0] = '-';
            set_win_tiles(1, (selected<<1) + 1, 1, 1, buffer);
        }
        lastPressedNegation = ~iterator;
    }
    for(iterator = 0; iterator < itemCount[characterID] + 1 && selected != 255; iterator++) {
        if(iterator == itemCount[characterID])
                current = noneItem;
        else current = ITEM_OF_ID(ITEM_OF_CHARACTER(characterID, iterator));
        if(ITEM_IS_POTION(*current)) {
           selected--;
        }
    }
    copyMemory(current, selectedItem, 16, ITEM_BANK);
    if(selectedItem[1]) {
        deleteItem(characterID, ITEM_OF_CHARACTER(characterID, iterator-1), 1);
    }
    rollWindowBack(104);
}
