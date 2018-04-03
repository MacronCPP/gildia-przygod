struct Character {
    unsigned char state, currentHealthPoints;
    unsigned char bank;
    const char* name;
    const unsigned char* graphics;
    unsigned char strength, dexterity, perception, charisma, vitality;
    unsigned char damageMelee, damageRanged;
    unsigned char moralBoost;
};

struct StunSkill {
    unsigned char header;
};

/* Functions:
 *  gets one pointer in temporaryFightPointer - pointer to Character* target
 *  must return in fightResult result of fight - 0 if skill damaged
 *                                               1 if skill missed
 *                                               2 if skill was helping target
*/

struct FunctionSkill {
    void (*function)();
    unsigned char bank;
};

struct StatisticModifierSkill {
    unsigned char header;
    unsigned char boostA;
    unsigned char boostB;
};

struct BoostedAttackSkill {
    unsigned char header;
    unsigned char boostA;
    unsigned char boostB;
};
union SkillStat {
    struct StunSkill stun;
    struct FunctionSkill function;
    struct StatisticModifierSkill modifier;
    struct BoostedAttackSkill boosted;
};

struct Skill {
   unsigned char type;
   union SkillStat stats;
   const char* nameAndDescription;
   unsigned char bank;
};
