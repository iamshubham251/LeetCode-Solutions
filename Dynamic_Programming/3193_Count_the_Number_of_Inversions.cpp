class Solution {
public:
    const int MOD = 1e9 + 7;

    int numberOfPermutations(int n, vector<vector<int>>& requirements) {

        vector<int> need(n, -1);
        for (auto &x : requirements) {
            if (need[x[0]] != -1 && need[x[0]] != x[1])
                return 0;
            need[x[0]] = x[1];
        }

        if (need[0] > 0) return 0;

        int maxInv = 0;
        for (int x : need)
            if (x != -1)
                maxInv = max(maxInv, x);

        vector<vector<int>> dp(n + 1, vector<int>(maxInv + 1, 0));
        dp[1][0] = 1;

        for (int len = 2; len <= n; len++) {

            for (int inv = 0; inv <= maxInv; inv++) {

                for (int add = 0; add <= min(inv, len - 1); add++) {

                    dp[len][inv] += dp[len - 1][inv - add];
                    dp[len][inv] %= MOD;
                }
            }
            if (need[len - 1] != -1) {

                for (int inv = 0; inv <= maxInv; inv++) {

                    if (inv != need[len - 1])
                        dp[len][inv] = 0;
                }
            }
        }

        if (need[n - 1] != -1)
            return dp[n][need[n - 1]];

        int ans = 0;
        for (int inv = 0; inv <= maxInv; inv++)
            ans = (ans + dp[n][inv]) % MOD;

        return ans;
    }
};
