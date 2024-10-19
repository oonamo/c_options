#ifndef _OPTIONS_H
#define _OPTIONS_H

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef struct Option
{
    void *data;
    unsigned int ok : 1;
} Option_t;

typedef void *(*convert)(void *);

#define Some(value)                                                            \
    (Option_t) { .data = (void*)value, .ok = 1 }

#define None                                                                   \
    (Option_t) { .data = NULL, .ok = 0 }

void *unwrap(Option_t);
void *unwrap_or(Option_t, void*);
void *unwrap_or_else(Option_t, void *(*defaultFn)());

int Option_OK(Option_t);
int Option_Bad(Option_t);

#endif //_OPTIONS_H
