const long long MOD = 1e9 + 7;

long long normalize(const long long a, const long long b = MOD) {
    long long ans = a % b;
    if (ans < 0) {
        ans += b;
    }
    return ans;
}

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return abs(a);
}

pair<long long, long long> egcd(long long a, long long b) {
    pair<long long, long long> ans = {1, 0};
    long long x1 = 0, y1 = 0, a1 = a, b1 = b ;
    while (b1) {
        long long q = a1 / b1;
        tie(ans.first, x1) = make_tuple(x1, ans.first - q * x1);
        tie(ans.second, y1) = make_tuple(y1, ans.second - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return ans;
}

long long lcm(const long long& a, const long long& b) {
    return (a * b) / gcd(a, b);
}

long long modpow(long long base, long long exp, long long mod = MOD) {
    base = normalize(base, mod);
    long long ans = 1;
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
long long crt(const vector<long long>& n, vector<long long> a) {
    long long x = 0;
    long long N = 1;
    int s = n.size();
    for (int i = 0; i < s; i++) {
        a[i] = normalize(a[i], n[i]);
        N *= n[i];
    }
    for (int i = 0; i < s; i++) {
        long long b = N / n[i];
        x = (x + ((((b * a[i]) % N) * (egcd(b, n[i]).first % n[i])) % N)) % N;
    }
    return normalize(x, N);
}

vector<int> eratosthenes(const int mx) {
    vector<int> primes;
    vector<int> max_prime(mx+1, 0);
    for (int i = 2; i <= mx; i++) {
        if (!max_prime[i]) {
            primes.push_back(i);
            max_prime[i] = i;
        }
        for (int& p : primes) {
            if (p * i > mx) {
                break;
            }
            primes[p * i] = (primes.back() == i ? i : p);
            if (i % p == 0) {
                break;
            }
        }
    }
    return max_prime;
}
