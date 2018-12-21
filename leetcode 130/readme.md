### leetcode 130.Surrounded Regions 

#### 题目：

Given a 2D board containing `'X'` and `'O'` (**the letter O**), capture all regions surrounded by `'X'`.

A region is captured by flipping all `'O'`s into `'X'`s in that surrounded region.

**Example:**

```
X X X X
X O O X
X X O X
X O X X
```

After running your function, the board should be:

```
X X X X
X X X X
X X X X
X O X X
```

**Explanation:**

Surrounded regions shouldn’t be on the border, which means that any `'O'` on the border of the board are not flipped to `'X'`. Any `'O'` that is not on the border and it is not connected to an `'O'` on the border will be flipped to `'X'`. Two cells are connected if they are adjacent cells connected horizontally or vertically.

-----

#### 解法：

拿到这个题首先要理清题意，这个题是让我们将一个矩形图中除边界上的`'O'`以及与边界上的`'O'`直接相连的`'O'`外的所有`'O'`都转化为`'X'`

对于矩形图的问题，我们一般考虑使用 `BFS` 算法（也即宽度优先搜索），从图的左上角往右下角进行搜索，但是这个题我们不需要做太多的无用功，因为`example 1 `中已经明显给出了我们要找的满足条件的情况，所以我们只需要`从边界出发，搜边界上的点即可`。

同时我们需要确保：

- 在搜索过程中不走重复的道路，也即我们需要将已经搜索过的`'O'`替换为别的字符(这里我使用的`'$'`)，这样可以减少我们搜索的时间复杂度;
- 当我们搜索所有完成时候，将没有被替换的`'O'`替换为`'X'`(这是因为没有被搜索过的`'O'`都是边界上的`'O'`所不可达的)，将`'$'`置换为`'O'`;
- 某一个`'O'`所在位置的四个方向都要进行搜索，需要保证我们的搜索不能越界

-----

#### 代码：

```cpp
class Solution {
public:
    void solve(vector<vector<char> >& board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if ((i == 0 || i == board.size() - 1 || j == 0 || j == board[i].size() - 1) && board[i][j] == 'O')
                    solveDFS(board, i, j);
            }
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '$') board[i][j] = 'O';
            }
        }
    }
    void solveDFS(vector<vector<char> > &board, int i, int j) {
        if (board[i][j] == 'O') {
            board[i][j] = '$';
            if (i > 0 && board[i - 1][j] == 'O') 
                solveDFS(board, i - 1, j);
            if (j < board[i].size() - 1 && board[i][j + 1] == 'O') 
                solveDFS(board, i, j + 1);
            if (i < board.size() - 1 && board[i + 1][j] == 'O') 
                solveDFS(board, i + 1, j);
            if (j > 1 && board[i][j - 1] == 'O') 
                solveDFS(board, i, j - 1);
        }
    }
};
```

