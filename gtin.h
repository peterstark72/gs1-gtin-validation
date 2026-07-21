#ifndef GTIN_H
#define GTIN_H

#define GTIN_MAX_LENGTH 14 // Maximum length of a GTIN string
#define GTIN_MAX_PREFIX_LENGTH 8 // Maximum length of a GTIN prefix        

typedef enum {
    GTIN_8_FORMAT = 8,    
    GTIN_12_FORMAT = 12,
    GTIN_13_FORMAT = 13,
    GTIN_14_FORMAT = 14,
    GTIN_UNKNOWN_FORMAT = 0,
} GtinFormat;

typedef enum {
    GTIN_OK               =  1,
    GTIN_ERR_NULL_INPUT   = -1,
    GTIN_ERR_INVALID_LEN  = -2,
    GTIN_ERR_INVALID_CHAR = -3,
    GTIN_ERR_BAD_CHECKSUM = -4,
    GTIN_ERR_UNKNOWN_PREFIX = -5
} GtinError;

typedef enum  {
    GTIN_PREFIX_BOOKLAND_ISBN,
    GTIN_PREFIX_COUPON,
    GTIN_PREFIX_DEMONSTRATION,
    GTIN_PREFIX_GS1_COMPANY,
    GTIN_PREFIX_GTIN_8,
    GTIN_PREFIX_NOT_APPLICABLE, // N/A
    GTIN_PREFIX_NOT_FOUND, // Not found
    GTIN_PREFIX_REFUND_RECEIPT,
    GTIN_PREFIX_RESERVED,
    GTIN_PREFIX_RESTRICTED_CIRCULATION, 
    GTIN_PREFIX_SERIAL_PUBLICATION,
    GTIN_PREFIX_UNUSED,
    GTIN_PREFIX_UPC,
} GtinRange;

typedef char gtin14[GTIN_MAX_LENGTH + 1]; // Type for GTIN digits (string)

// Define the GTIN type as a struct containing a character array (string)
typedef struct   {
    gtin14          digits; // GTIN digits (14) as a string, zero-padded if necessary
    char            prefix[GTIN_MAX_PREFIX_LENGTH + 1]; // GTIN prefix (up to 8 characters)
    char            check_digit; // GTIN check digit
    GtinFormat      format; // GTIN format (8, 12, 13, 14)
    GtinRange       range; // GTIN range based on the prefix
} GTIN;

// Calculates the check digit for a GTIN string of the specified length (excluding the check digit)
char GTIN_CalculateCheckDigit(const char *s, int length_without_check_digit);

// Copies the prefix from the GTIN digits into the provided prefix buffer based on the GTIN format
void GTIN_CopyPrefix(char *prefix, const gtin14 digits, GtinFormat format);

// Creates a GTIN string from the provided input string
GtinError GTIN_Init(GTIN *gt, const char *s);

// Returns a string representation of the error code
char* GTIN_Error(GtinError err);

// Returns a string representation of the range code
char* GTIN_Range(GtinRange range);

// Returns a string representation of the format code
char* GTIN_Format(GtinFormat fmt);



#endif // GTIN_H

