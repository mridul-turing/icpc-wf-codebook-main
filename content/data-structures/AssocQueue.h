/**
 * Author: islingr
 * Date: 2024-04-11
 * License: CC0
 * Source: Folklore
 * Description: Compute $\texttt{op}$ of all values in
 * queue for an associative binary operator. Error on querying
 * empty queue.
 * Usage: int op(int a, int b) { return min(a, b); }
 * AssocQueue<int, op> st;
 * Time: O(1) amortized
 */
#pragma once

#include "FoldStack.h"

template <class S, S (*op)(S, S)>
struct AssocQueue {
	static S op2(S a, S b) { return op(b, a); } // can remove for commutative functions
	FoldStack<S, op> s1;  // swap op, op2 to flip order of
	FoldStack<S, op2> s2; // evaluation, in front() too

	void push(S x) { s1.push(x); }
	S pop() {
		if (s2.empty())
			while (!s1.empty()) s2.push(s1.pop());
		return s2.pop();
	}
	S front() {
		if (s1.empty()) return s2.top();
		if (s2.empty()) return s1.top();
		return op(s1.top(), s2.top()); // swap here too
	}
	bool empty() { return s1.empty() && s2.empty(); }
};
