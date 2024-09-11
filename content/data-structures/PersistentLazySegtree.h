/**
 * Author: islingr
 * Date: 2024-11-04
 * License: CC0
 * Source: me
 * Description: Same syntax as lazy segtree.
 * Use bump allocator, SmallPtr or implicit
 * indices for better performance.
 * Remove instances of \texttt{F} to make it non-lazy,
 * don't remove \texttt{push()}, children if empty
 * need to be created.
 * Time: O(\log N).
 * Usage: using T = persistent_lazysegtree<...>;
 * T t(n); T::Node* root{nullptr};
 * root = t.set(root, i, x);
 * root = t.apply(root, l, r, f);
 * auto res = t.prod(root, l, r);
 */
#pragma once

template <class S, S (*op)(S, S), S (*e)(), class F,
	 S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct persistent_lazysegtree {
	struct Node {
		Node *l = nullptr, *r = nullptr;
		S val = e(); F lz = id();

		void apply(F f) {
			lz = composition(f, lz);
			val = mapping(f, val);
		}
		void push() {
			create(l)->apply(lz);
			create(r)->apply(lz);
			lz = id();
		}
		void pull() { val=op(l ? l->val : e(), r ? r->val : e()); }
	};
	static Node* create(Node* &x) {
		return x = x ? new Node(*x) : new Node();
	}

	int n;
	persistent_lazysegtree(int n = 0) : n{n} { }

	S prod(Node* root, int lo, int hi) { // [lo, hi)
		auto rec = [&](auto self, Node* v, int l, int r) -> S {
			if (r <= lo || hi <= l) return e();
			if (lo <= l && r <= hi) return v->val;
			v->push(); auto m = l + (r - l) / 2;
			return op(self(self, v->l, l, m),
				  self(self, v->r, m, r));
		};
		return root ? rec(rec, root, 0, n) : e();
	}
	Node* apply(Node* root, int lo, int hi, F f) { // [lo, hi)
		auto rec = [&](auto self, Node* v, int l, int r) -> void {
			// return v to get new node of [l, r)
			if (r <= lo || hi <= l) return;
			if (lo <= l && r <= hi) return v->apply(f);
			v->push(); auto m = l + (r - l) / 2;
			self(self, v->l, l, m);
			self(self, v->r, m, r);
			v->pull();
		};
		return rec(rec, create(root), 0, n), root;
	}
	Node* set(Node* root, int p, S x) {
		auto rec = [&](auto self, Node* v, int l, int r) -> void {
			if (r - l == 1) return v->val = x, void();
			v->push(); auto m = l + (r - l) / 2;
			if (p < m) self(self, v->l, l, m);
			else       self(self, v->r, m, r);
			v->pull();
		};
		return rec(rec, create(root), 0, n), root;
	}
};
