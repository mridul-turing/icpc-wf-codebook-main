/**
 * Author: pajenegod
 * Description: \texttt{root\_dp[u]} gives value at $u$ when $u$ is root,
 * \texttt{edge\_dp[u][e]} gives value for edge $e$ of $u$ when $u$ is root.
 */

const auto exclusive = [](const auto& a, const auto& base, const auto& merge_into, int vertex) {
	using Aggregate = decay_t<decltype(base)>;
	int n = sz(a); vector<Aggregate> b(n, base);
	for (int bit = (int)__lg(n); bit >= 0; --bit) {
		per(i, 0, n) b[i] = b[i >> 1];
		int sz = n - (n & !bit);
		rep(i, 0, sz) {
			int index = (i >> bit) ^ 1;
			b[index] = merge_into(b[index], a[i], vertex, i);
		}
	}
	return b;
};
// MergeInto: Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
// Base: Vertex(int) -> Aggregate
// FinalizeMerge: Aggregate * Vertex(int) * EdgeIndex(int) -> Value
const auto rerooter = [](const auto& g, const auto& base, const auto& merge_into, const auto& finalize_merge) {
	using Aggregate = decay_t<decltype(base(0))>;
	using Value = decay_t<decltype(finalize_merge(base(0), 0, 0))>;
	int n = sz(g); vector<Value> root_dp(n), dp(n);
	vector<vector<Value>> edge_dp(n), redge_dp(n);
	vector<int> bfs, par(n);
	bfs.reserve(n); bfs.push_back(0);
	rep(i, 0, n) {
		int u = bfs[i];
		for (auto v : g[u]) {
			if (par[u] == v) continue;
			par[v] = u;
			bfs.push_back(v);
		}
	}
	per(i, 0, n) {
		int u = bfs[i], p_e = -1;
		Aggregate aggregate = base(u);
		rep(e, 0, sz(g[u])) {
			int v = g[u][e];
			if (par[u] == v) p_e = e;
			else aggregate = merge_into(aggregate, dp[v], u, e);
		}
		dp[u] = finalize_merge(aggregate, u, p_e);
	}
	for (auto u : bfs) {
		dp[par[u]] = dp[u];
		edge_dp[u].reserve(g[u].size());
		for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
		auto dp_ex = exclusive(edge_dp[u], base(u), merge_into, u);
		redge_dp[u].reserve(g[u].size());
		rep(i, 0, sz(dp_ex)) redge_dp[u].push_back(finalize_merge(dp_ex[i], u, i));
		root_dp[u] = finalize_merge(n > 1 ? merge_into(dp_ex[0], edge_dp[u][0], u, 0) : base(u), u, -1);
		rep(i, 0, sz(g[u])) dp[g[u][i]] = redge_dp[u][i];
	}
	return make_tuple(move(root_dp), move(edge_dp), move(redge_dp));
};
