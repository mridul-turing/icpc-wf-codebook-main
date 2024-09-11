/**
 * Author: Tamajit Banerjee
 * Description: Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * backp stores the ind of the longest string which forms a suffix of the string ending at i.
 * back info in a node is the suffix link. final N gives the transition from find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns) that start at each position (shortest first). 
 * Duplicate patterns are allowed; empty patterns are not.
 * Time: construction takes $O(26N)$, where $N=$ sum of length of patterns.
 */
#pragma once

struct AhoCorasick {
	enum { alpha = 26, first = 'a' };  // Remeber to change this!
	struct Node {
		int back, next[alpha], start = -1, end = -1, nmatches = 0; // (nmatches is optional)
		Node(int v) { memset(next, v, sizeof(next)); }
		// add variables to store extra elements to back prop
		// int vis = 0;
	};
	vector<Node> N;
    vector<int> backp; // endpos
	vector<vector<int> > adj;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N);
              N.emplace_back(-1);
			} else n = m;
        }
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j; N[n].nmatches++;
		// endpos[j] = n;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		// endpos.resize(sz(pat));
		rep(i, 0, sz(pat)) insert(pat[i], i);
		N[0].back = sz(N); N.emplace_back(0);
		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i, 0, alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
		// take out info of patterns form a tree using .back and prop back
		adj.resize(sz(N));
		rep(i,0,sz(N)-1)
		 	adj[N[i].back].push_back(i);
	}
	// if you need to something up the tree
	// void treeup(int u){
	//	   rep(i,0,sz(adj[u])){
	//		   treeup(adj[u][i]);
	//		   N[u].vis += N[adj[u][i]].vis;
	//	   }
	// }
	vector<int> find(string word) {
		int n = 0;
		vector<int> res;  // ll count = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// N[n].vis++;
			// count += N[n].nmatches;
		}
		// treeup(sz(N)-1);
		return res;
	}
	vector<vector<int>> findAll(vector<string>& pat, string word) {
		vector<int> r = find(word);
		vector<vector<int>> res(sz(word));
		rep(i, 0, sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
