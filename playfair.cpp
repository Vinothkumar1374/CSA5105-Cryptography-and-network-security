#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the key
void prepareKey(char key[], char *keyMatrix) {
    int i, j, k, flag = 0;
    char tempKey[26] = {0};

    // Convert the key to uppercase
    for (i = 0; i < strlen(key); ++i) {
        if (key[i] == 'j' || key[i] == 'J')
            key[i] = 'I';
        key[i] = toupper(key[i]);
    }

    // Copy the key to tempKey
    j = 0;
    for (i = 0; i < strlen(key); ++i) {
        if (key[i] < 'A' || key[i] > 'Z')
            continue;
        tempKey[j++] = key[i];
    }

    // Eliminate duplicates
    for (i = 0; i < strlen(tempKey); ++i) {
        if (tempKey[i] == 'J')
            tempKey[i] = 'I';
        for (j = i + 1; j < strlen(tempKey); ++j) {
            if (tempKey[i] == tempKey[j]) {
                for (k = j; k < strlen(tempKey); ++k)
                    tempKey[k] = tempKey[k + 1];
            }
        }
    }

    // Fill the key matrix
    for (i = 0; i < 26; ++i)
        keyMatrix[i] = 0;
    for (i = 0; i < strlen(tempKey); ++i)
        keyMatrix[tempKey[i] - 'A'] = 1;

    // Fill the matrix with the remaining letters
    for (i = 0; i < 26; ++i) {
        if (keyMatrix[i] == 0) {
            keyMatrix[i] = 1;
            tempKey[j++] = (char) ('A' + i);
        }
    }

    j = 0;
    for (i = 0; i < 25; ++i) {
        printf("%c ", tempKey[i]);
        if (j == 4) {
            printf("\n");
            j = 0;
        } else {
            j++;
        }
    }
}

// Function to encrypt using Playfair Cipher
void encrypt(char *text, char *keyMatrix) {
    int i, a, b, c, d;
    for (i = 0; i < strlen(text); i += 2) {
        a = text[i] - 'A';
        b = text[i + 1] - 'A';
        if (a == b) {
            text[i + 1] = 'X';
            b = text[i + 1] - 'A';
        }
        c = a / 5;
        d = a % 5;
        if (c == b / 5) {
            text[i] = keyMatrix[c * 5 + (d + 1) % 5] + 'A';
            text[i + 1] = keyMatrix[c * 5 + (b + 1) % 5] + 'A';
        } else if (d == b % 5) {
            text[i] = keyMatrix[((c + 1) % 5) * 5 + d] + 'A';
            text[i + 1] = keyMatrix[((b + 1) % 5) + c * 5] + 'A';
        } else {
            text[i] = keyMatrix[c * 5 + b % 5] + 'A';
            text[i + 1] = keyMatrix[d + c * 5] + 'A';
        }
    }
}

int main() {
    char key[100], text[100], keyMatrix[26];

    printf("Enter the key: ");
    gets(key);

    // Prepare the key matrix
    printf("\nKey Matrix:\n");
    prepareKey(key, keyMatrix);

    printf("\nEnter the text to encrypt (in uppercase): ");
    gets(text);

    // Pad 'X' at the end if the text length is odd
    if (strlen(text) % 2 != 0) {
        text[strlen(text)] = 'X';
        text[strlen(text) + 1] = '\0';
    }

    // Encrypt the text
    encrypt(text, keyMatrix);

    printf("\nEncrypted text: %s\n", text);

    return 0;
}
