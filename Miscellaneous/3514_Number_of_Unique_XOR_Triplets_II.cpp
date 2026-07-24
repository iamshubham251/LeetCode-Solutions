class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<bitset<2048>> dp(4);
        dp[0][0] = 1;

        for (int x : nums)
            for (int k = 2; k >= 0; k--)
                for (int v = 0; v < 2048; v++)
                    if (dp[k][v]) dp[k + 1][v ^ x] = 1;

        bitset<2048> ans = dp[3];
        for (int x : nums) ans[x] = 1;

        return ans.count();
    }
};
