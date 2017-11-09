#include "messages.h"
#include "foods.h"
#include "days.h"
#include "ant.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <simulation.h>
#include <weather.h>
using namespace std;


void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


void Nachrichten()
{
    if (simulation::currentleaves < 75)
    {
        Ant::happy = 3;
    }
    if (simulation::currentleaves < 50)
    {
        Ant::happy = 2;
    }
    if (simulation::currentleaves < 25)
    {
        Ant::happy = 1;
    }
    if (simulation::currentleaves > 15)
    {
        Ant::happy = 0;
    }

    SetMyCursor(1,25);
    {
        cout << "1 Ants 2 Shop 3 Environment 4 Ende";
    }
    SetMyCursor(1,26);
    {
        cout << "Nachrichten: ";
    }
    if (simulation::currentleaves < 10)
    {
        SetMyCursor(1,27);
        cout << "Es fehlt an leaves! ";
        if (simulation::currentleaves > 10)
            cout << "                                                    ";
    }
    if (simulation::currentwater < 10)
    {
        SetMyCursor(1,28);
        cout << "Es fehlt an water! ";
        if (simulation::currentwater > 10)
            cout << "                                                    ";
    }
    if (weather::storm == 1)
    {
        SetMyCursor(1,29);
        cout << "Ein Sturm wuetet in deiner Kolonie.";

    }
    if (weather::storm == 0)
    {
        SetMyCursor(1,29);
        cout << "                                                    ";
    }
}
