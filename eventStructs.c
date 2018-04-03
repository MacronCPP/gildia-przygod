struct EventConditionPosition {
    unsigned char x, y;
};

struct EventConditionBitFlag {
    unsigned char bitNumber;
    unsigned char value;
};

struct EventConditionItem {
    unsigned char itemID, amount;
};

struct EventTeleport {
    unsigned char x, y;
};

struct EventMessage {
    unsigned char* pointer;
    unsigned char bank;
    unsigned char flag;
};

struct EventFunction {
    void(*pointer)();
    unsigned char bank;
};

struct EventEncounter {
    unsigned char* encounter;
    unsigned char bank;
};

struct EventDebug {
    char a, b, c, d;
};

struct EventChangeTile {
    unsigned char x, y, new;
};

struct EventChangeMap {
    unsigned char* mapPointer;
    unsigned char a, b;
};

struct EventDelay {
    int time;
};

struct EventMoveCamera {
    unsigned char x, y;
    int time;
};

struct EventSetBitFlag {
    unsigned char bitNumber;
    unsigned char value;
};

struct EventFade {
    int length;
};

union EventData {
   struct EventTeleport teleport;
   struct EventFunction function;
   struct EventMessage message;
   struct EventMoveCamera moveCamera;
   struct EventDelay delay;
   struct EventDebug debug;
   struct EventChangeMap changeMap;
   struct EventChangeTile changeTile;
   struct EventEncounter encounter;
   struct EventSetBitFlag bitflag;
   struct EventFade fade;
};

union EventConditionData {
    struct EventConditionBitFlag bitflag;
    struct EventConditionPosition position;
    struct EventConditionItem item;
};
