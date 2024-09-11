#pragma once
/**
 * Author: Tamajit Banerjee
 * Description: For each position in a string, computes p[0][i] = half len of even palin around pos i ([i - len, i + len -1])
 * p[1][i] = long odd (rounded down) [i - len, i + len].
 */
array<vector<int>, 2> manacher(const string& s) {
	int n = sz(s);
	array<vector<int>, 2> p = {vector<int>(n + 1), vector<int>(n)};
	rep(z, 0, 2) for (int i = 0, l = 0, r = 0; i < n; i++) {
		int t = r - i + !z;
		if (i < r) p[z][i] = min(t, p[z][l + t]);
		int L = i - p[z][i], R = i + p[z][i] - !z;
		while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
		if (R > r) l = L, r = R;
	}
	return p;
}
