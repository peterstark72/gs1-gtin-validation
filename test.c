#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtin.h"

#define MAX_LINE_LENGTH 256
#define MAX_COLUMNS 2


// Reads a CSV file of test codes
// and asserts GTIN_Parse produces the expected result for each row.
static void run_data_file_tests(const char *path)
{
    FILE *fp = fopen(path, "r");
    assert(fp != NULL);

    char line[MAX_LINE_LENGTH];
    char *columns[MAX_COLUMNS];
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        char *token, *stringp;
        stringp = strdup(line);
        int col=0;
        while((token = strsep(&stringp, ",")) != NULL && col < MAX_COLUMNS) {
            columns[col++] = token;
        }
        free(stringp);  // strdup'd line

        GTIN gt;
        GtinError err = GTIN_Init(&gt, columns[0]);
        if (err == GTIN_OK) {
            assert(strcmp(GTIN_PrefixStr(gt.prefix), columns[1]) == 0);
        } else {
            assert(strcmp(GTIN_ErrorStr(err), columns[1]) == 0);
        }        
    }

    fclose(fp);
}

void Test_GTIN_CalculateCheckDigit() {
    assert(GTIN_CalculateCheckDigit("39702530829", 11) == '8');
}



int main(void)
{
    run_data_file_tests("./data/gtin8_samples.txt");
    run_data_file_tests("./data/gtin12_samples.txt");
    run_data_file_tests("./data/gtin13_samples.txt");
    run_data_file_tests("./data/gtin_invalid_samples.txt");
    
    Test_GTIN_CalculateCheckDigit();

    return 0;
}