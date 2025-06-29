#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Step 4.1: Modular exponentiation function
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    srand(time(NULL));
    
    // Step 1: Initialization Phase
    unsigned long long p, g;
    
    // Step 2: Key Generation
    unsigned long long x_A, x_B; // Private keys
    unsigned long long y_A, y_B; // Public keys
    
    // Step 3: Key Exchange Protocol
    unsigned long long k, c1, s_A, s_B;
    
    char choice;

    do {
        // Step 1.2: Define constants
        printf("Enter prime number (p): ");
        scanf("%llu", &p);
        printf("Enter generator (g): ");
        scanf("%llu", &g);

        // Step 2.1: Generate private keys
        printf("Enter Party A private key (x_A): ");
        scanf("%llu", &x_A);
        printf("Enter Party B private key (x_B): ");
        scanf("%llu", &x_B);

        // Step 2.2: Compute public keys
        y_A = mod_exp(g, x_A, p);
        y_B = mod_exp(g, x_B, p);

        // Step 3.2: Choose random ephemeral key
        k = 2 + rand() % (p - 3);

        // Step 3.3: Party A computes c1 and shared secret
        c1 = mod_exp(g, k, p);
        s_A = mod_exp(y_B, k, p);

        // Step 3.7: Party B computes shared secret
        s_B = mod_exp(c1, x_B, p);

        // Step 5.4: Verify shared secrets match
        printf("Party A public key: %llu\n", y_A);
        printf("Party B public key: %llu\n", y_B);
        printf("c1: %llu\n", c1);
        printf("Party A shared secret: %llu\n", s_A);
        printf("Party B shared secret: %llu\n", s_B);
        printf("Secrets match: %s\n", (s_A == s_B) ? "YES" : "NO");

        printf("Another exchange? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
