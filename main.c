#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtin.h"

static void process(const char *s)
{
    GTIN gt;
    int err = GTIN_Parse(&gt, s);
    if (err != GTIN_OK) {
        printf("%s\t%s\n", s, GTIN_Error(err));
        return;
    }
    printf("%s\t%d\t%s\n", gt.digits, gt.length, gt.prefix);
}

int main(int argc, char *argv[])
{
    if (argc >= 2) {
        process(argv[1]);
        return 0;
    }

    char line[64];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\r\n")] = '\0'; // strip trailing newline
        if (line[0] == '\0') {
            continue; // skip blank lines
        }
        process(line);
    }

    return 0;
}