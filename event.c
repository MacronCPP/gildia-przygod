unsigned char bitflag[32];

unsigned char hasItem(unsigned char ID, unsigned char am);

#include "eventStructs.c"

unsigned char checkConditions(unsigned int eventPointer) {
    union EventConditionData* conditionData;
    conditionData = (union EventConditionData*)(eventPointer+1);
    if(MEM(eventPointer) == EVENT_CONDITION_POSITION) {
        return (overworldPosX>>3) == conditionData->position.x && (overworldPosY>>3) == conditionData->position.y;
    }
    if(MEM(eventPointer) == EVENT_CONDITION_BITFLAG) {
        return GET_BITFLAG((conditionData->bitflag.bitNumber)) == conditionData->bitflag.value;
    }
    if(MEM(eventPointer) == EVENT_CONDITION_ITEM) {
        return hasItem(conditionData->item.itemID, conditionData->item.amount);
    }
    return 0;
}
extern const unsigned char arenaMap[];
void processEvent(unsigned int eventPointer) {
    unsigned char tempByte;
    union EventData* eventData;
    eventData = (union EventData*)(eventPointer+1);
    if(MEM(eventPointer) == EVENT_FADE_IN) {
        fadeIn(eventData->fade.length);
        return;
    }
    if(MEM(eventPointer) == EVENT_FADE_OUT) {
        fadeOut(eventData->fade.length);
        return;
    }
    if(MEM(eventPointer) == EVENT_TELEPORT) {
        overworldPosX = (eventData->teleport.x)<<3;
        overworldPosY = (eventData->teleport.y)<<3;
        return;
    }
    if(MEM(eventPointer) == EVENT_MESSAGE) {
        showMessage(eventData->message.bank, eventData->message.flag, eventData->message.pointer);
        return;
    }
    if(MEM(eventPointer) == EVENT_FUNCTION) {
        tempByte = currentBank;
        SWITCH_ROMS(eventData->function.bank);
        eventData->function.pointer();
        SWITCH_ROMS(tempByte);
        return;
    }
    if(MEM(eventPointer) == EVENT_DELAY) {
        delay(eventData->delay.time);
        return;
    }
    if(MEM(eventPointer) == EVENT_MOVE_CAMERA) {
        moveSlowlyCamera(eventData->moveCamera.x, eventData->moveCamera.y);
        return;
    }
    if(MEM(eventPointer) == EVENT_CHANGE_TILE) {
        WAIT_FOR_NO_LCD;
        MAP_AT(eventData->changeTile.x, eventData->changeTile.y) = eventData->changeTile.new;
        return;
    }
    if(MEM(eventPointer) == EVENT_CHANGE_MAP) {
        loadMap(GET_MAP_BANK(eventData->changeMap.a, eventData->changeMap.b), eventData->changeMap.mapPointer, 32, 32);
        overworldPosX = (eventData->changeMap.a)&31;
        overworldPosY = (eventData->changeMap.b)&31;
        return;
    }
    if(MEM(eventPointer) == EVENT_ENCOUNTER) {
        tempByte = currentBank;
        fadeOut(150);
        loadEncounter(eventData->encounter.encounter, eventData->encounter.bank);
        eventPointer = ((((unsigned int)MEM(SCROLL_X)) << 4 << 4) | MEM(SCROLL_Y));
        MEM(SCROLL_X) = 0; //I'm using eventPointer to save camera position in it
        MEM(SCROLL_Y) = 0;
        fadeIn(150);
        SWITCH_ROMS(4);
        fightViewLoop();
        fadeOut(150);
        loadMap(currentMapBank, currentMap, 32, 32);
        MEM(SCROLL_X) = (unsigned char)(eventPointer >> 4 >> 4);
        MEM(SCROLL_Y) = (unsigned char)eventPointer;
        for(eventPointer = 0; eventPointer < 40; eventPointer++) {
            OAM_SET_SPRITE_POSITION_X(eventPointer, -8);
        }
        OAM_SET_SPRITE_POSITION_X(0, overworldPosX+8-MEM(SCROLL_X));
        OAM_SET_SPRITE_POSITION_X(1, overworldPosX+8-MEM(SCROLL_X));
        OAM_SET_SPRITE_POSITION_Y(0, overworldPosY+8-MEM(SCROLL_Y));
        OAM_SET_SPRITE_POSITION_Y(1, overworldPosY+16-MEM(SCROLL_Y));
        OAM_SET_SPRITE_TILE(0, TILE_OVERWORLD_CHARACTER);
        OAM_SET_SPRITE_TILE(1, TILE_OVERWORLD_CHARACTER_SECOND);
        OAM_START_TRANSFER();
        SWITCH_ROMS(currentTilesetBank);
        set_bkg_data(0, 255, currentTileset);
        set_sprite_data(0, 255, currentTileset);
        fadeIn(150);
        SWITCH_ROMS(tempByte);
        return;
    }
    if(MEM(eventPointer) == EVENT_ROLL_OUT_WINDOW) {
        rollWindowOut();
        return;
    }
    if(MEM(eventPointer) == EVENT_ROLL_IN_WINDOW) {
        rollWindowIn(104);
        return;
    }
    if(MEM(eventPointer) == EVENT_LOCK_CAMERA) {
        cameraStatus &= ~1;
        return;
    }
    if(MEM(eventPointer) == EVENT_UNLOCK_CAMERA) {
        cameraStatus |= 1;
        return;
    }
    if(MEM(eventPointer) == EVENT_SET_BITFLAG) {
        SET_BITFLAG((eventData->bitflag.bitNumber), (eventData->bitflag.value));
        return;
    }
    if(MEM(eventPointer) == EVENT_LOSE || MEM(eventPointer) == EVENT_WON) {
        reset();
        return;
    }
}

void checkEvents(unsigned int eventPointer, unsigned char bank) {
    unsigned char savedBank = currentBank, eventAmount, amount, succeded;
    SWITCH_ROMS(bank);
    eventAmount = MEM(eventPointer);
    eventPointer++;
    while(eventAmount) {
        eventAmount--;
        amount = MEM(eventPointer);
        succeded = 1;
        eventPointer++;
        while(amount) {
            if(!checkConditions(eventPointer)) {
                eventPointer += (amount<<2);
                succeded = 0;
                break;
            }
            amount--;
            eventPointer += 4;
        }
        amount = MEM(eventPointer);
        if(!succeded) {
            eventPointer += ((amount<<2)+amount) + 1;
            continue;
        }

        eventPointer++;
        while(amount) {
            processEvent(eventPointer);
            amount--;
            eventPointer += 5;
        }

    }

    SWITCH_ROMS(savedBank);
}
