#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char hex_to_char(int hex);
long long EA(long long a, long long b);
long long EEA(long long a, long long b);
void get_e(long long phi_N, long long* e_list);
int euler_seive(int N, int* prime);
int prime_F(int N, int* prime, int* pow_a, int idx);
int euler_p(int N);
int F(int N);
void create_RSA_key(long long p, long long q, long long *e, long long *d);
long long encrypt(long long plaintext, long long N, long long e);
long long decrypt(long long ciphertext, long long N, long long d);