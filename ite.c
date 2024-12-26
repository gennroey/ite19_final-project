#include <stdio.h>  // Standard input/output library for file operations and console I/O
#include <string.h> // Library for string manipulation functions like strlen, strcat, etc.
#include <stdlib.h> // Standard library for general-purpose functions like memory allocation

// Function to get the decimal value of a Roman numeral character
int romanToDecimal(char c) {
    switch (c) { // Match the Roman numeral character
        case 'I': return 1;   // 'I' corresponds to 1
        case 'V': return 5;   // 'V' corresponds to 5
        case 'X': return 10;  // 'X' corresponds to 10
        case 'L': return 50;  // 'L' corresponds to 50
        case 'C': return 100; // 'C' corresponds to 100
        case 'D': return 500; // 'D' corresponds to 500
        case 'M': return 1000;// 'M' corresponds to 1000
        default: return 0;    // Return 0 for invalid characters
    }
}

// Function to convert a Roman numeral string to a decimal number
int convertRomanToDecimal(char *roman) {
    int total = 0;                 // Initialize total to store the final decimal number
    int length = strlen(roman);    // Get the length of the Roman numeral string

    for (int i = 0; i < length; i++) {
        int current = romanToDecimal(roman[i]);   // Get the decimal value of the current character
        int next = romanToDecimal(roman[i + 1]); // Get the decimal value of the next character

        if (current < next) {  // If the current value is less than the next (e.g., IV = 4)
            total -= current;  // Subtract the current value from total
        } else {               // Otherwise (e.g., VI = 6)
            total += current;  // Add the current value to total
        }
    }

    return total; // Return the final decimal value
}

// Function to convert a number to its word representation
void numberToWords(int num, char *result) {
    // Arrays for words corresponding to digits, tens, and teens
    const char *ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
    const char *tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    const char *teens[] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

    char temp[500] = ""; // Temporary string to build the word representation

    if (num == 0) { // Special case for zero
        strcpy(result, "Zero");
        return;
    }

    if (num < 0) { // Handle negative numbers
        strcat(temp, "Negative "); // Add "Negative" to the result
        num = -num; // Make the number positive for processing
    }

    if (num / 1000000 > 0) { // If the number is in the millions
        strcat(temp, ones[num / 1000000]); // Add millions place
        strcat(temp, " Million ");
        num %= 1000000; // Remove the millions part
    }

    if (num / 1000 > 0) { // If the number is in the thousands
        int thousands = num / 1000; // Extract thousands part
        if (thousands >= 100) { // Handle hundreds in thousands
            strcat(temp, ones[thousands / 100]);
            strcat(temp, " Hundred ");
            thousands %= 100;
        }
        if (thousands >= 10 && thousands <= 19) { // Handle teens in thousands
            strcat(temp, teens[thousands - 10]);
        } else { // Handle tens and ones in thousands
            if (thousands / 10 > 0) {
                strcat(temp, tens[thousands / 10]);
                if (thousands % 10 > 0) strcat(temp, " ");
            }
            if (thousands % 10 > 0) {
                strcat(temp, ones[thousands % 10]);
            }
        }
        strcat(temp, " Thousand ");
        num %= 1000; // Remove the thousands part
    }

    if (num / 100 > 0) { // If the number has hundreds
        strcat(temp, ones[num / 100]);
        strcat(temp, " Hundred ");
        num %= 100; // Remove the hundreds part
    }

    if (num >= 10 && num <= 19) { // Handle teens
        strcat(temp, teens[num - 10]);
    } else { // Handle tens and ones
        if (num / 10 > 0) {
            strcat(temp, tens[num / 10]);
            if (num % 10 > 0) strcat(temp, " ");
        }
        if (num % 10 > 0) {
            strcat(temp, ones[num % 10]);
        }
    }

    strcpy(result, temp); // Copy the final word representation to the result
}

// Main function
int main() {
    FILE *inputFile = fopen("input.txt", "r");   // Open the input file for reading
    FILE *outputFile = fopen("output.txt", "w"); // Open the output file for writing

    if (!inputFile || !outputFile) { // Check if files were successfully opened
        printf("Error opening files.\n");
        return 1; // Exit with error
    }

    char roman1[100], roman2[100], operator; // Variables to store input Roman numerals and operator
    char wordResult[500]; // Buffer for storing the word result

    // Read input until end of file
    while (fscanf(inputFile, "%s %c %s", roman1, &operator, roman2) != EOF) {
        int num1 = convertRomanToDecimal(roman1); // Convert first Roman numeral to decimal
        int num2 = convertRomanToDecimal(roman2); // Convert second Roman numeral to decimal
        int result = 0; // Initialize result

        switch (operator) { // Perform the operation based on the operator
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            default: // Handle invalid operators
                printf("Invalid operator\n");
                fprintf(outputFile, "Invalid operator\n");
                continue;
        }

        numberToWords(result, wordResult); // Convert the result to words

        // Print the result to the console
        printf("%d %c %d = %d\n", num1, operator, num2, result);

        // Write the word representation to the output file
        fprintf(outputFile, "%s\n", wordResult);
    }

    fclose(inputFile); // Close the input file
    fclose(outputFile); // Close the output file

    printf("Conversion completed. Check 'output.txt' for results.\n");
    return 0; // Exit successfully
}
