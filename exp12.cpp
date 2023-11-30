#include <stdio.h>
#include <stdint.h>

// Function to perform a circular left shift on a 28-bit value
uint32_t circularLeftShift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}

// Function to generate 16 round keys for decryption
void generateRoundKeys(uint64_t key, uint32_t roundKeys[16]) {
    // Permutation Choice 1 (PC-1)
    uint64_t permutedKey = 0;
    const int pc1[] = {57, 49, 41, 33, 25, 17, 9,
                       1, 58, 50, 42, 34, 26, 18,
                       10, 2, 59, 51, 43, 35, 27,
                       19, 11, 3, 60, 52, 44, 36,
                       63, 55, 47, 39, 31, 23, 15,
                       7, 62, 54, 46, 38, 30, 22,
                       14, 6, 61, 53, 45, 37, 29,
                       21, 13, 5, 28, 20, 12, 4};

    for (int i = 0; i < 56; i++) {
        permutedKey |= ((key >> (64 - pc1[i])) & 1) << (55 - i);
    }

    // Split into left and right halves
    uint32_t left = permutedKey >> 28;
    uint32_t right = permutedKey & 0x0FFFFFFF;

    // Key schedule for decryption
    for (int i = 0; i < 16; i++) {
        // Perform circular right shifts
        left = circularLeftShift(left, 1);
        right = circularLeftShift(right, 1);

        // Permutation Choice 2 (PC-2)
        const int pc2[] = {14, 17, 11, 24, 1, 5,
                           3, 28, 15, 6, 21, 10,
                           23, 19, 12, 4, 26, 8,
                           16, 7, 27, 20, 13, 2,
                           41, 52, 31, 37, 47, 55,
                           30, 40, 51, 45, 33, 48,
                           44, 49, 39, 56, 34, 53,
                           46, 42, 50, 36, 29, 32};

        uint64_t combined = ((uint64_t)left << 28) | right;
        uint32_t roundKey = 0;

        for (int j = 0; j < 48; j++) {
            roundKey |= ((combined >> (56 - pc2[j])) & 1) << (47 - j);
        }

        roundKeys[15 - i] = roundKey;
    }
}

int main() {
    // Example 64-bit key (for illustration purposes only, DES keys should be kept secret)
    uint64_t key = 0x133457799BBCDFF1;

    // Array to store round keys
    uint32_t roundKeys[16];

    // Generate round keys for decryption
    generateRoundKeys(key, roundKeys);

    // Print the round keys
    printf("Round Keys for Decryption:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%d: %08X\n", i + 1, roundKeys[i]);
    }

    return 0;
}

