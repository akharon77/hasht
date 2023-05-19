#ifndef IOSTR_H
#define IOSTR_H

#include <stdint.h>
#include <stdio.h>

#include "iostr/iostr_debug.h"

struct Option
{
    const char *strFormLong,
               *strFormShort;

    int         optionId;

    const char *description;
};

struct TextInfo
{
    char     *base;
    uint32_t  words_cnt;
    uint32_t  size;

    const char **words;
};

extern       ErrorTag ERROR_TAGS[];
extern const char*    ERRORS[];
extern const int      MAX_LINE_LEN;

void TextInfoCtor          (TextInfo *text);
void TextInfoDtor          (TextInfo *text);

void TextInfoInputFromFile (TextInfo *text, const char *filename, int *err);

void TextInfoPrepare       (TextInfo *text);
void TextInfoMarkout       (TextInfo *text, int *err);
void TextInfoOptimize      (TextInfo *text);

bool GetOptions            (const int argc, const char *argv[], int optionsInd[], const Option exec_options[], int n_exec_options);

#endif  //IOSTR_H

