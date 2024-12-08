#include<bits/stdc++.h>
using namespace std;

template<typename T, typename F>
struct DST {
	int n;
	vector<vector<T>> mat;
	F f;
	DST(const vector<T> &a, const F &g) : n(a.size()), f(g) {
		mat.push_back(a);
    	for (int p = 1; (1 << p) < n; p++) {
      		mat.emplace_back(n);
      		for (int mid = 1 << p; mid < n; mid += 1 << (p + 1)) {
        		mat[p][mid - 1] = a[mid - 1];
        		for (int j = mid - 2; j >= mid - (1 << p); j--) {
          			mat[p][j] = f(a[j], mat[p][j + 1]);
        		}
        		mat[p][mid] = a[mid];
        		for (int j = mid + 1; j < min(n, mid + (1 << p)); j++) {
          			mat[p][j] = f(mat[p][j - 1], a[j]);
        		}
      		}
    	}
	} 
	T Query(int l, int r) {
		assert(0 <= l && l < r && r <= n);
    	if (r - l == 1) {
      		return mat[0][l];
    	}
    	int p = 31 - __builtin_clz(unsigned(l ^ (r - 1)));
    	return f(mat[p][l], mat[p][r - 1]);
	}
};

int32_t main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	int tc = 1; 
	cin >> tc;
	while(tc --) {
		int n, q;
		cin >> n >> q;
		vector<long long> a(n);
		for(int i = 0; i < n; i ++) {
			cin >> a[i];
		}
		vector<long long> b(n - 1);
		for(int i = 0; i < n - 1; i ++) {
			b[i] = abs(a[i] - a[i + 1]);
		}
		DST st(b, [&](long long x, long long y) {
			return __gcd(x, y);
		});
		while(q --) {
			int l, r;
			cin >> l >> r;
			l --; r --;
			cout << (l == r ? 0 : st.Query(l, r)) << ' ';
		}
		cout << '\n';
	}	
	return 0;
}
