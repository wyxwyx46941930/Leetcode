### leetcode 300. Longest Increasing Subsequence 

#### 题目：

Given an unsorted array of integers, find the length of longest increasing subsequence.

**Example:**

``` bash
Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
```

**Note:**

- There may be more than one LIS combination, it is only necessary for you to return the length.
- Your algorithm should run in O(*n2*) complexity.

**Follow up:** Could you improve it to O(*n* log *n*) time complexity?

-----

#### 解法：

这个题是让我们在序列中找出最长的递增序列的数目，思路大致是动态规划。

我们创立一个`dp`数组记录`nums[i]`结尾的最长上升子序列，`dp[i]`也即我们求坐标`i`之前的所有比`nums[i]`小的`nums[j]`的最大`dp[j]`值再+1 即可。

-----

#### 代码：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),1);
        if(nums.size()==0)
            return 0;
        int ans = 1;
        for(int i=1;i<nums.size();i++){
            int maxDp = 0;
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i])
                    maxDp = max(maxDp,dp[j]);
            }
            dp[i] = maxDp + 1;
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};
```

