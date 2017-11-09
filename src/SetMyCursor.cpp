#include "SetMyCursor.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>


    void SetMyCursor::SetMyCursorFunction(short x, short y)
{
    HANDLE console;                                         //Dient zur vergrößerung des Consolen Fensters
    COORD screenBufferSize;
    SMALL_RECT windowSize;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    screenBufferSize.X = 81;
    screenBufferSize.Y = 29;
    SetConsoleScreenBufferSize(console, screenBufferSize);
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = 80;
    windowSize.Bottom = 30;
    SetConsoleWindowInfo(console, true, &windowSize);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}

