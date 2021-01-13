const ll MOD = 1e9 + 7;

ll normalize(const ll a, const ll b = MOD) {
    ll ans = a % b;
    if (ans < 0)
        ans += b;
    return ans;
}

ll gcd(ll a, ll b) {
    assert(a != 0 && b != 0);
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return abs(a);
}

std::pair<ll,ll> egcd(ll a, ll b) {
    std::pair<ll,ll> ans = {1, 0};
    ll x1 = 0, y1 = 0, a1 = a, b1 = b ;
    while (b1) {
        ll q = a1 / b1;
        std::tie(ans.first, x1) = std::make_tuple(x1, ans.first - q * x1);
        std::tie(ans.second, y1) = std::make_tuple(y1, ans.second - q * y1);
        std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
    }
    return ans;
}

ll lcm(const ll& a, const ll& b) {
    return (a * b) / gcd(a, b);
}

ll modpow(ll base, ll exp, ll mod = MOD) {
    base = normalize(base, mod);
    ll ans = 1;
    base %= mod;
    while (exp) {
        if (exp & 1LL)
            ans = (ans * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return ans;
}

ll crt(const std::vector<ll>& n, std::vector<ll> a) {
    assert(n.size() == a.size());
    ll x = 0;
    ll N = 1;
    int s = n.size();
    for (int i = 0; i < s; i++) {
        a[i] = normalize(a[i], n[i]);
        N *= n[i];
        for (int j = i+1; j < s; j++)
            assert(gcd(n[i], n[j]) == 1);
    }
    for (int i = 0; i < s; i++) {
        ll b = N / n[i];
        x = (x + ((((b * a[i]) % N) * (egcd(b, n[i]).first % n[i])) % N)) % N;
    }
    return normalize(x, N);
}
