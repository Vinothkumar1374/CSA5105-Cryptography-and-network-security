#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to perform modular exponentiation (base^exponent mod modulus)
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    // Common parameters
    unsigned long long q = 23; // Prime modulus
    unsigned long long a = 5;  // Primitive root
    unsigned long long xa, ya, xb, yb; // Secret keys and public keys

    // Alice's secret key and public key
    unsigned long long x = 6; // Alice's secret key
    xa = mod_pow(a, x, q);   // Alice's public key

    // Bob's secret key and public key
    unsigned long long y = 15; // Bob's secret key
    xb = mod_pow(a, y, q);    // Bob's public key

    // Key exchange
    ya = mod_pow(xb, x, q); // Alice computes the shared secret
    yb = mod_pow(xa, y, q); // Bob computes the shared secret

    // Display results
    printf("Alice's Public Key (ya): %llu\n", ya);
    printf("Bob's Public Key (yb): %llu\n", yb);

    return 0;
}

