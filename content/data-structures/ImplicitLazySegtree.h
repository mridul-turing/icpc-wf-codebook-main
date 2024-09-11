/**
 * Author: islingr
 * Date: 2024-11-04
 * License: CC0
 * Source: me
 * Description: Replace \texttt{create()} in persistent lazy segtree.
 * Usage: T t(n); T::Node* root{nullptr};
 * t.create(root); // Important, empty tree otherwise
 */
#pragma once

#include "PersistentLazySegtree.h"

static Node* create(Node* &x) { return x ? : x = new Node(); }

/**
template <class S, S (*op)(S, S), S (*e)(), class F,
	 S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct implicit_lazysegtree {
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
	static Node* create(Node* &x) { return x ?:x = new Node(); }

	int n; Node *root;
	implicit_lazysegtree(int n = 0) : n{n}, root{nullptr} { create(root); }

	S prod(int lo, int hi) { // query [lo, hi)
		auto rec = [&](auto self, Node* v, int l, int r) -> S {
			if (r <= lo || hi <= l) return e();
			if (lo <= l && r <= hi) return v->val;
			v->push(); auto m = l + (r - l) / 2;
			return op(self(self, v->l, l, m),
				  self(self, v->r, m, r));
		};
		return rec(rec, root, 0, n);
	}
	void apply(int lo, int hi, F f) { // apply f to [lo, hi)
		auto rec = [&](auto self, Node* v, int l, int r) -> void {
			if (r <= lo || hi <= l) return;
			if (lo <= l && r <= hi) return v->apply(f);
			v->push(); auto m = l + (r - l) / 2;
			self(self, v->l, l, m);
			self(self, v->r, m, r);
			v->pull();
		};
		rec(rec, root, 0, n);
	}
	void set(int p, S x) {
		auto rec = [&](auto self, Node* v, int l, int r) -> void {
			if (r - l == 1) return v->val = x, void();
			v->push(); auto m = l + (r - l) / 2;
			if (p < m) self(self, v->l, l, m);
			else       self(self, v->r, m, r);
			v->pull();
		};
		rec(rec, root, 0, n);
	}
};
*/
