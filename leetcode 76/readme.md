### leetcode 76.Minimum Window Substring 

#### 题目：

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

**Example:**

```
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
```

**Note:**

- If there is no such window in S that covers all characters in T, return the empty string `""`.
- If there is such window, you are guaranteed that there will always be only one unique minimum window in S.

----

#### 解法：

这个题应该是每日一题开始做到现在难度最大的一个。

这个题跟一般的字符串匹配问题不太一样，是要让你在母字符串 S 中找出能够包含所给字符序列 S（其字符顺序可以乱序）的最小子序列。

那么首先我们要解决两个问题：

- 找出符合要求的字符序列
- 简化我们找到的字符序列，让其长度最小

对于第一个问题，我们采用遍历的方法就可以，比如序列`S = “ACBDHJEABDJ”`、`T = “ABJ”` ，我们可以找出两个复合要求的序列 `output1 = ACBDHJ`、`output2 = ABDJ`，从第二个要求中我们应当选择output2 ；

对于第二个问题，我使用的方法就是在第一个问题的基础上进行简化，比如删去末尾或者开头无用的字符，但是**我们需要注意我们不能删去夹杂在已求出的序列之间的字符**，同时也可以删去重复出现的待匹配字符。

在具体实现上，我们可以考虑使用哈希的方法，开辟数组存放待求字符串中每个字母出现的个数进而保证我们在找到已经给定的数目的某个字符时候，在后面优化时候可以压缩序列，同时也可以保证我们判断已经结束了优化与搜索。

----

#### 代码：

```cpp
class Solution {
public:
    string minWindow(string S, string T) {
        int hasFound[256] = {0};
        int needToFind[256] = {0};
        int windowBegin = 0;
        int windowEnd = 0;
        int minwindowBegin = 0;
        int minWindowEnd = 0;
        //NOTE1: int minLength = S.length(); //minWindow("a", "a"): expected return "a", actual wrong answer "";
        int minLength = INT_MAX;
        string minStr = "";
        for (int i =0; i < T.length(); ++i){
            needToFind[T[i]]++;
        }
        
        int begin = 0, end = 0, count = 0;
        //string str1 = "ADOBECODEBANC";
        //string str2 = "ABC";
        for (begin = 0, end = 0; end < S.length();++end) {
            if (needToFind[S[end]]<0) continue;
                hasFound[S[end]]++;
            if (hasFound[S[end]] <= needToFind[S[end]])
                count++;
            if (count >= T.length()) {
                while (needToFind[S[begin]] == 0 || hasFound[S[begin]] > needToFind[S[begin]]) { //NOTE2: two level logica
                    if (hasFound[S[begin]] > needToFind[S[begin]]) {
                        hasFound[S[begin]]--;
                    }
                    begin++;
                }
                windowBegin = begin;
                windowEnd = end;
                if (windowEnd - windowBegin + 1 < minLength) {
                    minLength = windowEnd - windowBegin + 1;
                    windowEnd = end;
                    windowBegin = begin;
                    minStr = S.substr(windowBegin, windowEnd - windowBegin + 1);
                }
            }
        }
        return minStr;
    }
};

```