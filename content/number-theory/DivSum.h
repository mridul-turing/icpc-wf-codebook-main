/**
 * Author: Simon Lindholm
 * Date: 2015-06-23
 * License: CC0
 * Source: own work
 * Description: Sums of div'ed arithmetic progressions.
 *
 * \texttt{divsum(to, c, k, m)} = $\sum_{i=0}^{\mathrm{to}-1}\lfloor\frac{ki+c}{m}\rfloor$.
 * Time: $\log(m)$, with a large constant.
 * Status: Tested for all |k|,|c|,to,m <= 50, and on kattis:aladin
 */
#pragma once

ull sumsq(ull to) { return to / 2 * ((to-1) | 1); }
/// ^ written in a weird way to deal with overflows correctly

ull divsum(ull to, ull c, ull k, ull m) {
	ull res = k / m * sumsq(to) + c / m * to;
	k %= m; c %= m;
	if (!k) return res;
	ull to2 = (to * k + c) / m;
	return res + (to - 1) * to2 - divsum(to2, m-1 - c, m, k);
}
