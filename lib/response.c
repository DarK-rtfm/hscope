int asprintf(char** a, char* b, ...); // meh..
#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "response.h"

static size_t writeFunction(void* ptr, size_t size, size_t nmemb, Buffer* data) {
    if (data->data == NULL) data->data = malloc (size * nmemb + 1); 
    else data->data = realloc (data->data, data->size + size*nmemb + 1); 
    memcpy (data->data + data->size, ptr, size * nmemb);
    data->size += size * nmemb;
    data->data[data->size] = 0;
    return size * nmemb;
}

Response* getsite(char* type, char* time) {
    char* url;
    asprintf(&url, "https://www.astronet.hu/horoszkop/%s-napi-horoszkop/%s/", type, time);
    Buffer* response_buff = malloc (sizeof(Buffer));
    response_buff->size = 0;
    response_buff->data = NULL;
    long response_code;

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "firefox");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buff);
        //curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);


        curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Could not init curl\n"); 
        free(response_buff);
        return NULL;
    }
    Response* response = malloc(sizeof(Response));
    response->code = response_code;
    response->data = response_buff;
    return response;
}

void cleanup(Response* r) {
    free(r->data);
    free(r);
}
