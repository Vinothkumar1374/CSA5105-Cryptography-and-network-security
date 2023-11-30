#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void multiplyMatrix(int key[2][2], int message[2], int result[2]) {
    result[0] = (key[0][0] * message[0] + key[0][1] * message[1]) % ALPHABET_SIZE;
    result[1] = (key[1][0] * message[0] + key[1][1] * message[1]) % ALPHABET_SIZE;
}

void hillCipherEncrypt(char *message, int key[2][2]) {
    int len = strlen(message);
    int messageVector[2], resultVector[2];

    printf("Encrypted message: ");

    for (int i = 0; i < len; i += 2) {
        // Convert pairs of letters to numerical values (0-25)
        messageVector[0] = message[i] - 'a';
        messageVector[1] = message[i + 1] - 'a';

        // Multiply the key matrix with the message vector
        multiplyMatrix(key, messageVector, resultVector);

        // Convert back to letters
        printf("%c%c", resultVector[0] + 'a', resultVector[1] + 'a');
    }

    printf("\n");
}

int main() {
    // Given key matrix
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    // Given message
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";

    // Perform encryption
    hillCipherEncrypt(message, key);

    return 0;
}

