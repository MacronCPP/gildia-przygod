# Gildia przygód
A RPG for Game Boy Classic, made using GBDK, written in C and Java.


## Overview
This game is based on a tabletop roleplaying game, made by THCobra, with a purpose of being an additional content, presented to another players just before final session of a RPG campaign. Limitations of the GB platform was used to make development of this project easier and more fun. Due to an unmovable deadline, the game engine hasn't got implemented all the features; some of them are unfinished, some work, but aren't used in a test map, some are nonexistent.

#### Credits
* Maciej "Macron" Ziolkowski - programmer, graphics designer
* Kacper "WielkiPierogo" Herchel - graphics designer(logo, arena tileset)
Based on a tabletop roleplaying game, made by Lukasz "TripleHededCobra" Pecia

This game is by gameplay divided into two parts:
* Overworld view - moving on map, events, messages 
* Fight view     - encounters


## Overworld

### Map format
In the overworld, player is moving on a 32x32, looping map. There is a camera, moving along with the player character. Maps are represented by tile values(0 - 63). They are compressed: there are 4 tiles saved on 3 bytes, every on 6 bites. AABBBBBB, AACCCCCC, AADDDDDD. Before transfering values to VRAM, 128 is added to them, resulting in a range of 112-175, that can be used on a map. You can also use a CHANGE_TILE event to use tiles with values out of that range; it will be descripted in Events section. 
To load a map, use loadMap function located in bank 0 - (bank number, uchar* pointer to map, map width, map heights).

Tiles with values V, that V % 16 > 4, have collisions. It can be changed by a modification of IS_COLLIDABLE(x) macro in defines.c.

### Character animations
The player character in the overworld is size of 8x16 pixels, it uses two separate sprites. The character animations are taken from the tileset range of 176-207. In 192-207 are placed lower halves of the character animations(ID of the second half is a ID of the first half + 16). With that, it is easier to draw the tileset as a 256x256 image. The animation consists of 4 frames in every side, making it 16 frames overall. First four frames are displayed while moving to the left, next - while moving up, while moving to the right and the last ones while moving down.

### Events
To make things happen in this game, a event mechanism is being used. Every character movement, a processEvent function is being run on eventsLocation variable. The events address is being read and  events' conditions are being checked.

Event memory syntax:
	
	<Events number(1 byte)>

	<Event (varying size)>
	<Event (varying size)>
	...
	<Event (varying size)>

Event syntax:
	
	<Conditions amount(1 byte)>
	<Condition (4 bytes)>
	<Condition (4 bytes)>
	...
	<Condition (4 bytes)>

	<Effects amount(1 byte)>
	<Effect (5 bytes)>
	<Effect (5 bytes)>
	...
	<Effect (5 bytes)>


Conditions consist of type(1 byte) and 3 bytes of a condition data. If condition has less arguments that 3 bytes, it has to be filled with 0 to the size of 3 bytes. All of conditions must be fulfilled to run a event.
Effects consist of type(1 byte) and 4 bytes of a condition data. If an effect takes less than 4 bytes as data, it also has to be filled with 0 to the size of 4 bytes.

Condition types
All the condition type names below are provided as in defines.c file.

| Condition type | Data 0(byte) | Data 1(byte) | Data 2(byte)  | Description |
| --- | --- | --- | --- | --- |
| EVENT_CONDITION_POSITION  | x position on a map(0 - 31) | y position on a map(0 - 31) | UNUSED | Checks if the player is on provided position |
| EVENT_CONDITION_ITEM  | Item ID  | Item amount  | UNUSED | Checks whether player's EQ has AT LEAST a provided amount of the specified item | 
| EVENT_CONDITION_BITFLAG  | Bit ID  | Bit value | UNUSED | Checks whether bitflag of a specified ID(0 - 255) is set(1) or cleared(0) |

The condition data is 3 bytes long, despite the fact that all of them uses only 2 bytes, because more events was planned, like EVENT_CONDITION_FUNCTION, but they didn't get implemented.

Effect types
All the effect type names below are provide as in defines.c file.

| Effect type | Data 0(byte) | Data 1(byte) | Data 2(byte)  | Data 3(byte) | Description |
| --- | --- | --- | --- | --- | --- |
| EVENT_MESSAGE  | Pointer_L | Pointer_H | Bank | Flags | Shows a message, read from a specified bank. |
| EVENT_CHANGE_TILE  | x position | y position | Tile | UNUSED | Changes map tile on x/y position to tile. **Changes get reset at changing map or going into an encounter!** |
| EVENT_CHANGE_MAP  | Pointer_L | Pointer_H | 3 high bits of bank/X position | 3 lower bits of bank/X position | Loads map from a specified bank and specified memory address, then places the player character on a provided position. Loads the map, using loadMap, with a width/height of 32.|
| EVENT_ENCOUNTER  | Pointer_L | Pointer_H | Bank | UNUSED | Loads and plays a encounter loaded from a specified location in the memory and a specified bank. The encounters will be descripted in the Fight section. | 
| EVENT_TELEPORT  | x position (0-31) | y position (0-31) | UNUSED | UNUSED | Teleports the player character to a specified position. | 
| EVENT_DELAY  | Time_L | Time_H | UNUSED | UNUSED | Waits the specified time, in milliseconds. (16 bit), it is not an address! | 
| EVENT_MOVE_CAMERA  | x position (0-255) | y position (0-255) | UNUSED | UNUSED | Moves camera to the specified location, using the closest route. Remember that when the player will regain control of their character, the camera will center on him! | 
| EVENT_ROLL_OUT_WINDOW  | UNUSED | UNUSED | UNUSED | UNUSED | Rolls out the GB window. | 
| EVENT_ROLL_IN_WINDOW  | UNUSED | UNUSED | UNUSED | UNUSED | Rolls in the GB window to the position of 104. **The window will be below all the sprites shown on the map(like the player character)!** | 
| EVENT_LOCK_CAMERA  | UNUSED | UNUSED | UNUSED | UNUSED | Locks the camera. It will not move with the player character. It is still possible for the player character to move out of the visible map. |
| EVENT_UNLOCK_CAMERA  | UNUSED | UNUSED | UNUSED | UNUSED | Unlocks the camera. It will now move with the player character. At default, the camera is unlocked.|
| EVENT_FADE_OUT  | UNUSED | UNUSED | UNUSED | UNUSED | Fades the screen out to the white. |
| EVENT_FADE_IN | UNUSED | UNUSED | UNUSED | UNUSED | Fades the screen in to the palette that was during the previous fading out. |
| EVENT_SET_BITFLAG | Bit ID | Bit value | UNUSED | UNUSED | Sets or clears a bitflag of a specified ID(0 - 255). 1 - set, 0 - clear. |
| EVENT_LOSE | UNUSED | UNUSED | UNUSED | UNUSED | Shows the game over screen. As there isn't any, it will just reset the game with a soft reset. |
| EVENT_WIN | UNUSED | UNUSED | UNUSED | UNUSED | Works just like a EVENT_LOSE. |
| EVENT_FUNCTION | Pointer_L | Pointer_H | Bank | UNUSED | Runs a void() function from a specified bank and a specified location. Can be used for some more advanced events. |

An example event from arena.c:

```cpp
4,
EVENT_CONDITION_POSITION, 10, 12, 0,
EVENT_CONDITION_BITFLAG, WAS_SECOND_FIGHT, 1, 0,
EVENT_CONDITION_BITFLAG, WAS_THIRD_FIGHT, 0, 0,
EVENT_CONDITION_BITFLAG, READY_FOR_NEXT_FIGHT, 1, 0,
4,
EVENT_SET_BITFLAG, READY_FOR_NEXT_FIGHT, 0, 0, 0,
EVENT_SET_BITFLAG, WAS_THIRD_FIGHT, 1, 0, 0,
EVENT_TELEPORT, 10, 11, 0, 0,
EVENT_ENCOUNTER, 0xF6U, 0x5EU/*pointerTHIRD_ARENA_FIGHT*/, 5, 0
```

#### Pointers
Pointers are represented in a two bytes, first the low byte, then the high byte. To make using it easier, I made a pointerupdater.jar file, that reads a .map generated file for the addresses, and then updates them in the source code. The source code of pointerupdater is in this repository. PointerUpdater takes a path to the .map file and a list of source code files to update. It searches for 

	, 0, 0/*pointerVARIABLENAME*/

and places address of VARIABLENAME at those two bytes. Remember that it has to find coma before the LOW byte to work correctly!

#### Messages
Messages are displayed on a GameBoy window, rolling in from bottom. The first row is a frame, as 64 value. If not stated otherwise, starting at x position of 1 of the first row will be displayed a title of message. A message pointer should point to array, containing one or two C-style strings. A string terminating value is '|'. If not stated otherwise, a first string in the array is the title. If the message flag FLAG_NO_TITLE is set, array should contain only one string, as a message content, otherwise, the second string will be a message content.

Message flags

| Flag | Description | 
| --- | --- | 
| FLAG_WINDOW_IN  | At the start of showing the message, the window will roll in. |
| FLAG_WINDOW_OUT  |  At the end of showing the message, the window will roll out.  |
| FLAG_NO_TITLE  | The message contains no title. |
| FLAG_DONT_CHANGE_BANK  | Don't change bank to read a message - the message is in a currently loaded bank, bank 0 or in a RAM memory |

#### Bitflags
Bitflags are 256 single bits, that you can address in the events. They're placed in bitflags variable(32 bytes long). They're not cleared, unless GB gets restarted. The game provides two flags: wonFight and loseFight, that let you check whether the player won or lose. Bitflags should be defined in bitflagDefine.c file for easier usage.

## Encounter view 
The encounter pointer should point to a simple structure of Encounter. First byte is an encounter header. 

	SSXXXXCC

SS are the bits that contains information, which team starts first.
* 00 - roll for the initiative to determine the first team
* 01 - the player starts
* 10 - the enemies start

CC is an amount of enemies that will participate in a fight(1 - 3).
X is an unused bit.

Next byte is a bank, that contains a background map. The background map has a size of 20x16, compressed in the same way, as an overworld map. Next two bytes are low and high byte of a pointer to the background. Similarly, a next three bytes are: a fight tileset bank, a low byte of a tileset pointer and a high byte. The tileset is should to have 255 tiles, tile with ID of 254 is an arrow that shows current character.

The next two bytes points to a loot table. It's an array, that contains an amount of an items, and then a item ID and amount of this item, in the same way that player's EQ.

### Items
In the player's EQ and loot tables are placed only IDs and amounts of the items; all the information about a specified item is taken from an item table. Every item is 16 bytes long, their ID is based on their order in the table. 
First byte is a header the item, next one is a item data, all of the others make up a string, not terminated with any value, with a resulting with maximal length of 14, containing a title of the item. Unused bytes should have a value of 0.

Header of an item is made up from 8 bits

	TTTAAAAA

T is a item type value(0 - 7), while A is a maximal amount of this item, that can be placed in a inventory (0-31). Checking whether a maximal amount is reached isn't implemented in the source code.

Item types

| Item type | Data bits | A bits | B bits | C bits | Description |
| --- | --- | --- | --- | --- | --- |
| ITEM_STAT_BOOST  | AAABBBBB | A statistic type(0 - 7) | A boost amount(0 - 31) | UNUSED | An item that boosts statistics of a character. The statistics are listed below in a character statistics section. |
| ITEM_QUEST  | XXXXXXXX | UNUSED | UNUSED | UNUSED | An empty item, just for a quest purposes. | 
| ITEM_ARMOR  | AAAAAAAA | A armor value | UNUSED | UNUSED | An item that give a character armor. | 
| ITEM_WEAPON_MELEE  | AABBBBCC | A number of dices | An amount of sides on the dices | An additonal modifier(0 - 3) | A weapon that activates a melee attack. |
| ITEM_WEAPON_RANGED | AABBBBCC | A number of dices | An amount of sides on the dices | An additonal modifier(0 - 3) | A weapon that activates a ranged attack. |
| ITEM_WEAPON_MELEE_CAMP  | AABBBBCC | A number of dices | An amount of sides on the dices | An additonal modifier(0 - 3) | A weapon that activates a melee attack. Replenishes HP equal to DMG that has been dealt. |
| ITEM_AMMO  | AAAAAAAA | An additional damage | UNUSED | UNUSED | An ammo type for the ranged weapon - it isn't implemented. |
| ITEM_POTION  | AAAAAAAA | A number of HP | UNUSED | UNUSED | An item that replenishes HP of a character. |

Item table can be on any bank, but it needs to be specified by a ITEM_BANK macro in defines.c file. 

Player's eq is a array in RAM memory. First 30 bytes belongs to the first character, second 30 bytes to the second character and last 30 bytes to the last character. Items are placed in 2-byte structure - an item ID and an item amount. Every of the main characters can have up to 15 items.

After a pointer to a loot table, there are placed enemy descriptions. First pointer to an enemy data, and next pointer to an enemy skills. If there is more than one enemy, then this description is repeated.

### Character data
Every character's data is 15 bytes long. It shouldn't be updated to apply modifiers for fights. 

| Byte number | Name | Description |
| --- | --- | --- |
| 0 | State flag | Current state of a character. 0 - unknown, 1 - fighting or 2 - uncouncious. |
| 1 | Current HP | Current HP of a character. It is updated after every fight. | 
| 2 | Bank | A bank, where name and animations of a character are placed. | 
| 3, 4 | Name pointer | A pointer to a C-style string, terminated with '|'. |
| 5, 6 | Animation | A pointer to a 96x64 image, consiting of 24 16x16 frames. Template of a image is in the character_template.xfc file. |
| 7 - 14 | Statistics | A statistics of a player, as presented in the Character statistics table. |

While loading an encounter, it is copied to a RAM memory. A nonexisting character should have state 0.

#### Character statistics
Statistics are used in a fight, may be temporary boosted with items or some skills.

| Statistic ID | Name | Description |
| --- | --- | --- | 
| 0 | Strength | Strength of a character. |
| 1 | Dexterity | Dexterity of a character. Used for a roll for accuracy and for initiative. | 
| 2 | Perception | Perception of a character. Used for a roll for scout. | 
| 3 | Charisma | Charisma of a character. |
| 4 | Vitality | Vitality of a character. Determines maximal HP of a character. |
| 5-7 | DMG/Moral Bonus | UNUSED |

### Character skills
Any character should have at least a one skill. There's no way to have a character with more than four skills, without modifying a code or using a "function" skill to hide beneath it more skills. Typically, the first skill is a normal attack, but it is possible to attach there another type of a skill.

Every skill takes up a memory of 7 bytes.

| Byte number | Name | Description |
| --- | --- | --- |
| 0 | Skill type | A skill type(bits 0-2), combined with a possible targets flag(bits 5-7). All of the skill flags are listed in the table below. Possible targets - 000 - enemy, 001 - all enemies, 010 - ally, 011 - all allies, 100 - self |
| 1 - 3 | Skill data | A skill data, associated with a skill type. Unused bytes should have a value of 0. | 
| 4, 5 | Name pointer | A pointer to a C-style string, terminated with '\|'. Should be shorter than 9 letters. Can be longer if the skill is only one in a row. |
| 6 | Bank | A bank, where the name of the skill is placed. |

An empty skill should have a name pointer value of 0.
Every skill, that is after an empty skill, may not work!

#### Skill types

| Skill type | Data bits | A bits | B bits | C bits | D bits | E bits | Description |
| --- | --- | --- | --- | --- | --- | --- | --- |
| SKILL_STUN(0)  | AABBBCCC X X | A reduction of a statistic. It gets multiplied to by 5 to make a roll modifier. | A length of a stun.  | A statistic type to check | UNUSED | UNUSED | This skill stuns an enemy. |
| SKILL_ATTACK(1)  | X X X | UNUSED | UNUSED | UNUSED | UNUSED | UNUSED | An ordinary attack. | 
| SKILL_FUNCTION(2)  | Pointer(16 bit) Bank(8 bit)| UNUSED | UNUSED | UNUSED | UNUSED | UNUSED |Runs a function located on a provided memory address and in a specified memory bank. It should take no arguments, use temporaryFightPointer(Character*) and write an output to a fightResult(0 - skill succeded, 1 - skill missed, 2 - skill was a boost/help, 8(flag) - skill was ranged). | 
| SKILL_STAT_REDUCTION(4)  | AABBBCCC DDDEEEEE DDDEEEEE | A reduction of a statistic to check. It gets multiplied to by 5 to make a roll modifier. | A length of a reduction.  | A statistic type to check. | A statistic modifier. | A statistic to reduce | A reduction value | Reduces value of a statistic. Only 7 modifiers can take place on any time, if more gets added, the shortest one gets removed. One skill can add up to 2 modifiers. |
| SKILL_STAT_BOOST(5) | AABBBCCC DDDEEEEE DDDEEEEE | A reduction of a statistic. It gets multiplied to by 5 to make a roll modifier. | A length of a boost.  | A statistic type to check. | A statistic to reduce | A boost value | Boosts the value of a statistic. Only 7 modifiers can take place on any time, if more gets added, the shortest one gets removed. One skill can add up to 2 modifiers. |

Unimplemented skill types:
* Boosted attack
* Moral boost

#### Enemies

Enemy AI works randomly, choosing the first skill with a most propability(then the second skill, then the third one). It takes a random target for its skill. 

The result gets written into the winFight/loseFight flags, where it can be checked.

## Additional applications

To help myself with making this game, I made a few applications:

* An image converter written in C++ and SFML. Lets you convert an image, modify contrast and brightness and save it in an assembly or .c file.
* A Java application that helps making item tables/skill sets/maps.
* A Java application, pointerUpdater, described in a Pointers section.

The source code of pointerUpdater is in this repository.

## Things that should be added to make this a game

Because of a strict deadline, I didn't manage to make it into a full game. It works as a 15-minutes demo, but in order to be a finished and polished game, these features should be implemented:

* Level up system
* Events that add items/skills, change graphics, making a roll
* Shops, decisions, dialog options
* Saves
* Statistics and EQ screens, managing it
* More skill types(some were planned, but not implemented, like moral boosts), some item types
* Audio! It's complicated and I didn't want to touch it.

## GBDK trivia

If you want to do something nowadays in GBDK, here's some advices:

* GBDK makes a OAM space on 0xC0XX and copies a DMA routine to a high RAM 0xFF80. I wrote a small routine in assembly that calls it to control that. It is placed in a interruptHandlers.asm file.
* GBDK's drawImage includes a lot of GBDK code, that can take up to 7 KB of ROM memory! That's a lot, so I copied assembly code of a draw_image function and change somewhat .
* draw_image is a very bugged function and hates interrupts. Do not use it. Or use it and then try to clean up all of the mess. You can look up it in my code.
* GBDK won't tell you whether you have taken more memory than there is on one ROM chip.
* A .map file is your best friend if you want to find a bug.
* GBDK can generate shift instructions wrongly.
* .area CODE_X is more important than the arguments sent to a compiler/linker!
* GBDK can't cast an int to a pointer to a function. Use a struct/union to do so!


There might be an update for readme.md or the source code someday.

Want any help? Have any question? Write to me at maciej.macron.ziolkowski@gmail.com or contact me on Discord: Macron#0171


