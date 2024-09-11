/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Takes as input the full adjacency list.
 * VALS\_EDGES being true means that values are stored in the edges,
 * as opposed to the nodes. Root must be 0.
 * Status: stress-tested against old HLD
 */
#pragma once

template <bool VALS_EDGES> struct HLD {
	int N, T = 0;
	vector<vi> g;
	vi par, sub, dep, nxt, tin;
	HLD(vector<vi> g_)
		: N(sz(g_)), g(g_), par(N, -1), sub(N, 1), dep(N),
		  nxt(N),tin(N){ dfsSz(0); dfsHld(0); }
	void dfsSz(int u) {
		for (int& v : g[u]) {
			g[v].erase(find(all(g[v]), u));
			par[v] = u, dep[v] = dep[u] + 1;
			dfsSz(v);
			sub[u] += sub[v];
			if (sub[v] > sub[g[u][0]]) swap(v, g[u][0]);
		}
	}
	void dfsHld(int u) {
		tin[u] = T++;
		for (int v : g[u]) {
			nxt[v] = (v == g[u][0] ? nxt[u] : v);
			dfsHld(v);
		}
	}
	template <class F> void process_path(int u, int v, F op) {
		for (; nxt[u] != nxt[v]; v = par[nxt[v]]) {
			if (dep[nxt[u]] > dep[nxt[v]]) swap(u, v);
			op(tin[nxt[v]], tin[v] + 1);
		}
		if (dep[u] > dep[v]) swap(u, v);
		op(tin[u] + VALS_EDGES, tin[v] + 1);
	}
	// process_subtree(u): [tin[u] + VALS_EDGES, tin[u] + sub[v])
};
