## Leetcode 97. Interleaving String

Given *s1*, *s2*, *s3*, find whether *s3* is formed by the interleaving of *s1* and *s2*.

**Example 1:**

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
```

**Example 2:**

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
```

### 思路：

一开始选择使用递归的方法，一个字符串一个字符串的进行字符搜索，但发现会跳不出最后的条件并且会把栈给堆爆，所以就选择了借鉴一下dalao们的思路。

大致想法如下：

整体思路是：**动态规划**

那么要怎么规划呢？

我们可以把给定的字符串`s1`与`s2`制作成一个布尔类型的二维地图（1表示可以通行，0表示不可通行），且初始化地图除了左上角的`[0,0]对应的格子为1外（后面会解释）`，其余空格全为0，

例：

`s1 = aa`与`s2 =ab  ` 

那么地图可以构建为：

|      | 0    | a    | a    |
| ---- | ---- | ---- | ---- |
| 0    | 1    | 0    | 0    |
| a    | 0    | 0    | 0    |
| b    | 0    | 0    | 0    |

- 地图第一行对应`s1`
- 地图第二行对应`s2`

我们可以这么理解，如果存在这么一个由`s1`与`s2`构成的字符串`s3`，那么就存在一条从左上角走到右下角的道路，这里我们举个例子：

假如：

`s3 = aaba`

那么我们可以这么走

- [0,0] `->（往右走）` 
- [0,a] (并将该格子置1,这一步匹配a) `->（往下走）`
- [a,a] (并将该格子置1，这一步匹配a) `->（往下走） `
- [b,a] (并将该格子置1，这一步匹配b) `->（往右走）` 
- [b,a] (并将该格子置1，这一步匹配a)

至此也就完成了匹配过程：`aaba`

当所有的搜索完成时候，如果我们可以得到右下角的格子的**布尔值为1**，那么证明**匹配完成**，如果**布尔值为0**，则证明**匹配不成立**。

还有一个问题就是：**我们如何判断将某个格子置0还是置1呢？**

方法如下：

这里假设`i = s1.size , j = s2.size + 1`, 地图为`DP[i +1][j +1]`

- 由于两个空串可以直接完成匹配，所以`DP[0]\[0]  = 1` (这也就解释为什么最最上角的格子置为1了)

- 对地图`DP`进行第一步赋值：

  - 当 j 等于0的时候，dp[i, 0]的值取决于dp[i-1, 0]是否为真以及s1[i-1]是否等于s3[i-1]，即`dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1]`

  - 同理，当 i 等于0的时候：

    `dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1]`

- 对地图进行除第一行或第一列外的格子进行赋值，递推公式为：`dp[i, j] = (s1[i-1] == s3[i+j-1] && dp[i-1, j]) || (s2[j-1] == s3[i+j-1] && dp[i, j-1])。 `

  - 如果s1[i-1]与s3[i+j-1]相同，说明当前位置s1可以进行匹配，因此如果dp[i-1, j]也为真，dp[i, j]就为真。
  - 如果s2[j-1]与s3[i+j-1]相同，说明当前位置s2可以进行匹配，因此如果dp[i, j-1]也为真，dp[i, j]就为真。

在完成以上所有操作后，如果DP[i]\[j] == 1,那么可判断s3 为 s2 与 s1交叉构成。

### 代码：

```c++
class Solution
{
    public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();

        if(l3 != l1 + l2)
            return false;

        vector<vector<bool> > dp(l1 + 1, vector<bool>(l2 + 1, false));

        dp[0][0] = true;
        for(int i = 1; i <= l1; ++ i)
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
        for(int j = 1; j <= l2; ++ j)
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];

        for(int i = 1; i <= l1; ++ i)
            for(int j = 1; j <= l2; ++ j)
                dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) 
                || (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
        return dp[l1][l2];
    }
};
```
