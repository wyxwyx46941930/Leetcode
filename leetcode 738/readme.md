### leetcode 738.Monotone Increasing Digits 

#### 题目：

Given a non-negative integer `N`, find the largest number that is less than or equal to `N` with monotone increasing digits.

(Recall that an integer has *monotone increasing digits* if and only if each pair of adjacent digits `x` and `y` satisfy `x <= y`.)

**Example 1:**

```
Input: N = 10
Output: 9
```

**Example 2:**

```
Input: N = 1234
Output: 1234
```

**Example 3:**

```
Input: N = 332
Output: 299
```

**Note:** `N` is an integer in the range `[0, 10^9]`.

----

#### 解答：

这个题也属于比较简单的题型，是要我们求出`小于等于正整数 N 的最大整数且满足每相邻两个数字之间前者小于等于后者`，具体思路如下：

我们给定一个正整数 N ，从后往前遍历这个数字（可以先把这个数字转换成字符串），

- 如果后一位数字均大于等于前一位数字，就证明复合题意；
- 如果出现某一组数对不满足题意，就把不满题意的这个数字的坐标记录下来（记为`i`），并把这个数字前一位的数字减一，随后继续遍历，每次遇到不满足情况的数字就把`i`更新为当前坐标的位置

上面的步骤结束后，我们可以再从`i`记录的位置开始往后遍历，并且每次都把`i`位置上的数字替换为`9`，这样就可以构造出满足题意的序列。

这里说明一下为什么上面有一步要减去`1`，这是因为我们要找的是不大于正整数 `N` 的最小正整数，且在找到不满足题意的数字对时候会从这一位开始往后置为`9`，为了同时满足这两个条件，我们就只能让不满足题意的数字位的前一位退位（也即 `- 1`;

----

#### 代码：

 ```cpp
C++ Solution 1 :
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string str = to_string(N);
        int n = str.size(), j = n;
        for (int i = n - 1; i > 0; --i) {
            if (str[i] >= str[i - 1]) continue;
            --str[i - 1];
            j = i;
        }        
        for (int i = j; i < n; ++i) {
            str[i] = '9';
        }
        return stoi(str);
    }
};
 ```

