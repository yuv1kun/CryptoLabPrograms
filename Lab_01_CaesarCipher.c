#include <stdio.h>
#include <string.h>

int main() {
    char message[1000];
    int key, choice;
    
    // Step 1: Input the plaintext (message)
    printf("Enter message: ");
    fgets(message, 1000, stdin);
    message[strcspn(message, "\n")] = '\0';
    
    // Step 2: Input the key (shift)
    printf("Enter key (shift): ");
    scanf("%d", &key);
    
    printf("1. Encrypt\n2. Decrypt\nChoose: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        // Step 3: Encryption
        for (int i = 0; message[i] != '\0'; i++) {
            if (message[i] >= 'A' && message[i] <= 'Z') {
                message[i] = (message[i] - 'A' + key) % 26 + 'A';
            }
            else if (message[i] >= 'a' && message[i] <= 'z') {
                message[i] = (message[i] - 'a' + key) % 26 + 'a';
            }
            // Non-alphabet characters remain unchanged
        }
    }
    else if (choice == 2) {
        // Step 4: Decryption
        for (int i = 0; message[i] != '\0'; i++) {
            if (message[i] >= 'A' && message[i] <= 'Z') {
                message[i] = (message[i] - 'A' - key + 26) % 26 + 'A';
            }
            else if (message[i] >= 'a' && message[i] <= 'z') {
                message[i] = (message[i] - 'a' - key + 26) % 26 + 'a';
            }
            // Non-alphabet characters remain unchanged
        }
    }
    
    // Step 5: Output the encrypted or decrypted message
    printf("Result: %s\n", message);
    
    return 0;
}
