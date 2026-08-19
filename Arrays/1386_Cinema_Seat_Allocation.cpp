class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, set<int>> mp;

        for (auto &seat : reservedSeats) {
            mp[seat[0]].insert(seat[1]);
        }

        int ans = 2 * n;

        for (auto &[row, seats] : mp) {
            bool left = true;
            bool middle = true;
            bool right = true;

            for (int seat : seats) {
                if (seat >= 2 && seat <= 5)
                    left = false;

                if (seat >= 4 && seat <= 7)
                    middle = false;

                if (seat >= 6 && seat <= 9)
                    right = false;
            }

            ans -= 2;

            if (left && right)
                ans += 2;
            else if (left || middle || right)
                ans += 1;
        }

        return ans;
    }
};
