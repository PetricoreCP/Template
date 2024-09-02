long long binModExp(long long base, long long exp, long long mod) {
    long long ans = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) ans = ans * base % mod;
        base = base * base % mod; 
        exp >>= 1;
    }
    return ans;
}

long long modInv(long long base, long long mod) {
    return binModExp(base, mod - 2, mod);
}
