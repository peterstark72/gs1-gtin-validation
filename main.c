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
            printf(",%s,%c,%s,%s\n", 
                gt.prefix_digits, gt.check_digit, GTIN_FormatStr(gt.format), GTIN_PrefixStr(gt.prefix));
        } else {
            GTIN_Print(&gt); printf("\n");
        }
    } else if (skip_invalid == FALSE) {
        printf("%s\t%s\n", s, GTIN_ErrorStr(err));
    }
}

void read_stdin()
{
    char line[64];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\r\n")] = '\0'; // strip trailing newline
        if (line[0] == '\0') {
            continue; // skip blank lines
        }
        process(line);
    }
}


void process_flags(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--skip-invalid") == 0) {
            skip_invalid = TRUE;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = TRUE;
        } else if (strcmp(argv[i], "-") == 0) {
            read_stdin();
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [--skip-invalid] [--verbose] [GTINs...]\n", argv[0]);
            printf("Options:\n");
            printf("  --skip-invalid   Skip invalid GTINs (default: show error)\n");
            printf("  --verbose        Show detailed output (default: show GTIN only)\n");
            printf("  -                Read GTINs from standard input\n");
            printf("  --help           Show this help message\n");
            exit(0);
        } else {
            process(argv[i]);
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc >= 2) {
        process_flags(argc, argv);
        return 0;
    }

    read_stdin();    
    return 0;
}