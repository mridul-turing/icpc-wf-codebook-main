/**
 * Author: Tamajit Banerjee
 * Description: O(N * 26) 
 * node 1 - root with len -1, node 2 - root with len 0 , max suffix palindrome
 * num in node stores depth of the node along suffixlink 
 */
#pragma once
struct PalindromeTree {
	static constexpr int ALPHA = 26;
	struct node {
		int next[ALPHA], len, sufflink, num;
		node() { memset(next, 0, sizeof(next)); }
	};
	string s; vector<node> tree; 
	int num, suff; long long ans = 0;
	bool addLetter(int pos) {
		int cur = suff, curlen = 0, let = s[pos] - 'a';
		while (true) {
			curlen = tree[cur].len;
			if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
			cur = tree[cur].sufflink;
		}
		if (tree[cur].next[let]) {
			suff = tree[cur].next[let];
			return false;
		}
		suff = ++num;
		tree[num].len = tree[cur].len + 2;
		tree[cur].next[let] = num;
		if (tree[num].len == 1) {
			tree[num].sufflink = 2, tree[num].num = 1;
			return true;
		}
		while (true) {
			cur = tree[cur].sufflink, curlen = tree[cur].len;
			if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
				tree[num].sufflink = tree[cur].next[let];
				break;
			}
		}
		tree[num].num = 1 + tree[tree[num].sufflink].num;
		return true;
	}

	PalindromeTree(string s) : s(s), tree(sz(s) + 10) {
		num = 2, suff = 2, tree[1].len = -1;
		tree[1].sufflink = 1; tree[2].len = 0;
		tree[2].sufflink = 1;
		rep(i, 0, sz(s)) {addLetter(i); 
			ans += tree[suff].num;}
	}
};
