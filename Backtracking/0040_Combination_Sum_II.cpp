class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void solve(int idx, int target, vector<int>& candidates) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }
        for (int i = idx; i < candidates.size(); i++) {
            if (i > idx && candidates[i] == candidates[i - 1])
                continue;
            if (candidates[i] > target)
                break;
            path.push_back(candidates[i]);
            solve(i + 1, target - candidates[i], candidates);

            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        solve(0, target, candidates);
        return ans;
    }
};
