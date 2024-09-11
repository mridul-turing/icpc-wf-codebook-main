/**
 * Author: Tamajit Banerjee
 * Description: Ukkonen's algorithm for online suffix tree construction.
 * Each node contains indices [l, r) into the string, and a list of child nodes.
 * Suffixes are given by traversals of this tree, joining [l, r) substrings.
 * The root is 0 (has l = -1, r = 0), non-existent children are -1.
 * To get a complete tree, append a dummy symbol -- otherwise it may contain an incomplete path (still useful for substring matching, though).
 * finding the lexographically kth smallest substring (repeatation allowed). (s + ('z' + 1)) dfs on nodes to store subtree info
 * dfs to find the kth on ( remember edges have more than 1 char) 
 * array of transitions (state, letter), left and right boundaries of the substring of a which correspond to
 * incoming edge p[N] = parent of the node, s[N] = suffix link, m = the num. of nodes
 * v = cur node, q = cur position
 */
#pragma once
struct SuffixTree {
	enum { ALPHA = 28 };
	int toi(char c) { return c - 'a'; }
	string a;
	int mxn, v = 0, q = 0, m = 2;
	vi r, s, p, l; vector<array<int, ALPHA>> t;
	vector<ll> nodes, leaf;
	
	SuffixTree(string _a):a(_a),mxn{2*sz(a)+10},r(mxn,sz(a)),s(mxn),p(mxn),l(mxn),t(mxn),nodes(mxn),leaf(mxn) {
		for (auto& x : t) fill(all(x), -1);
		fill(all(t[1]), 0); s[0] = 1;
		l[0] = l[1] = -1; r[0] = r[1] = 0;
		rep(i, 0, sz(a)) ukkadd(i, toi(a[i]));}

	void ukkadd(int i, int c) {
	suff:
		if (r[v] <= q) {
			if (t[v][c] == -1) {
				t[v][c] = m, l[m] = i;
				p[m++] = v, v = s[v], q = r[v];
				goto suff;}
			v = t[v][c];
			q = l[v];}
		if (q == -1 || c == toi(a[q])) ++q;
		else {
			l[m + 1] = i, p[m + 1] = m;
			l[m] = l[v], r[m] = q;
			p[m] = p[v], t[m][c] = m + 1;
			t[m][toi(a[q])] = v;
			l[v] = q, p[v] = m;
			t[p[m]][toi(a[l[m]])] = m;
			v = s[p[m]], q = l[m];
			while (q < r[m]) {
				v = t[v][toi(a[q])];
				q += r[v] - l[v];}
			s[m] = q == r[m] ? v : m + 2;
			q = r[v] - (q - r[m]);
			m += 2;
			goto suff;}}

	void dfs_nodes(int node) {
		bool pre = false;
		nodes[node] = 0, leaf[node] = 0;
		rep(c, 0, ALPHA) if (t[node][c] != -1) {
			pre |= true; dfs_nodes(t[node][c]);
			nodes[node] += nodes[t[node][c]];
			leaf[node] += leaf[t[node][c]];}
		if (node) { if (!pre) {
				leaf[node] = 1, nodes[node] = r[node] - l[node] - 1;
			} else
				nodes[node] += (r[node] - l[node]) * leaf[node];}
	}};
	// void kth(int node, ll k, string& ans) {
	// 	int cur = max(l[node], 0);
	// 	while (k > 0 and cur < r[node]) {
	// 		k -= leaf[node], ans += a[cur++];
	// 	}
	// 	if (k <= 0) return;
	// 	rep(c, 0, ALPHA) if (t[node][c] != -1) {
	// 		if (nodes[t[node][c]] >= k) {
	// 			kth(t[node][c], k, ans);
	// 			return;
	// 		}
	// 		k -= nodes[t[node][c]];
	// 	}
	// }
	// static string kth_substring(string s, ll k) {
	// 	SuffixTree st(s + (char)('z' + 1));
	// 	st.dfs_nodes(0);
	// 	string ans = "";
	// 	st.kth(0, k, ans);
	// 	return ans;
	// }
