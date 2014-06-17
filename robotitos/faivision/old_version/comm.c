/*
 * comm.c : curl module
 * 
 * Written 2011-2013 by Rafael Ignacio Zurita y Rodolfo del Castillo
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See the file COPYING.GPL for details.
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

