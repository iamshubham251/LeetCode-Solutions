class Solution {
public:
    vector<vector<int>> ans;
    void solve(vector<int>& nums,
               vector<int>& path,
               vector<bool>& used)
    {
        if(path.size() == nums.size())
        {
            ans.push_back(path);
            return;
        }
        for(int i = 0; i < nums.size(); i++)
        {
            if(used[i])
                continue;

            path.push_back(nums[i]);
            used[i] = true;
            solve(nums, path, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<int> path;
        vector<bool> used(nums.size(), false);

        solve(nums, path, used);

        return ans;
    }
};
