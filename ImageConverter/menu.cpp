#include "menu.h"
#include <termios.h>
#include <stdio.h>

static struct termios old, newy;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old);
    newy = old;
    newy.c_lflag &= ~ICANON;
    newy.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newy); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}


Menu::Menu::Menu()
{
    Highlighted = 0;
}

void Menu::Menu::setTitle(string _Title)
{
    Title = _Title;
}

void Menu::Menu::addOption(string Name, int ID)
{
    for(size_t a = 0; a != OptionsOnMenu.size(); a++)
    {
        if(OptionsOnMenu[a].ID == ID)
        {
            OptionsOnMenu[a].Name = Name;
            return;
        }
    }

    OptionsOnMenu.push_back(Option(Name, ID));
}

void Menu::Menu::addOptionSlider(string Name, int ID, double stValue, double step, double minValue, double maxValue)
{
    for(size_t a = 0; a != OptionsOnMenu.size(); a++)
    {
        if(OptionsOnMenu[a].ID == ID)
        {
            OptionsOnMenu[a].Name = Name;
            return;
        }
    }

    OptionsOnMenu.push_back(Option(Name, ID, stValue, step, minValue, maxValue));
}

Menu::Option& Menu::Menu::searchForFunction(int ID)
{
    for(size_t a = 0; a != OptionsOnMenu.size(); a++)
    {
        if(OptionsOnMenu[a].ID == ID)return OptionsOnMenu[a];
    }

    return OptionsOnMenu[0];
}

int Menu::Menu::update()
{
    unsigned char val = getch();
    std::cout << (int)val << std::endl;
    switch(val)
    {
        case 65:
            if(Highlighted)Highlighted--;
            else Highlighted = OptionsOnMenu.size()-1;

            break;

        case 66:
            Highlighted++;
            break;

        case 67:
            if(OptionsOnMenu[Highlighted].step != 0)
                OptionsOnMenu[Highlighted].value = min(max(OptionsOnMenu[Highlighted].value + OptionsOnMenu[Highlighted].step, OptionsOnMenu[Highlighted].min), OptionsOnMenu[Highlighted].max);

            val = '\r';
            break;

        case 68:
            if(OptionsOnMenu[Highlighted].step != 0)
                OptionsOnMenu[Highlighted].value = min(max(OptionsOnMenu[Highlighted].value - OptionsOnMenu[Highlighted].step, OptionsOnMenu[Highlighted].min), OptionsOnMenu[Highlighted].max);

            val = '\r';
            break;
    }

    if(Highlighted >= OptionsOnMenu.size())Highlighted = 0;

    if(val == '\r')
    {
        return OptionsOnMenu[Highlighted].ID;
    }

    return -1;
}

double Menu::Menu::getSliderValue(int ID)
{
    for(size_t a = 0; a != OptionsOnMenu.size(); a++)
    {
        if(OptionsOnMenu[a].ID == ID)return OptionsOnMenu[a].value;
    }

    return 0;
}

void Menu::Menu::draw()
{
    if(Title != "")std::cout << Title << std::endl << std::endl;

    for(size_t a = 0; a != OptionsOnMenu.size(); a++)
    {
        std::cout << a+1 << ". " + OptionsOnMenu[a].Name;

        if(a == Highlighted) std::cout << " <-----";

        std::cout << std::endl;
    }
}
