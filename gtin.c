#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "gtin.h"
#include "gcp.h"

struct prefix {
    int low;
    int high;
    int range;
};


// GTIN-8 Prefix ranges and their corresponding GTIN range codes
const struct prefix gs1_8_prefix[] = {
    {0, 99, GTIN_PREFIX_RESTRICTED_CIRCULATION},
    {100, 199, GTIN_PREFIX_GTIN_8},
    {200, 299, GTIN_PREFIX_RESTRICTED_CIRCULATION},
    {300, 951, GTIN_PREFIX_GTIN_8},
    {952, 952, GTIN_PREFIX_DEMONSTRATION},
    {953, 976, GTIN_PREFIX_GTIN_8},
    {977, 999, GTIN_PREFIX_RESERVED},
};

// UPC Prefix ranges and their corresponding GTIN range codes
const struct prefix upc_prefix[] = {
    {1, 1999, GTIN_PREFIX_UPC},
    {2000, 2999, GTIN_PREFIX_RESTRICTED_CIRCULATION},
    {3000, 3999, GTIN_PREFIX_UPC},
    {4000, 4999, GTIN_PREFIX_RESTRICTED_CIRCULATION},
    {5000, 5999, GTIN_PREFIX_RESERVED},
    {6000, 9999, GTIN_PREFIX_UPC},
};


// GS1 Prefix ranges and their corresponding GTIN range codes
const struct prefix gs1_prefix[] = {    
    {100, 199, GTIN_PREFIX_GS1_COMPANY},
    {200, 299, GTIN_PREFIX_RESTRICTED_CIRCULATION},
    {300, 950, GTIN_PREFIX_GS1_COMPANY}, 
    {951, 951, GTIN_PREFIX_UNUSED},
    {952, 952, GTIN_PREFIX_DEMONSTRATION},
    {953, 976, GTIN_PREFIX_GS1_COMPANY},
    {977, 977, GTIN_PREFIX_SERIAL_PUBLICATION},
    {978, 979, GTIN_PREFIX_BOOKLAND_ISBN},
    {980, 980, GTIN_PREFIX_REFUND_RECEIPT},
    {981, 983, GTIN_PREFIX_COUPON},
    {984, 989, GTIN_PREFIX_UNUSED},
    {990, 999, GTIN_PREFIX_COUPON},
};


// Returns 1 if the string starts with the specified prefix, otherwise returns 0
static int starts_with(const char *str, const char *prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) {
            return 0; // Not a match
        }
    }
    return 1; // Match
}

// Fills the destination string with leading zeros and copies the source string into it  
static void zerofill(char *dest, const char *src, int length, int maxlength)
{
    int maxfill = maxlength - length;
    for (int i = 0; i < maxfill; i++)
    {
        dest[i] = '0';
    }
    for (int i = 0; i < length; i++)
    {
        dest[maxfill + i] = src[i];
    }
    dest[maxlength] = '\0'; // Null-terminate the string
}


// Checks if the provided length is a valid GTIN length (8, 12, 13, or 14)
static int is_valid_gtin_format(int length) {
    return length == GTIN_8_FORMAT || length == GTIN_12_FORMAT || length == GTIN_13_FORMAT || length == GTIN_14_FORMAT;
}

// Checks if a character is a valid GTIN digit (0-9)
static int is_gtin_digit(char c) {
    return c >= '0' && c <= '9';
}
 

// Cast the string to an integer, returning the integer value of the first n characters
int dtio(const char *src, int n) {
    int num = 0;
    while (n-- && (*src)) {
        num = num * 10 + (*(src++) - '0'); // Convert the character to an integer and accumulate
    }
    return num;
}

// Copy n characters from src to dest starting at the specified start index, for n characters
char* sublcpy(char *dest, const char *src, int start, int length) {
    src += start;
    while (*src && length > 0) {
        *dest++ = *src++;
        length--;
    }
    *dest = '\0'; // Null-terminate the string
    return dest;
}


// Lookup the range description for a given prefix in the specified prefix array
static int lookup_range(int prefix, const struct prefix *prefix_array, size_t array_size) {
    for (size_t i = 0; i < array_size; i++) {
        if (prefix >= prefix_array[i].low && prefix <= prefix_array[i].high) {
            return prefix_array[i].range;
        }
    }
    return GTIN_PREFIX_NOT_FOUND; // Not found
}


static GtinRange determine_range(const char *prefix, GtinFormat format) {
    int prefix_value;
    switch (format) {
        case GTIN_8_FORMAT:
            prefix_value = dtio(prefix, 3); 
            return lookup_range(prefix_value, gs1_8_prefix, sizeof(gs1_8_prefix) / sizeof(gs1_8_prefix[0]));
        case GTIN_12_FORMAT:
            prefix_value = dtio(prefix, 4); 
            return lookup_range(prefix_value, upc_prefix, sizeof(upc_prefix) / sizeof(upc_prefix[0]));
        case GTIN_13_FORMAT:
        case GTIN_14_FORMAT:
            prefix_value = dtio(prefix, 3); 
            return lookup_range(prefix_value, gs1_prefix, sizeof(gs1_prefix) / sizeof(gs1_prefix[0]));
        default:
            return GTIN_PREFIX_NOT_FOUND; // Unknown format         
    }
}


// Calculates the check digit for a GTIN string of a given length
// https://www.gs1.org/services/how-calculate-check-digit-manually
char GTIN_CalculateCheckDigit(const char *s, int length_without_check_digit) {
    int sum = 0;
    int weight = (length_without_check_digit% 2 == 0) ? 1 : 3; // Start with weight 3 for even lengths, 1 for odd lengths
    for (int i = 0; i < length_without_check_digit; i++)
    {
        int digit = s[i] - '0';
        sum += digit * weight;
        weight = (weight == 3) ? 1 : 3; // Alternate weights
    }
    int check_digit = (10 - (sum % 10)) % 10;
    return '0' + check_digit; // Return as character
}

// Copies the prefix from the GTIN digits into the provided prefix buffer based on the GTIN format
void GTIN_CopyPrefix(char *prefix, const gtin14 digits, GtinFormat format) {
    switch (format) {
        case GTIN_8_FORMAT:
            sublcpy(prefix, digits, 6, 3); // GTIN-8 prefix is the first 3 digits
            break;
        case GTIN_12_FORMAT:
            sublcpy(prefix, digits, 2, 6); // GS1 Company Prefix is the first 6 digits for GTIN-12
            break;
        case GTIN_13_FORMAT:
            sublcpy(prefix, digits, 1, 8); // GS1 Company Prefix is the first 7 digits for GTIN-13
            break;
        case GTIN_14_FORMAT:
            sublcpy(prefix, digits, 1, 8); // GS1 Company Prefix is the first 8 digits for GTIN-14
            break;
        default:
            *prefix = '\0'; // Unknown format, set prefix to empty string
            return;
    }
    return; 
}

void GTIN_Print(const GTIN *gt) {
    char *ptr = (char*) gt->digits;
    switch (gt->format) {
        case GTIN_8_FORMAT:
            ptr += 6; // Skip the leading zeros for GTIN-8
            printf("%c%c%c%c %c%c%c%c", 
                ptr[0], ptr[1], ptr[2], ptr[3], 
                ptr[4], ptr[5], ptr[6], ptr[7]);
            break;
        case GTIN_12_FORMAT:
            ptr += 2; // Skip the leading zeros for GTIN-12
            printf("%c%c%c%c%c%c %c%c%c%c%c%c", 
                ptr[0], ptr[1], ptr[2], ptr[3], 
                ptr[4], ptr[5], ptr[6], ptr[7], 
                ptr[8], ptr[9], ptr[10], ptr[11]);
            break;
        case GTIN_13_FORMAT: 
            ptr += 1; // Skip the leading zero for GTIN-13
            printf("%c %c%c%c%c%c%c %c%c%c%c%c%c", 
                ptr[0], ptr[1], ptr[2], ptr[3], 
                ptr[4], ptr[5], ptr[6], ptr[7], 
                ptr[8], ptr[9], ptr[10], ptr[11], 
                ptr[12]);
            break;
        case GTIN_14_FORMAT:
            printf("%c %c%c%c%c %c%c%c%c %c%c%c%c %c",
                ptr[0], ptr[1], ptr[2], ptr[3],
                ptr[4], ptr[5], ptr[6], ptr[7],
                ptr[8], ptr[9], ptr[10], ptr[11],
                ptr[12], ptr[13]);
            break;
        default:
            printf("Unknown GTIN format\n");
            break;
    }
}


// Creates a new GTIN object from the provided string, validating its format and check digit
GtinError GTIN_Init(GTIN *gt, const char *s) {

    // Check for null input
    if (gt == NULL || s == NULL) {
        return GTIN_ERR_NULL_INPUT; // Return error for null input
    }

    
    // Get length of the input string
    int length = 0;
    const char *ptr = s; // Start from the beginning of the string
    while (*ptr != '\0') {
        if (!is_gtin_digit(*ptr)) {
            return GTIN_ERR_INVALID_CHAR;
        }
        length++;
        ptr++;
    }

    if (!is_valid_gtin_format(length)) {
        return GTIN_ERR_INVALID_LEN; // Invalid length
    }
    zerofill(gt->digits, s, length, GTIN_MAX_LENGTH); // Zero-fill to 14 characters
    
    // Determine the GTIN format based on the length and leading zeros
    if (length == GTIN_MAX_LENGTH) {
        if (starts_with(gt->digits, "000000")) {
            // Six consecutive leading zeros indicate a GTIN-8 format
            gt->format = GTIN_8_FORMAT; 
        } else  if (starts_with(gt->digits, "00")) {
            // Two leading zeros indicate a GTIN-12 format
            gt->format = GTIN_12_FORMAT; 
        } else if (starts_with(gt->digits, "0")) {
            // One leading zero indicates a GTIN-13 format
            gt->format = GTIN_13_FORMAT; 
        } else {
            // No leading zeros indicate a true GTIN-14 format
            gt->format = GTIN_14_FORMAT; 
        }
    } else {
        gt->format = (GtinFormat) length; // Set the format based on the length        
    }


    // Check the validity of the check digit
    int cd = GTIN_CalculateCheckDigit(s, length - 1); 
    if (cd != s[length - 1]) {
        return GTIN_ERR_BAD_CHECKSUM; // Invalid check digit
    }
    gt->check_digit = cd;

    GTIN_CopyPrefix(gt->prefix, gt->digits, gt->format); // Copy the prefix based on the format

    gt->range = determine_range(gt->prefix, gt->format); // Determine the range based on the prefix and format

    return GTIN_OK; // Successfully parsed GTIN
}

// Returns GTIN error as a string
char* GTIN_Error(GtinError err) {
    switch (err) {
        case GTIN_OK:
            return "GTIN_OK";
        case GTIN_ERR_NULL_INPUT:
            return "GTIN_ERR_NULL_INPUT";
        case GTIN_ERR_INVALID_LEN:
            return "GTIN_ERR_INVALID_LEN";
        case GTIN_ERR_INVALID_CHAR:
            return "GTIN_ERR_INVALID_CHAR";
        case GTIN_ERR_BAD_CHECKSUM:
            return "GTIN_ERR_BAD_CHECKSUM";
        default:
            return "GTIN_ERR_UNKNOWN";
    }
}

char* GTIN_Range(GtinRange range) {
    switch (range) {
        case GTIN_PREFIX_GTIN_8:
            return "GTIN_PREFIX_GTIN_8";
        case GTIN_PREFIX_UPC:
            return "GTIN_PREFIX_UPC";
        case GTIN_PREFIX_GS1_COMPANY:
            return "GTIN_PREFIX_GS1_COMPANY";
        case GTIN_PREFIX_RESERVED:
            return "GTIN_PREFIX_RESERVED";
        case GTIN_PREFIX_DEMONSTRATION:
            return "GTIN_PREFIX_DEMONSTRATION";
        case GTIN_PREFIX_SERIAL_PUBLICATION:
            return "GTIN_PREFIX_SERIAL_PUBLICATION";
        case GTIN_PREFIX_BOOKLAND_ISBN:
            return "GTIN_PREFIX_BOOKLAND_ISBN";
        case GTIN_PREFIX_REFUND_RECEIPT:
            return "GTIN_PREFIX_REFUND_RECEIPT";
        case GTIN_PREFIX_COUPON:
            return "GTIN_PREFIX_COUPON";
        case GTIN_PREFIX_RESTRICTED_CIRCULATION:
            return "GTIN_PREFIX_RESTRICTED_CIRCULATION";
        case GTIN_PREFIX_UNUSED:
            return "GTIN_PREFIX_UNUSED";
        case GTIN_PREFIX_NOT_APPLICABLE:
            return "GTIN_PREFIX_NOT_APPLICABLE";
        default:
            return "GTIN_PREFIX_NOT_FOUND";
    }
}

char* GTIN_Format(GtinFormat fmt) {
    switch (fmt) {
        case GTIN_8_FORMAT:
            return "GTIN-8";
        case GTIN_12_FORMAT:
            return "GTIN-12";
        case GTIN_13_FORMAT:
            return "GTIN-13";
        case GTIN_14_FORMAT:
            return "GTIN-14";
        default:
            return "GTIN_UNKNOWN_FORMAT";
    }
}