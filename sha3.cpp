#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SHA3_ROUNDS 24
#define STATE_SIZE 1600 // 5x5 matrix, each lane is 64 bits

// SHA-3 constants
const uint64_t RC[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
    0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001
};

// Function to perform Keccak-p permutation
void keccakp(uint64_t state[STATE_SIZE]) {
    for (int round = 0; round < SHA3_ROUNDS; ++round) {
        // Theta
        uint64_t C[5], D[5];
        for (int x = 0; x < 5; ++x) {
            C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];
        }
        for (int x = 0; x < 5; ++x) {
            D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> 63));
            for (int y = 0; y < 5; ++y) {
                state[x + 5 * y] ^= D[x];
            }
        }

        // Rho and Pi
        uint64_t tmp, current = state[1];
        int x = 0, y = 1;
        for (int t = 0; t < 24; ++t) {
            uint64_t prev = current;
            x = y;
            y = (2 * x + 3 * y) % 5;
            current = state[x + 5 * y];
            state[x + 5 * y] = ((prev << ((t + 1) * (t + 2) / 2)) | (prev >> (64 - (t + 1) * (t + 2) / 2)));
        }

        // Chi
        for (y = 0; y < 5; ++y) {
            for (x = 0; x < 5; ++x) {
                C[x] = state[x + 5 * y];
            }
            for (x = 0; x < 5; ++x) {
                state[x + 5 * y] ^= (~C[(x + 1) % 5] & C[(x + 2) % 5]);
            }
        }

        // Iota
        state[0] ^= RC[round];
    }
}

int main() {
    uint64_t state[STATE_SIZE] = {0}; // Initialize the state matrix with zeros
    int rounds = 0;

    // Continue until all lanes in the capacity portion have at least one nonzero bit
    while (1) {
        keccakp(state);
        ++rounds;

        // Check if all lanes in the capacity portion have at least one nonzero bit
        int allNonzero = 1;
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y < 5; ++y) {
                if (y < 2 && state[x + 5 * y] == 0) {
                    allNonzero = 0;
                    break;
                }
            }
        }

        if (allNonzero) {
            break;
        }
    }

    // Print the number of rounds required
    printf("Number of rounds needed: %d\n", rounds);

    return 0;
}

