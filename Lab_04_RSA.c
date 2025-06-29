#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Simple modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Simple modular inverse using brute force
long long mod_inverse(long long e, long long phi) {
    for (long long d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    long long p, q, n, phi, e, d;
    char message[100];
    long long encrypted[100];
    
    printf("RSA Encryption-Decryption\n");
    printf("=========================\n\n");
    
    // Step 1: Key Generation
    printf("Step 1: Key Generation\n");
    printf("Enter first prime number (p): ");
    scanf("%lld", &p);
    printf("Enter second prime number (q): ");
    scanf("%lld", &q);
    
    n = p * q;
    phi = (p - 1) * (q - 1);
    
    printf("Enter public exponent (e): ");
    scanf("%lld", &e);
    
    d = mod_inverse(e, phi);
    
    printf("Public key (e, n): (%lld, %lld)\n", e, n);
    printf("Private key (d, n): (%lld, %lld)\n\n", d, n);
    
    // Step 2: Encryption
    printf("Step 2: Encryption\n");
    printf("Enter message: ");
    scanf("%s", message);
    
    int len = strlen(message);
    printf("Plaintext: %s\n", message);
    printf("Encrypted: ");
    
    for (int i = 0; i < len; i++) {
        long long m = (long long)message[i];
        encrypted[i] = mod_exp(m, e, n);
        printf("%lld ", encrypted[i]);
    }
    printf("\n\n");
    
    // Step 3: Decryption
    printf("Step 3: Decryption\n");
    printf("Decrypted: ");
    
    for (int i = 0; i < len; i++) {
        long long decrypted = mod_exp(encrypted[i], d, n);
        printf("%c", (char)decrypted);
    }
    printf("\n");
    
    return 0;
}
