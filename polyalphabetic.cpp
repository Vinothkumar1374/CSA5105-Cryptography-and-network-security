#include <stdio.h>
#include <string.h>
#include <ctype.h>


void vigenereEncrypt(char *text, char *key, char *encryptedText) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int keyIndex = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char shift = isupper(key[keyIndex]) ? key[keyIndex] - 'A' : key[keyIndex] - 'a';
            encryptedText[i] = (text[i] + shift - (isupper(text[i]) ? 'A' : 'a')) % 26 + (isupper(text[i]) ? 'A' : 'a');
            keyIndex = (keyIndex + 1) % keyLen;
        } else {
            encryptedText[i] = text[i];
        }
    }
    encryptedText[textLen] = '\0';
}


void vigenereDecrypt(char *encryptedText, char *key, char *decryptedText) {
    int textLen = strlen(encryptedText);
    int keyLen = strlen(key);
    int keyIndex = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(encryptedText[i])) {
            char shift = isupper(key[keyIndex]) ? key[keyIndex] - 'A' : key[keyIndex] - 'a';
            decryptedText[i] = (encryptedText[i] - shift - (isupper(encryptedText[i]) ? 'A' : 'a') + 26) % 26 + (isupper(encryptedText[i]) ? 'A' : 'a');
            keyIndex = (keyIndex + 1) % keyLen;
        } else {
            decryptedText[i] = encryptedText[i];
        }
    }
    decryptedText[textLen] = '\0';
}

int main() {
    char text[100], key[100], encryptedText[100], decryptedText[100];

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter the key: ");
    scanf("%s", key);

    vigenereEncrypt(text, key, encryptedText);
    printf("Encrypted text: %s\n", encryptedText);

    vigenereDecrypt(encryptedText, key, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
