class Solution {
public:
    vector<vector<int>> ans;
    void backtrack(int start, int target,
                   vector<int>& cur, vector<int>& nums) {

        if (target == 0) {
            ans.push_back(cur);
            return;
        }
        for (int i = start; i < nums.size(); i++) {

            if (nums[i] > target)
                continue;
            cur.push_back(nums[i]);
            backtrack(i, target - nums[i], cur, nums);

            cur.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> cur;
        backtrack(0, target, cur, candidates);
        return ans;
    }
};
