class mint {
public:
    ll MOD = 1e9 + 7;
    ll val = 0;

    void normalize() {
        val %= MOD;
        if (val < 0) {
            val += MOD;
        }
    }

    mint() {}

    // gets
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

    // plus equals 
    mint& operator+=(const mint& other) {
        this->val += other.val;
        this->normalize();
        return *this;
    }

    mint& operator+=(const ll& other) {
        this->val += other;
        this->normalize();
        return *this;
    }

    // minus equals
    mint& operator-=(const mint& other) {
        this->val -= other.val;
        this->normalize();
        return *this;
    }

    mint& operator-=(const ll& other) {
        this->val -= other;
        this->normalize();
        return *this;
    }

    // mult equals
    mint& operator*=(const mint& other) {
        this->val *= other.val;
        this->normalize();
        return *this;
    }

    mint& operator*=(const ll& other) {
        this->val *= other;
        this->normalize();
        return *this;
    }

    // divide equals
    mint& operator/=(const mint& other) {
        this->val /= other.val;
        this->normalize();
        return *this;
    }

    mint& operator/=(const ll& other) {
        this->val /= other;
        this->normalize();
        return *this;
    }
/*
    // equals 
    bool operator==(const mint& other) {
        return this->val == other.val;
    }
    
    bool operator==(const ll& other) {
        return this->val == other;
    }

    // not equals 
    bool operator!=(const mint& other) {
        return this->val != other.val;
    }

    bool operator!=(const ll& other) {
        return this->val != other;
    }

    */// less than
    bool operator<(const mint& other) {
        return this->val < other.val;
    }

    bool operator<(const ll& other) {
        return this->val < other;
    }

    // greater than
    bool operator>(const mint& other) {
        return this->val > other.val;
    }

    bool operator>(const ll& other) {
        return this->val > other;
    }

    // less than or equal to
    bool operator<=(const mint& other) {
        return this->val <= other.val;
    }

    bool operator<=(const ll& other) {
        return this->val <= other;
    }

    // greater than or equal to 
    bool operator>=(const mint& other) {
        return this->val >= other.val;
    }

    bool operator>=(const ll& other) {
        return this->val >= other;
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

// add
ll operator+(const ll& a, const mint& b) {
    return a + b.val;
}

mint operator+(const mint& a, const mint& b) {
    mint ans;
    ans.val = a.val + b.val;
    ans.normalize();
    return ans;
}

mint operator+(const mint& a, const ll& b) {
    mint ans;
    ans.val = a.val + b;
    ans.normalize();
    return ans;
}

// subtract
ll operator-(const ll& a, const mint& b) {
    return a + b.val;
}

mint operator-(const mint& a, const mint& b) {
    mint ans;
    ans.val = a.val - b.val;
    ans.normalize();
    return ans;
}

mint operator-(const mint& a, const ll& b) {
    mint ans;
    ans.val = a.val - b;
    ans.normalize();
    return ans;
}

// mult
ll operator*(const ll& a, const mint& b) {
    return a * b.val;
}

mint operator*(const mint& a, const mint& b) {
    mint ans;
    ans.val = a.val * b.val;
    ans.normalize();
    return ans;
}

mint operator*(const mint& a, const ll& b) {
    mint ans;
    ans.val = a.val * b;
    ans.normalize();
    return ans;
}

// divide
ll operator/(const ll& a, const mint& b) {
    return a / b.val;
}

mint operator/(const mint& a, const mint& b) {
    mint ans;
    ans.val = a.val / b.val;
    ans.normalize();
    return ans;
}

mint operator/(const mint& a, const ll& b) {
    mint ans;
    ans.val = a.val / b;
    ans.normalize();
    return ans;
}