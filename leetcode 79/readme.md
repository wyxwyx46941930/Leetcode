### leetcode 79.Word Search 

#### 题目:

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

**Example:**

```
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
```

----

#### 解法:

这个题跟前几天做的`Knight`那个题比较像，不过这个题是对二维数组的搜索，完成字符串的匹配；

总体思路就是DFS，从左上角逐行开始往右下角搜索，在搜索过程中，对每一个落脚点进行四方位的搜索，这里需要注意一点我们需要避免往回走，所以就需要设置一个新的布尔类型的二维数组，用来记录哪里已经被走过，所以这次遍历时候就不能再退回去；

同时在搜索的过程中，我们如果可以判断，待匹配字符串的长度和已经搜索到匹配的字符串的长度一致，就证明我们已经搜索成功，即可返回结果。

----

#### 代码：

````cpp
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        if (word.empty()) return true;
        if (board.empty() || board[0].empty()) return false;
        vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (search(board, word, 0, i, j, visited)) return true;
            }
        }
        return false;
    }
    bool search(vector<vector<char> > &board, string word, int idx, int i, int j, vector<vector<bool> > &visited) {
        if (idx == word.size()) return true;
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) return false;
        //标识不往回走
        visited[i][j] = true;
        bool res = search(board, word, idx + 1, i - 1, j, visited) 
                 || search(board, word, idx + 1, i + 1, j, visited)
                 || search(board, word, idx + 1, i, j - 1, visited)
                 || search(board, word, idx + 1, i, j + 1, visited);
        //去除标识
        visited[i][j] = false;
        return res;
    }
};

````