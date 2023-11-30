#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MOD 26

int determinant(int a, int b, int c, int d) {
    return (a * d - b * c + MOD) % MOD;
}

int modInverse(int a, int m) {
    for (int i = 1; i < m; ++i) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

void inverseMatrix(int matrix[2][2], int inverse[2][2]) {
    int det = determinant(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);

    int invDet = modInverse(det, MOD);

    inverse[0][0] = (matrix[1][1] * invDet) % MOD;
    inverse[0][1] = ((-1 * matrix[0][1]) * invDet + MOD) % MOD;
    inverse[1][0] = ((-1 * matrix[1][0]) * invDet + MOD) % MOD;
    inverse[1][1] = (matrix[0][0] * invDet) % MOD;
}

void hillCipherEncrypt(char plaintext[], int key[2][2]) {
    int length = strlen(plaintext);
    int ciphertext[length];

    for (int i = 0; i < length; i += 2) {
        int x = plaintext[i] - 'A';
        int y = (i + 1 < length) ? plaintext[i + 1] - 'A' : 'X' - 'A'; 

        ciphertext[i] = (key[0][0] * x + key[0][1] * y) % MOD;
        ciphertext[i + 1] = (key[1][0] * x + key[1][1] * y) % MOD;
    }

    printf("Encrypted message: ");
    for (int i = 0; i < length; ++i) {
        printf("%c", ciphertext[i] + 'A');
    }
    printf("\n");
}

int main() {
    char plaintext[100];
    int key[2][2];

    printf("Enter the key matrix (4 integers): ");
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            scanf("%d", &key[i][j]);
        }
    }

    printf("Enter the plaintext (in uppercase): ");
    scanf("%s", plaintext);

    int inverseKey[2][2];
    inverseMatrix(key, inverseKey);

    hillCipherEncrypt(plaintext, key);

    return 0;
}
