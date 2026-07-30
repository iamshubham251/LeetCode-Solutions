class Solution {
public:
    static const long long LIMIT = 1000000LL;
    long long comb(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);

        long double res = 1;

        for (int i = 1; i <= r; i++) {
            res = res * (n - r + i) / i;
            if (res > LIMIT) return LIMIT + 1;
        }

        return min((long long)(res + 0.5), LIMIT + 1);
    }
    long long countWays(vector<int>& cnt) {
        int rem = 0;
        for (int x : cnt) rem += x;

        long long ans = 1;

        int left = rem;

        for (int x : cnt) {
            if (x == 0) continue;

            long long ways = comb(left, x);

            if (ans > LIMIT / ways)
                ans = LIMIT + 1;
            else
                ans *= ways;

            ans = min(ans, LIMIT + 1);

            left -= x;
        }

        return ans;
    }
    string smallestPalindrome(string s, int k) {

        vector<int> freq(26);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }

        if (countWays(half) < k)
            return "";

        string left = "";
        int len = s.size() / 2;

        for (int pos = 0; pos < len; pos++) {

            for (int c = 0; c < 26; c++) {

                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }
        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};
