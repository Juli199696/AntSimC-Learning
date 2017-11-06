#include <iostream>
#include <curl/curl.h>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>

using namespace std;


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
void UpdaterDownload()
{
    cout << "Update in progress please wait...";
    Sleep(1000);

     CURL *curl;
     FILE *fp;
    CURLcode res;
    char *url= "https://github.com/Juli199696/AntSimCPlusPlusLearning/raw/dev/bin/Release/Ameisensimulation.exe";
    char outfilename[FILENAME_MAX] = "./Ameisensimulation.exe";
    curl = curl_easy_init();
    if (curl) {
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
    cout << "Update complete";
    Sleep(3000);
    system("start Ameisensimulation.exe");
    exit(0);
}

void UpdaterDownloadCheck()
{
     if (system("ping -n 1 gaming-ftw.de")){
          system("cls");
          cout<<"\nNot connnected to the internet or blocked IP\n\n";
          cout << "Update failed, go back to previous version.";
          Sleep(2000);

          system("start Ameisensimulation.exe");
          exit(0);
  }
  else{
          system("cls");
          cout<<"\nConnected to the internet\n\n";
            }

string versionold;
ifstream version ("version.cfg");
    if (version.is_open())
        {
            while ( getline (version,versionold) )
            {
                cout << versionold << '\n';

            }
            version.close();
        }

CURL *curl;
     FILE *fp;
    CURLcode res;
    char *url= "https://raw.githubusercontent.com/Juli199696/AntSimCPlusPlusLearning/dev/bin/Release/version.cfg";
    char outfilename[FILENAME_MAX] = "./version.cfg";
    curl = curl_easy_init();
    if (curl) {
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


string versionneu;

ifstream versionabfrage ("version.cfg");
    if (versionabfrage.is_open())
        {
            while ( getline (versionabfrage,versionneu) )
            {
                cout << versionneu << '\n';

            }
            versionabfrage.close();
        }
    if (versionold == versionneu)
    {
        cout << "You already got the newest version of AntSim :)";
        Sleep(3000);
    system("start Ameisensimulation.exe");
    exit(0);
    }
    else UpdaterDownload();
    }

int main()
{
    cout << "Update in progress please wait!";
    FILE *file;
    if((file = fopen("Ameisensimulation.exe","r"))!=NULL)
        {
            // file exists
            fclose(file);
            UpdaterDownloadCheck();
            Sleep(3000);
        }
    else
        {
            cout << "test";
            Sleep(30000);
          UpdaterDownload();
        }


        return 0;
}
