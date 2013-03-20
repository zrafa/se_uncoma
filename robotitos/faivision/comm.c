/*
 * comm.c : curl module
 * 
 * Author : Rafael Ignacio Zurita 2011
 *
 */

#include <stdio.h>
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void comm_get_http_file(const char *url, const char *file)
{
        CURL *curl;
        CURLcode res;
        FILE *fp;

        curl = curl_easy_init();
        if(curl) {
                fp = fopen(file,"wb");
                curl_easy_setopt(curl, CURLOPT_URL, url);
 
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                res = curl_easy_perform(curl);

                /* always cleanup */ 
                curl_easy_cleanup(curl);
                fclose(fp);
        }
}

void comm_init(void)
{
}

