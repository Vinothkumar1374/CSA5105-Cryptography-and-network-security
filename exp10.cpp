#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies in a string
void calculateFrequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            frequencies[c - 'a']++;
        }
    }
}

// Function to perform additive decryption
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = tolower(ciphertext[i]);
        if (isalpha(c)) {
            char decrypted = 'a' + (c - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            if (isupper(ciphertext[i])) {
                decrypted = toupper(decrypted);
            }
            plaintext[i] = decrypted;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to print the top N possible plaintexts
void printTopPlaintexts(const char *ciphertext, int *frequencies, int topN) {
    char plaintext[1000];
    
    // Create a copy of the ciphertext
    char copy[1000];
    strcpy(copy, ciphertext);

    // Sort letters by frequency in descending order
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequencies[j] > frequencies[i]) {
                // Swap frequencies
                int tempFreq = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = tempFreq;

                // Swap letters
                char tempChar = copy[i];
                copy[i] = copy[j];
                copy[j] = tempChar;
            }
        }
    }

    // Print the top N possible plaintexts
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        int shift = copy[i] - 'e';
        decrypt(ciphertext, shift, plaintext);
        printf("Shift %d: %s\n", shift, plaintext);
    }
}

int main() {
    char ciphertext[1000];

    // Get the ciphertext from the user
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Initialize letter frequencies
    int frequencies[ALPHABET_SIZE] = {0};

    // Calculate frequencies
    calculateFrequencies(ciphertext, frequencies);

    // Print letter frequencies
    printf("Letter frequencies in the ciphertext:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'a' + i, frequencies[i]);
    }

    // Get the user's choice for the top N plaintexts
    int topN;
    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &topN);

    // Print the top N possible plaintexts
    printTopPlaintexts(ciphertext, frequencies, topN);

    return 0;
}

