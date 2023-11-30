#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If modular inverse doesn't exist
}

int main() {
    // Provided information
    int mostFrequent = 'B' - 'A';
    int secondMostFrequent = 'U' - 'A';
    
    // Calculate keys a and b
    int a, b;
    int modInverseResult = modInverse(mostFrequent, 26);
    
    if (modInverseResult == -1) {
        printf("Error: Modular inverse does not exist.\n");
        return 1;
    } else {
        a = (secondMostFrequent - mostFrequent + 26) * modInverseResult % 26;
        b = (secondMostFrequent - a * mostFrequent + 26) % 26;
    }

    printf("Keys found: a=%d, b=%d\n", a, b);

    return 0;
}

