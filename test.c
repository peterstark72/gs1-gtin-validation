#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "gtin.h"

int main(void)
{
    int err;
    GTIN gt;

    err = GTIN_Parse(&gt, "888494947182");
    assert(err == GTIN_OK);
    assert(strcmp(gt.digits, "00888494947182") == 0);
    assert(gt.length == 12);

    // Test with an invalid GTIN (bad checksum)
    err = GTIN_Parse(&gt, "888494947185");
    assert(err == GTIN_ERR_BAD_CHECKSUM);

    return 0;
}