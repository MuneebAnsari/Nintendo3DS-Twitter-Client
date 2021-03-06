#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <iostream>
#include <string>
#include <curl/curl.h>

typedef struct
{
    char *data;
    size_t size;
} Response;

class HttpClient
{

public:
    HttpClient();
    CURLcode GET(char const *url,
                 struct curl_slist *headers,
                 size_t responseCallback(void *contents,
                                         size_t size,
                                         size_t nmemb,
                                         void *dataChunk),
                 Response *responseChunk);

    CURLcode POST(std::string url,
                  struct curl_slist *headers,
                  std::string params,
                  size_t responseCallback(void *contents,
                                          size_t size,
                                          size_t nmemb,
                                          void *dataChunk),
                  Response *responseChunk);

    int setRequestHeaders(struct curl_slist **headers);
};

#endif
