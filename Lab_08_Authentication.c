#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USER_FILE "users.txt"
#define HASH_HEX_SIZE (SHA256_DIGEST_LENGTH * 2 + 1)

// Step 2: Hash password using SHA-256
void hash_password(const char *password, char hex[HASH_HEX_SIZE]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(hex + (i * 2), "%02x", hash[i]);
    hex[HASH_HEX_SIZE - 1] = '\0';
}

int main() {
    char username[64], password[128], hash[HASH_HEX_SIZE];
    char file_user[64], file_hash[HASH_HEX_SIZE];
    int choice, found = 0;

    printf("1. Register\n2. Login\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Step 1: Input username and password
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        // Step 2: Hash the password
        hash_password(password, hash);

        // Step 3: Store username and hash
        FILE *fp = fopen(USER_FILE, "a");
        fprintf(fp, "%s %s\n", username, hash);
        fclose(fp);
        printf("User registered!\n");
    }
    else if (choice == 2) {
        // Step 1: Input username and password for login
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        // Step 2: Hash the entered password
        hash_password(password, hash);

        // Step 4: Authentication process
        FILE *fp = fopen(USER_FILE, "r");
        while (fscanf(fp, "%s %s", file_user, file_hash) != EOF) {
            if (strcmp(username, file_user) == 0) {
                found = 1;
                if (strcmp(hash, file_hash) == 0) {
                    printf("Authentication successful!\n");
                } else {
                    printf("Authentication failed!\n");
                }
                break;
            }
        }
        fclose(fp);
        if (!found) printf("Username not found!\n");
    }

    return 0;
}
