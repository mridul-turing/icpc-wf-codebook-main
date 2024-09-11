/**
 * Author: islingr
 * Date: 2024-04-11
 * License: CC0
 * Source: Folklore
 * Description: Compute right fold of \texttt{op} of elements in
 * stack. Error on querying empty stack.
 * Usage: int op(int a, int b) { return min(a, b); }
 * FoldStack<int, op> st;
 * Time: O(1)
 */
#pragma once

template <class S, S (*op)(S, S)>
struct FoldStack {
	stack<pair<S, S>> st;
	void push(S x) {
		st.emplace(x, empty() ? x : op(x, st.top().second));
	}
	S pop() {
		auto res = st.top().first;
		return st.pop(), res;
	}
	S top() { return st.top().second; }
	bool empty() { return st.empty(); }
};
