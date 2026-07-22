#ifndef GTIN_H
#define GTIN_H

#include "prefix.h" // Include header with prefix definitions

#define GTIN_MAX_LENGTH 14 // Maximum length of a GTIN string
#define GTIN_MAX_PREFIX_LENGTH 8 // Maximum length of a GTIN prefix        

#define GTIN_8_LENGTH 8   // Length of GTIN-8
#define GTIN_12_LENGTH 12 // Length of GTIN-12
#define GTIN_13_LENGTH 13 // Length of GTIN-13
#define GTIN_14_LENGTH 14 // Length of GTIN-14

typedef enum {
    GTIN_8_FORMAT,    
    GTIN_12_FORMAT,
    GTIN_13_FORMAT,
    GTIN_14_FORMAT,
    GTIN_UNKNOWN_FORMAT,
} GtinFormat;

typedef enum {
    GTIN_OK,
    GTIN_ERR_NULL_INPUT,
    GTIN_ERR_INVALID_LEN,
    GTIN_ERR_INVALID_CHAR,
    GTIN_ERR_BAD_CHECKSUM,
    GTIN_ERR_UNKNOWN_PREFIX,
} GtinError;


typedef char gtin14[GTIN_MAX_LENGTH + 1]; // Type for GTIN digits (string)

// Define the GTIN type as a struct containing a character array (string)
typedef struct   {
    gtin14          digits; // GTIN digits (14) as a string, zero-padded if necessary
    char            prefix_digits[GTIN_MAX_PREFIX_LENGTH + 1]; // GTIN prefix (up to 8 characters)
    char            check_digit; // GTIN check digit, the last character of the GTIN string
    GtinFormat      format; // GTIN format (8, 12, 13, 14)
    GS1Prefix       prefix; // GS1 prefix (from the GS1Prefix enum)
} GTIN;

// Creates a GTIN string from the provided input string
GtinError GTIN_Init(GTIN *gt, const char *s);

// Returns GS1 prefix name
char* GTIN_PrefixStr(GS1Prefix prefix);

// Returns a string representation of the error code
char* GTIN_ErrorStr(GtinError err);

// Returns a string representation of the format code
char* GTIN_FormatStr(GtinFormat fmt);

// Prints the GTIN information to stdout
void GTIN_Print(const GTIN *gt);

// Calculates the check digit for a GTIN string of the specified length (excluding the check digit)
char GTIN_CalculateCheckDigit(const char *s, int length_without_check_digit);

#endif // GTIN_H

