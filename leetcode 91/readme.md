### leetcode 91.Decode Ways

#### 题目：

A message containing letters from `A-Z` is being encoded to numbers using the following mapping:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

Given a **non-empty** string containing only digits, determine the total number of ways to decode it.

**Example 1:**

```
Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
```

**Example 2:**

```
Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
```

----

#### 解法：

这个题是一道动态规划的题目，**是要我们找出给定的数字序列可以转换成多少种不同的字符串**；

具体思路如下：

给定长度为 N 的数字串`arr`，我们可以先找出前 K 个数字可以凑成的字符串的情况，随后找出 K + 1 、K + 2 、K + 3直到第 N 个，这里需要注意地方：有可能存在两个数字映射一个字母的情况，这时候我们就需要判断两个数字的情况是否满足`10<= arr[k-2][k-1] <=26`，举个例子，令 `total[N] = ｛0｝`（记录解集情况）：

arr = "123"

arr 可以推出 1 2 3 、12 3 、1 23 、 共3种情况

推导过程为：

total [0] = 1 ;

- arr[0] = 1 ， total[1] = 1 结束
- arr[0] = 1、arr[1] = 2 或 arr[0]arr[1] = 12 ，total[2]  = total[1] + total[0] = 2 结束
- arr[0] = 1、arr[1] = 2、arr[2] = 3 或 arr[0]arr[1] = 12、arr[2] = 3或arr[0] = 1、arr[1]arr[2] = 23， total[3] = total[2] + total[1] = 3 结束

最后可以发现其实我们是在前一次已经满足题意的序列上再加上一个字符，然后判断这个字符能否跟前一个字符凑成新的序列.

----

#### 代码：

````cpp
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || (s.size() > 1 && s[0] == '0')) return 0;
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < dp.size(); ++i) {
            dp[i] = (s[i - 1] == '0') ? 0 : dp[i - 1];
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] += dp[i - 2];
            }
        }
        return dp.back();
    }
};

````