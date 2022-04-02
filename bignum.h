#ifndef BIGNUM_H
#define BIGNUM_H

#define MAX_DIGITS 200

typedef struct {
    char num[MAX_DIGITS]; /* represent the number */
    int digit;            /* index of high-order digit */
} BigN;

static void init_BigN(BigN *n, long long input)
{
    for (int i = 0; i < MAX_DIGITS; i++)
        n->num[i] = (char) 0;
    n->digit = -1;
    if (input == 0)
        n->digit = 0;
    for (; input > 0; input /= 10) {
        n->digit++;
        n->num[n->digit] = (input % 10);
    }
}

static void add_BigN(BigN *a, BigN *b, BigN *c)
{
    int carry = 0;
    init_BigN(c, 0);
    c->digit = a->digit > b->digit ? a->digit + 1 : b->digit + 1;
    for (int i = 0; i <= c->digit; i++) {
        c->num[i] = (char) (carry + a->num[i] + b->num[i]) % 10;
        carry = (carry + a->num[i] + b->num[i]) / 10;
    }
    if (c->num[c->digit] == 0)
        c->digit--;
}

static char *result_BigN(BigN *result)
{
    size_t s = result->digit + 1;
    char *str = (char *) kmalloc(MAX_DIGITS, GFP_KERNEL);
    memset(str, '0', s);
    str[s] = '\0';
    for (int i = s - 1, j = 0; i > -1; i--, j++) {
        str[i] += result->num[j];
    }
    return str;
}

#endif