## Leetcode 600. Non-negative Integers without Consecutive Ones 

### 题目：

Given a positive integer n, find the number of **non-negative** integers less than or equal to n, whose binary representations do NOT contain **consecutive ones**.

**Example 1:**

```
Input: 5
Output: 5
Explanation: 
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 
```

**Note:** 1 <= n <= 10^9

### 解法：

先理解一下题意：大概意思是说找一下小于等于 N 的数里面有多少个数表示成二进制形式之后，不会有连续的两个 1 出现在其二进制序列里面。

先说一下我最开始的想法：

从 0 到 N 遍历 N 个数字，将小于等于 N 的每一个数字用`bitset`表示出来，然后用一个循环从`bitset`的0位置开始将相邻两位相加，观察结果是否会有 2 出现，如果出现就证明不满足题意；如果遍历完没出现，就让统计值 +1 ；

这种方法是可以求出最终结果的，但是会超时！所以直观的方法行不通！

如图：

![TIM截图20181125155829](https://github.com/wyxwyx46941930/Leetcode/blob/master/leetcode%20600/TIM%E6%88%AA%E5%9B%BE20181125155829.png)

------

#### 另寻他路

在网上查看大佬们的解题思路，有一种比较巧妙的方法介绍一下：

![TIM截图20181125161356](https://github.com/wyxwyx46941930/Leetcode/blob/master/leetcode%20600/TIM%E6%88%AA%E5%9B%BE20181125161356.png)

最后我们所要求的结果是：

`total = a[i-1] + b[i-1]`（ i 在这里指数字转二进制后的长度） 

**但是我们使用的这种方法会有多算的情况**，比如当我们输入 8 或 9 时候，其二进制长度都是 4 ，所以我们在计算小于等于 8 的满足题意的数字的时候，可能会把 9 10 都算进去，所以我们要把多余的情况减掉。

那具体应该怎么减去这些数字？

假如我们要计算 num = 8 的情况，那么当长度等于 4 时候，则 0、1、2、4、5、8共 6 个数字满足题意，但是`total = a[3]+b[3] = 8` ，多余的情况为 9 = 1001(2) 、10 = 1010(2) ；

我们算法最初开始在生成二进制数字时候，是逆序生成的，也即 8 = 0001 ，所以我们可以从待测序列的倒数第二位往前算

- 如果位置 `j` 和位置 `j+1` 上的数字都是 0 ，那么就在 `total `中减去 `b[j]`；
- 如果位置 `j` 和位置 `j+1` 上的数字都是 1 ，那么直接退出

这里之所以`减去 b[j] `，因为在位置`j`上可能会出现满足题设要求的 1 ，而在 1 位置上满足情况的个数为 b[j]

### 代码：

```cpp
class Solution 
{
public:
    int findIntegers(int num)
    {
        int n = num;
        string t = "";
        while (n > 0)
        {
            t += (n & 1) == 1 ? "1" : "0";
            n = n >> 1;
        }

        vector<int> zero(t.length() , 0), one(t.length(), 0);
        zero[0] = one[0] = 1;
        for (int i = 1; i < t.length(); i++)
        {
            zero[i] = zero[i - 1] + one[i -1];
            one[i] = zero[i - 1];
        }

        int res = zero[t.length() - 1] + one[t.length() - 1];
        for (int i = t.length() - 2; i >= 0; i--)
        {
            if (t[i] == '1' && t[i + 1] == '1')
                break;
            if (t[i] == '0' && t[i + 1] == '0')
                res -= one[i];
        }
        return res;
    }
};

```