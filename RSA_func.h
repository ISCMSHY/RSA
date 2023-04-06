#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char hex_to_char(int hex); // change hex to char
long long EA(long long a, long long b); // Euclidean Algorithm
long long EEA(long long a, long long b); // Extended Euclidean Algorithm
void get_e(long long phi_N, long long* e_list); // get All e(public key) that satisfied gcd(phi_N, e) = 1
int euler_seive(int N, int* prime); // euler_seive algorithm
int prime_F(int N, int* prime, int* pow_a, int idx); // prime Factorization
int euler_p(int N); // euler pi function algorithm
int F(int N); // integer Factorization
void create_RSA_key(long long p, long long q, long long *e, long long *d); // Generating RSA Key
long long encrypt(long long plaintext, long long N, long long e); // RSA Encryption
long long decrypt(long long ciphertext, long long N, long long d); // RSA Decryption