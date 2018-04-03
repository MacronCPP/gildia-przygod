#include "defines.c"
const unsigned char arenaMap[] = {14, 204, 13, 12, 204, 78, 13, 204, 76, 13, 206, 77, 14, 206, 12, 224, 0, 64, 48, 64, 96, 32, 0, 49,
                                  92, 254, 174, 124, 252, 28, 238, 252, 93, 221, 237, 125, 253, 222, 44, 64, 0, 0, 49, 0, 0, 0, 0, 0,
                                  190, 222, 29, 172, 236, 93, 92, 253, 109, 109, 237, 46, 189, 220, 189, 0, 0, 0, 49, 0, 0, 0, 0, 0,
                                  156, 237, 44, 189, 254, 124, 252, 253, 125, 190, 222, 109, 124, 222, 92, 48, 16, 48, 0, 0, 49, 0, 0, 0,
                                  222, 236, 157, 222, 238, 94, 236, 237, 158, 174, 254, 156, 190, 252, 94, 0, 32, 0, 0, 64, 64, 64, 0, 0,
                                  43, 107, 107, 134, 199, 239, 171, 171, 235, 134, 199, 239, 171, 171, 200, 0, 0, 0, 0, 16, 0, 64, 50, 16,
                                  123, 123, 123, 214, 215, 255, 251, 187, 251, 214, 215, 255, 251, 187, 216, 0, 0, 0, 0, 0, 0, 0, 0, 16,
                                  128, 64, 64, 192, 49, 176, 49, 0, 0, 0, 48, 0, 0, 48, 40, 0, 0, 48, 192, 0, 80, 0, 0, 0,
                                  128, 65, 98, 162, 34, 162, 162, 34, 162, 162, 34, 162, 130, 0, 168, 0, 0, 0, 0, 112, 64, 113, 0, 0,
                                  128, 83, 64, 0, 0, 16, 0, 48, 0, 0, 0, 0, 19, 0, 40, 0, 50, 0, 64, 16, 0, 0, 0, 0,
                                  128, 83, 64, 64, 0, 1, 162, 34, 162, 0, 0, 128, 19, 0, 40, 0, 0, 0, 0, 0, 0, 48, 50, 0,
                                  128, 83, 80, 48, 48, 19, 0, 0, 0, 64, 0, 242, 19, 16, 40, 0, 0, 0, 192, 0, 128, 0, 0, 0,
                                  128, 81, 98, 162, 34, 163, 162, 34, 162, 162, 34, 226, 146, 0, 168, 0, 16, 0, 50, 114, 64, 48, 0, 0,
                                  128, 64, 64, 96, 0, 19, 0, 16, 0, 64, 0, 208, 0, 0, 40, 48, 0, 49, 0, 0, 0, 0, 0, 0,
                                  144, 64, 64, 192, 0, 83, 0, 0, 50, 64, 0, 192, 64, 16, 40, 16, 0, 0, 0, 16, 0, 0, 0, 0,
                                  128, 64, 64, 0, 32, 17, 162, 34, 162, 114, 0, 128, 0, 0, 40, 0, 0, 0, 64, 0, 50, 0, 0, 0,
                                  144, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 40, 0, 0, 0, 0, 114, 64, 0, 50, 0,
                                  171, 171, 235, 171, 171, 235, 171, 171, 235, 171, 171, 235, 171, 171, 235, 0, 0, 16, 164, 0, 64, 49, 32, 0,
                                  251, 187, 251,  251, 187, 251, 251, 187, 251, 251, 187, 251, 251, 187, 251, 0, 0, 32, 0, 32, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 49, 0, 0, 0, 48, 64, 0, 0, 0, 32, 0, 0, 0, 0, 50, 0, 0,
                                  49, 48, 0, 192, 0, 64, 64, 0, 0, 64, 0, 0, 0, 0, 0, 128, 0, 50, 0, 0, 0, 0, 16, 16,
                                  0, 0, 48, 177, 50, 0, 177, 0, 16, 128, 48, 50, 0, 0, 16, 0, 32, 49, 0, 0, 0, 0, 0, 0,
                                  16, 48, 0, 0, 0, 0, 0, 32, 0, 192, 0, 128, 192, 0, 0, 16, 0, 0, 50, 32, 50, 0, 0, 0,
                                  0, 49, 0, 0, 0, 0, 16, 0, 16, 0, 0, 0, 0, 0, 32, 49, 16, 0, 0, 0, 0, 64, 0, 0,
                                  64, 50, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 32, 0, 32, 16, 16, 0, 0, 0, 0, 0,
                                  0, 49, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 50, 144, 0, 0, 16, 0, 48,
                                  0, 0, 0, 0, 32, 49, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 144, 0, 0, 0, 0, 0,
                                  0, 0, 0, 48, 0, 0, 0, 48, 49, 0, 16, 0, 16, 0, 0, 192, 0, 160, 16, 16, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 16, 0, 32, 0, 0, 16, 0, 0, 49, 0, 0, 0, 50, 0, 16, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 50, 0, 192, 0, 16, 0, 0, 0, 0, 48, 0, 208, 0, 128, 0, 0, 0,
                                  0, 16, 0, 192, 48, 128, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 16, 0, 16, 0, 0, 0, 48,
                                  0, 0, 0, 192, 0, 128, 0, 0, 0, 0, 32, 50, 0, 0, 49, 0, 0, 0, 0, 16, 0, 0, 0, 0};
const unsigned char arenaEvents[] =
{
10, 2,
EVENT_CONDITION_BITFLAG, ARENA_WELCOME, 0, 0,
EVENT_CONDITION_POSITION, 10, 7, 0,
23,
EVENT_MESSAGE, 0x7FU, 0x5FU/*pointerENTRY_A*/, 5, FLAG_WINDOW_IN,
EVENT_MOVE_CAMERA, 80, 80, 100U, 0,
EVENT_LOCK_CAMERA, 0, 0, 0, 0,
EVENT_SET_BITFLAG, ARENA_WELCOME, 1, 0, 0,
EVENT_MESSAGE, 0x9EU, 0x5FU/*pointerENTRY_B*/, 5, 0,
EVENT_MESSAGE, 0xC5U, 0x5FU/*pointerNAME_A*/, 5, 0, //6
EVENT_MESSAGE, 0xEFU, 0x5FU/*pointerNAME_B*/, 5, 0,
EVENT_MESSAGE, 0xD3U, 0x61U/*pointerARKEITZ_CONFUSED*/, 5, 0,
EVENT_MESSAGE, 0xF5U, 0x61U/*pointerRYSZARD_CALM*/, 5, 0,
EVENT_MESSAGE, 0x08U, 0x60U/*pointerAPPLAUSE*/, 5, 0,
EVENT_MESSAGE, 0x29U, 0x60U/*pointerFIGHT_AMOUNT*/, 5, 0,
EVENT_MESSAGE, 0x32U, 0x62U/*pointerARKEITZ_ANGRY*/, 5, 0,
EVENT_MESSAGE, 0x58U, 0x60U/*pointerMONEY_AMOUNT*/, 5, 0,
EVENT_MESSAGE, 0x4AU, 0x62U/*pointerTHIDEM_DEAL*/, 5, 0,
EVENT_MESSAGE, 0x6EU, 0x62U/*pointerARKEITZ_ANGRY2*/, 5, 0,//15
EVENT_MESSAGE, 0x80U, 0x60U/*pointerFIRST_ENEMY*/, 5, FLAG_WINDOW_OUT,
EVENT_FADE_OUT, 50, 0, 0, 0,
EVENT_CHANGE_TILE, 10, 13, 150U, 0, //9*16+6
EVENT_CHANGE_TILE, 10, 14, 166U, 0, //10*16+6
EVENT_FADE_IN, 50, 0, 0, 0, //20
EVENT_DELAY, 0, 4, 0, 0,
EVENT_MESSAGE, 0x9AU, 0x60U/*pointerFIRST_ENEMY_DESCRIPTION*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0xA8U, 0x62U/*pointerTHIDEM_LETS*/, 5, FLAG_WINDOW_OUT, //23

2,
EVENT_CONDITION_POSITION, 10, 12, 0,
EVENT_CONDITION_BITFLAG, WAS_FIRST_FIGHT, 0, 0,
3, // FIRST FIGHT
EVENT_SET_BITFLAG, WAS_FIRST_FIGHT, 1, 0, 0,
EVENT_TELEPORT, 10, 11, 0, 0,
EVENT_ENCOUNTER, 0xD0U, 0x5EU/*pointerFIRST_ARENA_FIGHT*/, 5, 0,
1,
EVENT_CONDITION_BITFLAG, loseFight, 1, 0,
1,
EVENT_LOSE, 0, 0, 0, 0,

3, // AFTER FIRST FIGHT
EVENT_CONDITION_BITFLAG, WAS_FIRST_FIGHT, 1, 0,
EVENT_CONDITION_BITFLAG, WAS_SECOND_FIGHT, 0, 0,
EVENT_CONDITION_BITFLAG, READY_FOR_NEXT_FIGHT, 0, 0,
12,
EVENT_MESSAGE, 0xC2U, 0x60U/*pointerWON_FIRST_FIGHT_A*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0xE9U, 0x60U/*pointerWON_FIRST_FIGHT_B*/, 5, 0,
EVENT_MESSAGE, 0x1CU, 0x63U/*pointerRYSZARD2*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0xC5U, 0x62U/*pointerARKEITZ2*/, 5, 0,
EVENT_MESSAGE, 0x54U, 0x61U/*pointerSECOND_ENEMY*/, 5, FLAG_WINDOW_OUT,
EVENT_FADE_OUT, 50, 0, 0, 0,
EVENT_CHANGE_TILE, 10, 13, 9*16+7, 0,
EVENT_CHANGE_TILE, 10, 14, 10*16+7, 0,
EVENT_FADE_IN, 50, 0, 0, 0, //20
EVENT_DELAY, 0, 6, 0, 0,
EVENT_MESSAGE, 0x76U, 0x61U/*pointerSECOND_ENEMY_DESCRIPTION*/, 5, FLAG_WINDOW_IN | FLAG_WINDOW_OUT,
EVENT_SET_BITFLAG, READY_FOR_NEXT_FIGHT, 1, 0, 0,

4,
EVENT_CONDITION_POSITION, 10, 12, 0,
EVENT_CONDITION_BITFLAG, WAS_FIRST_FIGHT, 1, 0,
EVENT_CONDITION_BITFLAG, WAS_SECOND_FIGHT, 0, 0,
EVENT_CONDITION_BITFLAG, READY_FOR_NEXT_FIGHT, 1, 0,
4,
EVENT_SET_BITFLAG, READY_FOR_NEXT_FIGHT, 0, 0, 0,
EVENT_SET_BITFLAG, WAS_SECOND_FIGHT, 1, 0, 0,
EVENT_TELEPORT, 10, 11, 0, 0,
EVENT_ENCOUNTER, 0xE5U, 0x5EU/*pointerSECOND_ARENA_FIGHT*/, 5, 0,
1,
EVENT_CONDITION_BITFLAG, loseFight, 1, 0,
1,
EVENT_LOSE, 0, 0, 0, 0,

3, // AFTER SECOND FIGHT
EVENT_CONDITION_BITFLAG, WAS_SECOND_FIGHT, 1, 0,
EVENT_CONDITION_BITFLAG, WAS_THIRD_FIGHT, 0, 0,
EVENT_CONDITION_BITFLAG, READY_FOR_NEXT_FIGHT, 0, 0,
12,
EVENT_MESSAGE, 0x0DU, 0x61U/*pointerWON_SECOND_FIGHT_A*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0x34U, 0x61U/*pointerWON_SECOND_FIGHT_B*/, 5, 0,
EVENT_MESSAGE, 0x2BU, 0x63U/*pointerRYSZARD3*/, 5, 0,
EVENT_MESSAGE, 0x8CU, 0x61U/*pointerTHIRD_ENEMY*/, 5, FLAG_WINDOW_OUT,
EVENT_FADE_OUT, 50, 0, 0, 0,
EVENT_CHANGE_TILE, 10, 13, 7*16+9, 0,
EVENT_CHANGE_TILE, 10, 14, 8*16+9, 0,
EVENT_FADE_IN, 50, 0, 0, 0, //20
EVENT_DELAY, 0, 6, 0, 0,
EVENT_MESSAGE, 0xBFU, 0x61U/*pointerTHIRD_ENEMY_DESCRIPTION*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0xF5U, 0x62U/*pointerARKEITZ3*/, 5, FLAG_WINDOW_OUT,
EVENT_SET_BITFLAG, READY_FOR_NEXT_FIGHT, 1, 0, 0,

4,
EVENT_CONDITION_POSITION, 10, 12, 0,
EVENT_CONDITION_BITFLAG, WAS_SECOND_FIGHT, 1, 0,
EVENT_CONDITION_BITFLAG, WAS_THIRD_FIGHT, 0, 0,
EVENT_CONDITION_BITFLAG, READY_FOR_NEXT_FIGHT, 1, 0,
4,
EVENT_SET_BITFLAG, READY_FOR_NEXT_FIGHT, 0, 0, 0,
EVENT_SET_BITFLAG, WAS_THIRD_FIGHT, 1, 0, 0,
EVENT_TELEPORT, 10, 11, 0, 0,
EVENT_ENCOUNTER, 0xF6U, 0x5EU/*pointerTHIRD_ARENA_FIGHT*/, 5, 0,

1,
EVENT_CONDITION_BITFLAG, loseFight, 1, 0,
1,
EVENT_LOSE, 0, 0, 0, 0,

1,
EVENT_CONDITION_BITFLAG, WAS_THIRD_FIGHT, 1, 0, //ENDING
10,
EVENT_MESSAGE, 0x66U, 0x63U/*pointerENDING*/, 5, FLAG_WINDOW_IN,
EVENT_MESSAGE, 0x9FU, 0x63U/*pointerENDING_PRIZE*/, 5, 0,
EVENT_MESSAGE, 0xBAU, 0x63U/*pointerENDING_PRIZE_RYSZ*/, 5, 0,
EVENT_MESSAGE, 0xF8U, 0x63U/*pointerENDING_TEAM_ROLL*/, 5, 0,
EVENT_MESSAGE, 0x2BU, 0x64U/*pointerENDING_ANOUNCER_ROLL*/, 5, 0,
EVENT_MESSAGE, 0x55U, 0x64U/*pointerENDING_ANOUNCER*/, 5, 0,
EVENT_MESSAGE, 0x74U, 0x64U/*pointerENDING_OH*/, 5, FLAG_WINDOW_OUT,
EVENT_MOVE_CAMERA, 80, 56, 0, 0,
EVENT_FADE_OUT, 50U, 1, 0, 0,
EVENT_WON, 0, 0, 0, 0
};

const char ratEnemyA[] = {
        1, 20, 3, 0xB1U, 0x60U/*pointerfirstEnemy*/, 0xADU, 0x4EU/*pointerenemy_ratData*/, 35, 70, 40, 40, 20, 0, 0, 0
};
const char bullEnemy[] = {
        1, 30, 3, 0xB6U, 0x60U/*pointersecondEnemy*/, 0xB1U, 0x5AU/*pointerenemy_bullData*/, 60, 50, 40, 40, 30, 0, 0, 0
};
const char ratEnemyB[] = {
        1, 20, 3, 0xBDU, 0x60U/*pointerthirdEnemy*/, 0xADU, 0x4EU/*pointerenemy_ratData*/, 35, 70, 40, 40, 20, 0, 0, 0
};
const char rhinoEnemyA[] = {
        1, 50, 3, 0xC5U, 0x60U/*pointerfourthEnemy*/, 0xAFU, 0x54U/*pointerenemy_rhinoData*/, 70, 50, 50, 50, 50, 0, 0, 0
};
const char rhinoEnemyB[] = {
        1, 45, 3, 0xCDU, 0x60U/*pointerfifthEnemy*/, 0xAFU, 0x54U/*pointerenemy_rhinoData*/, 70, 50, 50, 50, 45, 0, 0, 0
};
const char turtleEnemy[] = {
        1, 80, 3, 0xD5U, 0x60U/*pointersixthEnemy*/, 0xABU, 0x48U/*pointerenemy_turtleData*/, 45, 90, 70, 70, 80, 0, 0, 0
};

const char firstLootTable[] = {
  3, 9, 1, 0, 0, 9, 1
};
const char secondLootTable[] = {
  3, 10, 1, 0, 0, 10, 1
};
const char thirdLootTable[] = {
  0, 0, 8, 1, 0, 0
};
const char FIRST_ARENA_FIGHT[] = {3, 3, 0x9BU, 0x47U/*pointerarenaFight*/,
                          5, 0x85U, 0x64U/*pointertileset_fight_arenaData*/, 0xBCU, 0x5EU/*pointerfirstLootTable*/
                               , 0x62U, 0x5EU/*pointerratEnemyA*/, 0x2BU, 0x5FU/*pointerratSkillSet*/, 0x71U, 0x5EU/*pointerbullEnemy*/, 0x40U, 0x5FU/*pointerbullSkillSet*/, 0x80U, 0x5EU/*pointerratEnemyB*/, 0x2BU, 0x5FU/*pointerratSkillSet*/};

const char SECOND_ARENA_FIGHT[] = {2, 3, 0x9BU, 0x47U/*pointerarenaFight*/,
                          5, 0x85U, 0x64U/*pointertileset_fight_arenaData*/, 0xC3U, 0x5EU/*pointersecondLootTable*/
                               , 0x8FU, 0x5EU/*pointerrhinoEnemyA*/, 0x55U, 0x5FU/*pointerrhinoSkillSet*/, 0x9EU, 0x5EU/*pointerrhinoEnemyB*/, 0x55U, 0x5FU/*pointerrhinoSkillSet*/};

const char THIRD_ARENA_FIGHT[] = {1, 3, 0x9BU, 0x47U/*pointerarenaFight*/,
                          5, 0x85U, 0x64U/*pointertileset_fight_arenaData*/, 0xCAU, 0x5EU/*pointerthirdLootTable*/
                               , 0xADU, 0x5EU/*pointerturtleEnemy*/, 0x6AU, 0x5FU/*pointerturtleSkillSet*/};

const char attackNameDescription[] = "ATTACK|";
const char smokeBombNameDescription[] = "SMOKE BOMB|";
const char kickNameDescription[] = "KICK|";
const char biteNameDescription[] = "BITE|";
const char chargeNameDescription[] = "CHARGE|";
const char ratSkillSet[] = {
        1, 0, 0, 0, 0x03U, 0x5FU/*pointerattackNameDescription*/, 5,
        36, 40, 36, 68, 0x0BU, 0x5FU/*pointersmokeBombNameDescription*/, 5,
        0, 0, 0, 0, 0, 0, 0};

const char bullSkillSet[] = {
    1, 0, 0, 0, 0x03U, 0x5FU/*pointerattackNameDescription*/, 5,
    0, 24, 0, 0, 0x17U, 0x5FU/*pointerkickNameDescription*/, 5,
    0, 0, 0, 0, 0, 0, 0};

const char rhinoSkillSet[] = {
    1, 0, 0, 0, 0x03U, 0x5FU/*pointerattackNameDescription*/, 5,
    0, 24, 0, 0, 0x23U, 0x5FU/*pointerchargeNameDescription*/, 5,
    0, 0, 0, 0, 0, 0, 0};

const char turtleSkillSet[] = {
    1, 0, 0, 0, 0x03U, 0x5FU/*pointerattackNameDescription*/, 5,
    4, 32, 36, 4, 0x1DU, 0x5FU/*pointerbiteNameDescription*/, 5,
    0, 0, 0, 0, 0, 0, 0};

//9*16+6
//Enemy y - 12
//Enemy x - 10
const unsigned char ENTRY_A[] = "|WELCOME TO THE BENT'S ARENA!|";
const unsigned char ENTRY_B[] = "|TODAY, ON THIS ARENA, WE WILL SEE...|";
const unsigned char NAME_A [] = "|DELTA SZWADRON... EKHM... SUPER COOL...|";
const unsigned char NAME_B [] = "|COMMANDO ALPHA WOLVES!|";
const unsigned char APPLAUSE [] = "|GIVE THEM A ROUND OF APPLAUSE!|";
const unsigned char FIGHT_AMOUNT [] = "|THEY WON'T HAVE ONLY A ONE FIGHT, BUT THREE!|";
const unsigned char MONEY_AMOUNT [] = "|TRIPLE THE FIGHTS - DOUBLE THE MONEY!|";
const unsigned char FIRST_ENEMY  [] = "|THEIR FIRST ENEMY IS...|";
const unsigned char FIRST_ENEMY_DESCRIPTION  [] = "|THE TLYUGA TEAM, A BULL AND TWO RATS!|";

const unsigned char WON_FIRST_FIGHT_A[] = "|THE WOLVES JUST WON THE FIRST FIGHT!|";
const unsigned char WON_FIRST_FIGHT_B[] = "|BUT WILL THEY WIN THE SECOND ONE?|";

const unsigned char WON_SECOND_FIGHT_A[] = "|LOOKS LIKE THE WOLVES MADE IT AGAIN!|";
const unsigned char WON_SECOND_FIGHT_B[] = "|ONLY ONE FIGHT LEFT FOR THEM!|";

const unsigned char SECOND_ENEMY[] = "|THEIR SECOND ENEMY WILL BE... !|";
const unsigned char SECOND_ENEMY_DESCRIPTION  [] = "|THE RHINO BROTHERS!|";

const unsigned char THIRD_ENEMY[] = "|THEIR LAST, THE MOST POWERFUL ENEMY WILL BE... !|";
const unsigned char THIRD_ENEMY_DESCRIPTION  [] = "|DREEN THE TURTLE!|";

const unsigned char ARKEITZ_CONFUSED[] = "ARKEITZ|...THAT'S A STUPID IDEA.|";
const unsigned char RYSZARD_CALM[] = "RYSZARD|...THAT'S NOT A STUPID IDEA, BELIEVE ME, WE'LL WIN.|";
const unsigned char ARKEITZ_ANGRY[] = "ARKEITZ|...WAIT, WHAT?|";
const unsigned char THIDEM_DEAL[] = "THIDEM|WE COULD GET A BETTER DEAL.|";
const unsigned char ARKEITZ_ANGRY2[] = "ARKEITZ|THAT'S THE WORST DEAL YOU'VE... WE'VE EVER TOOK.|";
const unsigned char THIDEM_LETS[] = "THIDEM|LET'S APPROACH THEM.|";
//Some dialogs for afterfight
const unsigned char ARKEITZ2[] = "ARKEITZ|AH, I HOPE THE PRIZE WILL BE WORTH IT.|";
const unsigned char ARKEITZ3[] = "ARKEITZ|OH, FU. I MEAN DAMN. COME ON!|";

const unsigned char RYSZARD2[] = "RYSZARD|EASY.|";
const unsigned char RYSZARD3[] = "RYSZARD|TAKE THAT, YOU RHINOS.|";

const unsigned char THIDEM2[] = "THIDEM||";
const unsigned char THIDEM3[] = "THIDEM||";

const unsigned char FIGHT_DEBUG[] = "|FIGHT!|";

const unsigned char ENDING[] = "|THE WOLVES HAS WON ALL THE FIGHTS! THE PRIZE IS YOURS!|";
const unsigned char ENDING_PRIZE[] = "|THE PRIZE OF... 20 GOLD!|";
const unsigned char ENDING_PRIZE_RYSZ[] = "RYSZARD|WASN'T 20 GOLD A NORMAL PRIZE? WE SHOULD GET DOUBLE!|";
const unsigned char ENDING_TEAM_ROLL[] = "|THE TEAM HAS ROLLED 40(13, 44, -17) FOR CHARISMA|";
const unsigned char ENDING_ANOUNCER_ROLL[] = "|THE ANOUNCER HAS ROLLED 20 FOR CHARISMA|";
const unsigned char ENDING_ANOUNCER[] = "|20 GOLD IS DOUBLE THE PRIZE.|";
const unsigned char ENDING_OH[] = "THIDEM|...OH.|";
