# Options for C
## Examples
See `examples/`
```c
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

```
