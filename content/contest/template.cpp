#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (auto i{a}; i < (b); ++i)
#define per(i, a, b) for (auto i{b}; i-- > (a); )
#define all(x) begin(x), end(x)
#define all(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

template <class T> bool uax(T& a, const T& b) { return a < b ? a = b, true : false; }
template <class T> bool uin(T& a, const T& b) { return a > b ? a = b, true : false; }

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
}
