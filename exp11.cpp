#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// Function to check if two numbers are coprime
int areCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

// Function to print allowed values of a and limitations on b
void printAllowedValues() {
    printf("Allowed values of a:\n");
    for (int a = 1; a < 26; a++) {
        if (areCoprime(a, 26)) {
            printf("%d ", a);
        }
    }
    printf("\n");

    printf("Limitations on b (b must be coprime with 26):\n");
    for (int b = 1; b < 26; b++) {
        if (areCoprime(b, 26)) {
            printf("%d ", b);
        }
    }
    printf("\n");
}

int main() {
    printf("Affine Caesar Cipher - Allowed Values of a and Limitations on b\n");
    printAllowedValues();

    return 0;
}

