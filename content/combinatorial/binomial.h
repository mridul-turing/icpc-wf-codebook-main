/**
 * Author: islingr
 * Date: 2024-11-04
 * Source: folklore
 * Description: Computes $\binom{n}{r}$ modulo a prime
 */
#pragma once

#include "factorial.h"

int C(int n, int r) {
	if (r < 0 || r > n) return 0;
	return (ll)fac[n] * ifac[r] % mod * ifac[n - r] % mod;
}
