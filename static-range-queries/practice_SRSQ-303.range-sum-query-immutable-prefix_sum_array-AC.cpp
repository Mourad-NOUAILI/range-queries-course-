#include <bits/stdc++.h>
/*
 * @lc app=leetcode id=303 lang=cpp
 *
 * [303] Range Sum Query - Immutable
 */

// @lc code=start
class NumArray {
    private:
        std::vector<long> pre;
    public:
        NumArray(std::vector<int>& nums) {
          // Build the prefix sum array 
          int n = nums.size();
          pre.push_back(0);
          for (int i = 0 ; i < n ; ++i) pre.push_back(pre.back()+nums[i]);
        }
        
        int sumRange(int left, int right) {
          return pre[right+1] - pre[left];
        }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
// @lc code=end

