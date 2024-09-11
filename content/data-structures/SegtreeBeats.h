/**
 * Author: islingr
 * Date: 2024-04-11
 * License: CC0
 * Description: For supporting range $A_i \leftarrow \min(A_i, x)$ operations,
 * break if $\max < x$ and apply lazy update if $\text{second max} < x$.
 * Source: folklore
 * Time: O(\log N) amortized
 */

#include "LazySegmentTree.h"
