#ifndef BIGNUM_H
#define BIGNUM_H

struct BigN {
    unsigned long long lower, upper;
};

static inline void addBigN(struct BigN *output, struct BigN x, struct BigN y)
{
    output->upper = x.upper + y.upper;
    if (y.lower > ~x.lower)
        output->upper++;
    output->lower = x.lower + y.lower;
}

static char *BigNtoDec(struct BigN target)
{
    // log10(x) = log2(x) / log2(10) ~= log2(x) / 3.322
    size_t size = sizeof(struct BigN) * 8 / 3 + 2;
    char *str = (char *) kmalloc(size + 1, GFP_KERNEL);
    memset(str, '0', size);
    str[size] = '\0';
    int carry;
    for (unsigned long long i = 1ULL << 63; i; i >>= 1) {
        carry = (target.upper & i) > 0;
        for (int j = size - 1; j >= 0; j--) {
            str[j] += ((str[j] - '0') + carry);
            carry = str[j] > '9';
            if (carry)
                str[j] -= 10;
        }
    }
    for (unsigned long long i = 1ULL << 63; i; i >>= 1) {
        carry = (target.lower & i) > 0;
        for (int j = size - 1; j >= 0; j--) {
            str[j] += ((str[j] - '0') + carry);
            carry = str[j] > '9';
            if (carry)
                str[j] -= 10;
        }
    }
    char *ptr = str;
    for (; *ptr == '0' && ptr != &str[size - 1]; ptr++)
        ;
    return ptr;
}

#endif