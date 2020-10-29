class mint {
private:
    ll val = 0;

    void normalize() {
        val %= MOD;
        if (val < 0) {
            val += MOD;
        }
    }

public:
    ll MOD = 1e9 + 7;

    mint() {}

    mint(const ll& other) : val(other) {
        this->normalize(); 
        return;
    }

    mint& operator=(const ll& other) {
        this->val = other;
        normalize();
        return *this;
    }

    mint& operator=(const mint& other) {
        this->val = other.val;
        normalize();
        return *this;
    }

    mint operator-() const {
        mint ans(-(this->val));
        ans.normalize();
        return ans;
    }

    operator ll() const {
        return this->val;
    }

    mint& operator+=(const mint& other) {
        this->val += other.val;
        this->normalize();
        return *this;
    }

    mint& operator-=(const mint& other) {
        this->val -= other.val;
        this->normalize();
        return *this;
    }

    mint& operator*=(const mint& other) {
        this->val *= other.val;
        this->normalize();
        return *this;
    }

    mint& operator/=(const mint& other) {
        this->val /= other.val;
        this->normalize();
        return *this;
    }

    mint& operator++() {
        (*this) += 1;
        return *this;
    }

    mint& operator--() {
        (*this) -= 1;
        return *this;
    }
};

mint power(const mint& base, ll exp) {
    mint ans = 1, x = base;
    while (exp) {
        if (exp & 1) {
            ans *= x;
        }
        exp >>= 1;
        x *= x;
    }
    return ans;
}

mint inv(const mint& in) {
    return power(in, in.MOD-2);
}