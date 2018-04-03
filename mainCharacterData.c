//Arkeitz skills
//1. Normal attack
//2. Forfeit mind
//3. Control
//4. ------

const unsigned char arkeitzSkills[] =
{
    1, 0, 0, 0, 0x40U, 0x46U/*pointerFAttackNameDescription*/, 6,
    0, 24, 0, 0, 0xD8U, 0x46U/*pointerControlNameDescription*/, 6,
    4, 18, 36, 68, 0xE1U, 0x46U/*pointerFMindNameDescription*/, 6,
    0, 0, 0, 0, 0, 0, 0
};

//Ryszard skills
//1. Normal attack
//2. Lick
//3. Sing
//4. ------

const unsigned char ryszardSkills[] =
{
    1, 0, 0, 0, 0x40U, 0x46U/*pointerFAttackNameDescription*/, 6,
    0, 24, 0, 0, 0x7CU, 0x46U/*pointerLickNameDescription*/, 6,
    101, 19, 4, 36, 0x64U, 0x46U/*pointerSingNameDescription*/, 6,
    0, 0, 0, 0, 0, 0, 0
};

//Thidem skills
//1. Normal attack
//2. ------
//3. ------
//4. ------
const unsigned char thidemSkills[] =
{
    1, 0, 0, 0, 0x40U, 0x46U/*pointerFAttackNameDescription*/, 6,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

//Unused skills - not deleting them just because of sentiment

const unsigned char chickenSkills[] = {
    1, 0, 0, 0, 0x40U, 0x46U/*pointerFAttackNameDescription*/, 6,
    37, 64, 36, 68, 0xD4U, 0x45U/*pointerSqueekNameDescription*/, 6,
    98, 0xEBU, 0x46U/*pointerchickenHeal*/, 0, 0xF1U, 0x45U/*pointerHugNameDescription*/, 6,
    130, 0xEAU, 0x46U/*pointerswitchOutChicken*/, 0, 0x10U, 0x46U/*pointerRyszardNameDescription*/, 6};

const char SqueekNameDescription[] = "SQUEEK|THE CHICKEN SQUEEKS.|";
const char HugNameDescription[] = "HUG|THE CHICKEN HUGS AN ALLY.|";
const char RyszardNameDescription[] = "RYSZARD|THE CHICKEN SWITCHES OUT WITH RYSZARD.|";

const char FAttackNameDescription[] = "ATTACK|NORMAL ATTACK USING WEAPON.|";
const char SingNameDescription[] = "SING|SING WITH A LYRE.|";
const char LickNameDescription[] = "LICK|LICK AN ENEMY, GRABBING THEIR WEAPON.|";
const char ChickenNameDescription[] = "CHICKEN|RYSZARD SWITCHES OUT WITH THE CHICKEN.|";

const char ControlNameDescription[] = "CONTROL|";
const char FMindNameDescription[] = "F. MIND|";
void switchOutRyszard() {}

void switchOutChicken() {}

void chickenHeal() {}
