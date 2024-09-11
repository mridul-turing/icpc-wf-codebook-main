/**
 * Author: islingr
 * Date: 2024-04-12
 * License: CC0
 * Source: me
 * Description: $\texttt{fft\_2d(a)}$ computes $\hat f(y, x) = \sum_{jk} a[j][k] \omega_0^{jx} \omega_1^{kx}$ for all $x, y$,
 * where $\omega_0 = \exp(2\pi i / N)$, $\omega_1 = \exp(2\pi j / M)$. {\bf Note that $x, y$ are swapped.} $N, M$ must be powers of 2.
 * For inverse FT, compute FT, \texttt{reverse(start + 1, end)} in both dimensions, divide by $NM$.
 * This is for complex polynomials, can easily be modified for others.
 * Time: $O(NM \log NM)$
 * Status: tested on ICPC WF 2021 G
 */
#pragma once

#include "FastFourierTransform.h"

using C = complex<double>;
using poly = vector<C>;
using poly_2d = vector<poly>;

void fft_2d(poly_2d& a) { // returns transpose
	const int n = sz(a), Ln = 31 - __builtin_clz(n);
	const int m = sz(a[0]), Lm = 31 - __builtin_clz(m);
	assert(n == 1 << Ln);
	for (auto& v : a) assert(sz(v) == (1 << Lm)), fft(v);
	poly_2d at(m, poly(n, 0)); a.resize(n, poly(m, 0));
	rep(i, 0, m) rep(j, 0, n) at[i][j] = a[j][i];
	for (auto& v : at) fft(v);
	a = move(at);
}

poly_2d conv_2d(poly_2d a, poly_2d b) {
	if (a.empty() || b.empty()) return {};
	const int Ln=32-__builtin_clz(sz(a)+sz(b)-1), n=1<<Ln;
	const int Lm=32-__builtin_clz(sz(a[0])+sz(b[0])-1), m=1<<Lm;

	a.resize(n), b.resize(n); // make power of 2
	rep(i, 0, n) a[i].resize(m), b[i].resize(m);
	fft_2d(a), fft_2d(b); // FT
	rep(i, 0, m) rep(j, 0, n) a[i][j] *= b[i][j];
	fft_2d(a); // inverse FT
	for (auto& row : a) reverse(1 + all(row));
	reverse(1 + all(a));
	const double inv = 1.0 / (n * m);
	for (auto& row : a) for (auto& x : row) x *= inv;
	return a;
}
