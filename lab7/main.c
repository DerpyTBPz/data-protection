#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    unsigned long long value;
    int index;
} Entry;

int compare(const void *a, const void *b) {
    Entry *e1 = (Entry *)a;
    Entry *e2 = (Entry *)b;
    if (e1->value < e2->value) return -1;
    if (e1->value > e2->value) return 1;
    return 0;
}

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long m) {
    return (unsigned long long)((unsigned __int128)a * b % m);
}

unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul(res, base, mod);
        base = mul(base, base, mod);
        exp /= 2;
    }
    return res;
}

int main()
{
    long long G_in = 654;
    long long H_in = 4547;
    long long Q_in = 11087;
    // scanf("%lld%lld%lld", &G_in, &H_in, &Q_in);

    unsigned long long G = (unsigned long long)G_in;
    unsigned long long H = (unsigned long long)H_in;
    unsigned long long Q = (unsigned long long)Q_in;

    unsigned long long m = (unsigned long long)(sqrt((double)Q) + 1);

    Entry *table = (Entry *)malloc(m * sizeof(Entry));
    unsigned long long cur = 1;

    for (int j = 0; j < m; j++) {
        table[j].value = cur;
        table[j].index = j;
        cur = mul(cur, G, Q);
    }

    qsort(table, m, sizeof(Entry), compare);

    unsigned long long gm = power(G, m, Q);
    unsigned long long inv = power(gm, Q - 2, Q);
    unsigned long long target = H;

    for (unsigned long long i = 0; i < m; i++) {
        Entry key;
        key.value = target;
        Entry *found = (Entry *)bsearch(&key, table, m, sizeof(Entry), compare);

        if (found != NULL) {
            unsigned long long ans = i * m + found->index;
            printf("%llu\n", ans);
            free(table);
            return 0;
        }

        target = mul(target, inv, Q);
    }

    return 0;
}