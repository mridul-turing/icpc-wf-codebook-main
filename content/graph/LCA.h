/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
	int T = 0;
	vi tin, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : tin(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		tin[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(tin[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(tin[a], tin[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};
