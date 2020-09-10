#ifndef MODELS_H
#define MODELS_H

#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>

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

#endif