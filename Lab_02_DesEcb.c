#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

int main() {
    char input[9];
    printf("Enter text (max 8 chars): ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    unsigned char plaintext[8] = {0};
    strncpy((char *)plaintext, input, 8);

    DES_cblock key = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    DES_key_schedule key_schedule;
    DES_set_key_checked(&key, &key_schedule);

    // Encrypt
    DES_cblock ciphertext;
    DES_ecb_encrypt((DES_cblock *)plaintext, &ciphertext, &key_schedule, DES_ENCRYPT);

    // Show encrypted data
    printf("Encrypted (hex): ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decrypt
    DES_cblock decryptedtext;
    DES_ecb_encrypt(&ciphertext, &decryptedtext, &key_schedule, DES_DECRYPT);

    // Print decrypted text
    printf("Decrypted: %s\n", decryptedtext);

    return 0;
}