#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <argparse.h>

int main(int argc, char *argv[])
{
    Argument modeArg = createArg("mode", NULL);
    Argument hostArg = createArg("host", "0.0.0.0");
    Argument portArg = createArg("port", "13399");

    Argument *args[] = {
        &modeArg,
        &hostArg,
        &portArg,
    };

    // Each argument is 2 pointers + 1 byte bool, fixed size
    int numArgs = sizeof(args ) / sizeof(args[0]);

    {
        int res = parseArgs(argc, argv, args, numArgs);
        if(res!=0){
            return res;
        }
    }

    if (modeArg.value == NULL) {
        printf("Mode argument must be specified.\n");
        return 1;
    }
    if (strcmp(modeArg.value, "server") != 0 && strcmp(modeArg.value, "client") != 0) {
        printf("Mode argument should either be 'client' or 'server'.\n");
        return 1;
    }

    int port = -1;

    if (portArg.value != NULL) {
        char *endptr;
        port = (int) strtol(portArg.value, &endptr, 10);
        if (*endptr != '\0' || port <= 0 || port > 65535) {
            printf("Invalid port number: %s\n", portArg);
            return 1;
        }
    } else {
        printf("Port argument must be specified.\n");
        return 1;
    }

    printf("MODE: %s\n", modeArg.value);
    printf("HOST: %s\n", hostArg.value);
    printf("PORT: %d\n", port);

    return 0;
}