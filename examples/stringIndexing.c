#include "options.h"
#include <stdio.h>

Option_t nextChar(char *string)
{
    if (*string != '\0')
    {
        return Some(string);
    }
    return None;
}

int main()
{
    char *string = "Hello world!";
    while (Option_OK(nextChar(string)))
    {
      printf("%c", *string);
      string++;
    }
    printf("\n");
    return 0;
}
