#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtin.h"
#include "gcp.h"

static void process(const char *s)
{
    GTIN gt;
    GtinError err = GTIN_Init(&gt, s);
    printf("%s\t%s", GTIN_Error(err), s);
    if (err == GTIN_OK) 
    {
        printf("\t%s\t%s\t%s\t%s\n", gt.digits, GTIN_Range(gt.range), GTIN_Format(gt.format), GTIN_CompanyPrefix(&gt));
    } else 
    {
        printf("\n");
    }
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