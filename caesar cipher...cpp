#include <stdio.h>

void encryptCaesar(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
    } 
}

void decryptCaesar(char text[], int shift) {
    
    encryptCaesar(text, 26 - shift);
}

int main() {
    char text[100];
    int shift;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift (1-25): ");
    scanf("%d", &shift);

    encryptCaesar(text, shift);
    printf("Encrypted text: %s\n", text);

    // Reset text for decryption
    encryptCaesar(text, 26 - shift);
    printf("Decrypted text: %s", text);

    return 0;
}
