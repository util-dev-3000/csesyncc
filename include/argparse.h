#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdbool.h>

typedef struct {
    const char *name;
    char *value;
    bool passed;
} Argument;

Argument createArg(const char *name, char *value);

int parseIntArg(const char *name, const char *value, int min, int max, int *outPtr);

int parseArgs(int argc, char *argv[], Argument *args[], int numArgs);

#endif // argparse.h