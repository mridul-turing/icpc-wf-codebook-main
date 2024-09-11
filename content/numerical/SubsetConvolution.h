/**
 * Author: islingr
 * Date: 2024-1104
 * License: CC0
 * Source: me
 * Description: Compute $c(S) = \sum_{T \subseteq S} a(T) b(S \backslash T)$.
 * Time: O(N \log^2 N)
 */
#pragma once

vi conv(vi a, vi b) {
	int n = 31 - __builtin_clz(sz(a));
	vector f(n + 1, vi(1 << n, 0)); auto g = f, h = f;
	rep(S, 0, 1 << n) {
		auto i = __builtin_popcount(S);
		f[i][S] = a[S]; g[i][S] = b[S];
	}
	rep(i, 0, n + 1) rep(j, 0, n) rep(S, 0, 1 << n)
		if (S >> j & 1) { // subset sum
			f[i][S] += f[i][S ^ (1 << j)];
			g[i][S] += g[i][S ^ (1 << j)];
		}
	rep(i, 0, n + 1) rep(j, 0, i + 1) rep(S, 0, 1 << n)
		h[i][S] += f[j][S] * g[i - j][S];
	rep(i, 0, n + 1) rep(j, 0, n) rep(S, 0, 1 << n)
		if (S >> j & 1) h[i][S] -= h[i][S ^ (1 << j)];
	vi c(1 << n);
	rep(S, 0, 1 << n) c[S] = h[__builtin_popcount(S)][S];
	return c;
}
