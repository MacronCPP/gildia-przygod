void restoreArmor(unsigned char id) {
    CHARACTERS_CURRENT_ARMOR(id)
            = armorValue(id);
}

void damage(struct Character* character, unsigned char id, unsigned char value) {
    unsigned char* armor = &CHARACTERS_CURRENT_ARMOR(id);
    if(*armor >= value) {
        *armor -= value;
        return;
    }
    value -= *armor;
    *armor = 0;
    if(CHARACTERS_CURRENT_HP(id) > value) {
        CHARACTERS_CURRENT_HP(id) -= value;
        character->currentHealthPoints -= value;
        return;
    }
    CHARACTERS_CURRENT_HP(id) = 0;
    character->currentHealthPoints = 0;
    character->state &= ~1;
}

void addStun(unsigned char id, unsigned char length) {
    if(length > CHARACTERS_CURRENT_STUN(id)) {
        CLEAR_CHARACTERS_STUN(id);
        SET_CHARACTERS_STUN(id, length);
    }
}

void addModifier(unsigned char id, unsigned char length, unsigned char boost) {
    unsigned char minLength = length, minID = 8, iterator = 0;
    if(CHARACTERS_MODIFIERS_AMOUNT(id) != 7) {
        CLEAR_CHARACTERS_MODIFIERS_AMOUNT(id);
        SET_CHARACTERS_MODIFIERS_AMOUNT(id, CHARACTERS_MODIFIERS_AMOUNT(id) + 1);
        SET_CHARACTERS_MODIFIER(id, CHARACTERS_MODIFIERS_AMOUNT(id),
                length, boost >> 4 >> 1, boost & 15);
        SET_CHARACTERS_MODIFIER_SIGN(id, CHARACTERS_MODIFIERS_AMOUNT(id), (boost & 16) >> 4);
    } else {
        for(iterator = 0; iterator < 7; iterator++) {
            if(minLength > (boost >> 2 >> 4)) {
                minID = iterator;
                minLength = (boost >> 2 >> 4);
            }
        }
        if(minID != 8) {
            SET_CHARACTERS_MODIFIER(id, minID,
                    length, boost >> 4 >> 1, boost & 31);
        }
    }
}
/* ??SSSIII - I - id, S - statistic
 * */

int getStatistic(struct Character* character, unsigned char idAndStatistic) {
    unsigned char statistic = STATISTIC_TYPE_FROM_PACK(idAndStatistic), iterator = 0;
    int ret = STATISTIC_FROM_CHARACTER(character, statistic);
    if(statistic == STATISTIC_CHARISMA && ret != 84) {
        BACKGROUND_PALETTE = ~BACKGROUND_PALETTE;
    }
    ret += ((int)(eqStatistic(ID_FROM_PACK(idAndStatistic), statistic))) * 5;

    for(iterator = 0; iterator < CHARACTERS_MODIFIERS_AMOUNT(ID_FROM_PACK(idAndStatistic)); iterator++) {
        if(GET_MODIFIER_STATISTIC_TYPE(ID_FROM_PACK(idAndStatistic), iterator) == statistic) {
            if(GET_MODIFIER_SIGN(ID_FROM_PACK(idAndStatistic), iterator)) {
                ret -= GET_MODIFIER_VALUE(ID_FROM_PACK(idAndStatistic), iterator);
            } else {
                ret += GET_MODIFIER_VALUE(ID_FROM_PACK(idAndStatistic), iterator);
            }
        }
    }
    if(STUNNED_LENGTH(ID_FROM_PACK(idAndStatistic)))
            ret -= 20;
    return ret;
}
