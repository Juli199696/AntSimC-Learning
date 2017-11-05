/* 02.04.2014 Ant Simulation version : 0.5 Dev  Autor: Julian Märtin

==============================================================================================================================
Allgemeine Programm Infos wie Changelog und vorhandene Funktionen.
==============================================================================================================================

New functions     | +
Changed functions | #
Deleted functions | -

Vorhandene Funktionen:
-------------------------------------------------------------------------------------------------------------------------------
Ameisensterben          : Ameisen können sterben wenn Sie zu wenig Nahrung/ Wasser haben.
BewegeAmeise            : Ameisen werden zufällig bewegt.
Lebensmittel            : Ist für den verbrauch und das hinzufügen von Lebensmitteln wie Nahrung und Wasser zuständig.
Main                    : Startet das Grundprogramm.
Nachrichten             : News System informiert über aktuelle geschehnisse.
SetMyCurser             : Ist für das Setzten des Cursers in der Console verantwortlich und kann jederzeit verändert werden.
Simulation              : Lässt die Zeit laufen und ist mit für die Bewegung der Ameisen zuständig.
Spielfeld               : Baut / setzt den Spielfeld Rand und Objekte.
Start                   : Ist für das Hauptmenu zuständig.
Highscore               : Es ist nun möglich den Highscore vom letzten Spiel in einer Text Datei zu speichern und nachträglich wieder aufzurufen.

Changelog 15.10.2017:

*Inital Commit on Github.

+ Bugfixes for crashs and the ability to restart the simulation.
+ Ant Shop (You can now buy Food and Water for your ants to stay alive and rise your highscore!
+ Money money money! I have implemented a simple economy system but its not ready to use yet. You can use that money to buy new stuff from the shop or expand your current ant colony.
+ You can have highscores saved in text file!
+ I have added a game.cfg file which does not contain any usefull commands at the moment but will be handy to have later on.
+ UPDATER READY TO USE!!!

# Changes to simulation itself (Add shop, add new variables for shop).
# Highscore now can be watched every round without the game to be restarted.
# General code cleanup.
# TEST FOR GITHUB MERGE.

- New Born Ants, for now i have remove the feature to create new ants when you got enough of food and water. This will be added later on again!
- Removed some unused variables and old code.
- Removed rlutil.h as it is not needed anymore.
==============================================================================================================================*/
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
//#include "global.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
//Initialize every int var for the programm. I know this can be done much better. Feel free to correct me by making an issue on Github :)
int wasser;
int nahrung;
int glasses;
int anz;
int newant;           //Anzahl der Ameisen Random
int happy;
int tot;
int bornant;
int regen;
int sonne;
int sturm;
int blaetter;
int angreifer;
int ende;
int ameisenmax;
int gamerunning;
int geld;

using namespace std;

/*
==============================================================================================================================
Setzt die Position des Cursers um Zeichen zu setzen.
==============================================================================================================================
*/
void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}
/*
==============================================================================================================================
Spielfeld wird erstellt.
==============================================================================================================================
*/
void spielfeld()
{
    SetMyCursor(1,23);      // Setzt die Untermenü Linie
    {
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
}
/*
==============================================================================================================================
Ameisen Position wird übergeben und neu "geschrieben".
==============================================================================================================================
*/
void BewegeAmeise(int& altPosX, int& altPosY,int neuPosX, int neuPosY)   //Bei & wird findet eine übergabe statt
{

    SetMyCursor (altPosX, altPosY);        //altePos löschen
    cout << " ";
    SetMyCursor (neuPosX, neuPosY);        //Cursor neu plazieren...
    cout << "*";                      // ...und neu schreiben
    altPosX = neuPosX;
    altPosY = neuPosY;
}
/*
==============================================================================================================================
Ameisen sterben
==============================================================================================================================
*/
void Ameisensterben()
{
    if (nahrung < 10)
    {
        tot = rand() %10 +1;

        if (tot == 1)
        {
            if (anz > 0)
            {
                anz--;
            }
        }
    }
    if (wasser < 10)
    {
        tot = rand() %10 +1;

        if (tot == 1)
        {
            if (anz > 0)
            {
                anz--;
            }
        }
    }
}
/*
==============================================================================================================================
Lebensmittel verbrauch
==============================================================================================================================
*/
void Lebensmittel()
{
    int verbrauch ;
    Ameisensterben();
    SetMyCursor(2,24);
    {
        cout << "Wasser:" << wasser << "%";
        cout  << "  ";
    }
    /* Ich hab keine Ahnung mehr wofür ich die kacke gebraucht habe.. Meh
    int x[anz];
    int y[anz];
    char ameisen[anz];
    SetMyCursor(15,24);
    */

    {
        cout << "Nahrung:" << nahrung << "%";
        cout  << "  ";
    }
    verbrauch = rand() %55 +1;
    if (verbrauch == 1)
    {
        if (nahrung > 0)
        {
            nahrung--;
        }
    }
    if (verbrauch == 2)
    {
        if (wasser > 0)
        {
            wasser--;
        }
    }
}
/*
==============================================================================================================================
Nachrichten / Ameisen Informationen
==============================================================================================================================
*/
void Nachrichten()
{
    if (nahrung < 75)
    {
        happy = 3;
    }
    if (nahrung < 50)
    {
        happy = 2;
    }
    if (nahrung < 25)
    {
        happy = 1;
    }
    if (nahrung > 15)
    {
        happy = 0;
    }

    SetMyCursor(1,25);
    {
        cout << "1 Ants 2 Shop 3 Environment 4 Ende";
    }
    SetMyCursor(1,26);
    {
        cout << "Nachrichten: ";
    }
    if (nahrung < 10)
    {
        SetMyCursor(1,27);
        cout << "Es fehlt an Nahrung! ";
        if (nahrung > 10)
            cout << "                                                    ";
    }
    if (wasser < 10)
    {
        SetMyCursor(1,28);
        cout << "Es fehlt an Wasser! ";
        if (wasser > 10)
            cout << "                                                    ";
    }
    if (sturm == 1)
    {
        SetMyCursor(1,29);
        cout << "Ein Sturm wuetet in deiner Kolonie.";

    }
    if (sturm == 0)
    {
        SetMyCursor(1,29);
        cout << "                                                    ";
    }
}
//Befehle
void shop()
{
    string yesorno;
    int amounttobuy = 0;

    int leavesinstock = rand()%(25-1 + 1) + 1;

    int waterinstock = rand()%(25-1+ 1) + 1;

    int glassesinstock = rand()%(3-1 + 1) + 1;

    int sales = rand()%(3-1 + 1) + 1;
    system("cls");
    int shopping = 1;
    int checkout = 10;
    while (shopping == 1)
    {

        SetMyCursor(0,1);
        {
            cout << "Welcome to the ant shop" << endl << endl << "Here you can buy some good stuff for your ant colony" << endl << endl << "Todays sales are:" << endl;;


            if (sales == 1)
            {
                cout << "Leaves (5) " << leavesinstock << " x";

            }
            if (sales == 2)
            {
                cout << "Water (6) " << leavesinstock << " x";

            }
            if (sales == 3)
            {
                cout << "Glasses (7) " << leavesinstock << " x";

            }

            SetMyCursor(1,18);
            {
                cout << "Buy stuff with the shown key.";
            }
            SetMyCursor(1,20);
            {
                cout << "Press 0 to go back";
            }

            if(GetKeyState('5') & 0x8000/*check if high-order bit is set (1 << 15)*/)
            {
                if (geld > 0)
                {
                    SetMyCursor(1,12);
                    checkout = 0;
                    {
                        while (checkout == 0)
                        {
                            cout << "How much you wanna buy?" << endl;

                            cin >> amounttobuy;

                            if (amounttobuy > leavesinstock)
                            {
                                cout << "You cant buy more than " << leavesinstock << "!";
                                getch();
                                checkout = 10;
                            }
                            if (amounttobuy <= 0)
                            {
                                cout << "You cant buy less than one!";
                                getch();
                                checkout = 10;
                            }
                            else
                            {
                                if (sales == 1)
                                {


                                    cout << "Are you sure you want to buy " << amounttobuy << " of leaves?" << endl;
                                }
                                cin >> yesorno;
                                if (yesorno == "Y" || yesorno == "y" || yesorno == "yes" || yesorno == "Yes")
                                {
                                    nahrung = nahrung + amounttobuy;
                                    cout << "You bought " << amounttobuy << " of " << sales << endl;
                                    checkout = 10;

                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "You dont got enough money!";
                }



            }
            if(GetKeyState('6') & 0x8000/*check if high-order bit is set (1 << 15)*/)
            {
                if (geld > 0)
                {
                    SetMyCursor(1,12);
                    checkout = 1;
                    {
                        while (checkout == 1)
                        {
                            cout << "How much you wanna buy?" << endl;

                            cin >> amounttobuy;

                            if (amounttobuy > waterinstock)
                            {
                                cout << "You cant buy more than " << waterinstock << "!";
                                getch();
                                checkout = 10;
                            }
                            if (amounttobuy <= 0)
                            {
                                cout << "You cant buy less than one!";
                                getch();
                                checkout = 10;
                            }
                            else
                            {
                                if (sales == 2)
                                {


                                    cout << "Are you sure you want to buy " << amounttobuy << " of water?" << endl;
                                }
                                cin >> yesorno;
                                if (yesorno == "Y" || yesorno == "y" || yesorno == "yes" || yesorno == "Yes")
                                {
                                    wasser = wasser + amounttobuy;
                                    cout << "You bought " << amounttobuy << " of " << sales << endl;
                                    checkout = 10;

                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "You dont got enough money!";
                }



            }
            if(GetKeyState('7') & 0x8000/*check if high-order bit is set (1 << 15)*/)
            {
                if (geld > 0)
                {
                    SetMyCursor(1,12);
                    checkout = 2;
                    {
                        while (checkout == 2)
                        {
                            cout << "How much you wanna buy?" << endl;

                            cin >> amounttobuy;

                            if (amounttobuy > glassesinstock)
                            {
                                cout << "You cant buy more than " << glassesinstock << "!";
                                getch();
                                checkout = 10;
                            }
                            if (amounttobuy <= 0)
                            {
                                cout << "You cant buy less than one!";
                                getch();
                                checkout = 10;
                            }
                            else
                            {
                                if (sales == 3)
                                {


                                    cout << "Are you sure you want to buy " << amounttobuy << " of glasses?" << endl;
                                }
                                cin >> yesorno;
                                if (yesorno == "Y" || yesorno == "y" || yesorno == "yes" || yesorno == "Yes")
                                {
                                    glasses = glasses + amounttobuy;
                                    cout << "You bought " << amounttobuy << " of " << sales << endl;
                                    checkout = 10;

                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "You dont got enough money!";
                }
            }
        }



        getch();
        if(GetKeyState('0') & 0x8000/*check if high-order bit is set (1 << 15)*/)
        {
            shopping = 0;
            gamerunning = 1;
            system("cls");
            spielfeld();
        }
    }
}
void hotkeys ()
{
    if(GetKeyState('1') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {
        gamerunning = 0;
        while (gamerunning == 0)
        {
            system("cls");
            SetMyCursor(0,1);
            {
                cout << "Ants Info" << endl << endl << "Here you can see how your ants are feeling and what they need!" << endl << "Please check here regulary for happy ants." << endl;
                cout << "Your colony have " << anz <<" ants." << endl << endl << "You got " << nahrung << " food." << endl << "You got " << wasser << " water." << endl;
                if (happy == 3)
                {
                    cout << "Your ants are very happy." << endl << "Good job!";
                }
                if (happy == 2)
                {
                    cout << "Everything is okay." << endl << "No need to worry.";
                }
                if (happy == 1)
                {
                    cout << "Your ants need some love." << endl << "Watch your food and water.";
                }
                if (happy == 0)
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
                gamerunning = 1;
                system("cls");
                spielfeld();
            }

        }
    }

    if(GetKeyState('2') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {

        gamerunning = 2;
        while (gamerunning == 2)
        {
            shop();
        }
    }
    if(GetKeyState('4') & 0x8000/*check if high-order bit is set (1 << 15)*/)
    {
        exit(0);

    }
}
/*
==============================================================================================================================
Ameisen bewegung und grundfunktionen
==============================================================================================================================
*/
void simulation()
{
    srand (time(NULL));
    int x[anz];
    int y[anz];
    int i =0;
    char ameisen[anz];
    //const int anz = 5; //Anzahl der Ameisen

    for (i = 0; i < anz; i++)  //Ameisen werden hinzugefügt
    {
        ameisen[i] = '*';
        x[i] = rand()%77+2;     //Ameisen Spawn
        y[i] = rand()%21+2;
    }
    while (ende == 0) //Solange das Spiel nicht beendet ist, führe das aus.
    {

        for ( int zeit = 1; zeit++;)
        {
            hotkeys ();
            Lebensmittel();
            Nachrichten();
            SetMyCursor(40,24);
            {
                cout << "Ameisen:" << anz;
                cout  << "  ";
            }
            int zufallszahl;
            SetMyCursor(29,24);
            {
                cout << "Tage:" << zeit;
                _sleep(100);
                cout  << "  ";
            }
            newant = 0;
            if (newant == 0)
            {
            for (int i = 0; i < anz; i++)
            {
                zufallszahl = rand() %9 +1; //Hier  wird die Ameise zufällig bewegt.

                if (zufallszahl == 1 && x[i] != 78 && y[i] !=22)
                    BewegeAmeise(x[i], y[i], x[i]+1, y[i]+1);

                if (zufallszahl == 2 && x[i] != 2 && y[i] != 2)
                    BewegeAmeise(x[i], y[i], x[i]-1, y[i]-1);

                if (zufallszahl == 3 && x[i] != 2)
                    BewegeAmeise(x[i], y[i], x[i]-1, y[i]);

                if (zufallszahl == 4 && y[i] != 2)
                    BewegeAmeise(x[i], y[i], x[i], y[i]-1);

                if (zufallszahl == 5 && x[i] != 78)
                    BewegeAmeise(x[i], y[i], x[i]+1, y[i]);

                if (zufallszahl == 6 && x[i] != 78 && y[i] != 2)
                    BewegeAmeise(x[i], y[i], x[i]+1, y[i]-1);

                if (zufallszahl == 7 && x[i] != 2 && y[i] != 22)
                    BewegeAmeise(x[i], y[i], x[i]-1, y[i]+1);

                if (zufallszahl == 8 && y[i] != 22)
                    BewegeAmeise(x[i], y[i], x[i], y[i]+1);

                if (zufallszahl == 9) {};

                if (nahrung > 85)
                {
                    bornant = rand() %200;

                    if (bornant == 1)
                    {
                        anz++;
                        newant =1;
                        bornant =0;
                    }

                }
            }
            }

            /*
            ==============================================================================================================================
            Spielende
            ==============================================================================================================================
            */
            if  (anz == 0)
            {
                SetMyCursor(0,5);
                {
                    _sleep(2000);
                    system("cls");
                    cout << "GAME OVER" << endl << "You archived " << zeit << " days." << endl << "You got " << nahrung << " food and " << wasser << " water." << endl << "Your farm reached " << anz << " ants.";
                    _sleep(5000);
                    ofstream score;
                    score.open ("score.txt");
                    score << "You archived " << zeit << " days." << endl << "You got " << nahrung << " food and " << wasser << " water." << endl << "Your farm reached " << anz << " ants.";
                    score.close();
                    system("cls");
                    ende = 1;

                }

            }
            if (ende == 1)
            {
                int (start());
                start();
            }
        }
    }
}

/*
==============================================================================================================================
Startprogramm zum ausführen der Simulation.
==============================================================================================================================
*/
void start()
{
    ofstream cfgconfig;
    cfgconfig.open ("game.cfg");
    cfgconfig << "test";
    cfgconfig.close();

    cout << " ____________________________________________________ " << endl;
    cout << "|Willkommen zur Ameisen Simulation!                  |" << endl;
    cout << "|Bitte waehle ein nummer.                            |" << endl;
    cout << "|____________________________________________________|" << endl;           //Start Menü
    cout << "|                                                    |" << endl;
    cout << "|1. Start                                            |" << endl;
    cout << "|2. Ende                                             |" << endl;
    cout << "|3. Highscore                                        |" << endl;
	cout << "|4. Check for updates (DEV BRANCH)                   |" << endl;
    cout << "|____________________________________________________|" << endl;

    SetMyCursor(1,26);      //Text für untere Leiste
    {
        cout << "AntSimC++ Dev 1.3" << endl ;
        cout << "AntSimC++ Dev 1.3";
    }
    int zahl;
    SetMyCursor(1,10);
    cin >> zahl;
    if (zahl == 1)          //Bedingung für ausführung der Schleife 1, startet die Simulation
    {
        wasser = 50;
        nahrung = 50;
        glasses = 0;
        anz = rand()%50+3;
        newant = 0;            //Anzahl der Ameisen Random
        happy = 1;
        tot = 0;
        bornant = 0;
        regen = 0;
        sonne = 0;
        sturm = 0;
        blaetter = 0;
        angreifer = 0;
        ende = 0;
        ameisenmax = 0;
        gamerunning = 1;
        geld = 50;

        system("cls");
        spielfeld();
        simulation();
    }
    if (zahl == 2)          //Bedingung für ausführung der Schleife 2, beendet das Programm
    {
        exit(0);
    }

    if (zahl == 3)          //Highscore
    {
        system("cls");
        string line;
        ifstream score ("score.txt");
        if (score.is_open())
        {
            while ( getline (score,line) )
            {
                cout << line << '\n';
            }
            score.close();
            getch();
            system("cls");
            start();
        }
        else cout << "Unable to open file";
    }
    if (zahl == 4)          //Updates the program.
        system("start Updater.exe" ) ;
        exit(0);
    }


/*
==============================================================================================================================
Das Hauptprogramm wird inizialisiert und führt die unter Programme aus.
==============================================================================================================================
*/
int main()
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

    start();                //Führt das unterprogramm start aus
    return 0;
}
