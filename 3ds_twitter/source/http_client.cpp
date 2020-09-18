#include <iostream>
#include <string>
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
    return reqStatus;
}

CURLcode HttpClient::POST(std::string url,
                          struct curl_slist *headers,
                          std::string params,
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

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());

        // setup callback to handle response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)responseChunk);

        // make request
        reqStatus = curl_easy_perform(curl);
    }
    return reqStatus;
}

int HttpClient::setRequestHeaders(struct curl_slist **headers)
{
    *headers = curl_slist_append(*headers, "User-Agent: 3DSTwitterClient");
    if (*headers == NULL)
    {
        return -1;
    }
    *headers = curl_slist_append(*headers, "Connection: Keep-Alive");
    if (*headers == NULL)
    {
        return -1;
    }
    return 0;
}