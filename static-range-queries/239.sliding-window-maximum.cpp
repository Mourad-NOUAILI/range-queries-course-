#include <bits/stdc++.h>
/*
 * @lc app=leetcode id=239 lang=cpp
 *
 * [239] Sliding Window Maximum
 */

// @lc code=start
class Solution {
public:
    void build(std::vector<int> nums, int n , int** & st) {
        for(int i = 0 ; i < n ; ++i) st[i][0] = nums[i];

        for(int j= 1 ; (1<<j) <= n ; ++j){
            for(int i = 0 ; i+(1<<j)-1 < n ; ++i) {
                st[i][j] = std::max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int RMQ(int** st, int l, int r){
        int len = r-l+1;
        int k = log2(len);
        int p=r+1-(1<<k);
        return std::max(st[l][k],st[p][k]);
    }

    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> ans;

        int m = log2(n) + 1;
        int** st = new int*[n];
        for(int i = 0 ; i < n ; ++i) st[i] = new int[m];
        build(nums,n,st);

        for (int i = 0 ; i <= n-k ; ++i)
            ans.push_back(RMQ(st,i,k+i-1));
        
        delete[] st;
        return ans;
    }
};
// @lc code=end

