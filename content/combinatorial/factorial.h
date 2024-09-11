/**
 * Author: islingr
 * Date: 2024-11-04
 * Source: folklore
 * Description: Computes $i!$ and $(i!)^{-1}$ for all $0 \le i < N$ modulo a prime.
 */
#pragma once

#include "../number-theory/ModPow.h"

constexpr int N = 1e6, mod = 1e9 + 7;
int fac[N], ifac[N];

fac[0] = 1;
rep(i, 1, N) fac[i] = (ll)i * fac[i - 1] % mod;
ifac[N - 1] = modpow(fac[N - 1], mod - 2);
per(i, 1, N) ifac[i - 1] = (ll)i * ifac[i] % mod;
