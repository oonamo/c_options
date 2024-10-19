#include "options.h"

void *unwrap(Option_t option) { return option.data; }
void *unwrap_or(Option_t option, void *def)
{
    if (option.ok == 1)
    {
        return option.data;
    }
    return def;
}

void *unwrap_or_else(Option_t option, void *(*defaultFn)())
{
    if (option.ok)
    {
        return option.data;
    }
    return defaultFn();
}

int Option_OK(Option_t option) { return option.ok == 1; }
int Option_Bad(Option_t option) { return option.ok == 0; }
