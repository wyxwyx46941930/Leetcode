### leetcode 837. New 21 Game

#### 题目：

Alice plays the following game, loosely based on the card game "21".

Alice starts with `0` points, and draws numbers while she has less than `K` points.  During each draw, she gains an integer number of points randomly from the range `[1, W]`, where `W` is an integer.  Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets `K` or more points.  What is the probability that she has `N` or less points?

**Example 1:**

```bash
Input: N = 10, K = 1, W = 10
Output: 1.00000
Explanation:  Alice gets a single card, then stops.
```

**Example 2:**

```bash
Input: N = 6, K = 1, W = 10
Output: 0.60000
Explanation:  Alice gets a single card, then stops.
In 6 out of W = 10 possibilities, she is at or below N = 6 points.
```

**Example 3:**

```bash
Input: N = 21, K = 17, W = 10
Output: 0.73278
```

**Note:**

1. `0 <= K <= N <= 10000`
2. `1 <= W <= 10000`
3. Answers will be accepted as correct if they are within `10^-5` of the correct answer.
4. The judging time limit has been reduced for this question.

----

#### 解法：

这个题大致的意思是在点数不超过`K`的情况下，每次从`[1,W]`中任选一个数字,求出当和点数大于等于`K`时，小于等于`N`的概率。

这个题我们可以看作是给定N个台阶，每次上升`[1,W]`个台阶的问题，可以分三种情况，设当前已走步数为 `test`，当前步数`test`下的概率 dp[test]

- 当`i <= K`时，`dp[i] = （前W个dp的和）/ W`；(爬楼梯得到总楼梯数为i的概率）
- 当`K < i < K + W`时，那么在这次的前一次的点数范围是`[i - W, K - 1]`。我们的dp数组表示的是得到点i的概率，所以`dp[i]=(dp[K-1]+dp[K-2]+…+dp[i-W])/W`.（可以从前一次的基础的上选[1,W]个数字中的一个）
- 当`i>=K+W`时，这种情况下无论如何不都应该存在的，所以dp[i]=0.

-----

#### 代码：

```python
class Solution(object):
    def new21Game(self, N, K, W):
        """
        :type N: int
        :type K: int
        :type W: int
        :rtype: float
        """
        if K == 0: return 1
        dp = [1.0] + [0] * N
        tSum = 1.0
        for i in range(1, N + 1):
            dp[i] = tSum / W
            if i < K:
                tSum += dp[i]
            #减去不符合题意的情况
            if 0 <= i - W < K:
                tSum -= dp[i - W]
        return sum(dp[K:])
```

