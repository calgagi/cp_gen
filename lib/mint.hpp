class mint {
private:
    long long val = 0;

    void normalize() {
        val %= MOD;
        if (val < 0) {
            val += MOD;
        }
    }

public:
    friend mint power(const mint& base, long long exp);
    friend mint inv(const mint&);
    friend istream& operator>>(istream& stream, mint& number);

    long long MOD = 1e9 + 7;

    mint() {}

    mint(const long long& other) : val(other) {
        this->normalize(); 
        return;
    }

    mint& operator=(const long long& other) {
        this->val = other;
        this->normalize();
        return *this;
    }

    mint& operator=(const mint& other) {
        this->val = other.val;
        this->normalize();
        return *this;
    }

    mint operator-() const {
        mint ans(-(this->val));
        ans.normalize();
        return ans;
    }

    operator long long() const {
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
        this->val = this->val * inv(other);
        this->normalize();
        return *this;
    }

    mint& operator++(int) {
        (*this) += 1;
        return *this;
    }

    mint& operator--(int) {
        (*this) -= 1;
        return *this;
    }

    mint operator/(const mint& other) {
        mint ans;
        ans.val = this->val * inv(other);
        return ans;
    }
};

mint power(const mint& base, long long exp) {
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

// in and in.MOD must be coprime!
mint inv(const mint& in) {
    return power(in, in.MOD-2);
}

istream& operator>>(istream& stream, mint& number) {
    long long x;
    stream >> x;
    number.val = x;
    return stream;
}