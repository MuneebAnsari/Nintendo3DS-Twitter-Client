#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdlib.h>
#include <cstdarg>
#include <cstdio>
#include <sys/types.h>
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

    CURLcode POST(char const *url,
                  struct curl_slist *headers,
                  char const *body);

    int setRequestHeaders(struct curl_slist **headers);
};

#endif
