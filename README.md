# GS1 GTIN Validation in C99

This repository provides a C99 implementation for validating GS1 GTINs (Global Trade Item Numbers). The implementation includes functions for calculating check digits, copying prefixes, and initializing GTIN structures.

The GS1 GTIN (Global Trade Item Number) is a unique identifier for trade items, developed by 
GS1. The general specification for GTINs can be found in the GS1 General Specifications document, which is available at [GS1 General Specifications](https://www.gs1.org/standards/barcodes-epcrfid-id-keys/gs1-general-specifications).

## The GTIN CLI

The GTIN CLI is a command-line interface tool that allows users to validate GTINs directly from the terminal.

```bash
Usage: gtin [OPTIONS] <GTIN>
Options:
  -h, --help            Show this help message and exit
  -v, --verbose         Show detailed output (default: show GTIN only)
  -s, --skip-invalid    Skip invalid GTINs and continue processing
  -                     Read GTINs from standard input (stdin)
```

## GTIN Formats

Here are the different GTIN formats:

### GTIN-8

GTIN-8 is a compact GTIN format used for small items. It has the following characteristics:

* Has 8 digits.
* The first 7 digits are the data digits, and the last digit is the check digit.
* The first 3 digits are the prefix.

### GTIN-12

GTIN-12 is commonly used in North America and is also known as UPC-A. It has the following characteristics:

* Has 12 digits.
* The first 11 digits are the data digits, and the last digit is the check digit.
* The first 7 digits are the prefix.

### GTIN-13

GTIN-13 is the most widely used GTIN format and is also known as EAN-13. It has the following characteristics:

* Has 13 digits.
* The first 12 digits are the data digits, and the last digit is the check digit.
* The first 8 digits are the prefix.

## GTIN-14

GTIN-14 is used for grouping trade items and has the following characteristics:

* Has 14 digits.
* The first 13 digits are the data digits, and the last digit is the check digit.
* If the GTIN-14 has leading zeros, it can represent a GTIN-8, GTIN-12, or GTIN-13. 

## Check Digit Calculation

1. Calculate the length of the GTIN (excluding the check digit): **length**
2. Set the **weight (w)** to 3 if length is even, or 1 if length is odd.
3. Initialize a **sum** variable to 0.
4. For each digit in the GTIN (excluding the check digit), do the following:
   - Convert the character to an integer.
   - Multiply the digit by the weight (w) and add it to the sum.
   - Alternate the **weight (w)** between 3 and 1 for each digit.
5. Calculate the check digit as follows:
   - If the **sum** modulo 10 is 0, the check digit is 0.
   - Otherwise, the check digit is 10 minus (**sum** modulo 10).
