/**
 * Author: islingr
 * Date: 2024-11-04
 * License: CC0
 * Source: me
 * Description:
 * Time: O(\log N).
 * Usage: using S = int;
 * S op(S a, S b) { return max(a, b); }
 * S e() { return -inf; }
 * using F = int;
 * S mapping(F f, S x) { return x + f; }
 * F composition(F f, F g) { return f + g; }
 * F id() { return 0; }
 * lazy_segtree<S, op, e, F, mapping, composition, id> t(n);
 */
#pragma once

template <class S, S (*op)(S, S), S (*e)(), class F,
	 S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
	int n; vector<S> t; vector<F> lz;
	lazy_segtree(int n = 0) : n{n} {
		int sz = 1; while (sz < n) sz *= 2;
		t.assign(2 * sz, e()); lz.assign(sz, id());
	}

	void apply_node(int v, F f) {
		if (v < sz(lz)) lz[v] = composition(f, lz[v]);
		t[v] = mapping(f, t[v]);
	}
	void push(int v) {
		if (v < sz(lz)) {
			apply_node(v << 1 | 0, lz[v]);
			apply_node(v << 1 | 1, lz[v]);
			lz[v] = id();
		}
	}
	void pull(int v) { t[v] = op(t[v << 1], t[v << 1 | 1]); }

	S prod(int lo, int hi) { // query [lo, hi)
		auto rec = [&](auto self, int v, int l, int r) -> S {
			if (r <= lo || hi <= l) return e();
			if (lo <= l && r <= hi) return t[v];
			push(v); auto m = l + (r - l) / 2;
			return op(self(self, v << 1 | 0, l, m),
				  self(self, v << 1 | 1, m, r));
		};
		return rec(rec, 1, 0, n);
	}
	void apply(int lo, int hi, F f) { // apply f to [lo, hi)
		auto rec = [&](auto self, int v, int l, int r) -> void {
			if (r <= lo || hi <= l) return;
			if (lo <= l && r <= hi) return apply_node(v, f);
			push(v); auto m = l + (r - l) / 2;
			self(self, v << 1 | 0, l, m);
			self(self, v << 1 | 1, m, r);
			pull(v);
		};
		rec(rec, 1, 0, n);
	}
	void set(int p, S x) {
		auto rec = [&](auto self, int v, int l, int r) -> void {
			if (r - l == 1) return t[v] = x, void();
			push(v); auto m = l + (r - l) / 2;
			if (p < m) self(self, v << 1 | 0, l, m);
			else       self(self, v << 1 | 1, m, r);
			pull(v);
		};
		rec(rec, 1, 0, n);
	}
};
