### leetcode 466. Count The Repetitions 

#### 题目：

Define `S = [s,n]` as the string S which consists of n connected strings s. For example, `["abc", 3]` ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1. For example, “abc” can be obtained from “abdbec” based on our definition, but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. Now consider the strings S1 and S2, where `S1=[s1,n1]` and `S2=[s2,n2]`. Find the maximum integer M such that `[S2,M]` can be obtained from `S1`.

**Example:**

```bash
Input:
s1="acb", n1=4
s2="ab", n2=2

Return:
2
```

-----

#### 解法：

暴力搜索，在s1中持续寻找s2，直到搜索完毕，这种方法可以解决问题，但是时间复杂度会特别高：

```cpp
class Solution 
{
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) 
    {
        int i = 0, count1 = 0, j = 0, count2 = 0;
        while (count1 < n1)
        {
            if (s1[i] == s2[j])
            {
                j++;
                if (j == s2.length())
                {
                    count2++;
                    j = 0;
                }
            }

            i++;
            if (i == s1.length())
            {
                count1++;
                i = 0;
            }
        }
        return count2 / n2;
    }
};
```

反馈：

![1](https://img-blog.csdnimg.cn/20181222123130238.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eHd5eDQ2OTQxMDkzMA==,size_16,color_FFFFFF,t_70)

----

所以考虑换一种方法：

该解法来自于`leetcode`解题大神：

----

**Fact:**
If `s2` repeats in `S1` `R` times, then `S2` must repeats in `S1` `R / n2` times.
**Conclusion:**
We can simply count the repetition of `s2` and then divide the count by `n2`.

**How to denote repetition:**
We need to scan `s1` `n1` times. Denote each scanning of `s1` as a `s1` segment.
After each scanning of `i`-th `s1` segment, we will have

1. The accumulative count of `s2` repeated in this `s1` segment.
2. A `nextIndex` that `s2[nextIndex]` is the first letter you'll be looking for in the next `s1` segment.

> 
>
> Suppose `s1="abc"`, `s2="bac"`, `nextIndex` will be `1`; `s1="abca"`, `s2="bac"`, `nextIndex` will be `2`
>
> 

It is the `nextIndex` that is the denotation of the repetitive pattern.

**Example:**

```bash
Input:
s1="abacb", n1=6
s2="bcaa", n2=1

Return:
3
```

```bash
                    0  1   2 3 0      1    2 3 0      1    2 3 0  
S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb 
repeatCount ----->    0  |   1   |   1   |   2   |   2   |   3
Increment of 
repeatCount     ->    0  |   1   |   0   |   1   |   0   |   1
nextIndex ------->    2  |   1   |   2   |   1   |   2   |   1
```

The `nextIndex` has `s2.size()` possible values, ranging from `0` to `s2.size() - 1`. Due to PigeonHole principle, you must find two same `nextIndex` after scanning `s2.size() + 1` `s1`segments.

Once you meet a `nextIndex` you've met before, you'll know that the following `nextIndex`s and increments of `repeatCount` will repeat a pattern.

So let's separate the `s1` segments into 3 parts:

1. the prefix part before repetitive pattern
2. the repetitive part
3. the suffix part after repetitive pattern (incomplete repetitive pattern remnant)

All you have to do is add up the repeat counts of the 3 parts.

-----

这个题后序有时间我会继续进行研究，确实是一道值得思考的难题。

#### 代码：

```cpp
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        vector<int> repeatCnt(n1 + 1, 0);
        vector<int> nextIdx(n1 + 1, 0);
        int j = 0, cnt = 0;
        for (int k = 1; k <= n1; ++k) {
            for (int i = 0; i < s1.size(); ++i) {
                if (s1[i] == s2[j]) {
                    ++j;
                    if (j == s2.size()) {  
                        j = 0;
                        ++cnt;
                    }
                }
            }
            repeatCnt[k] = cnt;
            nextIdx[k] = j;
            for (int start = 0; start < k; ++start) {
                if (nextIdx[start] == j) {
                    int interval = k - start;
                    int repeat = (n1 - start) / interval;
                    int patternCnt = (repeatCnt[k] - repeatCnt[start]) * repeat;
                    int remainCnt = repeatCnt[start + (n1 - start) % interval];
                    return (patternCnt + remainCnt) / n2;
                }
            }
        }
        return repeatCnt[n1] / n2;
    }
};

```

