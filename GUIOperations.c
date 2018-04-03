void rollWindowIn(unsigned char target)
{
    while(MEM(WINDOW_POSITION_Y) > target)
    {
        move_win(7, MEM(WINDOW_POSITION_Y)-1);
        delay(10);
    }
}

void rollWindowBack(unsigned char target)
{
    while(MEM(WINDOW_POSITION_Y) < target)
    {
        move_win(7, MEM(WINDOW_POSITION_Y)+1);
        delay(10);
    }
}

void rollWindowOut()
{
    rollWindowBack(144);
}

void renderMessageOnWindow(unsigned char flag, unsigned char* memoryLocation)
{
    unsigned char buffer[1], *temp;
    unsigned char x = 0, y = 1, wordLength = 0;
    CLEAR_MESSAGE_WINDOW;
    buffer[0] = FRAME_TOP;
    set_win_tiles(0, 0, 1, 1, buffer);

    if(!(flag & FLAG_NO_TITLE)) {
        temp = memoryLocation;
        while(memoryLocation[x] != '|')x++;

        memoryLocation = temp;

        if(x)
            set_win_tiles(1, 0, x, 1, memoryLocation);

        x++;
        memoryLocation += x;
    }
    do
    {
        set_win_tiles(x, 0, 1, 1, buffer);
    }   while(++x < 20);
    x = 0;
    while(*memoryLocation != '|') {
        set_win_tiles(x, y, 1, 1, memoryLocation);
        if(*memoryLocation == ' ') {
            wordLength = 1;

            while(MEM(memoryLocation + wordLength) != ' ' && MEM(memoryLocation + wordLength) < '|')
                wordLength++;


            if(x + wordLength >= 20) {
                x = 255;
                y++;
            }
        }
        x++;
        memoryLocation++;
    }
}

void showMessage(unsigned char bank, unsigned char flag, unsigned char* memoryLocation)
{
    unsigned char savedBank = currentBank;
    if(!(flag & FLAG_DONT_CHANGE_BANK))
    {
        SWITCH_ROMS(bank);
    }
    if(flag & FLAG_WINDOW_IN)
        move_win(7, 144);
    renderMessageOnWindow(flag, memoryLocation);
    if(flag & FLAG_WINDOW_IN)
    {
        SHOW_WIN;
        rollWindowIn(104);
    }
    waitpadup();
    waitpad(J_A);
    waitpadup();
    if(flag & FLAG_WINDOW_OUT)
    {
        rollWindowOut();
        HIDE_WIN;
    }
    if(!(flag & FLAG_DONT_CHANGE_BANK))
    {
        SWITCH_ROMS(savedBank);
    }
}

void showBufferedMessage() {
    showMessage(0, FLAG_DONT_CHANGE_BANK | FLAG_NO_TITLE, messageBuffer);
}
void renderBufferedMessage() {
    renderMessageOnWindow(FLAG_NO_TITLE, messageBuffer);
}

unsigned char showOptions(unsigned char bank, unsigned char flag, const unsigned char* title,
                          const unsigned char* first, const unsigned char* second, const unsigned char* third, const unsigned char* fourth)
{
    unsigned char savedBank = currentBank, x = 0;
    unsigned char selected = 0, lastPressedNegation = 0, val = 0;
    const char* options[4] = {first, second, third, fourth};
    char buffer[1];
    if(!(flag & FLAG_DONT_CHANGE_BANK))
    {
        SWITCH_ROMS(bank);
    }
    if(flag & FLAG_WINDOW_IN)
        move_win(7, 144);
    CLEAR_MESSAGE_WINDOW;
    x = 0;
    buffer[0] = FRAME_TOP;
    set_win_tiles(0, 0, 1, 1, buffer);

    while(title[x] < '|')x++;
    if(x) set_win_tiles(1, 0, x, 1, title);
    x++;
    do
    {
        set_win_tiles(x, 0, 1, 1, buffer);
    }   while(++x < 20);

    while(options[selected] != 0 && selected < 4)
    {
        x = 2;
        while(options[selected][x-2] < '|' && x < 10)
        {
            set_win_tiles(x + 10*(selected&1), 2 + (selected&2), 1, 1, (char*)(options[selected]+(x-2)));
            x++;
        }
        selected++;
    }
    buffer[0] = '-';
    set_win_tiles(1, 2, 1, 1, buffer);
    if(flag & FLAG_WINDOW_IN)
    {
        SHOW_WIN;
        rollWindowIn(104);
    }
    selected = 0;
    while(1)
    {
        val = joypad();
        x = selected;
        if(val & J_DOWN & lastPressedNegation)
            if(!(selected & 2))
                selected += 2;

        if(val & J_UP & lastPressedNegation)
            if(selected & 2)
                selected -= 2;

        if(val & J_LEFT & lastPressedNegation)
            if(selected & 1)
                selected--;

        if(val & J_RIGHT & lastPressedNegation)
            if(!(selected & 1))
                selected++;

        if(options[selected] == 0)
            selected = x;

        if(val & J_A & lastPressedNegation)
            break;

        if((flag & FLAG_MENU_BACKABLE) && (val & J_B & lastPressedNegation))
        {
            selected = MENU_BACK;
            break;
        }

        if(x != selected)
        {
            buffer[0] = 0;
            set_win_tiles(1 + 10*(x&1), 2 + (x&2), 1, 1, buffer);
            buffer[0] = '-';
            set_win_tiles(1 + 10*(selected&1), 2 + (selected&2), 1, 1, buffer);
        }

        lastPressedNegation = ~val;
    }
    if(flag & FLAG_WINDOW_OUT)
    {
        rollWindowOut();
        HIDE_WIN;
    }
    if(!(flag & FLAG_DONT_CHANGE_BANK))
    {
        SWITCH_ROMS(savedBank);
    }
    return selected;
}
