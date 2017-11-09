#include "days.h"
#include "ant.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <simulation.h>

using namespace std;

int daystime;



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
void days()
{

    while (simulation::gameover == 0) //Solange das Spiel nicht beendet ist führe das aus.
    {
        for ( daystime; daystime++;)
        {
            SetMyCursor(28,24);
            {
                cout << "Days:" << daystime;
                cout  << "  ";
            }

        }

    }
}

days::days()
{
    //ctor
}

days::~days()
{
    //dtor
}
