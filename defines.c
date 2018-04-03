
#define SET_USHORT(x, y) (*((unsigned short*)x)=y)
#define SET_ULONG(x, y) (*((unsigned long*)x)=y)
#define SET_UBYTE(x, y) (*((unsigned char*)x)=y)

#define MEM(x) ((*(unsigned char *)(x)))
#define SET(x, y) while(MEM(x) != y) MEM(x) = y;

#define SECOND_SWITCH_ROMS(x)       (MEM(0x4000) = x)
#define BANK_MODE_SELECTING(x)      (MEM(0x6000) = x)
#define SELECT_WINDOW_TABLE_1   (MEM(0xFF40) |= 64)
#define SELECT_BACKGROUND_TABLE_1  (MEM(0xFF40) |= 8)
#define SELECT_TILEPATTERN_TABLE_1 (MEM(0xFF40) |= 16)
#define SELECT_WINDOW_TABLE_0   (MEM(0xFF40) &= 64)
#define SELECT_BACKGROUND_TABLE_0  (MEM(0xFF40) &= 8)
#define SELECT_TILEPATTERN_TABLE_0 (MEM(0xFF40) &= 16)
#define WAIT_FOR_NO_LCD             while(MEM(0xFF41) & 3)
#define DISABLE_INTERRUPTS          MEM(0xFFFF) = 0
#define ENABLE_INTERRPUTS           (MEM(0xFF41) = 0)
#define RESET_CMPLINE               (MEM(0xFF45) = 180U)

#define HIDE_SPRITES_MEM (MEM(0xFF40) &= 253U)
#define SHOW_SPRITES_MEM (MEM(0xFF40) |= 2)

#define CHARACTER_SPRITE(x, n) ((x << 2) + n + 1)

extern void zero(void* s, unsigned int sz);
extern void zeroVRAM(void* s, unsigned int sz);

#define BITFLAG_BIT(n)      ((1)                    << ((n) & 7))
#define BITFLAG_BYTE(n)     (bitflag[((n) & 248U)   >> 3])
#define GET_BITFLAG(n)      (((BITFLAG_BYTE(n)      & (1 << ((n) & 7))) ) > 0)
#define CLEAR_BITFLAG(n)    (BITFLAG_BYTE(n)        &= ~BITFLAG_BIT(n))
#define SET_BITFLAG(n, v)   if(v)  (BITFLAG_BYTE(n) |= BITFLAG_BIT(n)); else CLEAR_BITFLAG(n)

#define CMPLINE MEM(0xFF45U)

#define BACKGROUND_PALETTE_LOCATION 0xFF47U
#define SPRITE0_PALETTE_LOCATION 0xFF48U
#define SPRITE1_PALETTE_LOCATION 0xFF49U

#define BACKGROUND_PALETTE MEM(BACKGROUND_PALETTE_LOCATION)
#define SPRITE0_PALETTE MEM(SPRITE0_PALETTE_LOCATION)
#define SPRITE1_PALETTE MEM(SPRITE1_PALETTE_LOCATION)

#define LIGHTEST_PALETTE 0
#define DARKEST_PALETTE 255U

#define MENU_FIRST 0
#define MENU_SECOND 1
#define MENU_THIRD 2
#define MENU_FOURTH 3
#define MENU_BACK 255U

#define FLAG_WINDOW_IN 1
#define FLAG_WINDOW_OUT 2
#define FLAG_MENU_BACKABLE 4 //Only used in code.
#define FLAG_NO_TITLE 4
#define FLAG_DONT_CHANGE_BANK 8

#define FRAME_TOP ('A'-1)

#define WHO_STARTS(x) (x >> 4 >> 2)
#define NO_ONE_STARTS 0
#define PLAYER_STARTS 1
#define ENEMY_STARTS  2

#define TILE_UNCOMPRESS_COMBINED(address) (((MEM(address) & 0xC0U) >> 2) | ((MEM(address+1) & 0xC0U) >> 4) | ((MEM(address+2) & 0xC0U) >> 6))
#define TILE_UNCOMPRESS_PLAIN(address) (MEM(address) & 63)

#define GB_TILE(tile) (tile+112U)

#define MAP(address, x, y) ()

#define	J_START      0x80U
#define	J_SELECT     0x40U
#define	J_B          0x20U
#define	J_A          0x10U
#define	J_DOWN       0x08U
#define	J_UP         0x04U
#define	J_LEFT       0x02U
#define	J_RIGHT      0x01U

#define SKILL_STUN 0
#define SKILL_ATTACK 1
#define SKILL_FUNCTION 2
#define SKILL_STAT_REDUCTION 4
#define SKILL_STAT_BOOST 5


#define MAP (0x9800U)
#define WINDOW (0x9C00U)
#define SCROLL_X (0xFF43U)
#define SCROLL_Y (0xFF42U)
#define WINDOW_POSITION_X (0xFF4BU)
#define WINDOW_POSITION_Y (0xFF4AU)
#define SPRITE_TABLE (0xFE00U)
#define TILE_OVERWORLD_CHARACTER (176U)
#define TILE_OVERWORLD_CHARACTER_SECOND (192U)
#define TILE_OVERWORLD_CHARACTER_SECOND_TRANSLATION(x) (x + 16U)

#define CLEAR_MAIN_SCREEN zeroVRAM((void*)MAP, 576)
#define CLEAR_WHOLE_SCREEN zeroVRAM((void*)MAP, 1024)

#define CLEAR_MESSAGE_WINDOW zeroVRAM((void*)WINDOW, 240)
#define CLEAR_WHOLE_WINDOW zeroVRAM((void*)WINDOW, 1024)

#define CLEAR_MAIN_SCREEN_SAFE WAIT_FOR_NO_LCD; CLEAR_MAIN_SCREEN_UNSAFE
#define CLEAR_WHOLE_SCREEN_SAFE WAIT_FOR_NO_LCD; CLEAR_WHOLE_SCREEN_UNSAFE

#define CLEAR_MESSAGE_WINDOW_SAFE WAIT_FOR_NO_LCD; CLEAR_MESSAGE_WINDOW_UNSAFE
#define CLEAR_WHOLE_WINDOW_SAFE WAIT_FOR_NO_LCD; CLEAR_WHOLE_WINDOW_UNSAFE


#define OAM_TRANSFER_TABLE 0xC000U
#define OAM_TRANSFER_LOCATION 0xFF46U
#define CLEAR_OAM_TRANSFER_TABLE zero((void*)OAM_TRANSFER_TABLE, 160)

#define OAM_SET_SPRITE_POSITION_X(n, x) (MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2) + 1) = x)
#define OAM_SET_SPRITE_POSITION_Y(n, y) (MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2)) = y)
#define OAM_SET_SPRITE_TILE(n, tile) (MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2) + 2) = tile)
#define OAM_SET_SPRITE_PROP(n, prop) (MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2) + 3) = prop)

#define SET_SPRITE_POSITION_X(n, x) (MEM(SPRITE_TABLE + (((long int)n)<<2) + 1) = x)
#define SET_SPRITE_POSITION_Y(n, y) (MEM(SPRITE_TABLE + (((long int)n)<<2)) = y)
#define SET_SPRITE_TILE(n, tile) (MEM(SPRITE_TABLE + (((long int)n)<<2) + 2) = tile)
#define SET_SPRITE_PROP(n, prop) (MEM(SPRITE_TABLE + (((long int)n)<<2) + 3) = prop)

#define SAFE_SET_SPRITE_POSITION_X(n, x) SET(SPRITE_TABLE + (((long int)n)<<2) + 1, x)
#define SAFE_SET_SPRITE_POSITION_Y(n, y) SET(SPRITE_TABLE + (((long int)n)<<2), y)
#define SAFE_SET_SPRITE_TILE(n, tile)    SET(SPRITE_TABLE + (((long int)n)<<2) + 2, tile)
#define SAFE_SET_SPRITE_PROP(n, prop)         SET(SPRITE_TABLE + (((long int)n)<<2) + 3, prop)

#define GET_SPRITE_POSITION_X(n) MEM(SPRITE_TABLE + (((long int)n)<<2) + 1)
#define GET_SPRITE_POSITION_Y(n) MEM(SPRITE_TABLE + (((long int)n)<<2))

#define OAM_GET_SPRITE_POSITION_X(n) MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2) + 1)
#define OAM_GET_SPRITE_POSITION_Y(n) MEM(OAM_TRANSFER_TABLE + (((long int)n)<<2))

#define EVENT_MESSAGE 0
#define EVENT_GET_ITEM 1 // Not implemented
#define EVENT_LOSE_ITEM 2 // Not implemented
#define EVENT_CHANGE_TILE 3
#define EVENT_CHANGE_MAP 4
#define EVENT_ENCOUNTER 5
#define EVENT_TELEPORT 6
#define EVENT_DELAY 7
#define EVENT_MOVE_CAMERA 8
#define EVENT_ROLL_OUT_WINDOW 9
#define EVENT_ROLL_IN_WINDOW 10
#define EVENT_LOCK_CAMERA 11
#define EVENT_UNLOCK_CAMERA 12
#define EVENT_SET_BITFLAG 13
#define EVENT_FADE_OUT 14
#define EVENT_FADE_IN 15
#define EVENT_LOSE 16
#define EVENT_WON 17
#define EVENT_FUNCTION 31

#define GET_MAP_BANK(x, y) (((x >> 4 >> 1)<<3) | (y >> 4 >> 1))

#define CAMERA_MOVING 1

#define REACTION_TYPE(x) ((x) & 3)
#define REACTION_HIT 0
#define REACTION_MISS 1
#define REACTION_CHEER 2
#define REACTION_NONE 3

#define REACTION_SKILL_ID(x) (((x) >> 2) & 3)
#define REACTION_PERSON_ID(x) (((x) >> 4) & 3)
#define COMBINE_REACTION_FLAG(person, skill, type) (((person) << 4) | ((skill) << 2) | (type))

#define TRY_STATISTIC_MODIFIER(x) ((x) >> 3)
#define TRY_PERSON_ID(x) ((x) & 7)
#define COMBINE_TRY_FLAG(id, modifier) ((((modifier)/5) << 3) | (id))

#define SET_SKILL_ANIMATION(attacker, n) OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(attacker, 0), CHARACTER_SKILL_ANIMATION+((n)<<1)+((attacker) > 2)); OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(attacker, 1), CHARACTER_SKILL_ANIMATION+((n)<<1)+1-((attacker) > 2)); OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(attacker, 2), CHARACTER_SKILL_ANIMATION+((n)<<1)+6+((attacker) > 2)); OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(attacker, 3), CHARACTER_SKILL_ANIMATION+((n)<<1)+7-((attacker) > 2))
/*Reaction flag:
 * ?axxyyzz
 * - xx - ID of persone reacting
 * - yy - ID of skill of attacker
 * - zz - type - 0 - HIT, 1 - MISS, 2 - CHEER*/

#define ATTACK_ANIMATION_TYPE(x) ((x) & 8)
#define ATTACK_ANIMATION_ATTACKER_ID(x) ((x) & 7)
/*Attack animation flag:
 * ????axxx
 * - xxx - ID of character attacking(0 - 5)
 * - a   - attack type - 0 - melee, 8 - ranged*/
#define ATTACK_ANIMATION_MELEE 0
#define ATTACK_ANIMATION_RANGED 8


#define MAP_AT(x, y) MEM(MAP+(((long int)y)<<5)+(x))
#define IS_COLLIDABLE(x) (((x) & 15) > 4)

#define EVENT_CONDITION_POSITION 0
#define EVENT_CONDITION_ITEM 1
#define EVENT_CONDITION_BITFLAG 4

#define ABS(x) (((x) > 0) ? (x) : (-(x)))

#define CHARACTER_STATE_FIGHTING    1
#define CHARACTER_STATE_UNCONSCIOUS 2



#define ATTACK_ANIMATION_INNER_LEFT  1
#define ATTACK_ANIMATION_INNER_RIGHT 2
#define ATTACK_ANIMATION_INNER_MULTI 4

#define CHARACTER_TILESET_TABLE 144u
#define CHARACTER_IDLE_TILESET(x) (CHARACTER_TILESET_TABLE + (((x)*3)<<2))
#define CHARACTER_SKILL_ANIMATION 216u //136+6*4*3
#define CHARACTER_REACTION(x) (228u+((x)<<2)) //208+3*4
#define POINTER_TO_TILE(pointer, n) ((pointer) + (((unsigned int)n)<<4))
#define ARROW_TILE 254u
#define ARROW_SPRITE 0

#define CHARACTER_FRONT_POSITION_X (45) // 45-8
#define CHARACTER_BEHIND_POSITION_X (37)

#define SKILL_LENGTH 7
#define CHARACTER_SKILLS_LENGTH 28
#define CHARACTER_LENGTH 15
#define CHARACTER_STATE_LENGTH 11

#define STATISTIC_STRENGTH   0
#define STATISTIC_DEXTERITY  1
#define STATISTIC_PERCEPTION 2
#define STATISTIC_CHARISMA   3
#define STATISTIC_VITALITY   4
#define STATISTIC_DAMAGE_MELEE  5
#define STATISTIC_DAMAGE_RANGED 6
#define STATISTIC_MORALE_BOOST  7

#define IS_FIGHTING(x) ((x)->state & CHARACTER_STATE_FIGHTING)
#define STUNNED_LENGTH(id) (((characterStateMemory) + (id)*CHARACTER_STATE_LENGTH + 2) >> 4 >> 2)

#define COMBINE_DATA_STATISTIC_ID(statistic, id) (((id) << 3) | (statistic))
#define ID_FROM_PACK(x) (((x) >> 3) & 7)
#define STATISTIC_TYPE_FROM_PACK(x) ((x) & 7)
#define STATISTIC_FROM_CHARACTER(character, type) *(((unsigned char*)character)+7+(type))

#define CHARACTER_MODIFIER_SIGN_BYTE(id) (*(((unsigned char*)characterStateMemory) + CHARACTER_STATE_LENGTH*(id) + 10))

#define CHARACTERS_CURRENT_HP(id) *((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id))
#define CHARACTERS_CURRENT_ARMOR(id) *((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 1)
#define CHARACTERS_CURRENT_STUN(id) ((*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2)) >> 4 >> 2)
#define CLEAR_CHARACTERS_STUN(id) (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2) &= ~224)
#define SET_CHARACTERS_STUN(id, stun) (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2) |= ((stun) << 4 << 2))
#define CHARACTERS_MODIFIERS_AMOUNT(id) (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2) & 7)
#define CLEAR_CHARACTERS_MODIFIERS_AMOUNT(id) (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2) &= 248)
#define SET_CHARACTERS_MODIFIERS_AMOUNT(id, amount) (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 2) |= (amount))

#define GET_MODIFIER_BYTE(id, n)  (*((unsigned char*)characterStateMemory + CHARACTER_STATE_LENGTH*(id) + 3 + n))
#define GET_MODIFIER_LENGTH(id, n) (GET_MODIFIER_BYTE(id, n) >> 4 >> 2)
#define GET_MODIFIER_STATISTIC_TYPE(id, n) ((GET_MODIFIER_BYTE(id, n) >> 3) & 7)
#define GET_MODIFIER_VALUE(id, n) (GET_MODIFIER_BYTE(id, n)  & 7)
#define GET_MODIFIER_SIGN(id, n) ((CHARACTER_MODIFIER_SIGN_BYTE(id) >> n) & 1)
#define COMBINE_MODIFIER(length, statistic, value) (((((length) << 3) | (statistic)) << 3) | (value))

#define SET_CHARACTERS_MODIFIER(id, n, length, statistic, value) GET_MODIFIER_BYTE(id, n) = COMBINE_MODIFIER(length, statistic, value)
#define SET_CHARACTERS_MODIFIER_SIGN(id, n, bit) (CHARACTER_MODIFIER_SIGN_BYTE(id) = ((CHARACTER_MODIFIER_SIGN_BYTE(id) & ~(1 << (n))) | (1 << (n))))
#define TARGET_ENEMY 0
#define TARGET_ALL_ENEMIES 1
#define TARGET_ALLY 2
#define TARGET_ALL_ALLIES 3
#define TARGET_SELF 4

#define ITEM_STAT_BOOST 0
#define ITEM_QUEST 1
#define ITEM_ARMOR 2
#define ITEM_WEAPON_MELEE 3
#define ITEM_WEAPON_RANGED 4
#define ITEM_WEAPON_MELEE_VAMP 5
#define ITEM_AMMO 6
#define ITEM_POTION 7

#define ITEM_TYPE(x) ((((x) & 224) >> 4) >> 1)
#define ITEM_AMOUNT_OF_DICES(x) ((*(x+1) >> 4) >> 2)
#define ITEM_DICE_VALUES(x) ((*(x+1) >> 2) & 15)
#define ITEM_ADD_VALUE(x) (*(x+1) & 3)
#define ITEM_ARMOR_VALUE(x) (*(x + 1))
#define ITEM_IS_WEAPON(x) (((((x) >> 4) >> 1) > 2) && ((((x) >> 4) >> 1) < 6))
#define ITEM_IS_POTION(x) (((x) >> 4 >> 1) == ITEM_POTION)
#define ITEM_OF_ID(x) ((char*)(itemTableLocation+((x) << 4)))
#define ITEM_BOOST_TYPE(x, n) ((*(x+1+n)) >> 5)
#define ITEM_BOOST_AMOUNT(x, n) ((*(x+1+n)) & 31)
#define ITEM_HP_VALUE(x) (*(x+1))

#define ITEM_OF_CHARACTER(character, n) (items[(character)*30 + ((n)<<1)])
#define AMOUNT_OF_ITEM(character, n) (items[(character)*30 + ((n)<<1) + 1])

#define BOOST_TYPE(x) ((x) >> 3 >> 2)
#define BOOST_AMOUNT(x) ((x) & 31)

#define SKILL_TARGET(skillType) ((skillType) >> 3 >> 2)
#define SKILL_TYPE(skillType) ((skillType) & 7)
#define SKILL_CHARACTER_MOVES(skillType) (((skillType) >> 3) & 1)

#define HEADER_STATISTIC(x) ((x) & 7)
#define HEADER_LENGTH(x) (((x) >> 3) & 3)
#define HEADER_STATISTIC_REDUCTION(x) ((x) >> 3 >> 2)

#define PLAYER_SKILL(character, id)  ((struct Skill*)(mainCharacterSkillMemory+CHARACTER_SKILLS_LENGTH*(character)+(id)*SKILL_LENGTH))
#define PLAYER_CHARACTER(character) ((struct Character*)(mainCharacterMemory + CHARACTER_LENGTH*(character)))

#define ENEMY_SKILL(character, id)  ((struct Skill*)(enemySkillMemory+CHARACTER_SKILLS_LENGTH*(character)+(id)*SKILL_LENGTH))
#define ENEMY_CHARACTER(character) ((struct Character*)(enemyMemory + CHARACTER_LENGTH*(character)))

#define ITEM_BANK 5
#define FIGHT_STRING_BANK 7
#include "bitflagDefines.c"
