#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdlib.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <json-c/json.h>

struct tweet
{
    char *text;
    int favCount;
    struct tweet *next;
};
typedef struct tweet Tweet;

typedef struct
{
    char *id_str;
    char *name;
    char *screen_name;
} User;

class JsonParser
{
private:
    struct json_object *parsed_response;
    struct json_object *tweetsObj;
    struct json_object *tweetObj;
    struct json_object *tweetTextObj;
    struct json_object *tweetUserObj;
    struct json_object *tweetFavoriteCountObj;

public:
    JsonParser();
    void parseTweetObj(json_object *tweetObj,
                       int n_tweetObj,
                       Tweet **parsedTweets,
                       void addTweet(Tweet **parsedTweets, char *text, int favCount));
    void parseUserObj(json_object *userObj);
};
#endif