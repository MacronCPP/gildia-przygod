#include "skillStructs.c"

unsigned char* temporaryFightPointer;
unsigned char fightResult, isRanged;
/*CharacterStateEncounter
 * - 1B - currentHP
 * - 1B - currentArmor
 * - 1B - status - 2b - stunLength, 3b - modifiersAmount
 * - 7B - modifier - 2b - length, 3b - statistic, 3b - (unsigned value - 1)*5 - 40 max
 * - 1B - modifiers signs - 1b per modifer
 * */
unsigned char characterBufferTable[8];
unsigned char characterStateMemory[6*CHARACTER_STATE_LENGTH];
struct Encounter {
    unsigned char encounterHeader;
    unsigned char backgroundBank;
    unsigned char* background;
    unsigned char tilesetBank;
    unsigned char* tileset;
    unsigned char* loot;
    unsigned char* firstEnemy;
    unsigned char* firstEnemySkills;
    unsigned char* secondEnemy;
    unsigned char* secondEnemySkills;
    unsigned char* thirdEnemy;
    unsigned char* thirdEnemySkills;
};

unsigned char encounterHeader = 0;
extern const unsigned char arenaMap[];
unsigned char* enemies[6];
void loadEncounter(const unsigned char* memory, unsigned char bank) {
    unsigned char iterator = 0, toLoad = 0, loaded = 0;
    unsigned char savedBank = currentBank;
    unsigned int savedMap = (unsigned int)currentMap;
    struct Encounter* encounter = (struct Encounter*)memory;

    SWITCH_ROMS(bank);
    enemies[0] = encounter->tileset; //Optimalizing with using again variable. It's pointer so...
    enemies[2] = (unsigned char*)currentMapBank; //...ditto. dumping loaded map to not overwriting it
    CLEAR_WHOLE_SCREEN;
    SWITCH_ROMS(encounter->tilesetBank);
    set_bkg_data(0, 255, enemies[0]);
    set_win_data(0, 128, enemies[0]);
    SWITCH_ROMS(bank);

    loadMap(encounter->backgroundBank, encounter->background, 20, 16);
    SWITCH_ROMS(bank);
    currentMap = (unsigned char*)savedMap;
    currentMapBank = (unsigned char)enemies[2];


    enemies[0] = encounter->firstEnemy;
    enemies[1] = encounter->firstEnemySkills;
    enemies[2] = encounter->secondEnemy;
    enemies[3] = encounter->secondEnemySkills;
    enemies[4] = encounter->thirdEnemy;
    enemies[5] = encounter->thirdEnemySkills;
    copyMemory(encounter->loot, enemyLoot, ENEMY_LOOT_TABLE_LENGTH, bank);
    encounterHeader = encounter->encounterHeader;
    zero(characterStateMemory, 6*CHARACTER_STATE_LENGTH);
    zero(enemyMemory, 3*15);
    zero(enemySkillMemory, 3*CHARACTER_SKILLS_LENGTH);
    for(iterator = 0; iterator < 3; iterator++) {
        toLoad = 0;
        if((encounter->encounterHeader & 3) == 1) {
            toLoad = (iterator == 1);
        } else if((encounter->encounterHeader & 3) == 2) {
            toLoad = (iterator != 1);
        } else
            toLoad = 1;

        if(toLoad) {
            copyMemory(enemies[loaded], enemyMemory+CHARACTER_LENGTH*iterator, CHARACTER_LENGTH, bank);
            copyMemory(enemies[loaded+1], enemySkillMemory+CHARACTER_SKILLS_LENGTH*iterator, CHARACTER_SKILLS_LENGTH, bank);
            characterStateMemory[CHARACTER_STATE_LENGTH*(3+iterator)] = enemies[loaded][1];
            loaded += 2;
        }
    }
    if((loaded >> 1) != encounter->encounterHeader & 3)
        delay(20000);
    SWITCH_ROMS(savedBank);
}


void runFunction(struct Character* target, struct Skill* skill) {
    unsigned char savedBank = currentBank;
    SWITCH_ROMS(skill->stats.function.bank);
    temporaryFightPointer = (char*)target;
    ((skill->stats).function.function());
    SWITCH_ROMS(savedBank);
}
