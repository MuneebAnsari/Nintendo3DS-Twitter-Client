#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <curl/curl.h>
#include "http_client.h"
#include "twitter_data_service.h"

TwitterDataService::TwitterDataService(){};

TwitterDataService::TwitterDataService(HttpClient httpClient)
{
    this->httpClient = httpClient;
}

Response TwitterDataService::getUserTweets()
{
    CURLcode res;

    struct curl_slist *headers = NULL;
    this->httpClient.setRequestHeaders(&headers);

    Response responseChunk;
    responseChunk.data = NULL;
    responseChunk.size = 0;

    if ((res = this->httpClient.GET(
             (char const *)"http://localhost:3001/get",
             headers,
             this->responseCallback,
             &responseChunk)) != CURLE_OK)
    {
        fprintf(stderr, "getUserTweets -> curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return responseChunk;
}

Response TwitterDataService::postTweet(std::string params)
{
    CURLcode res;

    struct curl_slist *headers = NULL;
    this->httpClient.setRequestHeaders(&headers);

    Response responseChunk;
    responseChunk.data = NULL;
    responseChunk.size = 0;

    if ((res = this->httpClient.POST(
             (char const *)"http://localhost:3001/post",
             headers,
             params,
             this->responseCallback,
             &responseChunk)) != CURLE_OK)
    {
        fprintf(stderr, "postTweet -> curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return responseChunk;
}

/*
    Reference: https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
    This callback function gets called by libcurl as soon as there is data 
    received that needs to be saved. For most transfers, this callback gets 
    called many times and each invoke delivers another chunk of data.
*/
size_t TwitterDataService::
    responseCallback(void *contents,
                     size_t size,
                     size_t nmemb,
                     void *responseChunk)
{
    size_t realsize = size * nmemb;
    Response *resp = (Response *)responseChunk;

    char *ptr = (char *)realloc(resp->data, resp->size + realsize + 1);
    if (ptr == NULL)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    resp->data = ptr;
    memcpy(&(resp->data[resp->size]), contents, realsize);
    resp->size += realsize;
    resp->data[resp->size] = 0;
    return realsize;
}
