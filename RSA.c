#include "RSA_func.h"

// compile command : gcc -o RSA RSA.c RSA_func.c -lm


void problem1(){
    printf("\n---------------- problem 1 --------------\n");
    long long p = 13, q = 11, e = 37, d = 0;
    create_RSA_key(p, q, &e, &d);
    printf("p = %lld, q = %lld, e = %lld, d = %lld\n", p, q, e, d);
}

void problem2(){
    printf("\n---------------- problem 2 --------------\n");
    long long N = 0xE79BB; //948667
    long long q = F(N);
    long long p = N / q;
    long long e = 37, d = 0;
    create_RSA_key(p, q, &e, &d);
    printf("%lld = %lld X %lld\n", N, q, p);
    printf("p = %lld, q = %lld, e = %lld, d = %lld\n", p, q, e, d);
}

void rsa(){
    printf("\n---------------- RSA Process --------------\n");
    long long p = 971, q = 977, e = 37, d = 0;
    long long N = p * q;
    long long plaintext = 0x4869; // Hi
    create_RSA_key(p, q, &e, &d);

    printf("p = %lld, q = %lld, e = %lld, d = %lld\n", p, q, e, d);
    printf("plaintext : %c%c\n", hex_to_char(plaintext >> 8), hex_to_char(plaintext & 0xff));
    long long ciphertext = encrypt(plaintext, N, e);
    printf("ciphertext : %c%c\n", hex_to_char(ciphertext >> 8), hex_to_char(ciphertext & 0xff));
    long long decrypted = decrypt(ciphertext, N, d);
    printf("decrypted text : %c%c\n", hex_to_char(decrypted >> 8), hex_to_char(decrypted & 0xff));
}

void main(){
    problem1();
    problem2();
    rsa();
}