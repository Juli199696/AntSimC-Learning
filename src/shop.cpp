#include "shop.h"
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
#include <ant.h>
#include <simulation.h>
#include <foods.h>
#include <environment.h>
#include <SetMyCursor.h>
using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int buyMaterial(int currentAmount, int inStock, string materialName)
{
    int amounttobuy = 0;
    int newAmount = currentAmount;
    int checkout = 0;
    string yesorno;

    while (checkout == 0)
    {
        cout << "How much of " << materialName <<" you wanna buy?" << endl;
        cin >> amounttobuy;

        if (amounttobuy > inStock or amounttobuy <= 0)
        {
            cout << "You cant buy more than " << inStock << " or less than 0!";
            system("cls");
            checkout = 1;
            break;
        }
        else
        {
            cout << "Are you sure you want to buy " << amounttobuy << " of " << materialName << endl;
        }
        cin >> yesorno;
        if (yesorno == "Y" || yesorno == "y" || yesorno == "yes" || yesorno == "Yes")
        {
            newAmount = currentAmount + amounttobuy;
            cout << "You bought " << amounttobuy << " of " << materialName << endl;
            checkout = 1;
        }
    }

    return newAmount;
}
//Shop instance

void shop::shoplist()
{
    int leavesinstock = rand()%(25-1 + 1) + 1;

    int waterinstock = rand()%(25-1+ 1) + 1;

    int googlesinstock = rand()%(3-1 + 1) + 1;

    int itemid = 0;
    system("cls");
    int shopping = 1;
    while (shopping == 1)
    {
        if (itemid == 0)
        {
            itemid = rand()%(3-1 + 1) + 1;
        }
        SetMyCursorFunction(0,1);

        cout << "Welcome to the ant shop" << endl << endl << "Here you can buy some good stuff for your ant colony" << endl;
        cout << "You have " << simulation::currentleaves << " leaves, " << simulation::currentwater << " water and " << simulation::currentgoogles << " googles" << endl;
        cout << endl << "Todays sales are:" << endl;
        if (itemid == 1)
        {
            cout << "Leaves (Key 5) " << leavesinstock << " x";

        }
        if (itemid == 2)
        {
            cout << "Water (Key 6) " << waterinstock << " x";

        }
        if (itemid == 3)
        {
            cout << "Glasses (Key 7) " << googlesinstock << " x";

        }

        SetMyCursor(1,18);
        {
            cout << "Buy stuff with the shown key.";
        }
        SetMyCursor(1,20);
        {
            cout << "Press 0 to go back";
        }

        if(GetKeyState('5') & 0x8000)
        {
            SetMyCursor(1,12);
            foods::leaves = buyMaterial(foods::leaves, leavesinstock, "Leaves");
        }

        if(GetKeyState('6') & 0x8000)
        {
            SetMyCursor(1,12);
            foods::water = buyMaterial(foods::water, waterinstock, "Water");
        }

        if(GetKeyState('7') & 0x8000)
        {
            SetMyCursor(1,12);
            foods::googles = buyMaterial(foods::googles, googlesinstock, "Lupe");
        }
        getch();

        if(GetKeyState('0') & 0x8000/*check if high-order bit is set (1 << 15)*/)
        {
            shopping = 0;
            simulation::gamerunning = 1;
            system("cls");
            environment();
        }

    }


}
