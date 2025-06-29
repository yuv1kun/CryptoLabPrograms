#include <stdio.h>
#include <string.h>

int main() {
    char message[1000];
    char cipher[1000];
    int rails, choice;
    
    // Step 1: Input the plaintext (message)
    printf("Enter message: ");
    fgets(message, 1000, stdin);
    message[strcspn(message, "\n")] = '\0';
    
    // Step 2: Choose the number of rails
    printf("Enter number of rails: ");
    scanf("%d", &rails);
    
    printf("1. Encrypt\n2. Decrypt\nChoose: ");
    scanf("%d", &choice);
    
    int len = strlen(message);
    
    if (choice == 1) {
        // Step 3: Construct the zigzag pattern
        char rail[rails][len];
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < len; j++) {
                rail[i][j] = '\n';
            }
        }
        
        int row = 0, dir_down = 1;
        for (int i = 0; i < len; i++) {
            rail[row][i] = message[i];
            if (row == 0) dir_down = 1;
            else if (row == rails - 1) dir_down = 0;
            row += (dir_down ? 1 : -1);
        }
        
        // Step 4: Read the rows
        int index = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < len; j++) {
                if (rail[i][j] != '\n') {
                    cipher[index++] = rail[i][j];
                }
            }
        }
        cipher[index] = '\0';
        printf("Encrypted: %s\n", cipher);
    }
    else if (choice == 2) {
        // Step 5: Decrypt the message
        char rail[rails][len];
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < len; j++) {
                rail[i][j] = '\n';
            }
        }
        
        int row = 0, dir_down = 1;
        for (int i = 0; i < len; i++) {
            rail[row][i] = '*';
            if (row == 0) dir_down = 1;
            else if (row == rails - 1) dir_down = 0;
            row += (dir_down ? 1 : -1);
        }
        
        int index = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < len; j++) {
                if (rail[i][j] == '*') {
                    rail[i][j] = message[index++];
                }
            }
        }
        
        row = 0; dir_down = 1; index = 0;
        for (int i = 0; i < len; i++) {
            cipher[index++] = rail[row][i];
            if (row == 0) dir_down = 1;
            else if (row == rails - 1) dir_down = 0;
            row += (dir_down ? 1 : -1);
        }
        cipher[index] = '\0';
        printf("Decrypted: %s\n", cipher);
    }
    
    return 0;
}
