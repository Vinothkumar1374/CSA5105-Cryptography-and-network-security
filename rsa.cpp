#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse using the extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) {
        return 0;
    }

    // Apply extended Euclidean algorithm
    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

int main() {
    // Given public key
    int e = 31;
    int n = 3599;

    // Variables for trial-and-error
    int p, q;

    // Find p and q using trial-and-error
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Calculate f(n) = (p-1)(q-1)
    int phi = (p - 1) * (q - 1);

    // Calculate the private key d using the extended Euclidean algorithm
    int d = modInverse(e, phi);

    // Print the private key
    printf("Private Key (d): %d\n", d);

    return 0;
}

