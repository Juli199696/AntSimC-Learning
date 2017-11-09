#include "simulation.h"
#include "ant.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <days.h>
#include <foods.h>
#include <main.h>
using namespace std;
int currentants;
int gameover = 0;






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
void simulation()
{

    while (gameover == 0) //Solange das Spiel nicht beendet ist, führe das aus.
    {


            /*
            ==============================================================================================================================
            Spielende
            ==============================================================================================================================
            */

            if  (simulation::currentants == 0)
            {
                SetMyCursor(0,5);
                {
                    Sleep(2000);
                    system("cls");
                    cout << "GAME OVER" << endl << "You archived " << days::daystime << " days." << endl << "You got " << simulation::currentleaves << " food and " << simulation::currentwater << " water." << endl << "Your farm reached " << Ant::antsmax << " ants.";
                    Sleep(5000);
                    ofstream score;
                    score.open ("score.txt");
                    score << "You archived " << days::daystime << " days." << endl << "You got " << simulation::currentleaves << " food and " << simulation::currentwater << " water." << endl << "Your farm reached " << Ant::antsmax << " ants.";
                    score.close();
                    system("cls");
                    gameover = 1;

                }

            }
            if (gameover == 1)
            {
                main();

            }
        }
    }

