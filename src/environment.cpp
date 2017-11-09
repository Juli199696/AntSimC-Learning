#include "environment.h"
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

void environment()
{
        SetMyCursor(1,23);      // Setzt die Untermenü Linie
        for (int i=0; i<79; i++)
        {
            cout << (char)205 ;
        }
        SetMyCursor(1,0);       // Setzt die obere Spielfeldlinie
        for (int i=0; i<79; i++)
        {
            cout << (char)205 ;
        }
        for (int i=0; i<23; i++) // Setzt die linke Spielfeldlinie
        {
            SetMyCursor(0,i);
            cout << (char)186 ;

            SetMyCursor(79,i);  // Setzt die rechte Spielfeldlinie
            cout << (char)186 ;
        }
        SetMyCursor(0,0);      //Setzt die linke obere Ecke ╔
        cout << (char)201 ;
        SetMyCursor(79,0);      //Setzt obere rechte Ecke   ╗
        cout << (char)187 ;
        SetMyCursor(0,23);      //Setzt untere linke Ecke ╚
        cout << (char)200 ;
        SetMyCursor(79,23);      //Setzt untere rechte Ecke ╝
        cout << (char)188 ;
    }
