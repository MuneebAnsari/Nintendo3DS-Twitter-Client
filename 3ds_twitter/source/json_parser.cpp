#include <json-c/json.h>
#include "json_parser.h"

JsonParser::JsonParser() {}

void JsonParser::parseTweetObj(json_object *tweetObj,
                               int n_tweetObj,
                               Tweet **parsedTweets,
                               void addTweet(Tweet **parsedTweets, char *text, int favCount))
{
    for (int i = 0; i < n_tweetObj; i++)
    {
        json_object *currTweetObj = json_object_array_get_idx(tweetObj, i);
        json_object_object_get_ex(currTweetObj, "text", &tweetTextObj);
        char *text = (char *)json_object_get_string(tweetTextObj);
        json_object_object_get_ex(currTweetObj, "favorite_count", &tweetFavoriteCountObj);
        int favCount = json_object_get_int64(tweetFavoriteCountObj);
        addTweet(parsedTweets, text, favCount);
    }
}

void JsonParser::parseUserObj(json_object *userObj)
{
}