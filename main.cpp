/* 06.11.2017 Ant Simulation version : 2.1 Dev  Autor: Julian Märtin

==============================================================================================================================
Allgemeine Programm Infos wie Changelog und vorhandene Funktionen.
==============================================================================================================================

New functions     | +
Changed functions | #
Deleted functions | -

Vorhandene Funktionen:
-------------------------------------------------------------------------------------------------------------------------------
Ameisensterben          : Ameisen können sterben wenn Sie zu wenig leaves/ water haben.
BewegeAmeise            : Ameisen werden zufällig bewegt.
Lebensmittel            : Ist für den verbrauch und das hinzufügen von Lebensmitteln wie leaves und water zuständig.
Main                    : Startet das Grundprogramm.
Nachrichten             : News System informiert über aktuelle geschehnisse.
SetMyCurser             : Ist für das Setzten des Cursers in der Console verantwortlich und kann jederzeit verändert werden.
Simulation              : Lässt die Zeit laufen und ist mit für die Bewegung der Ameisen zuständig.
Spielfeld               : Baut / setzt den Spielfeld Rand und Objekte.
Start                   : Ist für das Hauptmenu zuständig.
Highscore               : Es ist nun möglich den Highscore vom letzten Spiel in einer Text Datei zu speichern und nachträglich wieder aufzurufen.

Changelog 06.11.2017:
+Updater check version of AntSim.

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

float version = 2.3;
float updater = 1.2;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
//Initialize every int var for the programm. I know this can be done much better. Feel free to correct me by making an issue on Github :)
int water;
int leaves;
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

int news = 1;
int checkupdates = 0;
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
    if (leaves < 10)
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
    if (water < 10)
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
        cout << "water:" << water << "%";
        cout  << "  ";
    }
    /* Ich hab keine Ahnung mehr wofür ich die kacke gebraucht habe.. Meh
    int x[anz];
    int y[anz];
    char ameisen[anz];
    SetMyCursor(15,24);
    */

    {
        cout << "leaves:" << leaves << "%";
        cout  << "  ";
    }
    verbrauch = rand() %55 +1;
    if (verbrauch == 1)
    {
        if (leaves > 0)
        {
            leaves--;
        }
    }
    if (verbrauch == 2)
    {
        if (water > 0)
        {
            water--;
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
    if (leaves < 75)
    {
        happy = 3;
    }
    if (leaves < 50)
    {
        happy = 2;
    }
    if (leaves < 25)
    {
        happy = 1;
    }
    if (leaves > 15)
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
    if (leaves < 10)
    {
        SetMyCursor(1,27);
        cout << "Es fehlt an leaves! ";
        if (leaves > 10)
            cout << "                                                    ";
    }
    if (water < 10)
    {
        SetMyCursor(1,28);
        cout << "Es fehlt an water! ";
        if (water > 10)
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
//Commands for shopping
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
void shop()
{
    int leavesinstock = rand()%(25-1 + 1) + 1;

    int waterinstock = rand()%(25-1+ 1) + 1;

    int glassesinstock = rand()%(3-1 + 1) + 1;

    int itemid = 0;
    system("cls");
    int shopping = 1;
    while (shopping == 1)
    {
        if (itemid == 0)
        {
            itemid = rand()%(3-1 + 1) + 1;
        }
        SetMyCursor(0,1);

        cout << "Welcome to the ant shop" << endl << endl << "Here you can buy some good stuff for your ant colony" << endl;
        cout << "You have " << leaves << " leaves, " << water << " water and " << glasses << " glasses" << endl;
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
            cout << "Glasses (Key 7) " << glassesinstock << " x";

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
            leaves = buyMaterial(leaves, leavesinstock, "Leaves");
        }

        if(GetKeyState('6') & 0x8000)
        {
            SetMyCursor(1,12);
            water = buyMaterial(water, waterinstock, "Water");
        }

        if(GetKeyState('7') & 0x8000)
        {
            SetMyCursor(1,12);
            glasses = buyMaterial(glasses, glassesinstock, "Lupe");
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
//Menu usage with keys
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
                cout << "Your colony have " << anz <<" ants." << endl << endl << "You got " << leaves << " food." << endl << "You got " << water << " water." << endl;
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
        ende = 1;

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
                Sleep(100);
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

                    /*if (leaves > 85)
                    {
                        bornant = rand() %200;

                        if (bornant == 1)
                        {
                            anz++;
                            newant =1;
                            bornant =0;
                        }

                    }*/
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
                    Sleep(2000);
                    system("cls");
                    cout << "GAME OVER" << endl << "You archived " << zeit << " days." << endl << "You got " << leaves << " food and " << water << " water." << endl << "Your farm reached " << anz << " ants.";
                    Sleep(5000);
                    ofstream score;
                    score.open ("score.txt");
                    score << "You archived " << zeit << " days." << endl << "You got " << leaves << " food and " << water << " water." << endl << "Your farm reached " << anz << " ants.";
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

// Check for News
void NewsCheck()
{
    remove( "news.txt" );
    system("cls");
    SetMyCursor(0,27);
    cout<<"\nCheck for News!\n\n";
    Sleep(1000);

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url= "https://github.com/Juli199696/AntSimCPlusPlusLearning/raw/dev/news.txt";
    char outfilename[FILENAME_MAX] = "./news.txt";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        /* Setup the https:// verification options - note we do this on all requests as there may
           be a redirect from http to https and we still want to verify */
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

    }
}

void UpdateCheck()
{

    ofstream cfgconfig;
    cfgconfig.open ("version.cfg");
    cfgconfig << "Version = " << version;
    cfgconfig.close();

    ofstream patcherconfig;
    patcherconfig.open ("patcher.cfg");
    patcherconfig << "Updater = " << updater;
    patcherconfig.close();

    string patcherold;
    string versionold;
    ifstream version ("version.cfg");
    if (version.is_open())
    {
        while ( getline (version,versionold) )
        {
        }
        version.close();
    }
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url= "https://github.com/Juli199696/AntSimCPlusPlusLearning/raw/dev/version.cfg";
    char outfilename[FILENAME_MAX] = "./version.cfg";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        /* Setup the https:// verification options - note we do this on all requests as there may
           be a redirect from http to https and we still want to verify */
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

    }
    ifstream patcher ("patcher.cfg");
    if (patcher.is_open())
    {
        while ( getline (patcher,patcherold) )
        {
        }
        patcher.close();
    }
    CURL *dpatcher;
    FILE *dfp;
    CURLcode dres;
    char *durl= "https://github.com/Juli199696/AntSimCPlusPlusLearning/raw/dev/patcher.cfg";
    char doutfilename[FILENAME_MAX] = "./patcher.cfg";
    dpatcher = curl_easy_init();
    if (dpatcher)
    {
        dfp = fopen(doutfilename,"wb");
        curl_easy_setopt(dpatcher, CURLOPT_URL, durl);
        /* Setup the https:// verification options - note we do this on all requests as there may
           be a redirect from http to https and we still want to verify */
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(dpatcher, CURLOPT_CAINFO, "./ca-bundle.crt");
        curl_easy_setopt(dpatcher, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(dpatcher, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(dpatcher, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(dpatcher, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(dpatcher, CURLOPT_WRITEDATA, dfp);
        dres = curl_easy_perform(dpatcher);
        curl_easy_cleanup(dpatcher);
        fclose(dfp);

    }

    string versionneu;
    string patchernew;
    ifstream versionabfrage ("version.cfg");
    if (versionabfrage.is_open())
    {
        while ( getline (versionabfrage,versionneu) )
        {
        }
        versionabfrage.close();
    }
    if (versionold == versionneu)
    {
        cout << "You already got the newest version of AntSim :) " << versionold <<endl;
        Sleep(2000);

    }
    else
    {
        ofstream cfgconfig;
        cfgconfig.open ("version.cfg");
        cfgconfig << versionold;
        cfgconfig.close();
        cout << "Current version: " << versionold << endl;
        cout << "New update!" << endl;
        cout << "New version: " << versionneu << endl;
        Sleep(2000);
    }

    ifstream patchercheck ("patcher.cfg");
    if (patchercheck.is_open())
    {
        while ( getline (patchercheck,patchernew) )
        {
        }
        patchercheck.close();
    }
    if (patcherold == patchernew)
    {
        cout << "Updater v. " << patcherold;
        Sleep(2000);

    }
    else
    {
        ofstream patcherconfig;
        patcherconfig.open ("patcher.cfg");
        patcherconfig << patcherold;
        patcherconfig.close();
        cout << "Updater v. " << patcherold << endl;
        cout << "New updater v. " << patchernew << endl;
        cout << "Updating!" << endl;
        Sleep(3000);
        CURL *curl;
        cout << "1%"<< endl;
        Sleep(500);
        FILE *fp;
        cout << "12%"<< endl;
        Sleep(500);
        CURLcode res;
        cout << "24%"<< endl;
        Sleep(500);
        char *url= "https://github.com/Juli199696/AntSimCPlusPlusLearning/raw/dev/Updater/Updater/bin/Release/Updater.exe";
        char outfilename[FILENAME_MAX] = "./Updater.exe";
        cout << "34%"<< endl;
        Sleep(500);
        curl = curl_easy_init();
        if (curl)
        {
            fp = fopen(outfilename,"wb");
            cout << "45%"<< endl;
            Sleep(500);
            curl_easy_setopt(curl, CURLOPT_URL, url);
            /* Setup the https:// verification options - note we do this on all requests as there may
               be a redirect from http to https and we still want to verify */
            //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
            curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
            cout << "69%"<< endl;
            Sleep(500);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            cout << "78%"<< endl;
            Sleep(500);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            cout << "90%"<< endl;
            Sleep(500);
            fclose(fp);
            cout << "Update complete! :)"<< endl;
            Sleep(3000);

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
    if (checkupdates == 0)
    {
        if (system("ping -n 1 gaming-ftw.de"))
        {
            system("cls");
            SetMyCursor(0,26);
            cout<<"\nCan't check for updates!\n\n";
            checkupdates = 1;

        }
        else
        {
            system("cls");
            SetMyCursor(0,26);
            cout<<"\nCheck for Update!\n\n";
            UpdateCheck();
            NewsCheck();


        }
    }


    checkupdates = 1;
    system("cls");
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

    SetMyCursor(0,26);      //Text für untere Leiste
    {
        cout << "AntSimC++ Dev "<< version << endl ;
    }
    SetMyCursor(0,27);

    string newsinfo;
    ifstream news ("news.txt");
    if (news.is_open())
    {
        while ( getline (news,newsinfo) )
        {
            cout << newsinfo << '\n';
        }
        news.close();
    }
    int zahl;
    SetMyCursor(1,10);
    cin >> zahl;
    if (zahl == 1)          //Bedingung für ausführung der Schleife 1, startet die Simulation
    {
        water = 50;
        leaves = 50;
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
        string points;
        ifstream score ("score.txt");
        if (score.is_open())
        {
            while ( getline (score,points) )
            {
                cout << points << '\n';
            }
            score.close();
            getch();
            system("cls");
            start();
        }
        else cout << "No highscore yet!";
        Sleep(3000);
        start();

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
