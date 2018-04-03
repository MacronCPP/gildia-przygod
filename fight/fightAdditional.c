#include "defines.c"

extern void OAM_START_TRANSFER();
extern void delay(unsigned int value);
extern unsigned char characterStateMemory[];
extern unsigned characterIdleAnimation, isRanged;
unsigned char findFlag(unsigned char attacked) {
    unsigned char ret = 0, iterator = 0;
    for(iterator = 0; iterator < 6; iterator++) {     //Finding target - middle if multiple targets
        if(attacked & (1 << iterator)) {
            if(ret)
                ret |= ATTACK_ANIMATION_INNER_MULTI;
            if(iterator < 3)
                ret |= ATTACK_ANIMATION_INNER_LEFT;
            else
                ret |= ATTACK_ANIMATION_INNER_RIGHT;
        }
    }
    return ret;
}
/*setCharacterToIdleAdditional was too long name for compiler!*/
void setCharacterToIdle(unsigned char id)
{
    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(id, 0), CHARACTER_IDLE_TILESET((id)) + (id > 2));
    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(id, 1), CHARACTER_IDLE_TILESET((id)) + 1 - (id > 2));
    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(id, 2), CHARACTER_IDLE_TILESET((id)) + 6 + (id > 2));
    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(id, 3), CHARACTER_IDLE_TILESET((id)) + 7 - (id > 2));
    if(id == 1 || id == 4)
    {
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 0), CHARACTER_BEHIND_POSITION_X+86*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 1), CHARACTER_BEHIND_POSITION_X+8+86*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 2), CHARACTER_BEHIND_POSITION_X+86*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 3), CHARACTER_BEHIND_POSITION_X+8+86*(id>2));
    }
    else
    {
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 0), CHARACTER_FRONT_POSITION_X+70*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 1), CHARACTER_FRONT_POSITION_X+8+70*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 2), CHARACTER_FRONT_POSITION_X+70*(id>2));
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(id, 3), CHARACTER_FRONT_POSITION_X+8+70*(id>2));
    }
    OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(id, 0), 56+(((id)%3)<<4));
    OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(id, 1), 56+(((id)%3)<<4));
    OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(id, 2), 64+(((id)%3)<<4));
    OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(id, 3), 64+(((id)%3)<<4));

    OAM_SET_SPRITE_PROP(CHARACTER_SPRITE(id, 0), 32*(id>2));
    OAM_SET_SPRITE_PROP(CHARACTER_SPRITE(id, 1), 32*(id>2));
    OAM_SET_SPRITE_PROP(CHARACTER_SPRITE(id, 2), 32*(id>2));
    OAM_SET_SPRITE_PROP(CHARACTER_SPRITE(id, 3), 32*(id>2));
    characterIdleAnimation |= (1<<(id));
}

void playAnimation(unsigned char flag, unsigned char attacked) {
    unsigned char subIterator, attacker = ATTACK_ANIMATION_ATTACKER_ID(flag), animationIdlePre = characterIdleAnimation;
    int xT = 0, yT = 0;
    int fX, fY;
    char stepX = 0, stepY;
    int iterator;
    subIterator = 0;
    stepX = findFlag(attacked);
    fX = OAM_GET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 0));
    fY = OAM_GET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 0));
    if(stepX & ATTACK_ANIMATION_INNER_MULTI) {
        isRanged = 1;
    }
    if((stepX & ATTACK_ANIMATION_INNER_LEFT) && (stepX & ATTACK_ANIMATION_INNER_RIGHT)) {
        xT = 72;
        yT = 72;
    } else if(stepX & ATTACK_ANIMATION_INNER_MULTI) {
        if(stepX & ATTACK_ANIMATION_INNER_LEFT) {
            xT = 45 + 8;
        } else {
            xT = 160-(45 + 8 + 16);
        }
        yT = 72;
    } else {
        subIterator = 0;
        for(subIterator = 0; subIterator < 6; subIterator++) {
            if(attacked & (1 << subIterator)) {
                subIterator <<= 1;
                if(subIterator == 2 || subIterator == 8)
                    xT = CHARACTER_BEHIND_POSITION_X+78*(subIterator>4)-8;
                else
                    xT = CHARACTER_FRONT_POSITION_X+54*(subIterator>4);
                yT = 56+(((subIterator>>1)%3)<<4);
                break;
            }
        }
        subIterator >>= 1;
        if(subIterator < 3 && subIterator != 1)
            xT += 16;
        else if(subIterator == 1) {
            xT += 24;
        }
    }
    characterIdleAnimation &= ~attacked;
    characterIdleAnimation &= (~(1 << (attacker)));
    SET_SKILL_ANIMATION(flag, 0);
    OAM_START_TRANSFER();
    for(iterator = 0; iterator < 100; iterator++) {
        if(iterator == 60) {
            SET_SKILL_ANIMATION(flag, 1);
            OAM_START_TRANSFER();

        } else if(iterator == 84) {
            iterator = 0;
            for(subIterator = 0; subIterator < 6; subIterator++) {
                if(attacked & (1 << subIterator)) {
                    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(subIterator, 0), CHARACTER_REACTION(((unsigned char)iterator))+(subIterator > 2));
                    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(subIterator, 1), CHARACTER_REACTION(((unsigned char)iterator))+1-(subIterator > 2));
                    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(subIterator, 2), CHARACTER_REACTION(((unsigned char)iterator))+2+(subIterator > 2));
                    OAM_SET_SPRITE_TILE(CHARACTER_SPRITE(subIterator, 3), CHARACTER_REACTION(((unsigned char)iterator))+3-(subIterator > 2));
                    iterator++;
                }
            }
            SET_SKILL_ANIMATION(flag, 2);
            OAM_START_TRANSFER();
            iterator = 84;
        }
        if(!isRanged && iterator <= 96) {
            stepX = (char)(fX + (xT-fX)*iterator/96);
            stepY = (char)(fY + (yT-fY)*iterator/96);
            OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 0), stepX);
            OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 1), stepX+8);
            OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 2), stepX);
            OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 3), stepX+8);

            OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 0), stepY);
            OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 1), stepY);
            OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 2), stepY+8);
            OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 3), stepY+8);
            OAM_START_TRANSFER();
        }
        if(isRanged)
            delay(13);
        else delay(2);
    }
    delay(100);
    for(iterator = 19; iterator != 0 && !isRanged; iterator--) {
        stepX = (char)(fX + (xT-fX)*iterator/19);
        stepY = (char)(fY + (yT-fY)*iterator/19);
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 0), stepX);
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 1), stepX+8);
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 2), stepX);
        OAM_SET_SPRITE_POSITION_X(CHARACTER_SPRITE(attacker, 3), stepX+8);

        OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 0), stepY);
        OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 1), stepY);
        OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 2), stepY+8);
        OAM_SET_SPRITE_POSITION_Y(CHARACTER_SPRITE(attacker, 3), stepY+8);
        OAM_START_TRANSFER();
        delay(5);
    }
    if(isRanged)
        delay(300);

    for(subIterator = 0; subIterator < 6; subIterator++) {
        if(attacked & (1 << subIterator))
            setCharacterToIdle(subIterator);
    }
    setCharacterToIdle(attacker);
    characterIdleAnimation = animationIdlePre;
    OAM_START_TRANSFER();
}

void progressStunsAndModifiers(unsigned char characterID) {
    unsigned char iterator, temp = 0;
    if(CHARACTERS_CURRENT_HP(characterID) == 0)
        return;
    for(iterator = 0; iterator < CHARACTERS_MODIFIERS_AMOUNT(characterID); iterator++)
    {
        if(GET_MODIFIER_LENGTH(characterID, iterator) == 0) {
            for(temp = iterator; temp < CHARACTERS_MODIFIERS_AMOUNT(characterID) - 1; temp++) {
                GET_MODIFIER_BYTE(characterID, temp) = GET_MODIFIER_BYTE(characterID, temp+1);
                SET_CHARACTERS_MODIFIER_SIGN(characterID, temp,
                                             GET_MODIFIER_SIGN(characterID, temp+1));
            }
            temp = CHARACTERS_MODIFIERS_AMOUNT(characterID);
            CLEAR_CHARACTERS_MODIFIERS_AMOUNT(characterID);
            SET_CHARACTERS_MODIFIERS_AMOUNT(characterID, temp-1);

        }
        temp = GET_MODIFIER_LENGTH(characterID, iterator);
        SET_CHARACTERS_MODIFIER(characterID, iterator,
                                temp-1, GET_MODIFIER_STATISTIC_TYPE(characterID, iterator),
                                GET_MODIFIER_VALUE(characterID, iterator));
    }
    temp = CHARACTERS_CURRENT_STUN(characterID);
    if(temp) {
        CLEAR_CHARACTERS_STUN(characterID);
        SET_CHARACTERS_STUN(characterID, temp-1);
        if(!(temp-1)) {
             characterIdleAnimation |= (1<<characterID);
        }
    }

}

void setArrowAtCharacter(unsigned char id)
{
    if(id > 2) id++;
    if(id & 1)
    {
        if(id & 4)
        {
            OAM_SET_SPRITE_POSITION_X(ARROW_SPRITE, 164u-CHARACTER_BEHIND_POSITION_X);
        }
        else
        {
            OAM_SET_SPRITE_POSITION_X(ARROW_SPRITE, CHARACTER_BEHIND_POSITION_X+4);
        }
    }
    else
    {
        if(id & 4)
        {
            OAM_SET_SPRITE_POSITION_X(ARROW_SPRITE, 164u-CHARACTER_FRONT_POSITION_X);
        }
        else
        {
            OAM_SET_SPRITE_POSITION_X(ARROW_SPRITE, CHARACTER_FRONT_POSITION_X+4);
        }
    }
    OAM_SET_SPRITE_POSITION_Y(ARROW_SPRITE, 48+((id&3)<<4));
    OAM_SET_SPRITE_TILE(ARROW_SPRITE, ARROW_TILE);
    OAM_START_TRANSFER();
}
