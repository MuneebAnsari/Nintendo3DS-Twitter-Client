#ifndef MODELS_H
#define MODELS_H

struct tweet
{
    char *text;
    int favCount;
    struct tweet *next;
    struct tweet *prev;
};
typedef struct tweet Tweet;

typedef struct
{
    char *id_str;
    char *name;
    char *screen_name;
} User;

#endif