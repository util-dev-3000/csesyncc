#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <argparse.h>
#include <server.h>
#include <client.h>

int main(int argc, char *argv[])
{
    Argument modeArg = createArg("mode", NULL);
    Argument hostArg = createArg("host", "0.0.0.0");
    Argument portArg = createArg("port", "13399");
    Argument directoryArg = createArg("dir", NULL);

    // Can be specified only by client
    // Chunk size should be specified by the client to avoid server-side exploiting
    Argument chunkSizeArg = createArg("chunksize", "4096"); // 4 KB by default

    Argument *args[] = {
        &modeArg,
        &hostArg,
        &portArg,
        &directoryArg,
        &chunkSizeArg,
    };

    // Each argument is 2 pointers + 1 byte bool, fixed size
    int numArgs = sizeof(args) / sizeof(args[0]);

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

    int port;
    {
        int res = parseIntArg("Port", portArg.value, 1, 65535, &port);
        if (res!=0) {
            return res;
        }
    }

    if (directoryArg.value == NULL) {
        printf("Directory argument must be specified.\n");
        return 1;
    }

    int chunkSize;
    {
        int res = parseIntArg("Chunk size", chunkSizeArg.value, 256, 4194304, &chunkSize); // Min 256B, max 4 MB
        if (res!=0) {
            return res;
        }
    }

    printf("MODE: %s\n", modeArg.value);
    printf("HOST: %s\n", hostArg.value);
    printf("PORT: %d\n", port);
    printf("DIRECTORY: %s\n", directoryArg.value);
    printf("CHUNKSIZE: %dB\n", chunkSize);

    if (strcmp(modeArg.value, "client") == 0)
    {
        int res = serveClient(args);
        if(res!=0){
            return res;
        }
    }
    else if(strcmp(modeArg.value, "server") == 0)
    {
        int res = serveServer(args);
        if(res!=0){
            return res;
        }
    }
    else {
        printf("%s mode is not a valid mode.", modeArg.value);
        return 1;
    }

    return 0;
}