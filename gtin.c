#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "gtin.h"

struct prefix_range {
    int low;
    int high;
    GS1Prefix prefix;
};


// GTIN-8 Prefix ranges and their corresponding GTIN range codes
const struct prefix_range gtin8_prefix[] = {
    {0, 99, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {100, 199, GS1_PREFIX_GTIN_8},
    {200, 299, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {300, 951, GS1_PREFIX_GTIN_8},
    {952, 952, GS1_PREFIX_DEMONSTRATION},
    {953, 976, GS1_PREFIX_GTIN_8},
    {977, 999, GS1_PREFIX_RESERVED},
};

// UPC Prefix ranges and their corresponding GTIN range codes
const struct prefix_range upc_prefix[] = {
    {1, 1999, GS1_PREFIX_UPC},
    {2000, 2999, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {3000, 3999, GS1_PREFIX_UPC},
    {4000, 4999, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {5000, 5999, GS1_PREFIX_RESERVED},
    {6000, 9999, GS1_PREFIX_UPC},
};

// GS1 Prefix ranges and their corresponding GTIN range codes
// https://www.gs1.org/standards/id-keys/company-prefix
const struct prefix_range gs1_prefix[] = {
    {0, 19, GS1_COMPANY_PREFIX_US},
    {20, 29, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {30, 39, GS1_COMPANY_PREFIX_US},
    {40, 49, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {50, 59, GS1_COMPANY_PREFIX_US_FUTURE},
    {60, 139, GS1_COMPANY_PREFIX_US},
    {200, 299, GS1_PREFIX_RESTRICTED_CIRCULATION},
    {300, 379, GS1_COMPANY_PREFIX_FRANCE_RANGE},
    {380, 380, GS1_COMPANY_PREFIX_BULGARIA_RANGE},
    {381, 381, GS1_COMPANY_PREFIX_KOSOVO_RANGE},
    {383, 383, GS1_COMPANY_PREFIX_SLOVENIJA_RANGE},
    {385, 385, GS1_COMPANY_PREFIX_CROATIA_RANGE},
    {387, 387, GS1_COMPANY_PREFIX_BOSNIA_HERZEGOVINA_RANGE},
    {389, 389, GS1_COMPANY_PREFIX_MONTENEGRO_RANGE},
    {450, 459, GS1_COMPANY_PREFIX_JAPAN_RANGE},
    {460, 469, GS1_COMPANY_PREFIX_RUSSIA_RANGE},
    {470, 470, GS1_COMPANY_PREFIX_KYRGYZSTAN_RANGE},
    {471, 471, GS1_COMPANY_PREFIX_CHINESE_TAIPEI_RANGE},
    {472, 472, GS1_COMPANY_PREFIX_VIETNAM_RANGE},
    {473, 473, GS1_COMPANY_PREFIX_ARMENIA_RANGE},
    {474, 474, GS1_COMPANY_PREFIX_ESTONIA_RANGE},
    {475, 475, GS1_COMPANY_PREFIX_LATVIA_RANGE},
    {476, 476, GS1_COMPANY_PREFIX_AZERBAIJAN_RANGE},
    {477, 477, GS1_COMPANY_PREFIX_LITHUANIA_RANGE},
    {478, 478, GS1_COMPANY_PREFIX_UZBEKISTAN_RANGE},
    {479, 479, GS1_COMPANY_PREFIX_SRI_LANKA_RANGE},
    {480, 480, GS1_COMPANY_PREFIX_PHILIPPINES_RANGE},
    {481, 481, GS1_COMPANY_PREFIX_BELARUS_RANGE},
    {482, 482, GS1_COMPANY_PREFIX_UKRAINE_RANGE},
    {483, 483, GS1_COMPANY_PREFIX_TURKMENISTAN_RANGE},
    {484, 484, GS1_COMPANY_PREFIX_MOLDOVA_RANGE},
    {485, 485, GS1_COMPANY_PREFIX_ARMENIA_RANGE},
    {486, 486, GS1_COMPANY_PREFIX_GEORGIA_RANGE},
    {487, 487, GS1_COMPANY_PREFIX_KAZAKSTAN_RANGE},
    {488, 488, GS1_COMPANY_PREFIX_TAJIKISTAN_RANGE},
    {489, 489, GS1_COMPANY_PREFIX_HONG_KONG_RANGE},
    {490, 499, GS1_COMPANY_PREFIX_JAPAN_RANGE},
    {500, 509, GS1_COMPANY_PREFIX_UK_RANGE},
    {520, 521, GS1_COMPANY_PREFIX_GREECE_RANGE},
    {528, 528, GS1_COMPANY_PREFIX_LEBANON_RANGE},
    {529, 529, GS1_COMPANY_PREFIX_CYPRUS_RANGE},
    {530, 530, GS1_COMPANY_PREFIX_ALBANIA_RANGE},
    {531, 531, GS1_COMPANY_PREFIX_MACEDONIA_RANGE},
    {535, 535, GS1_COMPANY_PREFIX_MALTA_RANGE},
    {539, 539, GS1_COMPANY_PREFIX_IRELAND_RANGE},
    {540, 549, GS1_COMPANY_PREFIX_BELGIUM_LUXEMBOURG_RANGE},
    {560, 560, GS1_COMPANY_PREFIX_PORTUGAL_RANGE},
    {569, 569, GS1_COMPANY_PREFIX_ICELAND_RANGE},
    {570, 579, GS1_COMPANY_PREFIX_DENMARK_RANGE},
    {590, 590, GS1_COMPANY_PREFIX_POLAND_RANGE},
    {594, 594, GS1_COMPANY_PREFIX_ROMANIA_RANGE},
    {599, 599, GS1_COMPANY_PREFIX_HUNGARY_RANGE},
    {600, 601, GS1_COMPANY_PREFIX_SOUTH_AFRICA_RANGE},
    {603, 603, GS1_COMPANY_PREFIX_GHANA_RANGE},
    {604, 604, GS1_COMPANY_PREFIX_SENEGAL_RANGE},
    {605, 605, GS1_COMPANY_PREFIX_UGANDA_RANGE},
    {606, 606, GS1_COMPANY_PREFIX_ANGOLA_RANGE},
    {607, 607, GS1_COMPANY_PREFIX_OMAN_RANGE},
    {608, 608, GS1_COMPANY_PREFIX_BAHRAIN_RANGE},
    {609, 609, GS1_COMPANY_PREFIX_MAURITIUS_RANGE},
    {610, 610, GS1_PREFIX_GLOBAL_OFFICE},
    {611, 611, GS1_COMPANY_PREFIX_MOROCCO_RANGE},
    {613, 613, GS1_COMPANY_PREFIX_ALGERIA_RANGE},
    {614, 614, GS1_PREFIX_GLOBAL_OFFICE},
    {615, 615, GS1_COMPANY_PREFIX_NIGERIA_RANGE},
    {616, 616, GS1_COMPANY_PREFIX_KENYA_RANGE},
    {617, 617, GS1_COMPANY_PREFIX_CAMEROON_RANGE},
    {618, 618, GS1_COMPANY_PREFIX_COTE_DIVOIRE_RANGE},
    {619, 619, GS1_COMPANY_PREFIX_TUNISIA_RANGE},
    {620, 620, GS1_COMPANY_PREFIX_TANZANIA_RANGE},
    {621, 621, GS1_COMPANY_PREFIX_SYRIA_RANGE},
    {622, 622, GS1_COMPANY_PREFIX_EGYPT_RANGE},
    {623, 623, GS1_PREFIX_GLOBAL_OFFICE},
    {624, 624, GS1_COMPANY_PREFIX_LIBYA_RANGE},
    {625, 625, GS1_COMPANY_PREFIX_JORDAN_RANGE},
    {626, 626, GS1_COMPANY_PREFIX_IRAN_RANGE},
    {627, 627, GS1_COMPANY_PREFIX_KUWAIT_RANGE},
    {628, 628, GS1_COMPANY_PREFIX_SAUDI_ARABIA_RANGE},
    {629, 629, GS1_COMPANY_PREFIX_EMIRATES_RANGE},
    {630, 630, GS1_COMPANY_PREFIX_QATAR_RANGE},
    {631, 631, GS1_COMPANY_PREFIX_NAMIBIA_RANGE},
    {632, 632, GS1_COMPANY_PREFIX_RWANDA_RANGE},
    {640, 649, GS1_COMPANY_PREFIX_FINLAND_RANGE},
    {680, 681, GS1_COMPANY_PREFIX_CHINA_RANGE},
    {690, 699, GS1_COMPANY_PREFIX_CHINA_RANGE},
    {700, 709, GS1_COMPANY_PREFIX_NORWAY_RANGE},
    {729, 729, GS1_COMPANY_PREFIX_ISRAEL_RANGE},
    {730, 739, GS1_COMPANY_PREFIX_SWEDEN_RANGE},
    {740, 740, GS1_COMPANY_PREFIX_GUATEMALA_RANGE},
    {741, 741, GS1_COMPANY_PREFIX_EL_SALVADOR_RANGE},
    {742, 742, GS1_COMPANY_PREFIX_HONDURAS_RANGE},
    {743, 743, GS1_COMPANY_PREFIX_NICARAGUA_RANGE},
    {744, 744, GS1_COMPANY_PREFIX_COSTA_RICA_RANGE},
    {745, 745, GS1_COMPANY_PREFIX_PANAMA_RANGE},
    {746, 746, GS1_COMPANY_PREFIX_REPUBLICA_DOMINICANA_RANGE},
    {750, 750, GS1_COMPANY_PREFIX_MEXICO_RANGE},
    {754, 755, GS1_COMPANY_PREFIX_CANADA_RANGE},
    {758, 758, GS1_PREFIX_GLOBAL_OFFICE},
    {759, 759, GS1_COMPANY_PREFIX_VENEZUELA_RANGE},
    {760, 769, GS1_COMPANY_PREFIX_SWITZERLAND_RANGE},
    {770, 771, GS1_COMPANY_PREFIX_COLOMBIA_RANGE},
    {773, 773, GS1_COMPANY_PREFIX_URUGUAY_RANGE},
    {775, 775, GS1_COMPANY_PREFIX_PERU_RANGE},
    {777, 777, GS1_COMPANY_PREFIX_BOLIVIA_RANGE},
    {778, 779, GS1_COMPANY_PREFIX_ARGENTINA_RANGE},
    {780, 780, GS1_COMPANY_PREFIX_CHILE_RANGE},
    {784, 784, GS1_COMPANY_PREFIX_PARAGUAY_RANGE},
    {786, 786, GS1_COMPANY_PREFIX_ECUADOR_RANGE},
    {789, 790, GS1_COMPANY_PREFIX_BRASIL_RANGE},
    {800, 839, GS1_COMPANY_PREFIX_ITALY_RANGE},
    {840, 849, GS1_COMPANY_PREFIX_SPAIN_RANGE},
    {850, 850, GS1_COMPANY_PREFIX_CUBA_RANGE},
    {858, 858, GS1_COMPANY_PREFIX_SLOVAKIA_RANGE},
    {859, 859, GS1_COMPANY_PREFIX_CZECH_RANGE},
    {860, 860, GS1_COMPANY_PREFIX_SERBIA_RANGE},
    {865, 865, GS1_COMPANY_PREFIX_MONGOLIA_RANGE},
    {867, 867, GS1_COMPANY_PREFIX_NORTH_KOREA_RANGE},
    {868, 869, GS1_COMPANY_PREFIX_TURKIYE_RANGE},
    {870, 879, GS1_COMPANY_PREFIX_NETHERLANDS_RANGE},
    {880, 881, GS1_COMPANY_PREFIX_SOUTH_KOREA_RANGE},
    {883, 883, GS1_COMPANY_PREFIX_MYANMAR_RANGE},
    {884, 884, GS1_COMPANY_PREFIX_CAMBODIA_RANGE},
    {887, 887, GS1_COMPANY_PREFIX_LAOS_RANGE},
    {885, 885, GS1_COMPANY_PREFIX_THAILAND_RANGE},
    {888, 888, GS1_COMPANY_PREFIX_SINGAPORE_RANGE},
    {890, 890, GS1_COMPANY_PREFIX_INDIA_RANGE},
    {893, 893, GS1_COMPANY_PREFIX_VIETNAM_RANGE},
    {894, 894, GS1_PREFIX_GLOBAL_OFFICE},
    {896, 896, GS1_COMPANY_PREFIX_PAKISTAN_RANGE},
    {899, 899, GS1_COMPANY_PREFIX_INDONESIA_RANGE},
    {900, 919, GS1_COMPANY_PREFIX_AUSTRIA_RANGE},
    {930, 939, GS1_COMPANY_PREFIX_AUSTRALIA_RANGE},
    {940, 949, GS1_COMPANY_PREFIX_NEW_ZEALAND_RANGE},
    {951, 951, GS1_PREFIX_GLOBAL_OFFICE},
    {952, 952, GS1_PREFIX_DEMONSTRATION},
    {955, 955, GS1_COMPANY_PREFIX_MALAYSIA_RANGE},
    {958, 958, GS1_COMPANY_PREFIX_MACAU_RANGE},
    {959, 959, GS1_COMPANY_PREFIX_TAIWAN_RANGE},
    {960, 969, GS1_PREFIX_GLOBAL_OFFICE},
    {977, 977, GS1_COMPANY_PREFIX_SERIAL_PUBLICATION_RANGE},
    {978, 979, GS1_PREFIX_BOOKLAND},
    {980, 980, GS1_COMPANY_PREFIX_REFUND_RECEIPT_RANGE},
    {981, 983, GS1_PREFIX_COUPON},
    {984, 989, GS1_PREFIX_UNUSED},
    {990, 999, GS1_PREFIX_COUPON},
};


// Lookup the range description for a given prefix in the specified prefix array
static GS1Prefix lookup_range(int prefix, const struct prefix_range *prefix_array, size_t array_size) {
    for (size_t i = 0; i < array_size; i++) {
        if (prefix >= prefix_array[i].low && prefix <= prefix_array[i].high) {
            return prefix_array[i].prefix;
        }
    }
    return GS1_PREFIX_NOT_FOUND; // Not found
}


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
static int is_gtin_length(int length) {
    return length == GTIN_8_LENGTH || length == GTIN_12_LENGTH || length == GTIN_13_LENGTH || length == GTIN_14_LENGTH;
}

// Checks if a character is a valid GTIN digit (0-9)
static int is_gtin_digit(char c) {
    return c >= '0' && c <= '9';
}
 

// Cast the first n characters to an integer, returning the integer value
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


static void set_prefix(GTIN *gt) {

    const struct prefix_range *prefix_array;
    size_t array_size;
    int prefix_start, prefix_length, number_of_range_digits;
    switch (gt->format) {
        case GTIN_8_FORMAT:
            prefix_start = 6;
            prefix_length = 3;
            number_of_range_digits = 3;
            prefix_array = gtin8_prefix;
            array_size = sizeof(gtin8_prefix) / sizeof(gtin8_prefix[0]);
            break;
        case GTIN_12_FORMAT:
            prefix_start = 2;
            prefix_length = 7;
            number_of_range_digits = 4;
            prefix_array = upc_prefix;
            array_size = sizeof(upc_prefix) / sizeof(upc_prefix[0]);
            break;
        case GTIN_13_FORMAT:
        case GTIN_14_FORMAT:
            prefix_start = 1;
            prefix_length = 8;
            number_of_range_digits = 3;
            prefix_array = gs1_prefix;
            array_size = sizeof(gs1_prefix) / sizeof(gs1_prefix[0]);
            break;
        default:
            gt->prefix = GS1_PREFIX_NOT_FOUND; // Unknown format
            gt->prefix_digits[0] = '\0'; // Empty prefix digits
            return;
    }
    sublcpy(gt->prefix_digits, gt->digits, prefix_start, prefix_length); 
    int prefix_value = dtio(gt->prefix_digits, number_of_range_digits); 
    gt->prefix = lookup_range(prefix_value, prefix_array, array_size); 
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


static GtinFormat get_format(const char *digits, int length) {

    if (length == GTIN_12_LENGTH) 
        return GTIN_12_FORMAT;
    
    if (length == GTIN_13_LENGTH) 
        return GTIN_13_FORMAT;

    if (length == GTIN_8_LENGTH)
        return GTIN_8_FORMAT;

    if (length == GTIN_14_LENGTH) {
        if (starts_with(digits, "000000"))
            // Six consecutive leading zeros indicate a GTIN-8 format
            return GTIN_8_FORMAT; 

        if (starts_with(digits, "00"))
            // Two leading zeros indicate a GTIN-12 format
            return GTIN_12_FORMAT; 

        if (starts_with(digits, "0"))
            // One leading zero indicates a GTIN-13 format
            return GTIN_13_FORMAT; 
        
        return GTIN_14_FORMAT;
    }

    return GTIN_UNKNOWN_FORMAT; // Invalid length
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

    if (!is_gtin_length(length)) {
        return GTIN_ERR_INVALID_LEN; // Invalid length
    }
    zerofill(gt->digits, s, length, GTIN_MAX_LENGTH); // Zero-fill to 14 characters
    
    // Determine the GTIN format based on the length and leading zeros
    gt->format = get_format(gt->digits, length);

    // Check the validity of the check digit
    int cd = GTIN_CalculateCheckDigit(s, length - 1); 
    if (cd != s[length - 1]) {
        return GTIN_ERR_BAD_CHECKSUM; // Invalid check digit
    }
    gt->check_digit = cd;

    set_prefix(gt);

    return GTIN_OK; // Successfully parsed GTIN
}

// Returns GTIN error as a string
char* GTIN_ErrorStr(GtinError err) {
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

char* GTIN_FormatStr(GtinFormat fmt) {
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

char* GTIN_PrefixStr(GS1Prefix prefix) {
    switch (prefix) {
        case GS1_PREFIX_NOT_APPLICABLE: return "GS1_PREFIX_NOT_APPLICABLE";
        case GS1_PREFIX_NOT_FOUND: return "GS1_PREFIX_NOT_FOUND";
        case GS1_PREFIX_COUPON: return "GS1_PREFIX_COUPON";
        case GS1_PREFIX_DEMONSTRATION: return "GS1_PREFIX_DEMONSTRATION";
        case GS1_PREFIX_GTIN_8: return "GS1_PREFIX_GTIN_8";
        case GS1_PREFIX_REFUND_RECEIPT: return "GS1_PREFIX_REFUND_RECEIPT";
        case GS1_PREFIX_RESERVED: return "GS1_PREFIX_RESERVED";
        case GS1_PREFIX_RESTRICTED_CIRCULATION: return "GS1_PREFIX_RESTRICTED_CIRCULATION";
        case GS1_PREFIX_SERIAL_PUBLICATION: return "GS1_PREFIX_SERIAL_PUBLICATION";
        case GS1_PREFIX_UNUSED: return "GS1_PREFIX_UNUSED";
        case GS1_PREFIX_UPC: return "GS1_PREFIX_UPC";
        case GS1_PREFIX_BOOKLAND: return "GS1_PREFIX_BOOKLAND";
        case GS1_PREFIX_GLOBAL_OFFICE: return "GS1_PREFIX_GLOBAL_OFFICE";

        // Members of the GS1 Company Prefix range
        case GS1_COMPANY_PREFIX_ALBANIA_RANGE: return "Albania";
        case GS1_COMPANY_PREFIX_ALGERIA_RANGE: return "Algeria";
        case GS1_COMPANY_PREFIX_ANGOLA_RANGE: return "Angola";
        case GS1_COMPANY_PREFIX_ARGENTINA_RANGE: return "Argentina";
        case GS1_COMPANY_PREFIX_ARMENIA_RANGE: return "Armenia";
        case GS1_COMPANY_PREFIX_AUSTRALIA_RANGE: return "Australia";
        case GS1_COMPANY_PREFIX_AUSTRIA_RANGE: return "Austria";
        case GS1_COMPANY_PREFIX_AZERBAIJAN_RANGE: return "Azerbaijan";
        case GS1_COMPANY_PREFIX_BAHRAIN_RANGE: return "Bahrain";
        case GS1_COMPANY_PREFIX_BELARUS_RANGE: return "Belarus";
        case GS1_COMPANY_PREFIX_BELGIUM_LUXEMBOURG_RANGE: return "Belgium/Luxembourg";
        case GS1_COMPANY_PREFIX_BOLIVIA_RANGE: return "Bolivia";
        case GS1_COMPANY_PREFIX_BOSNIA_HERZEGOVINA_RANGE: return "Bosnia and Herzegovina";
        case GS1_COMPANY_PREFIX_BRASIL_RANGE: return "Brasil";
        case GS1_COMPANY_PREFIX_BULGARIA_RANGE: return "Bulgaria";
        case GS1_COMPANY_PREFIX_CAMBODIA_RANGE: return "Cambodia";
        case GS1_COMPANY_PREFIX_CAMEROON_RANGE: return "Cameroon";
        case GS1_COMPANY_PREFIX_CANADA_RANGE: return "Canada";
        case GS1_COMPANY_PREFIX_CHILE_RANGE: return "Chile";
        case GS1_COMPANY_PREFIX_CHINA_RANGE: return "China";
        case GS1_COMPANY_PREFIX_CHINESE_TAIPEI_RANGE: return "Chinese Taipei";
        case GS1_COMPANY_PREFIX_COLOMBIA_RANGE: return "Colombia";
        case GS1_COMPANY_PREFIX_COSTA_RICA_RANGE: return "Costa Rica";
        case GS1_COMPANY_PREFIX_COTE_DIVOIRE_RANGE: return "Côte d'Ivoire";
        case GS1_COMPANY_PREFIX_CROATIA_RANGE: return "Croatia";
        case GS1_COMPANY_PREFIX_CUBA_RANGE: return "Cuba";
        case GS1_COMPANY_PREFIX_CYPRUS_RANGE: return "Cyprus";
        case GS1_COMPANY_PREFIX_CZECH_RANGE: return "Czech Republic";
        case GS1_COMPANY_PREFIX_DENMARK_RANGE: return "Denmark";
        case GS1_COMPANY_PREFIX_ECUADOR_RANGE: return "Ecuador";
        case GS1_COMPANY_PREFIX_EGYPT_RANGE: return "Egypt";
        case GS1_COMPANY_PREFIX_EL_SALVADOR_RANGE: return "El Salvador";
        case GS1_COMPANY_PREFIX_EMIRATES_RANGE: return "United Arab Emirates";
        case GS1_COMPANY_PREFIX_ESTONIA_RANGE: return "Estonia";
        case GS1_COMPANY_PREFIX_FINLAND_RANGE: return "Finland";
        case GS1_COMPANY_PREFIX_FRANCE_RANGE: return "France";
        case GS1_COMPANY_PREFIX_GEORGIA_RANGE: return "Georgia";
        case GS1_COMPANY_PREFIX_GHANA_RANGE: return "Ghana";        
        case GS1_COMPANY_PREFIX_GREECE_RANGE: return "Greece";
        case GS1_COMPANY_PREFIX_GUATEMALA_RANGE: return "Guatemala";
        case GS1_COMPANY_PREFIX_HONDURAS_RANGE: return "Honduras";
        case GS1_COMPANY_PREFIX_HONG_KONG_RANGE: return "Hong Kong";
        case GS1_COMPANY_PREFIX_HUNGARY_RANGE: return "Hungary";
        case GS1_COMPANY_PREFIX_ICELAND_RANGE: return "Iceland";
        case GS1_COMPANY_PREFIX_INDIA_RANGE: return "India";
        case GS1_COMPANY_PREFIX_INDONESIA_RANGE: return "Indonesia";
        case GS1_COMPANY_PREFIX_IRAN_RANGE: return "Iran";
        case GS1_COMPANY_PREFIX_IRELAND_RANGE: return "Ireland";
        case GS1_COMPANY_PREFIX_ISRAEL_RANGE: return "Israel";
        case GS1_COMPANY_PREFIX_ITALY_RANGE: return "Italy";
        case GS1_COMPANY_PREFIX_JAPAN_RANGE: return "Japan";
        case GS1_COMPANY_PREFIX_JORDAN_RANGE: return "Jordan";
        case GS1_COMPANY_PREFIX_KAZAKSTAN_RANGE: return "Kazakhstan";
        case GS1_COMPANY_PREFIX_KENYA_RANGE: return "Kenya";
        case GS1_COMPANY_PREFIX_KOSOVO_RANGE: return "Kosovo";
        case GS1_COMPANY_PREFIX_KUWAIT_RANGE: return "Kuwait";
        case GS1_COMPANY_PREFIX_KYRGYZSTAN_RANGE: return "Kyrgyzstan";
        case GS1_COMPANY_PREFIX_LAOS_RANGE: return "Laos";
        case GS1_COMPANY_PREFIX_LATVIA_RANGE: return "Latvia";
        case GS1_COMPANY_PREFIX_LEBANON_RANGE: return "Lebanon";
        case GS1_COMPANY_PREFIX_LIBYA_RANGE: return "Libya";
        case GS1_COMPANY_PREFIX_LITHUANIA_RANGE: return "Lithuania";
        case GS1_COMPANY_PREFIX_MACAU_RANGE: return "Macau";
        case GS1_COMPANY_PREFIX_MACEDONIA_RANGE: return "Macedonia";
        case GS1_COMPANY_PREFIX_MALAYSIA_RANGE: return "Malaysia";
        case GS1_COMPANY_PREFIX_MALTA_RANGE: return "Malta";
        case GS1_COMPANY_PREFIX_MAURITIUS_RANGE: return "Mauritius";
        case GS1_COMPANY_PREFIX_MEXICO_RANGE: return "Mexico";
        case GS1_COMPANY_PREFIX_MOLDOVA_RANGE: return "Moldova";
        case GS1_COMPANY_PREFIX_MONGOLIA_RANGE: return "Mongolia";
        case GS1_COMPANY_PREFIX_MONTENEGRO_RANGE: return "Montenegro";
        case GS1_COMPANY_PREFIX_MOROCCO_RANGE: return "Morocco";
        case GS1_COMPANY_PREFIX_NETHERLANDS_RANGE: return "Netherlands";
        case GS1_COMPANY_PREFIX_NEW_ZEALAND_RANGE: return "New Zealand";
        case GS1_COMPANY_PREFIX_NICARAGUA_RANGE: return "Nicaragua";
        case GS1_COMPANY_PREFIX_NIGERIA_RANGE: return "Nigeria";
        case GS1_COMPANY_PREFIX_NORTH_KOREA_RANGE: return "North Korea";
        case GS1_COMPANY_PREFIX_NORWAY_RANGE: return "Norway";
        case GS1_COMPANY_PREFIX_OMAN_RANGE: return "Oman";
        case GS1_COMPANY_PREFIX_PAKISTAN_RANGE: return "Pakistan"; 
        case GS1_COMPANY_PREFIX_PARAGUAY_RANGE: return "Paraguay";
        case GS1_COMPANY_PREFIX_PERU_RANGE: return "Peru";
        case GS1_COMPANY_PREFIX_POLAND_RANGE: return "Poland";
        case GS1_COMPANY_PREFIX_PORTUGAL_RANGE: return "Portugal";
        case GS1_COMPANY_PREFIX_QATAR_RANGE: return "Qatar";
        case GS1_COMPANY_PREFIX_ROMANIA_RANGE: return "Romania";
        case GS1_COMPANY_PREFIX_RUSSIA_RANGE: return "Russia";
        case GS1_COMPANY_PREFIX_RWANDA_RANGE: return "Rwanda";
        case GS1_COMPANY_PREFIX_SAUDI_ARABIA_RANGE: return "Saudi Arabia";
        case GS1_COMPANY_PREFIX_SERBIA_RANGE: return "Serbia";
        case GS1_COMPANY_PREFIX_SINGAPORE_RANGE: return "Singapore";
        case GS1_COMPANY_PREFIX_SLOVAKIA_RANGE: return "Slovakia";
        case GS1_COMPANY_PREFIX_SLOVENIJA_RANGE: return "Slovenija";
        case GS1_COMPANY_PREFIX_SOUTH_AFRICA_RANGE: return "South Africa";
        case GS1_COMPANY_PREFIX_SOUTH_KOREA_RANGE: return "South Korea";
        case GS1_COMPANY_PREFIX_SPAIN_RANGE: return "Spain";
        case GS1_COMPANY_PREFIX_SRI_LANKA_RANGE: return "Sri Lanka";
        case GS1_COMPANY_PREFIX_SWEDEN_RANGE: return "Sweden";
        case GS1_COMPANY_PREFIX_SWITZERLAND_RANGE: return "Switzerland";
        case GS1_COMPANY_PREFIX_TAIWAN_RANGE: return "Taiwan";
        case GS1_COMPANY_PREFIX_TANZANIA_RANGE: return "Tanzania";
        case GS1_COMPANY_PREFIX_THAILAND_RANGE: return "Thailand";
        case GS1_COMPANY_PREFIX_TUNISIA_RANGE: return "Tunisia";
        case GS1_COMPANY_PREFIX_TURKIYE_RANGE: return "Türkiye";
        case GS1_COMPANY_PREFIX_TURKMENISTAN_RANGE: return "Turkmenistan";
        case GS1_COMPANY_PREFIX_UK_RANGE: return "United Kingdom";
        case GS1_COMPANY_PREFIX_UKRAINE_RANGE: return "Ukraine";
        case GS1_COMPANY_PREFIX_URUGUAY_RANGE: return "Uruguay";
        case GS1_COMPANY_PREFIX_UZBEKISTAN_RANGE: return "Uzbekistan";
        case GS1_COMPANY_PREFIX_VENEZUELA_RANGE: return "Venezuela";
        case GS1_COMPANY_PREFIX_VIETNAM_RANGE: return "Vietnam";
        default: return "Unknown";
    }
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
