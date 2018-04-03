/*tryStatistic needs prepared messageBuffer!
 * Place for value and name of statistic
 * */
int tryStatistic(struct Character* character, unsigned char statistic, unsigned char tryFlag) {
    int rolled = 0;
    replaceInBuffer(character->bank, character->name);
    rolled = (randw() % 100) - getStatistic(character,
                            COMBINE_DATA_STATISTIC_ID(statistic, TRY_PERSON_ID(tryFlag))) + (TRY_STATISTIC_MODIFIER(tryFlag) * 5);
    replaceInBufferInt(rolled);
    replaceFightStringInBuffer(statisticNames[statistic]);
    if(TRY_STATISTIC_MODIFIER(tryFlag)) {
        replaceFightStringInBuffer(statisticAdd);
        replaceInBufferInt(TRY_STATISTIC_MODIFIER(tryFlag) * 5);
    }
    return rolled;
}



unsigned char test(int rolled) {
    if(rolled < -100)
        return 6;
    else if(rolled < -70)
        return 5;
    else if(rolled < -50)
        return 4;
    else if(rolled < -30)
        return 3;
    else if(rolled < -10)
        return 2;
    else if(rolled <= 0)
        return 1;
    return 0;
}

unsigned char randomSkill(unsigned char id) {
    unsigned char temp = rand();
    if(temp > 64 || ENEMY_SKILL(id, 1)->nameAndDescription == 0)
        return 0;
    if(temp > 16 || ENEMY_SKILL(id, 2)->nameAndDescription == 0)
        return 1;
    if(temp > 8  || ENEMY_SKILL(id, 3)->nameAndDescription == 0)
        return 2;
    return 3;
}

unsigned char pickRandomBit(unsigned char from) {
    unsigned char bits = 0, temp = from;
    while(temp) {
        if(temp & 1)
            bits++;
        temp >>= 1;
    }
    bits = rand() % bits;
    temp = 1;
    while(1) {
        while(from) {
            if(from & temp) {
                break;
            }
            temp <<= 1;
        }
        if(!bits)
            return temp;
        temp <<= 1;
        bits--;
    }
    return 0;
}
