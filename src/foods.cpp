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
