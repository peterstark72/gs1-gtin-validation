#include <stdio.h>
#include <stdlib.h>
#include "gtin.h"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <gtin>\n", argv[0]);
        return 1;
    }

    GTIN gt;
    int err = GTIN_Parse(&gt, argv[1]);
    if (err != GTIN_OK) {
        printf("Error parsing GTIN: %s\n",  GTIN_Error(err));
        return 1;
    }
    printf("%s\t%d\t%s\n", gt.digits, gt.length, gt.prefix);

}