class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        for (int i = nums[0]; i <= nums.back(); i++) {
            if (!binary_search(nums.begin(), nums.end(), i)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
