#include <stdlib.h>
#include <cstdarg>
#include <cstdio>
#include <sys/types.h>
#include <curl/curl.h>
#include "http_client.h"

HttpClient::HttpClient() {}

CURLcode HttpClient::GET(char const *url,
                         struct curl_slist *headers,
                         size_t responseCallback(void *contents,
                                                 size_t size,
                                                 size_t nmemb,
                                                 void *dataChunk),
                         Response *responseChunk)
{
    CURL *curl = curl_easy_init();
    CURLcode reqStatus = CURLE_OK;

    if (curl)
    {
        // build request
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // setup callback to handle response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)responseChunk);

        // make request
        reqStatus = curl_easy_perform(curl);
    }
    //sprintf("reqStatus: %d\n", reqStatus);
    return reqStatus;
}

CURLcode HttpClient::POST(char const *url,
                          struct curl_slist *headers,
                          char const *body)
{
    CURLcode ret = CURLE_OK;
    printf("NOT IMPLEMENTED");
    return ret;
}

int HttpClient::setRequestHeaders(struct curl_slist **headers)
{
    *headers = curl_slist_append(*headers, "User-Agent: 3DStest");
    if (*headers == NULL)
    {
        return -1;
    }
    *headers = curl_slist_append(*headers, "Connection Keep-Alive");
    if (*headers == NULL)
    {
        return -1;
    }
    return 0;
}