#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtin.h"

#define TRUE 1
#define FALSE 0

// Flags
int skip_invalid = FALSE; // Skip invalid GTINs
int verbose = FALSE; // Verbose output

static void process(const char *s)
{
    GTIN gt;
    GtinError err = GTIN_Init(&gt, s);
    if (err == GTIN_OK) 
    {
        if (verbose == TRUE) {
            GTIN_Print(&gt); 
            printf("\t%s\t%c\t%s\t%s\n", 
                gt.prefix_digits, gt.check_digit, GTIN_FormatStr(gt.format), GTIN_PrefixStr(gt.prefix));
        } else {
            GTIN_Print(&gt); printf("\n");
        }
    } else if (skip_invalid == FALSE) {
        printf("%s\t%s\n", s, GTIN_ErrorStr(err));
    }
}


void process_flags(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--skip-invalid") == 0) {
            skip_invalid = TRUE;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = TRUE;
        } else {
            process(argv[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc >= 2) {
        process_flags(argc, argv);
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