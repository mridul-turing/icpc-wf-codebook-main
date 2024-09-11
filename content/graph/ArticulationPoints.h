/**
 * Author: islingr
 * Source: folklore
 * Description: In the biconnected components code, $\texttt{at}$
 * is an articulation point only if
 * \begin{itemize}
 * \item it is the root and has > 1 children in the tree (not in original graph),
 * \item it is not the root and there's a child (tree) edge such that $\texttt{up} \ge \texttt{me}$.
 * \end{itemize}
 */
#pragma once

#include "BiconnectedComponents.h"
