#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "general.h"
#include "iostr/colors.h"
#include "iostr/iostr.h"

const int MAX_LINE_LEN = 256;

ErrorTag ERROR_TAGS[] =
    {
        {"",                                            NO_ERROR                },
        {"Error in reading file",                       FILE_READING_ERROR      },
        {"Error in reading file stats",                 FILE_STATS_READING_ERROR},
        {"Error in opening file",                       FILE_OPEN_ERROR         },
        {"Wrong filename",                              FILE_NAME_ERROR         },
        {"Error in allocation memory for TextInfo",     TEXT_MALLOC_ERROR       },
        {"Error in allocation memory for lines (Line)", LINES_MALLOC_ERROR      },
        {"Null pointer to the text",                    TEXT_MARKOUT_NULL_ERROR }
    };

const char* ERRORS[N_ERRORS] = {};

bool GetOptions(int argc, const char *argv[], int optionsInd[], const Option exec_options[], int n_exec_options)
{
    ASSERT(argv != NULL);

    for (int i = 1; i < argc; ++i)
        for (size_t j = 0; j < n_exec_options; ++j)
            if (strcmp(exec_options[j].strFormLong, argv[i])  == 0 ||
                strcmp(exec_options[j].strFormShort, argv[i]) == 0)
            {
                int id = exec_options[j].optionId;
                if (optionsInd[id])
                    return false;

                optionsInd[id] = i;
            }

    return true;
}

void TextInfoCtor(TextInfo *text)
{
    ASSERT(text != NULL);

    text->size  = 0;
    text->base  = NULL;

    text->words_cnt = 0;
    text->words     = NULL;
}

void TextInfoInputFromFile(TextInfo *text, const char *filename, int *err)
{
    ASSERT(text != NULL);
    *err = NO_ERROR;

    RET_ERR(filename == NULL, err, FILE_NAME_ERROR);

    int32_t fd = open(filename, O_RDONLY, 0);
    RET_ERR(fd == -1, err, FILE_OPEN_ERROR);

    struct stat fileStatBuf = {};
    RET_ERR(fstat(fd, &fileStatBuf) != 0, err, FILE_STATS_READING_ERROR);

    uint32_t  fileSize = (uint32_t) fileStatBuf.st_size;
    char     *fileCont = (char*)  calloc(fileSize + 1, sizeof(char));

    RET_ERR(fileCont == NULL, err, FILE_CONTENT_MALLOC_ERROR);

    int64_t n_read = read(fd, fileCont, fileSize);
    RET_ERR(n_read < fileSize, err, FILE_READING_ERROR);

    text->size = fileSize + 1;
    text->base = fileCont;

    text->base[fileSize] = '\0';

    close(fd);
}

void TextInfoPrepare(TextInfo *text)
{
    ASSERT(text != NULL);

    uint32_t res = 0;

    for (uint32_t i = 0; i < text->size; ++i)
    {
        text->base[i] = tolower(text->base[i]);

        if (!isalpha(text->base[i]    ) && i > 0 && 
             isalpha(text->base[i - 1]))
            {
                ++res;
                text->base[i] = '\0';
            }
    }

    text->words_cnt = res;
}

void TextInfoMarkout(TextInfo *text, int32_t *err)
{
    ASSERT(text != NULL);
    ASSERT(err  != NULL);
    
    *err = NO_ERROR;

    RET_ERR(text == NULL, err, TEXT_MARKOUT_NULL_ERROR);

    TextInfoPrepare(text);
    text->words = (const char**) calloc(text->words_cnt, sizeof(const char*));

    for (uint32_t i = 0, j = 0; i < text->size; ++i)
    {
        if (text->base[i] == '\0')
            ++j;

        if (isalpha(text->base[i]) && text->words[j] == NULL)
            text->words[j] = text->base + i;
    }
}

void TextInfoDtor(TextInfo *text)
{
    free(text->base);
    free(text->words);

    text->base  = NULL;
    text->words = NULL;
}

void InitErrorTags()
{
    for (int i = 0; i < N_ERRORS; ++i)
        ERRORS[ERROR_TAGS[i].errorId] = ERROR_TAGS[i].description;
}

