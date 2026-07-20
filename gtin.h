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

    
// Define the GTIN type as a struct containing a character array (string)
typedef struct   {
    char            digits[GTIN_MAX_LENGTH + 1];
    char            prefix[GTIN_MAX_PREFIX_LENGTH + 1];
    GtinFormat      format; 
    GtinRange       range;
} GTIN;

// Creates a GTIN string from the provided input string
GtinError GTIN_Init(GTIN *gt, const char *s);

// Returns a string representation of the error code
char* GTIN_Error(GtinError err);

// Returns a zero-padded 14-character string representation of the GTIN, or NULL if the GTIN is invalid
char* GTIN_String(GTIN *gt);

// Returns a string representation of the range code
char* GTIN_Range(GtinRange range);

// Returns a string representation of the format code
char* GTIN_Format(GtinFormat fmt);


#endif // GTIN_H

