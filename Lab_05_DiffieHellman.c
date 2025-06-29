#include <stdio.h>
#include <math.h>

// Function to perform modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    unsigned long long p, g;
    unsigned long long a, b;
    unsigned long long A, B;
    unsigned long long s_alice, s_bob;
    char choice;

    do {
        // Step 1: Public Parameters
        printf("Enter prime number (p): ");
        scanf("%llu", &p);
        printf("Enter primitive root modulo (g): ");
        scanf("%llu", &g);

        // Step 2: Private Keys
        printf("Enter Alice's private key (a): ");
        scanf("%llu", &a);
        printf("Enter Bob's private key (b): ");
        scanf("%llu", &b);

        // Step 3: Public Keys
        A = mod_exp(g, a, p);
        B = mod_exp(g, b, p);

        // Step 4: Key Exchange
        printf("Alice's public key A = %llu\n", A);
        printf("Bob's public key B = %llu\n", B);

        // Step 5: Shared Secret
        s_alice = mod_exp(B, a, p);
        s_bob = mod_exp(A, b, p);

        // Step 6: Result
        printf("Alice's shared secret: %llu\n", s_alice);
        printf("Bob's shared secret: %llu\n", s_bob);
        printf("Keys match: %s\n", (s_alice == s_bob) ? "YES" : "NO");

        printf("Another execution? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
