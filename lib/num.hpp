const ll MOD = 1e9 + 7;

void normalize(ll& a, const ll b = MOD) {
    a %= b;
    if (a < 0) {
        a += b;
    }
    return;
}

ll gcd(ll a, ll b) {
    assert(a != 0 && b != 0);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

pair<ll,ll> egcd(ll a, ll b) {
    pair<ll,ll> ans = {1, 0};
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
    return (a * b) / gcd(a, b);
}

ll modpow(ll base, ll exp, ll mod = MOD) {
    ll ans = 1;
    base %= mod;
    while (exp) {
        if (exp & 1LL) {
            ans = (ans * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return ans;
}

ll crt(const vector<ll>& n, vector<ll> a) {
    assert(n.size() == a.size());
    ll x = 0;
    ll N = 1;
    int s = n.size();
    for (int i = 0; i < s; i++) {
        normalize(a[i], n[i]);
        N *= n[i];
        for (int j = i+1; j < s; j++) {
            assert(gcd(n[i], n[j]) == 1);
        }
    }
    for (int i = 0; i < s; i++) {
        ll b = N / n[i];
        x = (x + ((((b * a[i]) % N) * (egcd(b, n[i]).first % n[i])) % N)) % N;
    }
    normalize(x, N);
    return x;
}
