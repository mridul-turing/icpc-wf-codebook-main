/**
 * Author: islingr
 * Date: 2024-11-04
 * License: CC0
 * Source: me
 * Description: Computes min $l$ such that $g[l, r)$ is true for a monotone $g$.
 * $g(\texttt{e()})$ must be true. Add to segtree struct,
 * works on both segment trees.
 * Time: O(\log N).
 * Usage: t.min_left(r, [x](S y) { return y < x; });
 * Rightmost $l \le r$ with value at $l - 1$ $\ge x$, assuming t stores $\max$.
 */
#pragma once

#include "LazySegmentTree.h"

template <class G> int min_left(int p, G g) {
	assert(g(e())); S x{e()};
	auto rec = [&](auto self, int v, int l, int r) -> int {
		if (r - l == 1) {
			auto nxt_x = op(t[v], x);
			return g(nxt_x) ? x = nxt_x, l : r;
		}
		push(v); // remove for non-lazy segtree
		auto m = l + (r - l) / 2;
		if (p > m) {
			if (p >= r) {
				auto nxt_x = op(t[v], x);
				if (g(nxt_x)) return x = nxt_x, l;
			}
			auto idx = self(self, v << 1 | 1, m, r);
			if (idx > m) return idx;
		}
		return self(self, v << 1 | 0, l, m);
	};
	return rec(rec, 1, 0, n); // n -> sz for non-lazy
}

