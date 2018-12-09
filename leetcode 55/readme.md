### leetcode 55. Jump Game 

#### 题目：

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

**Example 1:**

```
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2:**

```
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```

----

#### 解法：

这个题可以使用搜索遍历求解；

从数组以及其下标从前往后搜，数组下标 N 表示已经移动 N 步，数组元素 nums[N] 表示当前位置最大可以移动几步，我们要求的能否到达最终结点其实就是在**找当前已经移动的步数与可移动的步数之和是否能够大于数组的长度-1（由于下标是从 0 开始，所以要数组长度 - 1）** 

所以有了这个思路，我们就可以实现代码。

---

#### 代码：

```
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size() - 1 ;
        int rch = 0;
        for(int i = 0; i <= rch; i ++)
        {
            rch = max(rch, nums[i]+i);
            if(rch > n-1)
                return true;
        }
        return false;
    }
};
```