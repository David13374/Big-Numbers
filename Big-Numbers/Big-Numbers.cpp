#include "Big-Numbers.h"

BigInt::BigInt(std::string& s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(unsigned long long nr) {
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}
BigInt::BigInt(const char* s) {
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(BigInt& a) {
    digits = a.digits;
}

bool Null(const BigInt& a) {
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}
int Length(const BigInt& a) {
    return a.digits.size();
}
std::string GetDigits(const BigInt& a) {
    std::string trueDigits = "";
    trueDigits.resize(a.digits.length());
    for (size_t i = 0; i < a.digits.length(); i++) {
        trueDigits[a.digits.length() - i - 1] = a.digits[i] + '0';
    }

    return trueDigits;
}
int BigInt::operator[](const int index)const {
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}
bool operator==(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits;
}
bool operator!=(const BigInt& a, const BigInt& b) {
    return !(a == b);
}
bool operator<(const BigInt& a, const BigInt& b) {
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt& a, const BigInt& b) {
    return b < a;
}
bool operator>=(const BigInt& a, const BigInt& b) {
    return !(a < b);
}
bool operator<=(const BigInt& a, const BigInt& b) {
    return !(a > b);
}

BigInt& BigInt::operator=(const BigInt& a) {
    digits = a.digits;
    return *this;
}

BigInt& BigInt::operator++() {
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}
BigInt BigInt::operator++(int temp) {
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}

BigInt& BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1)
        throw("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}
BigInt BigInt::operator--(int temp) {
    BigInt aux;
    aux = *this;
    --(*this);
    return aux;
}

BigInt& operator+=(BigInt& a, const BigInt& b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt& operator-=(BigInt& a, const BigInt& b) {
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
        n--;
    return a;
}
BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

namespace NTT {
    const long long MOD = 998244353;
    const long long g = 3;

    long long power(long long a, long long b, long long mod) {
        long long res = 1;
        a %= mod;
        while (b > 0) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void ntt(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) std::swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            long long w = invert
                ? power(g, MOD - 1 - (MOD - 1) / len, MOD)
                : power(g, (MOD - 1) / len, MOD);
            for (int i = 0; i < n; i += len) {
                long long wn = 1;
                for (int j = 0; j < len / 2; j++) {
                    long long u = a[i + j];
                    long long v = a[i + j + len / 2] * wn % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len / 2] = (u - v + MOD) % MOD;
                    wn = wn * w % MOD;
                }
            }
        }
        if (invert) {
            long long n_inv = power(n, MOD - 2, MOD);
            for (auto& x : a) x = x * n_inv % MOD;
        }
    }

    std::vector<long long> multiply(const std::vector<long long>& a,
        const std::vector<long long>& b) {
        std::vector<long long> fa(a), fb(b);
        int n = 1;
        while (n < (int)(a.size() + b.size())) n <<= 1;
        fa.resize(n); fb.resize(n);
        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % MOD;
        ntt(fa, true);
        return fa;
    }
}

BigInt& operator*=(BigInt& a, const BigInt& b) {
    if (Null(a) || Null(b)) { a = BigInt(); return a; }

    std::vector<long long> fa(a.digits.begin(), a.digits.end());
    std::vector<long long> fb(b.digits.begin(), b.digits.end());

    std::vector<long long> res = NTT::multiply(fa, fb);

    a.digits.resize(res.size());
    long long carry = 0;
    int i = 0;
    for (; i < (int)res.size(); i++) {
        long long val = res[i] + carry;
        a.digits[i] = val % 10;
        carry = val / 10;
    }
    while (carry) {
        a.digits.push_back(carry % 10);
        carry /= 10;
    }

    while (a.digits.size() > 1 && a.digits.back() == 0)
        a.digits.pop_back();

    return a;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    BigInt temp; temp = a; temp *= b; return temp;
}

BigInt& operator/=(BigInt& a, const BigInt& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        a = BigInt();
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    return a;
}
BigInt operator/(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}

BigInt& operator%=(BigInt& a, const BigInt& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        return a;
    }
    if (a == b) {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInt operator%(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}

BigInt& operator^=(BigInt& a, const BigInt& b) {
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}
BigInt operator^(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp ^= b;
    return temp;
}

void divide_by_2(BigInt& a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}

BigInt sqrt(BigInt& a) {
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a) {
            v = mid;
            ++mid;
            left = mid;
        }
        else {
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}

std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string s;
    if (!(in >> s)) return in;

    a.digits.clear();
    int n = s.size();

    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i])) {
            throw std::runtime_error("INVALID NUMBER");
        }
        a.digits.push_back(s[i] - '0');
    }

    while (a.digits.size() > 1 && a.digits.back() == 0) {
        a.digits.pop_back();
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        std::cout << (short)a.digits[i];
    return std::cout;
}