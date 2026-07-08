#ifndef GTIN_H
#define GTIN_H

#define GTIN_8 8
#define GTIN_12 12
#define GTIN_13 13
#define GTIN_14 14


typedef enum {
    GTIN_OK               =  0,
    GTIN_ERR_NULL_INPUT   = -1,
    GTIN_ERR_INVALID_LEN  = -2,
    GTIN_ERR_INVALID_CHAR = -3,
    GTIN_ERR_BAD_CHECKSUM = -4,
} GtinError;

// Define the GTIN type as a struct containing a character array (string)
typedef struct {
    char    digits[GTIN_14 + 1]; // +1 for the null terminator
    char    *prefix; // Pointer to the prefix string
    int     length; // Length of the GTIN string
} GTIN;

// Creates a GTIN string from the provided input string, filling with leading zeros if necessary
int GTIN_Parse(GTIN *gt, const char *s);

// Returns a string representation of the error code
char* GTIN_Error(GtinError err);

#endif // GTIN_H

