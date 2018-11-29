## Leetcode 688.Knight Probability in Chessboard 

### 题目：

On an `N`x`N` chessboard, a knight starts at the `r`-th row and `c`-th column and attempts to make exactly `K` moves. The rows and columns are 0 indexed, so the top-left square is `(0, 0)`, and the bottom-right square is `(N-1, N-1)`.

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

 

![img](https://assets.leetcode.com/uploads/2018/10/12/knight.png)  

 

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly `K` moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

 

**Example:**

```
Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
```

 

**Note:**

- `N` will be between 1 and 25.
- `K` will be between 0 and 100.
- The knight always initially starts on the board.

---

### 解法：

这个题是要我们算出 `knight ` 在随机走K步之后留在棋盘上的概率 `P`，
$$
P = \frac{可以留在棋盘上的走法}{总的走法}
$$
`knight` 每次都会向八个方向走，所以我们可以推出：走K步 -> 可以有 `8^K` 种走法；

那么接下来就需要考虑`可以留在棋盘上的走法`怎么计算了

在求这种情况时候，我们可以看作是求解 `迷宫问题` ，大致思路就是，每次我都让`knight`都可以向八个方向移动，但是如果有跳出棋盘的走法，就舍弃这种走法，最后只保留下`knight`不跳出棋盘的走法，随后在前一步的基础上继续进行向八个方向移动的操作，迭代 `K `步后，最后把这些情况汇总起来，就是满足要求的解。

这个题思路比较直观，但是实现的代码需要嵌套循环多一点，所以上面的这种做法效率会比较低一点。

---

### 代码： 

```cpp
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        if (K == 0) return 1;
        vector<vector<double>> dp(N, vector<double>(N, 1));
        vector<vector<int>> dirs{{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
        for (int m = 0; m < K; ++m) {
            vector<vector<double>> t(N, vector<double>(N, 0));
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    for (auto dir : dirs) {
                        int x = i + dir[0], y = j + dir[1];
                        if (x < 0 || x >= N || y < 0 || y >= N) continue;
                        t[i][j] += dp[x][y];
                    }
                }
            }
            dp = t;
        }
        return dp[r][c] / pow(8, K);
    }
};

```