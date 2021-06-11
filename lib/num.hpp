#pragma once
ll MOD = 1e9 + 7;

ll normalize(ll a, ll b = MOD) {
    return ((a % b) + b) % b;
}

ll lgcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return abs(a);
}

array<ll,2> egcd(ll a, ll b) {
    array<ll,2> ans = {1, 0};
    ll x1 = 0, y1 = 0, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(ans[0], x1) = make_tuple(x1, ans[0] - q * x1);
        tie(ans[1], y1) = make_tuple(y1, ans[1] - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return ans;
}

ll modpow(ll base, ll exp, ll mod = MOD) {
    base = normalize(base, mod);
    ll ans = 1;
    base %= mod;
    while (exp) {
        if ((exp & 1LL)) ans = (ans * base) % mod;
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
        x = (x + ((((b * a[i]) % N) * (egcd(b, n[i])[0] % n[i])) % N)) % N;
    }
    return normalize(x, N);
}

// primes populated with primes in range [2, mx] and sieve[i] = largest prime factor of i
pair<vector<int>, vector<int>> eratosthenes(const ll mx) {
    vector<int> primes, sieve(mx+1, 1);
    for (ll i = 2; i <= mx; i++) {
        if (sieve[i] == 1) {
            sieve[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < (int) primes.size() && primes[j] <= sieve[i] && i*primes[j] <= mx; j++) sieve[i*primes[j]] = primes[j];
    }
    return {sieve, primes}; 
}
