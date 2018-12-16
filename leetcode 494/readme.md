###  leetcode 494. Target Sum

#### 题目：

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols `+` and `-`. For each integer, you should choose one from `+` and `-` as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

**Example 1:**

```
Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
```



**Note:**

1. The length of the given array is positive and will not exceed 20.
2. The sum of elements in the given array will not exceed 1000.
3. Your output answer is guaranteed to be fitted in a 32-bit integer.

-----

#### 解法：

这个题是要我们在给定序列中找到使用不同符号组成的序列求和的值等于给定值的个数。

思路很直接，从`vector`中第一个值开始往后递归，每层都有两种递归情况，分别是加上这个数字或者是减去这个数字，照着这个思路我们就可以构建出基本的递归框架：

```cpp
 find(nums,S,position+1(往后遍历),total-nums[position](选择进行加海世建),number(已经满足题意的个数));
```

但是我们还需要注意的一个问题就是：`如何判断我们已经找到了这个解集序列`，我们有可能会在求和的过程中就发现已经找到满足题目要求的情况，比如：1+1+1 = 3 而不是 1+1+1+1-1 = 3 ，1+1+1=3这种情况并不满足情况，所以我们就需要设置条件排除干扰：

```cpp
// 当且仅当求和的值相等且已经遍历到序列最后一位时才让 总个数+1
if(total == S && position == nums.size())
{
    number ++ ;
}
```

----

#### 代码：

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int total = 0 ;//计算当前的值
        int position = 0 ;
        int number = 0 ;
        find(nums,S,position,total,number);
        return number ;
    }
    void find(vector<int>& nums, int S , int position , int total,int &number )
    {
        if(total == S && position == nums.size())
        {
            number ++ ;
        }
        if(position == nums.size())
        {
            return ;
        }
        find(nums,S,position+1,total-nums[position],number);
        find(nums,S,position+1,total+nums[position],number);
    }
};
```

