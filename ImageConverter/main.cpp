#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "menu.h"


using namespace std;

void changeVal(string name, int& val)
{
    cout << "Change value " << name << ":";
    cin >> val;
}

void saveSpriteASM(string filename, int** im, int sizeX, int sizeY, int memoryBank)
{
    ofstream file("output/" + filename + ".s");
    file << ".area _CODE";

    if(memoryBank) file << "_" << memoryBank;

    file << "\n.globl _" << filename << "Data" << endl;

    file << ".dw _" << filename << "Data" << endl;

    file << "_" << filename << "Data:" << endl;

    for(size_t j = 0; j != sizeY / 8 + ((bool)(sizeY % 8)); j++)
    {
        for(size_t i = 0; i != sizeX / 8 + ((bool)(sizeX % 8)); i++)
        {
            file << ".db ";

            for(size_t y = 0; y != 8; y++)
            {
                unsigned int highByte = 0, lowByte = 0;

                for(size_t x = 0; x != 8; x++)
                {
                    unsigned int currX = i*8 + x, currY = j*8 + y, val = 0;

                    if(currX < sizeX && currY < sizeY)
                        val = 3-im[currX][currY];

                    highByte |= (3-im[currX][currY]) % 2;

                    lowByte |= (3-im[currX][currY]) / 2;

                    if(x != 7)
                    {
                        highByte <<= 1;
                        lowByte <<= 1;
                    }
                }

                file << highByte << "," << lowByte;

                if(y != 7) file << ",";
            }

            file << "\n";
        }
    }

    file.close();
}
void saveSpriteC(string filename, int** im, int sizeX, int sizeY)
{
    ofstream file(filename + ".c");
    file << "#define " << filename << "SIZEX " << sizeX << endl;
    file << "#define " << filename << "SIZEY " << sizeY << endl;
    file << endl;

    file << "#define " << filename << "SPRITEX " << sizeX / 8 + ((bool)(sizeX % 8)) << endl;
    file << "#define " << filename << "SPRITEY " << sizeY / 8 + ((bool)(sizeY % 8)) << endl;
    file << endl << endl;


    for(size_t j = 0; j != sizeY / 8 + ((bool)(sizeY % 8)); j++)
    {
        for(size_t i = 0; i != sizeX / 8 + ((bool)(sizeX % 8)); i++)
        {
            file << "UBYTE " << filename << i << "x" << j << "[] = {" << endl;

            for(size_t y = 0; y != 8; y++)
            {
                file << "\t";
                unsigned int highByte = 0, lowByte = 0;

                for(size_t x = 0; x != 8; x++)
                {
                    unsigned int currX = i*8 + x, currY = j*8 + y, val = 0;

                    if(currX < sizeX && currY < sizeY)
                        val = 3-im[currX][currY];

                    highByte |= (3-im[currX][currY]) % 2;

                    lowByte |= (3-im[currX][currY]) / 2;

                    if(x != 7)
                    {
                        highByte <<= 1;
                        lowByte <<= 1;
                    }
                }

                file << highByte << ", " << lowByte;

                if(y != 7) file << "," << endl;
            }

            file << "};" << endl << endl;
        }
    }

    file << endl;
    file << "UBYTE* " << filename << "PointersTable[] = {" << endl;

    for(size_t j = 0; j != sizeY / 8 + ((bool)(sizeY % 8)); j++)
    {
        file << "\t";

        for(size_t i = 0; i != sizeX / 8 + ((bool)(sizeX % 8)); i++)
        {
            file << filename << i << "x" << j;

            if(i != sizeX / 8 + ((bool)(sizeX % 8)) - 1)
                file << ", ";
        }

        if(j != sizeY / 8 + ((bool)(sizeY % 8)) - 1)
            file << ',';
        else file << "};";

        file << endl;
    }

    file << endl;
    file.close();
}

void drawSprite(int** sprite, int sizeX, int sizeY)
{
    for(int i = 0; i != sizeY; i++)
    {
        for(int j = 0; j != sizeX; j++)
        {
            switch(sprite[j][i])
            {
                case 0:
                    cout << " ";
                    break;

                case 1:
                    cout << (char)'.';
                    break;

                case 2:
                    cout << (char)':';
                    break;

                case 3:
                    cout << (char)'#';
                    break;
            }
        }

        cout << '\n';
    }
}

int** convertImageToGBSprite(string filename, int& sizeX, int& sizeY, double contrast = 1, double rcon = 1, double gcon = 1, double bcon = 1)
{
    sf::Image image;
    image.loadFromFile("input/" + filename);

    if(sizeX > 0 && sizeY > 0)
    {
        sf::Texture tex;
        tex.loadFromImage(image);
        tex.setSmooth(true);
        sf::Sprite spr;
        spr.setTexture(tex);
        spr.setScale((double)sizeX/tex.getSize().x, (double)sizeY/tex.getSize().y);
        sf::RenderTexture rtex;

        if(!rtex.create(sizeX, sizeY))
        {
            cout << "COULDN'T CREATE RTEX TEXTURE" << endl;
        }

        rtex.clear(sf::Color::Blue);
        rtex.draw(spr);
        rtex.display();
        image = sf::Image();
        image = rtex.getTexture().copyToImage();
    }

    sizeX = image.getSize().x, sizeY = image.getSize().y;
    int** im = new int* [image.getSize().x];

    for(size_t i = 0; i != image.getSize().x; i++)
    {
        im[i] = new int[image.getSize().y];

        for(size_t j = 0; j != image.getSize().y; j++)
        {
            int col = image.getPixel(i, j).r*rcon + image.getPixel(i, j).g*gcon + image.getPixel(i, j).b*bcon;
            im[i][j] = min(contrast * col / ((double)(256*rcon + 256*gcon + 256*bcon)/4), 3.);
        }
    }

    return im;
}

void convertF(int sizeX, int sizeY)
{
    bool isCodeASM = true;
    int memoryBank = 0;
    string filename, cutname;
    cout << "Filename: ";
    cin >> filename;
    int** image = convertImageToGBSprite(filename, sizeX, sizeY);

    cutname = filename.substr(0, filename.find('.'));

    Menu::Menu converting;
    converting.addOptionSlider("Change contrast(1.0)", 1, 1, 0.05, 0, 2);
    converting.addOptionSlider("Change red weight(1.0)", 2, 1, 0.05, 0, 2);
    converting.addOptionSlider("Change green weight(1.0)", 3, 1, 0.05, 0, 2);
    converting.addOptionSlider("Change blue weight(1.0)", 4, 1, 0.05, 0, 2);
    converting.addOption("Change code language(ASM)", 5);
    converting.addOptionSlider("Change memory bank(FIXED)", 6, 0, 1, 0, 32);
    converting.addOption("Show image", 7);
    converting.addOption("Save and exit", 9);
    converting.addOption("Exit", 0);

    while(1)
    {
        system("clear");
        //
        converting.draw();

        switch(converting.update())
        {
            case 1:
                converting.addOption(string("") + "Change contrast(" + to_string(converting.getSliderValue(1)) + ")", 1);

                for(int i = 0; i != sizeX; i++)
                {
                    delete [] image[i];
                }

                delete [] image;
                image = convertImageToGBSprite(filename, sizeX, sizeY, converting.getSliderValue(1), converting.getSliderValue(2), converting.getSliderValue(3), converting.getSliderValue(4));
                break;

            case 2:
                converting.addOption(string("") + "Change red weight(" + to_string(converting.getSliderValue(2)) + ")", 2);

                for(int i = 0; i != sizeX; i++)
                {
                    delete [] image[i];
                }

                delete [] image;
                image = convertImageToGBSprite(filename, sizeX, sizeY, converting.getSliderValue(1), converting.getSliderValue(2), converting.getSliderValue(3), converting.getSliderValue(4));
                break;

            case 3:
                converting.addOption(string("") + "Change green weight(" + to_string(converting.getSliderValue(3)) + ")", 3);

                for(int i = 0; i != sizeX; i++)
                {
                    delete [] image[i];
                }

                delete [] image;
                image = convertImageToGBSprite(filename, sizeX, sizeY, converting.getSliderValue(1), converting.getSliderValue(2), converting.getSliderValue(3), converting.getSliderValue(4));
                break;

            case 4:
                converting.addOption(string("") + "Change blue weight(" + to_string(converting.getSliderValue(4)) + ")", 4);

                for(int i = 0; i != sizeX; i++)
                {
                    delete [] image[i];
                }

                delete [] image;
                image = convertImageToGBSprite(filename, sizeX, sizeY, converting.getSliderValue(1), converting.getSliderValue(2), converting.getSliderValue(3), converting.getSliderValue(4));
                break;

            case 5:
                isCodeASM = !isCodeASM;
                converting.addOption(string("Change code language(") + ((isCodeASM) ? ("ASM") : ("C")) + ")", 5);
                break;

            case 6:
                converting.addOption(string("Change memory bank(") + ((converting.getSliderValue(6)) ? (to_string((int)converting.getSliderValue(6))) : ("FIXED")) + ")", 6);
                break;

            case 7:
                drawSprite(image, sizeX, sizeY);
                std::cin.ignore(1024, '\n');
                std::cout << "Press enter to continue...";
                std::cin.get();
                break;

            case 9:
                if(!isCodeASM)saveSpriteC( cutname, image, sizeX, sizeY);
                else saveSpriteASM(cutname, image, sizeX, sizeY, converting.getSliderValue(6));

                return;

            case 0:
                return;
        }
    }
}
void convertGBSpr()
{
    int sizeX = -1, sizeY = -1;
    Menu::Menu settings;
    settings.setTitle("GB Sprites Converter - Change settings.");
    settings.addOption("Convert file", 1);
    settings.addOption(string("") + "Change width(now: " + ((sizeX > 0) ? (std::to_string(sizeX)) : ("Auto")) + ")", 2);
    settings.addOption(string("") + "Change height(now: " + ((sizeY > 0) ? (std::to_string(sizeY)) : ("Auto")) + ")", 3);
    settings.addOption("Return to main menu", 0);

    while(1)
    {
        system("clear");
        settings.draw();

        switch(settings.update())
        {
            case 1:
                convertF(sizeX, sizeY);
                break;

            case 2:
                changeVal("X", sizeX);
                settings.addOption(string("") + "Change width(now: " + ((sizeX > 0) ? (std::to_string(sizeX)) : ("Auto")) + ")", 2);
                break;

            case 3:
                changeVal("Y", sizeY);
                settings.addOption(string("") + "Change height(now: " + ((sizeY > 0) ? (std::to_string(sizeY)) : ("Auto")) + ")", 3);
                break;

            case 0:
                return;
        }
    }
}

void mainMenu()
{
    Menu::Menu main;
    main.setTitle("GB HELPER");
    main.addOption("Convert image into GB Sprites", 1);
    main.addOption("Exit", 0);

    while(1)
    {
        system("clear");
        main.draw();

        switch(main.update())
        {
            case 1:
                convertGBSpr();
                break;

            case 0:
                return;
        }
    }
}


int main(int argc, char* argv[])
{
    mainMenu();
}
