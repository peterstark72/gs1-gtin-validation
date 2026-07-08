#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gtin.h"
#include "gs1.h"


// Fills the destination string with leading zeros and copies the source string into it  
void zerofill(char dest[], const char *src, int length)
{
    int maxfill = GTIN_14 - length;
    for (int i = 0; i < maxfill; i++)
    {
        dest[i] = '0';
    }
    for (int i = 0; i < length; i++)
    {
        dest[maxfill + i] = src[i];
    }
    dest[GTIN_14] = '\0'; // Null-terminate the string
}

// Checks if the provided length is a valid GTIN length (8, 12, 13, or 14)
int is_valid_gtin_length(int length) {
    return length == GTIN_8 || length == GTIN_12 || length == GTIN_13 || length == GTIN_14;
}

// Checks if a character is a valid GTIN digit (0-9)
int is_gtin_digit(char c) {
    return c >= '0' && c <= '9';
}


// Returns 1 if the check digit is valid, 0 otherwise
int is_valid_checkdigit(const GTIN gt)
{
    int sum = 0;
    int weight = 3;
    for (int i = 0; i < GTIN_14 - 1; i++)
    {
        int digit = gt.digits[i] - '0';
        sum += digit * weight;
        weight = (weight == 3) ? 1 : 3; // Alternate weights
    }
    int check_digit = (10 - (sum % 10)) % 10;
    return check_digit == (gt.digits[GTIN_14 - 1] - '0');
}    



//Prefix is the first 3 digits of the GTIN code
char* getprefix(const GTIN gt) {
    char prefix[3] = {'\0'}; // Buffer to hold the prefix as a string
    for (int i = 0; i < 3; i++) {
        prefix[i] = gt.digits[i+1]; // Skip the first digit (which is the packaging indicator)
    }

    // Convert the prefix string to an integer for comparison
    int prefix_num = (prefix[0] - '0') * 100 + (prefix[1] - '0') * 10 + (prefix[2] - '0');
    int length = GS1_PREFIX_COUNT; // Get the number of entries in the gs1_prefix array
    for (int i = 0; i < length; i++) {
        if (prefix_num >= gs1_prefix[i].low && prefix_num <= gs1_prefix[i].high) {
            return gs1_prefix[i].name;
        }
    }
    return "Unknown prefix";
}



// Creates a new GTIN object from the provided string, validating its format and check digit
int GTIN_Parse(GTIN *gt, const char *s) {

    int length = 0;
    const char *ptr = s;
    while (*ptr != '\0') {
        if (!is_gtin_digit(*ptr)) {
            return GTIN_ERR_INVALID_CHAR; // Invalid character found
        }
        length++;
        ptr++;
    }
    if (!is_valid_gtin_length(length)) {
        return GTIN_ERR_INVALID_LEN; // Invalid GTIN length
    }
    gt->length = length; // Store the length of the GTIN

    zerofill(gt->digits, s, length); // Fill the GTIN string with leading zeros and the provided string
    
    if (!is_valid_checkdigit(*gt)) {
        return GTIN_ERR_BAD_CHECKSUM; // Invalid check digit
    }

    gt->prefix = getprefix(*gt); // Get the prefix for the GTIN
    
    return GTIN_OK; 
}

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
            return "Unknown error";
    }
}
