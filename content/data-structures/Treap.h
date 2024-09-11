/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Node {
	Node *l = nullptr, *r = nullptr;
	int val, y, c = 1;
	Node(int val) : val(val), y(rng()) {}
	void push();
	void pull();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::push() {}
void Node::pull() { c = cnt(l) + cnt(r) + 1; }

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	n->push();
	if (cnt(n->l) >= k) {  // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->pull();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1);  // and just "k"
		n->r = pa.first;
		n->pull();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->push();
		l->r = merge(l->r, r);
		l->pull();
		return l;
	} else {
		r->push();
		r->l = merge(l, r->l);
		r->pull();
		return r;
	}
}
