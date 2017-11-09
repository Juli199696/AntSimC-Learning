#include "ant.h"
#include "foods.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>

int ant;
int randomnumber;
int newant;           //antahl der ants Random
int happy;
int dead;
int bornant;
int antsmax;
int life;
using namespace std;
void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}
void spawnant()
{

    srand (time(NULL));
    //const int ant = 5; //antahl der Ameisen
    int ant = rand()%20+1; //antahl der Ameisen Random
    char ants[ant];
    int x[ant];
    int y[ant];
    SetMyCursor(40,24);
    {
        cout << "Ants:" << ant;
        cout  << "  ";
    }
    for (int i = 0; i < ant; i++)  //Ameisen werden hinzugefügt
    {
        ants[i] = '*';
        x[i] = rand()%77+2;     //Ameisen Spawn
        y[i] = rand()%21+2;     //
    }
}

void MoveAnt(int& altPosX, int& altPosY,int neuPosX, int neuPosY)  //Bei & wird findet eine übergabe statt
{
    int x[ant];
    int y[ant];
    SetMyCursor(altPosX, altPosY);        //altePos löschen
    cout << " ";

    SetMyCursor (neuPosX, neuPosY);        //Cursor neup plazieren...
    cout << "*";                           // ...und neu malen
    altPosX = neuPosX;
    altPosY = neuPosY;
    for (int i = 0; i < ant; i++)
            {
              randomnumber = rand() %9 +1;

                if (randomnumber == 1 && x[i] != 78 && y[i] !=22)
                    MoveAnt(x[i], y[i], x[i]+1, y[i]+1);

                if (randomnumber == 2 && x[i] != 2 && y[i] != 2)
                    MoveAnt(x[i], y[i], x[i]-1, y[i]-1);

                if (randomnumber == 3 && x[i] != 2)
                    MoveAnt(x[i], y[i], x[i]-1, y[i]);

                if (randomnumber == 4 && y[i] != 2)
                    MoveAnt(x[i], y[i], x[i], y[i]-1);

                if (randomnumber == 4 && x[i] != 78)
                    MoveAnt(x[i], y[i], x[i]+1, y[i]);

                if (randomnumber == 5 && x[i] != 78 && y[i] != 2)
                    MoveAnt(x[i], y[i], x[i]+1, y[i]-1);

                if (randomnumber == 6 && x[i] != 2 && y[i] != 22)
                    MoveAnt(x[i], y[i], x[i]-1, y[i]+1);

                if (randomnumber == 7 && y[i] != 22)
                    MoveAnt(x[i], y[i], x[i], y[i]+1);

                if (randomnumber == 8) {};

            }
}

void antdie()
{


    if (foods::leaves < 10)
    {
        dead = rand() %10 +1;

        if (dead == 1)
        {
            if (ant > 0)
            {
                life = 0;
            }
        }
    }
    if (foods::water < 10)
    {
        dead = rand() %10 +1;

        if (dead == 1)
        {
            if (ant > 0)
            {
                ant--;
            }
        }
    }
}




