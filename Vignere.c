#include <stdio.h>
#include <string.h>
void vigenere_encrypt(char *plaintext, char *key) {
    int pt_len = strlen(plaintext);
    int key_len = strlen(key);
    char new_key[pt_len];
    for (int i = 0, j = 0; i < pt_len; i++, j = (j + 1) % key_len) {
        new_key[i] = key[j];
    }
    new_key[pt_len] = '\0';
    for (int i = 0; i < pt_len; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = 'a' + (plaintext[i] - 'a' + new_key[i] - 'a') % 26;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = 'A' + (plaintext[i] - 'A' + new_key[i] - 'a') % 26;
        }
    }
}
void vigenere_decrypt(char *ciphertext, char *key) {
    int ct_len = strlen(ciphertext);
    int key_len = strlen(key);

    char new_key[ct_len];
    for (int i = 0, j = 0; i < ct_len; i++, j = (j + 1) % key_len) {
        new_key[i] = key[j];
    }
    new_key[ct_len] = '\0';
    for (int i = 0; i < ct_len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = 'a' + (ciphertext[i] - new_key[i] + 26) % 26;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = 'A' + (ciphertext[i] - new_key[i] + 26) % 26;
        }
    }
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    strcpy(ciphertext, plaintext);
    vigenere_encrypt(ciphertext, key);
    printf("Encrypted text: %s\n", ciphertext);
    vigenere_decrypt(ciphertext, key);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

