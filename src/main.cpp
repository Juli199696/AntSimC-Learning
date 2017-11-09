/* 06.11.2017 Ant Simulation version : 2.1 Dev  Autor: Julian Märtin

==============================================================================================================================
Allgemeine Programm Infos wie Changelog und vorhandene Funktionen.
==============================================================================================================================

New functions     | +
Changed functions | #
Deleted functions | -

Vorhandene Funktionen:
-------------------------------------------------------------------------------------------------------------------------------
antssterben          : ants können sterben wenn Sie zu wenig leaves/ water haben.
moveants            : ants werden zufällig bewegt.
Lebensmittel            : Ist für den verbrauch und das hinzufügen von Lebensmitteln wie leaves und water zuständig.
Main                    : Startet das Grundprogramm.
Nachrichten             : News System informiert über aktuelle geschehnisse.
SetMyCurser             : Ist für das Setzten des Cursers in der Console verantwortlich und kann jederzeit verändert werden.
Simulation              : Lässt die Zeit laufen und ist mit für die Bewegung der ants zuständig.
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
int glasses;

int gamerunning;
int geld;
int news = 1;
int checkupdates = 0;
using namespace std;

void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
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
    cout << "|Willkommen zur ants Simulation!                  |" << endl;
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
        /*water = 50;
        leaves = 50;
        glasses = 0;
        ant = rand()%50+3;
        newant = 0;            //antahl der ants Random
        happy = 1;
        dead = 0;
        bornant = 0;
        regen = 0;
        sonne = 0;
        sturm = 0;
        blaetter = 0;
        angreifer = 0;
        ende = 0;
        antsmax = 0;
        gamerunning = 1;
        geld = 50;

        system("cls");
        gamefield();
        simulation();
        */
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
