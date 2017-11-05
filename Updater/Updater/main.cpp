#include <iostream>
#include <curl/curl.h>
using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


void UpdaterDownload()
{
 CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url= "https://gaming-ftw.de/antsimupdates/Ameisensimulation.exe";
    //char *url=    "https://wordpress.org/";
    char outfilename[FILENAME_MAX] = "./Ameisensimulation.exe";


    curl_version_info_data * vinfo = curl_version_info(CURLVERSION_NOW);

    if(vinfo->features & CURL_VERSION_SSL){
        printf("CURL: SSL enabled\n");
    }else{
        printf("CURL: SSL not enabled\n");
    }


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

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

    }
    cout << "Update complete";

}


int main()
{
    cout << "Update in progress please wait!";

        UpdaterDownload();
        _sleep(1000);
        system("cls");
        system ("start Ameisensimulation.exe");
        exit(0);
}
