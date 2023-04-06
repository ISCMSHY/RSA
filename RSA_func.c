#include "RSA_func.h"

// change hex to char
char hex_to_char(int hex){
    return hex - 48 + '0';
}

// Euclidean Algorithm
long long EA(long long a, long long b){
    if(b == 0)  return a;
    else    return EA(b, a % b);
}

// Extended Euclidean Algorithm
long long EEA(long long a, long long b){
    long long r0 = a, s0 = 1, t0 = 0;
    long long r1 = b, s1 = 0, t1 = 1;
    long long temp = 0, q = 0;
    while(r1){
        q = r0 / r1;
        temp = r0;
        r0 = r1;
        r1 = temp - r1 * q;
        temp = s0;
        s0 = s1;
        s1 = temp - s1 * q;
        temp = t0;
        t0 = t1;
        t1 = temp - t1 * q;
    }
    return t0;
}

// gcd(phi_N, e) = 1을 만족하는 모든 e를 구함
void get_e(long long phi_N, long long* e_list){
    int idx = 0;
    for(int i = 2; i < phi_N; i++)  if(EA(phi_N, i) == 1)   e_list[idx++] = i;
}

// 오일러 체 알고리즘 사용
int euler_seive(int N, int* prime){
    int *spf = (int*) calloc(N, sizeof(int));
    int prime_idx = 0;
    for(int i = 2; i <= N; i++){
        if(spf[i] == 0) prime[prime_idx++] = spf[i] = i;
        for(int j = 0; j < prime_idx; j++){
            if(i * prime[j] > N)    break;
            spf[i * prime[j]] = prime[j];
            if(i % prime[j] == 0)   break;
        }
    }
    free(spf);
    return prime_idx - 1;
}

// 소인수 분해
int prime_F(int N, int* prime, int* pow_a, int idx){
    while(1){
        for(int i = 0; i < idx; i++){
            if(N % prime[i] == 0){
                pow_a[i]++;
                N /= prime[i];
                if(N == 1)  return 0;
                break;
            }else if(i + 1 == idx)  return 1; // N값이 소수일 경우.
        }
    }
}

// 오일러 파이 함수 구현
int euler_p(int N){
    int result = 1;
    int *prime = (int*) calloc(N, sizeof(int)); // N 이하의 모든 소수를 담을 list
    int idx = euler_seive(N, prime); // 오일러 체를 이용하여 N 이하의 모든 소수를 담음
    int *pow_a = (int*) calloc(idx, sizeof(int)); // 위에서 구한 소수를 통해 N을 소인수 분해 할 때 지수를 담을 list
    if(prime_F(N, prime, pow_a, idx) == 1)  return N - 1; // 위에서 구한 소수를 통해 N을 소인수 분해 후 각 소수들의 지수를 return (return == 1 인 경우는 소수)
    // 오일러 파이 함수의 특징 phi(p^a) = p^a - p^(a-1)을 이용하여 오일러 파이 값을 구함
    for(int i = 0; i < idx; i++)    if(pow_a[i] != 0)   result *= (pow(prime[i], pow_a[i]) - pow(prime[i], pow_a[i] - 1)); // 
    return result;
}

int F(int N){
    int *prime = (int*) calloc(N, sizeof(int));
    int p_idx = euler_seive(N, prime);
    int idx = 0;
    int result = 0;
    while(idx < p_idx){
        if(N % prime[idx] == 0){
            result = prime[idx];
            free(prime);
            return result;
        }
        idx++;
    }
}

void create_RSA_key(long long p, long long q, long long *e, long long *d){
    long long phi_N = (p-1)*(q-1);
    // gcd(phi_n, e) = 1을 만족하는 모든 e를 구하기
    if(*e == 0){
        long long *e_list = (long long*) calloc(euler_p(phi_N) - 1, sizeof(long long)); // 서로소 개수 구하는데 1과 자기자신을 제외하니까 -2
        get_e(phi_N, e_list);
        *e = e_list[8]; // 가장 효율적인 e값이 무엇인지 모르겠음... 그냥 8번째 인덱스에 있는 e return
        for(int i = 0; i < 31; i++) printf("%lld, %lld\n", e_list[i], EEA(phi_N, e_list[i]));
    }
    *d = EEA(phi_N, *e);
    if(*d < 0)  *d += phi_N;
}

long long encrypt(long long plaintext, long long N, long long e){
    long long result = 1;
    for(long long i = 0; i < e; i++)    result = (result * plaintext) % N;
    return result;
}

long long decrypt(long long ciphertext, long long N, long long d){
    long long result = ciphertext;
    for(long long i = 1; i < d; i++)   result = (result * ciphertext) % N;
    return result;
}