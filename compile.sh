lcc -Wa-l -Wl-m -Wl-j -c -o obj/main.o main.c
lcc -Wa-l -Wl-m -Wl-j -c -o obj/interruptHandlers.o interruptHandlers.asm
lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o obj/bankedBasicFunctions.o bankedBasicFunctions.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o obj/intro.o intro.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o obj/logo.o tileset/logo.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o obj/draw_image.o draw_image.asm
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/worldView.o worldView.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo4 -c -o obj/fightView.o fight/fightView.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o obj/itemTable.o itemTable.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o obj/mainCharacterData.o mainCharacterData.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o obj/tileset_arena.o tileset/tileset_arena.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o obj/tileset_fight_arena.o tileset/tileset_fight_arena.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o obj/arenaMap.o maps/arena.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/fightMaps.o maps/fightMaps.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo7 -c -o obj/fightStrings.o fight/fightStrings.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo7 -c -o obj/fightAdditional.o fight/fightAdditional.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o obj/arkeitz.o tileset/arkeitz.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o obj/thidem.o tileset/thidem.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o obj/ryszard.o tileset/ryszard.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/enemy_bull.o tileset/enemy_bull.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/enemy_rhino.o tileset/enemy_rhino.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/enemy_rat.o tileset/enemy_rat.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/enemy_turtle.o tileset/enemy_turtle.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o obj/enemyBank3Names.o enemyBank3Names.c
lcc -Wa-l -Wl-m -Wl-j -Wl-yt1 -Wl-yo8 -o gp.gb obj/main.o obj/logo.o obj/intro.o obj/draw_image.o obj/interruptHandlers.o obj/worldView.o obj/fightView.o obj/fightMaps.o obj/itemTable.o obj/bankedBasicFunctions.o obj/fightStrings.o obj/fightAdditional.o obj/mainCharacterData.o obj/tileset_arena.o obj/arenaMap.o obj/ryszard.o obj/thidem.o obj/arkeitz.o obj/tileset_fight_arena.o obj/enemy_turtle.o obj/enemy_rat.o obj/enemy_rhino.o obj/enemy_bull.o obj/enemyBank3Names.o
