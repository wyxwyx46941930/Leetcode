### LeetCode 441. Arranging Coins 

#### 题目：

You have a total of *n* coins that you want to form in a staircase shape, where every *k*-th row must have exactly *k* coins.

Given *n*, find the total number of **full** staircase rows that can be formed.

*n* is a non-negative integer and fits within the range of a 32-bit signed integer.

**Example 1:**

```
n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.
```

**Example 2:**

```
n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.
```

----

#### 解法：

这是一道数学类的问题，意思是让求出给定的数字 N 可以构造出的满足阶梯型架构的最后一个整数行。

这个题可以用循环做，但是也可以直接使用求通向公式的方法做，解法如图：

![test](C:\Users\WYX\Desktop\leetcode 441\test.png)

大致也就是配完全平方式，求解 K

有了通项公式，我们写出代码就不算难了，还要注意一点这里要把 n 转成 长整型`long`否则会有溢出的问题

----

#### 代码：

```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        return (int) (sqrt(2*(long)n+0.25) - 0.5);
    }
};
```

