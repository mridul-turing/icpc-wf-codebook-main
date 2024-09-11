Z summation_i_power_k (int n, int k) {
        if (n == 0) return 0;
        Z a[k + 3];
        for (int i = 1; i <= k + 2; i++) a[i] = (a[i - 1] + power(Z(i), k));
        if (n <= k + 2) return a[n];
        Z totn = 1, tot = 1, ans = 0;
        for (int i = 1; i <= k + 2; i++) totn *= (n - i);
        for (int i = 2; i <= k + 2; i++) tot *= (1 - i);
        for (int i = 1; i <= k + 2; tot = tot * i / (i - k - 2), i++)
                ans += a[i] * totn / (n - i) / tot;
        return ans;
}