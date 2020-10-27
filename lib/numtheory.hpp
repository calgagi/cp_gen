class numtheory {
public:
    int64_t MOD = 1e9 + 7;

    int64_t add(int64_t a, int64_t b) {
        return (a + b) % MOD;
    } 
    
    int64_t mult(int64_t a, int64_t b) {
        return (a * b) % MOD;
    }
    
    int64_t binexp(int64_t base, int64_t exp) {
        int64_t ans = 1, now = base;
        while (exp) {
            if ((exp & 1)) {
                ans = mult(ans, now);
            }
            now = mult(now, now);
            exp >>= 1;
        }
        return ans;
    }

    int64_t gcd(int64_t a, int64_t b) {
        if (a == 0) {
            return b;
        } 
        return gcd(b % a, a);
    }

    int64_t lcm(int64_t a, int64_t b) {
        return (a * b) / gcd(a, b);
    }

};
