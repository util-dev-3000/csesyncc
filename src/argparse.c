#include "argparse.h"
#include <stdio.h>
#include <string.h>

Argument createArg(const char *name, char *value) {
    Argument arg;
    arg.name = name;
    arg.value = value;
    arg.passed = false;
    return arg;
}

int parseArgs(int argc, char *argv[], Argument *args[], int numArgs) {
    for (int i = 0; i < argc; i++)
    {
        char *argName = NULL;
        char *value = NULL;

        if (i > 0)
        {
            if (strncmp(argv[i], "--", 2) == 0)
            {
                argName = argv[i] + 2;
                if (i < argc - 1)
                {
                    if (strncmp(argv[i + 1], "--", 2) != 0)
                    {
                        value = argv[i + 1];
                    }
                }
            }
        }

        if (argName != NULL)
        {
            // Assign value for args
            int found = 0;
            for (int j = 0; j < numArgs; j++)
            {
                if (strcmp(argName, args[j]->name) == 0)
                {
                    // Value may be null
                    args[j]->value = value;
                    args[j]->passed = true;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Unknown argument: --%s\n", argName);
                return 1;
            }
        }
    }

    return 0;
}