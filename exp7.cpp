#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void computeLetterFrequency(const char *text, int *frequency) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            frequency[c - 'a']++;
        }
    }
}

void decryptWithShift(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char c = tolower(ciphertext[i]);
            char decrypted = ((c - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            plaintext[i] = isupper(ciphertext[i]) ? toupper(decrypted) : decrypted;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[500];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    int frequency[ALPHABET_SIZE] = {0};
    computeLetterFrequency(ciphertext, frequency);
    int maxFreq = 0;
    int maxFreqIndex = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFreq) {
            maxFreq = frequency[i];
            maxFreqIndex = i;
        }
    }
    int shift = (maxFreqIndex + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    printf("Shift value (assuming 'e' in plaintext): %d\n", shift);
    char plaintext[500];
    decryptWithShift(ciphertext, shift, plaintext);
    printf("Plaintext: %s\n", plaintext);
    printf("\nTop 10 possible plaintexts:\n");
    for (int i = 0; i < 10; i++) {
        decryptWithShift(ciphertext, (shift + i) % ALPHABET_SIZE, plaintext);
        printf("%d. %s\n", i + 1, plaintext);
    }

    return 0;
}
