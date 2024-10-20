#define _CRT_SECURE_NO_WARNINGS
#include "options.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 120
#define INITIAL_CONTENTS_CAPCITY 15

typedef struct
{
    char *data;
    unsigned int lines;
    unsigned int capacity;
} file_contents_t;

int init_file_contents(file_contents_t *file)
{
    file->lines = 0;
    file->capacity = INITIAL_CONTENTS_CAPCITY;
    file->data = malloc(sizeof(char) * file->capacity * MAX_LINE_LENGTH);
    return file->data != NULL;
}

Option_t get_data(char *filepath)
{
    FILE *fp;
    Option_t opt = None;

    fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        return None;
    }

    file_contents_t file = {0};
    if (!init_file_contents(&file))
    {
        goto defer;
    }

    char ch;

    int currentCharCount = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != '\n' && currentCharCount < MAX_LINE_LENGTH)
        {
            if (file.lines >= file.capacity)
            {
                file.capacity *= 2;
                file.data = realloc(file.data, sizeof(char) * file.capacity *
                                                   MAX_LINE_LENGTH);
                if (file.data == NULL)
                {
                    goto defer;
                }
            }
            file.data[file.lines * MAX_LINE_LENGTH + currentCharCount] = ch;
            currentCharCount++;
        }
        else
        {
            if (currentCharCount != MAX_LINE_LENGTH)
            {
                while (currentCharCount < MAX_LINE_LENGTH)
                {
                    file.data[file.lines * MAX_LINE_LENGTH + currentCharCount++] =
                        ' ';
                }
            }
            file.lines++;
            currentCharCount = 0;
        }
    }

    opt = Some(&file);

defer:
    fclose(fp);
    return opt;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Print out the first %d characters of each line of `filepath`"
               "USAGE:\n"
               "fileIo [filepath]\n", MAX_LINE_LENGTH);
        argv = realloc(argv, sizeof(char *) * 3);
        argv[1] = "README.md";
        argc++;
    }
    for (int i = 1; i < argc; i++)
    {
        printf("Reading from %s\n", argv[i]);
        Option_t opt = get_data(argv[i]);
        if (Option_Bad(opt))
        {
            printf("Could not read file %s!\n", argv[i]);
            continue;
        }
        file_contents_t *file = unwrap(opt);
        for (int i = 0; i < file->lines; i++)
        {
            for (int j = 0; j < MAX_LINE_LENGTH; j++)
            {
                printf("%c", file->data[i * MAX_LINE_LENGTH + j]);
            }
            printf("\n");
        }
        free(file->data);
    }
    printf("done!");
}
