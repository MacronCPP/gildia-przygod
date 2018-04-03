#include "defines.c"
#include <types.h>
#define FIGHT_PLAYER 0
#define FIGHT_ENEMY 4

#include "skillStructs.c"
#include "fightStringsExtern.c"
#include "externNonbankedFunction.c"

unsigned char timerFrame = 0;
unsigned char characterIdleAnimation = 0;
extern unsigned char fightResult, isRanged;
extern void playAnimationBanked(unsigned char flag, unsigned char attacked);
extern void progressStunsAndModifiers(unsigned char characterID);
extern void setArrowAtCharacter(unsigned char characterID);
extern void setCharacterToIdle(unsigned char characterID);
void runIdleAnimationTimer()
{
    MEM(0xFFFF) = 4;
    MEM(0xFF07) = 4;
    MEM(0xFF07) &= 253;
    add_TIM(interruptIdle);
}

void replaceFightStringInBuffer(const char* string) {
    replaceInBuffer(FIGHT_STRING_BANK, string);
}

#include "fightSimpleFunctions.c"

void loadCharacterIdle(struct Character* character, unsigned char id)
{
    loadBankedTileset(character->bank, CHARACTER_IDLE_TILESET(id), 6, character->graphics);
    loadBankedTileset(character->bank, CHARACTER_IDLE_TILESET(id)+6, 6, POINTER_TO_TILE(character->graphics, 12));
}

void loadReaction(unsigned char flag, struct Character* target) {
    loadBankedTileset(target->bank, CHARACTER_REACTION(REACTION_PERSON_ID(flag)), 2, POINTER_TO_TILE(target->graphics, 6+(REACTION_TYPE(flag)<<1)));
    loadBankedTileset(target->bank, CHARACTER_REACTION(REACTION_PERSON_ID(flag))+2, 2, POINTER_TO_TILE(target->graphics, 18+(REACTION_TYPE(flag)<<1)));
}

void loadSkillAnimation(unsigned char flag, struct Character* attacker) {
    unsigned char value = 0;
    if(isRanged && REACTION_SKILL_ID(flag) == 0) {
        value = 54;
    }
    loadBankedTileset(attacker->bank, CHARACTER_SKILL_ANIMATION, 6, POINTER_TO_TILE(attacker->graphics,
                                      (value+24)+ (((REACTION_SKILL_ID(flag)&1) + ((REACTION_SKILL_ID(flag)&2) << 1) ) * 6)));
    loadBankedTileset(attacker->bank, CHARACTER_SKILL_ANIMATION+6, 6, POINTER_TO_TILE(attacker->graphics,
                                      (value+36)+ (((REACTION_SKILL_ID(flag)&1) + ((REACTION_SKILL_ID(flag)&2) << 1) ) * 6)));
}

#include "fightRolls.c"

void setVanilla(struct Character* attacker, struct Skill* skill) {
    copyToBuffer(FIGHT_STRING_BANK, vanilla);
    replaceInBuffer(attacker->bank, attacker->name);
    replaceInBuffer(skill->bank, skill->nameAndDescription);
}

int testAttack(struct Character* attacker, struct Skill* skill, unsigned char characterID) {
    int rolled = 0;
    fightResult = 0;
    switch(SKILL_TYPE(skill->type)) {
        case SKILL_STUN:
            setVanilla(attacker, skill);
            replaceInBuffer(FIGHT_STRING_BANK, roll);
            rolled = tryStatistic(attacker, HEADER_STATISTIC(skill->stats.stun.header), COMBINE_TRY_FLAG(characterID, HEADER_STATISTIC_REDUCTION(skill->stats.stun.header)));
            showBufferedMessage();
            break;
        case SKILL_ATTACK:
            chooseWeaponBanked(characterID);
            if(ITEM_TYPE(selectedItem[0]) == ITEM_WEAPON_RANGED) {
                isRanged = 1;
            } else {
                isRanged = 0;
            }
            setVanilla(attacker, skill);
            replaceInBuffer(FIGHT_STRING_BANK, roll);
            rolled = tryStatistic(attacker, STATISTIC_DEXTERITY, COMBINE_TRY_FLAG(characterID, 0));
            showBufferedMessage();
            break;
        case SKILL_FUNCTION:
            break;
        case SKILL_STAT_REDUCTION:
            setVanilla(attacker, skill);
            replaceFightStringInBuffer(roll);
            rolled = test(tryStatistic(attacker, HEADER_STATISTIC(skill->stats.modifier.header),
                                   COMBINE_TRY_FLAG(characterID, HEADER_STATISTIC_REDUCTION(skill->stats.modifier.header))));
            showBufferedMessage();
            break;
        case SKILL_STAT_BOOST:
            setVanilla(attacker, skill);
            replaceFightStringInBuffer(roll);
            rolled = test(tryStatistic(attacker, HEADER_STATISTIC(skill->stats.modifier.header),
                                       COMBINE_TRY_FLAG(characterID, HEADER_STATISTIC_REDUCTION(skill->stats.modifier.header))));
            showBufferedMessage();
            if(!rolled)
            {
                copyToBuffer(FIGHT_STRING_BANK, failed);
                replaceInBuffer(attacker->bank, attacker->name);
                showBufferedMessage();
                fightResult |= 3;
             }
        break;
    }
    return rolled;
}

void endCheer(struct Character** team, unsigned char position) {
    unsigned char iterator;
    characterIdleAnimation = 0;
    for(iterator = 0; iterator < 3; iterator++) {
        if(IS_FIGHTING(team[iterator])) {
            loadReaction(COMBINE_REACTION_FLAG(iterator, 0, REACTION_CHEER), team[iterator]);
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE((iterator+position*3), 0), CHARACTER_REACTION((iterator))+position);
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE((iterator+position*3), 1), CHARACTER_REACTION((iterator))+1-position);
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE((iterator+position*3), 2), CHARACTER_REACTION((iterator))+2+position);
            OAM_SET_SPRITE_TILE(CHARACTER_SPRITE((iterator+position*3), 3), CHARACTER_REACTION((iterator))+3-position);
        }
    }
    OAM_START_TRANSFER();
}

#define WIN_FLAG 1
#define LOSE_FLAG 2
unsigned char checkWinLoseCondition(struct Character** mainCharacters,
                                    struct Character** enemies) {
    unsigned char iterator = 0, ret = 3;
    for(iterator = 0; iterator < 3; iterator++) {
        if(IS_FIGHTING(mainCharacters[iterator])) {
            ret &= ~2;
        }
        if(IS_FIGHTING(enemies[iterator])) {
            ret &= ~1;
        }
    }
    if(!ret)
        return 0;
    CLEAR_BITFLAG(wonFight);
    CLEAR_BITFLAG(loseFight);
    copyToBuffer(FIGHT_STRING_BANK, end);
    if(ret & WIN_FLAG) {
        endCheer(mainCharacters, 0);
        replaceFightStringInBuffer(playerNames[rand() & 3]);
        SET_BITFLAG(wonFight, 1);
    }
    else if(ret & LOSE_FLAG) {
        endCheer(enemies, 1);
        replaceFightStringInBuffer(enemyNames[rand() & 3]);
        SET_BITFLAG(loseFight, 1);
    }
    showBufferedMessage();
    rollWindowOut();
    return ret;
}

void parseAttack(struct Character* attacker, struct Character* target, struct Skill* skill, unsigned char characterID, unsigned char targetID, int rolled) {
    unsigned char iterator = 0;
    int rolled2 = 0;
    if(fightResult != 0)
        showBufferedMessage();
    fightResult = 0;
    switch(SKILL_TYPE(skill->type)) {
        case SKILL_STUN:
            copyToBuffer(FIGHT_STRING_BANK, roll);
            rolled2 = tryStatistic(target, HEADER_STATISTIC(skill->stats.stun.header), COMBINE_TRY_FLAG(targetID, 0));
            if(rolled > rolled2) {
                replaceInBuffer(FIGHT_STRING_BANK, soMissed);
                replaceInBuffer(attacker->bank, attacker->name);
                fightResult |= 1;
                renderBufferedMessage();
            } else {
                replaceInBuffer(FIGHT_STRING_BANK, soStunned);
                replaceInBuffer(attacker->bank, attacker->name);
                replaceInBuffer(target->bank, target->name);
                showBufferedMessage();
                copyToBuffer(FIGHT_STRING_BANK, stunnedTurns);
                replaceInBuffer(target->bank, target->name);
                replaceInBufferInt(HEADER_LENGTH(skill->stats.stun.header));
                fightResult &= (~3);
                characterIdleAnimation &= ~(1<<(targetID));
                addStun(targetID, HEADER_LENGTH(skill->stats.stun.header));
                renderBufferedMessage();
            }
            break;
        case SKILL_ATTACK:
            copyToBuffer(FIGHT_STRING_BANK, roll);
            rolled2 = tryStatistic(target, STATISTIC_DEXTERITY, COMBINE_TRY_FLAG(targetID, 20));
            if(rolled > rolled2) {
                replaceFightStringInBuffer(soMissed);
                replaceInBuffer(attacker->bank, attacker->name);
                fightResult |= 1;
                renderBufferedMessage();
            } else {
                replaceFightStringInBuffer(soHit);
                replaceInBuffer(attacker->bank, attacker->name);
                replaceInBuffer(target->bank, target->name);
                fightResult |= 0;

                showBufferedMessage();
                copyToBuffer(FIGHT_STRING_BANK, lostHP);
                replaceInBuffer(attacker->bank, attacker->name);

                replaceInBuffer(target->bank, target->name);
                rolled = ITEM_ADD_VALUE((unsigned char*)selectedItem);
                for(iterator = 0; iterator < ITEM_AMOUNT_OF_DICES((unsigned char*)selectedItem); iterator++) {
                    rolled += (rand() % ITEM_DICE_VALUES((unsigned char*)selectedItem)) + 1;
                }

                replaceInBufferInt(rolled);
                damage(target, targetID, rolled);
                renderBufferedMessage();
            }
            break;
        case SKILL_FUNCTION:
            runFunction((char*)target, (char*)skill);
            break;
        case SKILL_STAT_REDUCTION:
            copyToBuffer(FIGHT_STRING_BANK, roll);
            rolled2 = tryStatistic(target, HEADER_STATISTIC(skill->stats.modifier.header), COMBINE_TRY_FLAG(targetID, 0));
            if(rolled > rolled2) {
                replaceFightStringInBuffer(soFailed);
                replaceInBuffer(attacker->bank, attacker->name);
                fightResult |= 1;
                renderBufferedMessage();
                break;
            } else {
                replaceFightStringInBuffer(soReduced);
                replaceInBuffer(attacker->bank, attacker->name);
                showBufferedMessage();
                for(iterator = 0; iterator != 2; iterator++)
                {
                    //characterID is now boostA and boostB because I don't have enought ROM.
                    if(iterator)
                        characterID = skill->stats.modifier.boostB;
                    else
                        characterID = skill->stats.modifier.boostA;
                    if(!characterID)
                        continue;
                    if(iterator)
                        showBufferedMessage();
                    copyToBuffer(FIGHT_STRING_BANK, debuff);
                    replaceInBuffer(target->bank, target->name);
                    replaceFightStringInBuffer(statisticNames[BOOST_TYPE(characterID)]);
                    replaceInBufferInt(BOOST_AMOUNT(characterID)*5);
                    replaceInBufferInt(HEADER_LENGTH(skill->stats.modifier.header));
                    addModifier(targetID, HEADER_LENGTH(skill->stats.modifier.header), BOOST_AMOUNT(characterID) | 16);
                }
                fightResult &= (~3);
                renderBufferedMessage();
            }
        break;
        case SKILL_STAT_BOOST:
            if(rolled) {
                for(iterator = 0; iterator != 2; iterator++)
                {
                    //characterID is now boostA and boostB because I don't have enought ROM.
                    if(iterator)
                        characterID = skill->stats.modifier.boostB;
                    else
                        characterID = skill->stats.modifier.boostA;
                    if(!characterID)
                        continue;
                    if(iterator) //that'd let me make 250 bytes more free so i'm happy.
                        showBufferedMessage();
                    copyToBuffer(FIGHT_STRING_BANK, buff);
                    replaceInBuffer(target->bank, target->name);
                    replaceFightStringInBuffer(statisticNames[BOOST_TYPE(characterID)]);
                    rolled2 = 0;
                    if(rolled > 2) {
                        replaceFightStringInBuffer(greatly);
                        replaceInBufferInt(10 + (BOOST_AMOUNT(characterID))*5);
                        rolled2 = 2;
                    } else {
                        replaceFightStringInBuffer(nullString);
                        replaceInBufferInt(BOOST_AMOUNT(characterID)*5);
                        rolled2 = 0;
                    }
                    replaceInBufferInt(HEADER_LENGTH(skill->stats.modifier.header));
                    addModifier(targetID, HEADER_LENGTH(skill->stats.modifier.header), BOOST_AMOUNT(characterID)+rolled2);
                }
                renderBufferedMessage();
            }
            break;
    }
}

unsigned char selectCharacter(unsigned char pickable)
{
    unsigned char selected = 0, val, x, lastPressedNegation = 0, temp;
    temp = pickable;
    while(!(temp & 1))
    {
        temp >>= 1;
        selected++;
        if(!temp) return MENU_BACK;
    }
    runAdditionalBankedFunction(setArrowAtCharacter, selected);
    while(1)
    {
        val = joypad();
        x = selected;
        if((val & J_RIGHT & lastPressedNegation) && selected < 3) selected += 3;
        if((val & J_LEFT  & lastPressedNegation) && selected > 2) selected -= 3;
        if((val & J_UP    & lastPressedNegation) && (selected && selected != 3)) selected--;
        if((val & J_DOWN  & lastPressedNegation) && (selected != 2 && selected != 5)) selected++;

        if(!(pickable & (1 << selected)))
        {
            temp = selected;
            while(1)
            {
                temp--;
                selected++;
                if((pickable & (1 << temp)) && (temp != x))
                {
                    selected = temp;
                    break;
                }
                if((pickable & (1 << selected)) && (selected != x))
                {
                    break;
                }
                if(temp > 5 && selected > 5)
                {
                    selected = x;
                    break;
                }
            }
        }

        if((val & J_A & lastPressedNegation) && (pickable & (1 << selected))) break;
        if(x != selected)
        {
            runAdditionalBankedFunction(setArrowAtCharacter, selected);
        }
        lastPressedNegation = ~val;
    }
    return selected;
}

void checkCounsciousness(struct Character** mainCharacters, struct Character** enemies) {
    unsigned char iterator, subIterator;
    struct Character* character;
    for(iterator = 0; iterator < 6; iterator++)
    {
        if(iterator < 3)
            character = mainCharacters[iterator];
        else
            character = enemies[iterator-3];

        if(IS_FIGHTING(character) && CHARACTERS_CURRENT_HP(iterator) == 0) {
            copyToBuffer(FIGHT_STRING_BANK, fainted);
            replaceInBuffer(character->bank, character->name);
            character->state ^= 1;
            characterIdleAnimation &= ~(1<<(iterator));
            renderBufferedMessage();
            delay(200);
            loadBankedTileset(character->bank, CHARACTER_IDLE_TILESET(iterator), 6, POINTER_TO_TILE(character->graphics, 72));
            loadBankedTileset(character->bank, CHARACTER_IDLE_TILESET(iterator)+6, 6, POINTER_TO_TILE(character->graphics, 84));
            //here
            for(subIterator = 0; subIterator < 3; subIterator++) {
                OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 0), CHARACTER_IDLE_TILESET(iterator)+(subIterator<<1)+(iterator>2));
                OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 1), CHARACTER_IDLE_TILESET(iterator)+(subIterator<<1)+1-(iterator>2));
                OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 2), CHARACTER_IDLE_TILESET(iterator)+(subIterator<<1)+6+(iterator>2));
                OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(iterator, 3), CHARACTER_IDLE_TILESET(iterator)+(subIterator<<1)+7-(iterator>2));
                OAM_START_TRANSFER();
                delay(500);
            }
        }
    }
}

void scout(struct Character* character, int characterID, struct Character* enemies[]) {
    unsigned char testResult, iterator;
    copyToBuffer(FIGHT_STRING_BANK, vanilla);
    replaceInBuffer(character->bank, character->name);
    replaceFightStringInBuffer(scoutMessage);
    replaceFightStringInBuffer(roll);
    testResult = test(tryStatistic(character, STATISTIC_PERCEPTION, COMBINE_TRY_FLAG(characterID, 0)));
    showBufferedMessage();
    if(!testResult) {
        iterator = 0;
        while(iterator < 3) {
            if(enemies[iterator]->state & 1) {
                testResult = (((int)(enemies[iterator]->currentHealthPoints))*4)/(enemies[iterator]->vitality);
                if(testResult == 4)testResult = 3;
                copyToBuffer(FIGHT_STRING_BANK, scoutDescriptions[testResult]);
                replaceInBuffer(enemies[iterator]->bank, enemies[iterator]->name);
                showBufferedMessage();
            }
            iterator++;
        }
    } else {
        iterator = 0;
        while(iterator < 3) {
            if(enemies[iterator]->state & 1) {
                copyToBuffer(FIGHT_STRING_BANK, scoutAmount);
                replaceInBuffer(enemies[iterator]->bank, enemies[iterator]->name);
                replaceInBufferInt(enemies[iterator]->currentHealthPoints);
                showBufferedMessage();
            }
            iterator++;
        }
        showBufferedMessage();
        if(testResult >= 3) {
            copyToBuffer(FIGHT_STRING_BANK, scoutBenefit);
            replaceInBuffer(character->bank, character->name);
            if(testResult != 6)
                iterator = 1 << (testResult - 2);
            else
                iterator = 6;
            replaceInBufferInt(5*iterator);
            addModifier(characterID, 2, iterator);
            showBufferedMessage();
        }
    }
}

unsigned char usePotion(struct Character* character, unsigned char iterator) {
    if(CHARACTERS_CURRENT_HP(iterator) == character->vitality) {
        copyToBuffer(FIGHT_STRING_BANK, cantUsePotion);
        replaceInBuffer(character->bank, character->name);
        showBufferedMessage();
        return 0;
    }
    choosePotionBanked(iterator);
    if(selectedItem[1] == 0)
        return 0;
    character->currentHealthPoints += selectedItem[1];
    if(character->currentHealthPoints > character->vitality)
        character->currentHealthPoints = character->vitality;
    copyToBuffer(FIGHT_STRING_BANK, usedPotion);
    replaceInBuffer(character->bank, character->name);
    replaceInBuffer(0, selectedItem+2);
    replaceInBufferInt(character->currentHealthPoints);
    CHARACTERS_CURRENT_HP(iterator) = character->currentHealthPoints;
    showBufferedMessage();
}

void stunTurnMessage(struct Character* character) {
    copyToBuffer(FIGHT_STRING_BANK, skipTurn);
    replaceInBuffer(character->bank, character->name);
    showBufferedMessage();
}

void runAway(struct Character* character, int characterID, struct Character* enemies[]) {
   unsigned char iterator;
   int rolled, rolled2, sum = 0;
   copyToBuffer(FIGHT_STRING_BANK, vanilla);
   replaceInBuffer(character->bank, character->name);
   replaceFightStringInBuffer(runAwayMessage);
   replaceFightStringInBuffer(roll);
   rolled = tryStatistic(character, STATISTIC_DEXTERITY, COMBINE_TRY_FLAG(characterID, 0));
   showBufferedMessage();
   copyToBuffer(FIGHT_STRING_BANK, tryNotToRunAway);
   replaceFightStringInBuffer(enemyNames[rand() & 3]);
   for(iterator = 0; iterator < 3; iterator++)
   {
       if(!IS_FIGHTING(enemies[iterator]) || CHARACTERS_CURRENT_STUN(iterator+3))
           rolled2 = 0;
       else
       {
           rolled2 = randw() % 100;
           rolled2 -= getStatistic(enemies[iterator],
                                  COMBINE_DATA_STATISTIC_ID(STATISTIC_DEXTERITY, iterator+3));
       }
       replaceInBufferInt(rolled2);
       sum += rolled2;
   }
   replaceInBufferInt(sum);
   showBufferedMessage();
   if(rolled < sum)
        copyToBuffer(FIGHT_STRING_BANK, soRanAway);
   else
        copyToBuffer(FIGHT_STRING_BANK, soCouldntRun);
   replaceInBuffer(character->bank, character->name);
   if(rolled < sum) {
       renderBufferedMessage();
       while(OAM_GET_SPRITE_POSITION_X(CHARACTER_SPRITE(characterID, 2)) != -8) {
           for(iterator = 0; iterator < 4; iterator++) {
               OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(characterID, iterator),
                                         OAM_GET_SPRITE_POSITION_X(CHARACTER_SPRITE(characterID, iterator))-1);
           }
           OAM_START_TRANSFER();
           delay(16);
       }
       characterIdleAnimation &= ~(1<<characterID);
       character->state &= ~1; //Now is not fighting!
   }
   showBufferedMessage();
}

void fightViewLoop()
{
    unsigned char currentPhase = FIGHT_PLAYER, iterator = 0, subIterator = 0, option = 0, tempByte = 0, anotherTempByte = 0;
    int rolled = 0, sum = 0, secondSum = 0;
    struct Skill* selectedSkill;
    struct Character* mainCharacters[3];
    struct Character* enemies[3];
    OAM_SET_SPRITE_POSITION_X(ARROW_SPRITE, -8);
    OAM_SET_SPRITE_TILE(ARROW_SPRITE, ARROW_TILE);
    for(iterator = 0; iterator < 3; iterator++)
    {
        mainCharacters[iterator] = mainCharacterMemory + (15*iterator);
        enemies[iterator] = enemyMemory + (15*iterator);
        if(mainCharacters[iterator]->bank)loadCharacterIdle(mainCharacters[iterator], iterator);
        runAdditionalBankedFunction(setCharacterToIdle, iterator);
        if(enemies[iterator]->bank)loadCharacterIdle(enemies[iterator], iterator+3);
        runAdditionalBankedFunction(setCharacterToIdle, iterator+3);
        CHARACTERS_CURRENT_HP(iterator)
                = mainCharacters[iterator]->currentHealthPoints;
        CHARACTERS_CURRENT_HP(iterator + 3)
                = enemies[iterator]->currentHealthPoints;
        restoreArmor(iterator);
        restoreArmor(iterator+3);
    }
    OAM_START_TRANSFER();
    /*entry*/
    runIdleAnimationTimer();
    if(WHO_STARTS(encounterHeader) == NO_ONE_STARTS)
    {
        copyToBuffer(FIGHT_STRING_BANK, rolledStart);
        replaceFightStringInBuffer(playerNames[rand() & 3]);
        for(iterator = 0; iterator < 3; iterator++)
        {
            if(!IS_FIGHTING(mainCharacters[iterator]))
                rolled = 0;
            else
            {
                rolled = randw() % 100;
                rolled -= getStatistic(mainCharacters[iterator],
                                       COMBINE_DATA_STATISTIC_ID(STATISTIC_DEXTERITY, iterator));
            }
            replaceInBufferInt(rolled);
            sum += rolled;
        }
        replaceInBufferInt(sum);
        showMessage(0, FLAG_DONT_CHANGE_BANK | FLAG_WINDOW_IN | FLAG_NO_TITLE, messageBuffer);
        copyToBuffer(FIGHT_STRING_BANK, rolledStart);
        replaceFightStringInBuffer(enemyNames[rand() & 3]);
        for(iterator = 0; iterator < 3; iterator++)
        {
            if(!IS_FIGHTING(enemies[iterator]))
                rolled = 0;
            else
            {
                rolled = randw() % 100;
                rolled -= getStatistic(enemies[iterator],
                                       COMBINE_DATA_STATISTIC_ID(STATISTIC_DEXTERITY, iterator+3));
            }
            replaceInBufferInt(rolled);
            secondSum += rolled;
        }
        replaceInBufferInt(secondSum);
        showBufferedMessage();
        if(secondSum <= sum) // cause at default player start(not changing anything if the player starts)
            currentPhase = FIGHT_ENEMY;
    }
    else if(WHO_STARTS(encounterHeader) == ENEMY_STARTS)
        currentPhase = FIGHT_ENEMY; //same

    copyToBuffer(FIGHT_STRING_BANK, whoStarts);
    if(currentPhase == FIGHT_PLAYER)
        replaceFightStringInBuffer(playerNames[rand() & 3]);
    else
        replaceFightStringInBuffer(enemyNames[rand() & 3]);

    showBufferedMessage();

    while(1)
    {
        if(currentPhase == FIGHT_PLAYER)
        {
            for(iterator = 0; iterator < 3; iterator++)
            {
                if(!IS_FIGHTING(mainCharacters[iterator]))
                    continue;

                runAdditionalBankedFunction(setArrowAtCharacter, iterator);
                copyToBuffer(FIGHT_STRING_BANK, turnMessage);
                replaceInBuffer(mainCharacters[iterator]->bank, mainCharacters[iterator]->name);
                replaceInBufferInt(mainCharacters[iterator]->currentHealthPoints);
                replaceInBufferInt(CHARACTERS_CURRENT_ARMOR(iterator));
                option = showOptions(FIGHT_STRING_BANK, 0, messageBuffer,
                                     attackOption, itemsOption, fightOption, runawayOption);

                if(CHARACTERS_CURRENT_STUN(iterator)) {
                    stunTurnMessage(mainCharacters[iterator]);
                    continue;
                }
                switch(option)
                {
                    case MENU_FIRST:
                        copyToBuffer(FIGHT_STRING_BANK, selectActionOption);
                        option = showOptions(PLAYER_SKILL(iterator, 0)->bank, FLAG_MENU_BACKABLE, messageBuffer,
                                             PLAYER_SKILL(iterator, 0)->nameAndDescription,
                                             PLAYER_SKILL(iterator, 1)->nameAndDescription,
                                             PLAYER_SKILL(iterator, 2)->nameAndDescription,
                                             PLAYER_SKILL(iterator, 3)->nameAndDescription);
                        if(option == MENU_BACK)
                        {
                            iterator--;
                            break;
                        }
                        selectedSkill = PLAYER_SKILL(iterator, option);
                        tempByte = IS_FIGHTING(mainCharacters[0]);
                        tempByte |= IS_FIGHTING(mainCharacters[1]) << 1;
                        tempByte |= IS_FIGHTING(mainCharacters[2]) << 2;
                        tempByte |= IS_FIGHTING(enemies[0]) << 3;
                        tempByte |= IS_FIGHTING(enemies[1]) << 4;
                        tempByte |= IS_FIGHTING(enemies[2]) << 4 << 1;
                        isRanged = 0;
                        if(SKILL_TARGET(selectedSkill->type) == TARGET_ALLY || SKILL_TARGET(selectedSkill->type) == TARGET_ENEMY)
                        {
                            copyToBuffer(FIGHT_STRING_BANK, selectTarget);
                            replaceInBuffer(mainCharacters[iterator]->bank, mainCharacters[iterator]->name);
                            replaceInBuffer(selectedSkill->bank, selectedSkill->nameAndDescription);
                            renderBufferedMessage();
                            if(SKILL_TARGET(selectedSkill->type) == TARGET_ALLY)
                                option = selectCharacter(7 & tempByte);
                            else
                                option = selectCharacter(248 & tempByte);
                            tempByte = (1 << option);
                        } else if(SKILL_TARGET(selectedSkill->type) == TARGET_ALL_ALLIES) {
                            tempByte = 7 & tempByte;
                            isRanged = 1;
                        } else if(SKILL_TARGET(selectedSkill->type) == TARGET_ALL_ENEMIES) {
                            tempByte = 248 & tempByte;
                            isRanged = 1;
                        }
                        anotherTempByte = 0;
                        rolled = testAttack(mainCharacters[iterator], selectedSkill, iterator);
                        fightResult = 0;
                        for(subIterator = 0; subIterator < 6; subIterator++) {
                            if(tempByte & (1 << subIterator)) {
                                if(subIterator < 3) {
                                    parseAttack(mainCharacters[iterator], mainCharacters[subIterator], selectedSkill, iterator,
                                                subIterator, rolled);
                                    loadReaction(COMBINE_REACTION_FLAG(anotherTempByte, 0, fightResult), mainCharacters[subIterator]);
                                } else {
                                    parseAttack(mainCharacters[iterator], enemies[subIterator - 3], selectedSkill, iterator,
                                            subIterator, rolled);
                                    loadReaction(COMBINE_REACTION_FLAG(anotherTempByte, 0, fightResult), enemies[subIterator - 3]);
                                }
                                if((fightResult & 3) == 3) tempByte ^= (1 << subIterator);
                                else anotherTempByte++;
                            }
                        }

                        for(anotherTempByte = 0; selectedSkill != PLAYER_SKILL(iterator, anotherTempByte); anotherTempByte++);
                        loadSkillAnimation(COMBINE_REACTION_FLAG(0, anotherTempByte, fightResult), mainCharacters[iterator]);
                        playAnimationBanked(iterator, tempByte);
                        checkCounsciousness(mainCharacters, enemies);

                        break;
                    case MENU_SECOND:
                        if(!usePotion(mainCharacters[iterator], iterator))
                            iterator--;
                        break;
                    case MENU_THIRD:
                        scout(mainCharacters[iterator], iterator, enemies);
                        break;
                    case MENU_FOURTH:
                        runAway(mainCharacters[iterator], iterator, enemies);
                        break;
                }
                tempByte = checkWinLoseCondition(mainCharacters, enemies);
                if(tempByte) {
                    return;
                }
            }
            for(iterator = 0; iterator < 3; iterator++)
                runAdditionalBankedFunction(progressStunsAndModifiers, iterator);
            currentPhase = FIGHT_ENEMY;
        }
        if(currentPhase == FIGHT_ENEMY)
        {
            for(iterator = 0; iterator < 3; iterator++) {

                if(!IS_FIGHTING(enemies[iterator]))
                    continue;
                runAdditionalBankedFunction(setArrowAtCharacter, iterator+3);
                if(CHARACTERS_CURRENT_STUN(iterator+3)) {
                    stunTurnMessage(enemies[iterator]);
                    continue;
                }
                selectedSkill = ENEMY_SKILL(iterator, randomSkill(iterator));
                tempByte = IS_FIGHTING(mainCharacters[0]);
                tempByte |= IS_FIGHTING(mainCharacters[1]) << 1;
                tempByte |= IS_FIGHTING(mainCharacters[2]) << 2;
                tempByte |= IS_FIGHTING(enemies[0]) << 3;
                tempByte |= IS_FIGHTING(enemies[1]) << 4;
                tempByte |= IS_FIGHTING(enemies[2]) << 4 << 1;
                isRanged = 0;
                if(SKILL_TARGET(selectedSkill->type) == TARGET_ALLY || SKILL_TARGET(selectedSkill->type) == TARGET_ENEMY)
                {
                    if(SKILL_TARGET(selectedSkill->type) == TARGET_ENEMY)
                        tempByte = 7 & tempByte;
                    else
                        tempByte = 248 & tempByte;
                    tempByte = pickRandomBit(tempByte);
                } else if(SKILL_TARGET(selectedSkill->type) == TARGET_ALL_ENEMIES) {
                    tempByte = 7 & tempByte;
                    isRanged = 1;
                } else if(SKILL_TARGET(selectedSkill->type) == TARGET_ALL_ALLIES) {
                    tempByte = 248 & tempByte;
                    isRanged = 1;
                }

                rolled = testAttack(enemies[iterator], selectedSkill, iterator + 3);
                fightResult = 0;
                anotherTempByte = 0;
                for(subIterator = 0; subIterator < 6; subIterator++) {
                    if(tempByte & (1 << subIterator)) {
                        if(subIterator > 2) {
                            parseAttack(enemies[iterator], enemies[subIterator-3], selectedSkill, iterator+3,
                                        subIterator, rolled);
                            loadReaction(COMBINE_REACTION_FLAG(anotherTempByte, 0, fightResult), enemies[subIterator-3]);
                        } else {
                            parseAttack(enemies[iterator], mainCharacters[subIterator], selectedSkill, iterator+3,
                                    subIterator, rolled);
                            loadReaction(COMBINE_REACTION_FLAG(anotherTempByte, 0, fightResult), mainCharacters[subIterator]);
                        }
                        if((fightResult & 3) == 3) tempByte ^= (1 << subIterator);
                        else anotherTempByte++;
                    }
                }
                for(anotherTempByte = 0; selectedSkill != ENEMY_SKILL(iterator, anotherTempByte); anotherTempByte++);
                loadSkillAnimation(COMBINE_REACTION_FLAG(0, anotherTempByte, fightResult), enemies[iterator]);
                playAnimationBanked((iterator + 3), tempByte);
                checkCounsciousness(mainCharacters, enemies);
            }
            for(iterator = 0; iterator < 3; iterator++) {
                runAdditionalBankedFunction(progressStunsAndModifiers, iterator + 3);
            }
            currentPhase = FIGHT_PLAYER;
        }
    }
}
