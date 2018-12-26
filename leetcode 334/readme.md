### leetcode 334. Increasing Triplet Subsequence 

#### 题目：

Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:

> Return true if there exists *i, j, k* 
> such that *arr[i]* < *arr[j]* < *arr[k]* given 0 ≤ *i* < *j* < *k* ≤ *n*-1 else return false.

**Note:** Your algorithm should run in O(*n*) time complexity and O(*1*) space complexity.

**Example 1:**

```bash
Input: [1,2,3,4,5]
Output: true
```

**Example 2:**

```bash
Input: [5,4,3,2,1]
Output: false
```

-----

#### 解法：

这个题是让我们判断在给定数组中能否找到一个递增序列，且这个序列坐标可以不连续。

如果在不考虑时间复杂度的情况下，我们可以使用三重循环逐个遍历的方法，但是这个题要求我们时间复杂度是`O(n)`，所以就另寻他路。

我们可以维护一个长度为 2 的子序列，我们每次都更新这个序列的最大值和最小值

- 如果存在一个数字，比原先序列最小值最大值都大，证明满足题意
- 如果存在一个数字，比最大值小，但比最小值大，那么我们就更新最大值
- 如果存在一个数字，比最小值还小，直接更新最小值

举例，比如序列`1,6,5,2,3`，令初始下标 i = 0 ；

- 初始我们令`MIN =0xFFFFFF` ,`MAX=OxFFFFFF`
- i =  0 , `MIN  = 1`
- i =  1 , `MAX = 6`
- i =  2 , `MAX = 5`
- i =  3 , `MAX = 2`
- i =  4 ,  此时 `3 > MAX > MIN`，满足题意

------

#### 代码：

```cpp
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int small = INT_MAX, big = INT_MAX;
        for(auto val: nums)
        {
            if(val <= small) small = val;
            else if(val <= big) big = val;
            else return true;
        }
        return false;
    }
};
```

