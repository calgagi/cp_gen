const ll MOD = 1e9 + 7;

ll normalize(const ll a, const ll b = MOD) {
    ll ans = a % b;
    if (ans < 0) {
        ans += b;
    }
    return ans;
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return abs(a);
}

pair<ll, ll> egcd(ll a, ll b) {
    pair<ll, ll> ans = {1, 0};
    ll x1 = 0, y1 = 0, a1 = a, b1 = b ;
    while (b1) {
        ll q = a1 / b1;
        tie(ans.first, x1) = make_tuple(x1, ans.first - q * x1);
        tie(ans.second, y1) = make_tuple(y1, ans.second - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return ans;
}

ll lcm(const ll& a, const ll& b) {
    return a / gcd(a, b) * b;
}

ll modpow(ll base, ll exp, ll mod = MOD) {
    base = normalize(base, mod);
    ll ans = 1;
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
ll crt(const vector<ll>& n, vector<ll> a) {
    ll x = 0;
    ll N = 1;
    int s = n.size();
    for (int i = 0; i < s; i++) {
        a[i] = normalize(a[i], n[i]);
        N *= n[i];
    }
    for (int i = 0; i < s; i++) {
        ll b = N / n[i];
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
