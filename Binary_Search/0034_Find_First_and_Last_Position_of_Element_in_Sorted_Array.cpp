class Solution {
public:
    int firstOcc(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1, ans = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] > target) end = mid - 1;
            else if (nums[mid] < target) start = mid + 1;
            else {
                ans = mid;
                end = mid - 1;
            }
        }

        return ans;
    }

    int lastOcc(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1, ans = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] > target) end = mid - 1;
            else if (nums[mid] < target) start = mid + 1;
            else {
                ans = mid;
                start = mid + 1;
            }
        }

        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int first = firstOcc(nums, target);

        if (first == -1) return {-1, -1};

        return {first, lastOcc(nums, target)};
    }
};
