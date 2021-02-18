const int64_t MOD = 1e9 + 7;

int64_t normalize(const int64_t a, const int64_t b = MOD) {
    int64_t ans = a % b;
    if (ans < 0) {
        ans += b;
    }
    return ans;
}

int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return abs(a);
}

pair<int64_t, int64_t> egcd(int64_t a, int64_t b) {
    pair<int64_t, int64_t> ans = {1, 0};
    int64_t x1 = 0, y1 = 0, a1 = a, b1 = b ;
    while (b1) {
        int64_t q = a1 / b1;
        tie(ans.first, x1) = make_tuple(x1, ans.first - q * x1);
        tie(ans.second, y1) = make_tuple(y1, ans.second - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return ans;
}

int64_t lcm(const int64_t& a, const int64_t& b) {
    return (a * b) / gcd(a, b);
}

int64_t modpow(int64_t base, int64_t exp, int64_t mod = MOD) {
    base = normalize(base, mod);
    int64_t ans = 1;
    base %= mod;
    while (exp) {
        if ((exp & 1LL)) {
            ans = (ans * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return ans;
}

// make sure gcd(n[i], n[j]) == 1
int64_t crt(const vector<int64_t>& n, vector<int64_t> a) {
    int64_t x = 0;
    int64_t N = 1;
    int s = n.size();
    for (int i = 0; i < s; i++) {
        a[i] = normalize(a[i], n[i]);
        N *= n[i];
    }
    for (int i = 0; i < s; i++) {
        int64_t b = N / n[i];
        x = (x + ((((b * a[i]) % N) * (egcd(b, n[i]).first % n[i])) % N)) % N;
    }
    return normalize(x, N);
}

vector<bool> eratosthenes(const int n, vector<int>& primes) {
    primes = {1};
    vector<bool> is_composite(n+1);
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < (int) primes.size() && primes[j] * i <= n; j++) {
            is_composite[primes[j] * i] = true;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    return is_composite;
}
