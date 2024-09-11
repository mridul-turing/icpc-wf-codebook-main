/**
 * Author: Tamajit Banerjee
 * Description: kmp[x] computes the length of the longest prefix of s that ends at x
 * (abacaba -> 0010123). Time: O(n)
 * aut[i][j] = the length of the longest prefix of s that equals at s[0..i] + a + j. Time: O(n * 26)
 */
#pragma once
vector<int> kmp(const string& s) {
	vector<int> p(sz(s));
	rep(i, 1, sz(s)) {
		int g = p[i - 1];
		while (g && s[i] != s[g]) g = p[g - 1];
		p[i] = g + (s[i] == s[g]);}
	return p;
}
vector<int> match(const string& s, const string& pat) {
	vi p = kmp(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
const char a = 'a'; const int alpha = 26;
void compute_automaton(string s, vector<vector<int>>& aut) {
	s += '#'; int n = s.size();
	vector<int> pi = kmp(s);
	aut.assign(n, vector<int>(alpha));
	for (int i = 0; i < n; i++) {
		for (int c = 0; c < alpha; c++) {
			if (i > 0 && a + c != s[i])
				aut[i][c] = aut[pi[i - 1]][c];
			else
				aut[i][c] = i + (a + c == s[i]);}}
}