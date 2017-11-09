#include "hotkeys.h"
#include "days.h"
#include "ant.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <simulation.h>
#include "environment.h"
#include <shop.h>
using namespace std;
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}



void hotkeys ()
{
    if(GetKeyState('1') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {
        simulation::gamerunning = 0;
        while (simulation::gamerunning == 0)
        {
            system("cls");
            SetMyCursor(0,1);
            {
                cout << "Ants Info" << endl << endl << "Here you can see how your ants are feeling and what they need!" << endl << "Please check here regulary for happy ants." << endl;
                cout << "Your colony have " << simulation::currentants <<" ants." << endl << endl << "You got " << simulation::currentleaves << " food." << endl << "You got " << simulation::currentwater << " water." << endl;
                if (Ant::happy == 3)
                {
                    cout << "Your ants are very happy." << endl << "Good job!";
                }
                if (Ant::happy == 2)
                {
                    cout << "Everything is okay." << endl << "No need to worry.";
                }
                if (Ant::happy == 1)
                {
                    cout << "Your ants need some love." << endl << "Watch your food and water.";
                }
                if (Ant::happy == 0)
                {
                    cout << "Your ants are in danger :(" << endl << "You need to do something now!";
                }
            }
            SetMyCursor(1,20);
            {
                cout << "Press 0 to go back";
            }
            getch();
            if(GetKeyState('0') & 0x8000/*check if high-order bit is set (1 << 15)*/)
            {
                simulation::gamerunning = 1;
                system("cls");

            }

        }
    }

    if(GetKeyState('2') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {

        simulation::gamerunning = 2;
        while (simulation::gamerunning == 2)
        {
            shop();
        }
    }
    if(GetKeyState('4') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {
        simulation::gameover = 1;

    }
}
hotkeys::hotkeys()
{
    //ctor
}

hotkeys::~hotkeys()
{
    //dtor
}
