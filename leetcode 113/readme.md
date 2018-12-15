### leetcode 113. Path Sum II  

#### 题目：

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

**Note:** A leaf is a node with no children.

**Example:**

Given the below binary tree and `sum = 22`,

```bash
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
```

Return:

``` bash
[
   [5,4,11,2],
   [5,8,4,5]
]
```

----

#### 解法：

这个题从实质上看也是一道二叉树遍历的题，多了一个附加条件就是我们在遍历的时候，需要找出与给定的`sum`相同的路径结点值的和的集合。

我的解题思路是：从二叉树根开始遍历，并做下路径记录，存在`临时vector` **out** 中，随后在遍历过程中，如果到达最下层叶子结点，且 **sum** 值与求和的值相同，那么就把这个`临时vector ` **out** 存放到待求集合中。

至于`pop`出 **out** 的最后一个元素，是因为我们每次从递归进入上一层时候，我们都需要只记录从根节点到此层之前的数据，所以就需要`pop`出最后一个元素。

----

#### 代码：

```cpp
class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> res;
        vector<int> out;
        helper(root, sum, out, res);
        return res;
    }
    void helper(TreeNode* node, int sum, vector<int>& out, vector<vector<int>>& res) {
        if (!node) return;
        out.push_back(node->val);
        if (sum == node->val && !node->left && !node->right) {
            res.push_back(out);
        }
        helper(node->left, sum - node->val, out, res);
        helper(node->right, sum - node->val, out, res);
        out.pop_back();
    }
};
```

