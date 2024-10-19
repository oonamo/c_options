#include "options.h"
#include <stdio.h>
#include <string.h>

Option_t search_list(char **list, char *item, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(list[i], item) == 0)
        {
            const int *result = &i;
            return Some(result);
        }
    }
    return None;
}

int main()
{
    char *weekdays[7] = {
        "Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat",
    };

    int fallback = 0;

    const int *day = unwrap_or(search_list(weekdays, "Fri", 7), &fallback);
    printf("%s day is the %dth day of the week!\n", weekdays[*day],
           *day + 1 <= 7 ? *day + 1 : 1);

    const int *otherDay =
        unwrap_or(search_list(weekdays, "Friday", 7), &fallback);
    printf("%s day is the %dth day of the week!\n", weekdays[*otherDay],
           *otherDay + 1 <= 7 ? *otherDay + 1 : 1);
}
