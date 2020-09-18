#ifndef TWITTER_DATA_SERVICE_H
#define TWITTER_DATA_SERVICE_H

#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include "http_client.h"

class TwitterDataService
{

private:
    HttpClient httpClient;

public:
    TwitterDataService();
    TwitterDataService(HttpClient httpClient);
    Response getUserTweets();
    Response postTweet(std::string params);
    static size_t responseCallback(void *contents,
                                   size_t size,
                                   size_t nmemb,
                                   void *responseChunk);
};
#endif