/**
 * Author: islingr
 * Description: Returns the immediate dominator of each node reachable from root.
 * Time: $O((n + m) \alpha (n))$
 */
#pragma once

vi find_dominators(const vector<vector<int>> &g, int root) {
	int n = sz(g); vi pos(n, -1), ord, par(n, -1);
	auto dfs = [&](auto &self, int u) -> void {
		pos[u] = sz(ord); ord.push_back(u);
		for (auto v : g[u]) if(pos[v]==-1) par[v]=u, self(self,v);
	};
	dfs(dfs, root);
	vi p(n), best(n), sdom = pos;
	iota(all(p), 0); iota(all(best), 0);
	auto fb = [&](auto &self, int x) -> int {
		if (p[x] != x) {
			int u = self(self, p[x]);
			if (sdom[u] < sdom[best[x]]) best[x] = u;
			p[x] = p[p[x]];
		}
		if (sdom[best[p[x]]] < sdom[best[x]]) best[x] = best[p[x]];
		return best[x];
	};
	vector<vector<int>> gr(n), bucket(n);
	vi idom(n, -1), link(n, -1);
	rep(u, 0, n) for (auto v:g[u]) gr[v].push_back(u);
	per(it, 0, sz(ord)) {
		int w = ord[it];
		for (auto u : gr[w])
			if (pos[u] != -1) uin(sdom[w], sdom[fb(fb, u)]);
		idom[w] = ord[sdom[w]];
		for (auto u : bucket[w]) link[u] = fb(fb, u);
		for (auto u : g[w]) if (par[u] == w) p[u] = w;
		bucket[ord[sdom[w]]].push_back(w);
	}
	rep(it, 1, sz(ord)) idom[ord[it]] = idom[link[ord[it]]];
	return idom;
}
