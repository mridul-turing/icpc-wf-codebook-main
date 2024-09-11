/**
 * Author: islingr
 * Date: 2024-04-11
 * License: CC0
 * Description:
 * Source: folklore
 * Usage: using S = int;
 * S op(S a, S b) { return max(a, b); }
 * S e() { return -inf; }
 * segtree<S, op, e> t(n);
 * Time: O(\log N)
 */
#pragma once

template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
	int sz; vector<S> t;
	segtree(int n = 0) : sz{1} { // can replace with just n
		while (sz < n) sz *= 2;
		t.assign(2 * sz, e());
	}
	void set(int pos, S val) {
		for (t[pos += sz] = val; pos /= 2;)
			t[pos] = op(t[pos << 1], t[pos << 1|1]);
	}
	S prod(int l, int r) { // query [l, r)
		S a = e(), b = e();
		for (l += sz, r += sz; l < r; l /= 2, r /= 2) {
			if (l & 1) a = op(a, t[l++]);
			if (r & 1) b = op(t[--r], b);
		}
		return op(a, b);
	}
};
