#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

// Function to print data in hexadecimal format
void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // 128-bit key (16 bytes)
    unsigned char key[] = "1234567890abcdef";
    
    // Sample plaintext (32 bytes, multiple of 16 for ECB without padding)
    unsigned char plaintext[] = "This is a test message for AES!"; 
    int plaintext_len = strlen((char *)plaintext);
    
    // Buffers for ciphertext and decrypted text
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];
    
    // AES context structures
    AES_KEY enc_key, dec_key;
    
    // Check if plaintext length is a multiple of AES block size (16 bytes)
    if (plaintext_len % AES_BLOCK_SIZE != 0) {
        printf("Error: Plaintext length must be a multiple of %d bytes for ECB mode without padding.\n", AES_BLOCK_SIZE);
        return 1;
    }
    
    printf("Original plaintext: %s\n", plaintext);
    printf("Plaintext length: %d bytes\n", plaintext_len);
    print_hex("Plaintext (hex)", plaintext, plaintext_len);
    
    // Set encryption key
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        printf("Error setting encryption key\n");
        return 1;
    }
    
    // Encrypt the plaintext in ECB mode
    for (int i = 0; i < plaintext_len; i += AES_BLOCK_SIZE) {
        AES_ecb_encrypt(plaintext + i, ciphertext + i, &enc_key, AES_ENCRYPT);
    }
    
    printf("Ciphertext length: %d bytes\n", plaintext_len);
    print_hex("Ciphertext (hex)", ciphertext, plaintext_len);
    
    // Set decryption key
    if (AES_set_decrypt_key(key, 128, &dec_key) < 0) {
        printf("Error setting decryption key\n");
        return 1;
    }
    
    // Decrypt the ciphertext in ECB mode
    for (int i = 0; i < plaintext_len; i += AES_BLOCK_SIZE) {
        AES_ecb_encrypt(ciphertext + i, decryptedtext + i, &dec_key, AES_DECRYPT);
    }
    
    // Null-terminate the decrypted text for printing
    decryptedtext[plaintext_len] = '\0';
    
    printf("Decrypted text: %s\n", decryptedtext);
    printf("Decrypted text length: %d bytes\n", plaintext_len);
    print_hex("Decrypted (hex)", decryptedtext, plaintext_len);
    
    return 0;
}