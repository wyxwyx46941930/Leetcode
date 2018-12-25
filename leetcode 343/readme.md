### leetcode 343. Integer Break

#### 题目：

Given a positive integer *n*, break it into the sum of **at least** two positive integers and maximize the product of those integers. Return the maximum product you can get.

**Example 1:**

```bash
Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
```

**Example 2:**

```bash
Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
```

**Note**: You may assume that *n* is not less than 2 and not larger than 58.

----

#### 解法：

这个题刚开始我选择使用了深搜，虽然运算结果正确，但是发现会有超时的问题，所以就只能另寻他路。

这个题也是一道数学类问题，所以是可以发现规律的，也即`只要我们把数据拆出足够多的3`就可以保证积最大。

证明借鉴一下网上某位dalao的写法：

![2](https://img-blog.csdnimg.cn/20181225105231426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eHd5eDQ2OTQxMDkzMA==,size_16,color_FFFFFF,t_70)

所以有了这个思路，我们就很容易解决这个题了。

-----

#### 代码：

```cpp
int integerBreak(int n)
{
    if(n == 2) return 1;
    if(n == 3) return 2;
    int ret = 1;
    while( n>4 )
    {
        ret *= 3;
        n -= 3;
    }
    return ret * n;
}
```

