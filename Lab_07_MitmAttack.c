#include <stdio.h>

// Modular exponentiation: (base^exp) % mod
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
    // Step 1: Public Parameters
    unsigned long long p, g;
    unsigned long long a, b, k; // Alice, Bob, Attacker private keys
    unsigned long long A, B, T; // Alice, Bob, Attacker public keys
    unsigned long long S_A, S_B; // Shared secrets
    char choice;

    do {
        // Step 1: Public Parameters
        printf("Enter prime number (p): ");
        scanf("%llu", &p);
        printf("Enter generator (g): ");
        scanf("%llu", &g);

        printf("Enter Alice's private key (a): ");
        scanf("%llu", &a);
        printf("Enter Bob's private key (b): ");
        scanf("%llu", &b);
        printf("Enter Attacker's private key (k): ");
        scanf("%llu", &k);

        // Compute original public keys
        A = mod_exp(g, a, p);
        B = mod_exp(g, b, p);
        T = mod_exp(g, k, p); // Attacker's public key

        // Step 2: Attacker intercepts public keys
        // Attacker sends T to Alice instead of B
        // Attacker sends T to Bob instead of A

        // Step 3: Key Computation
        S_A = mod_exp(T, a, p); // Alice computes S_A = T^a mod p
        S_B = mod_exp(T, b, p); // Bob computes S_B = T^b mod p

        // Step 4: Final Step
        printf("Alice's public key A: %llu\n", A);
        printf("Bob's public key B: %llu\n", B);
        printf("Attacker's public key T: %llu\n", T);
        printf("Alice's shared secret S_A: %llu\n", S_A);
        printf("Bob's shared secret S_B: %llu\n", S_B);

        printf("Another simulation? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
